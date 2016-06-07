-- Class LuaState:
    -- methods:
        -- LuaState:getPitchToTracked      ( int TARGET_TRACK )
        -- LuaState:getPitchToTracked      ( int TARGET_TRACK )
        -- LuaState:getHeadingToTracked    ( int TARGET_TRACK )
        -- LuaState:getDistanceToTracked   ( int TARGET_TRACK )
    -- properties:
        -- real values:
            -- LuaState:roll
            -- LuaState:pitch
            -- LuaState:heading
            -- LuaState:rollrate
            -- LuaState:pitchrate
            -- LuaState:yawrate
            -- LuaState:altitude
            -- LuaState:throttle
            -- LuaState:speed
            -- LuaState:pitchtrim
            -- LuaState:numtracks
            -- LuaState:targettrack
            -- LuaState:numengines
        -- boolean values:
            -- LuaState:isAlive
            -- LuaState:isIncomingMissile
            -- LuaState:isTracking
            -- LuaState:isMissileFired

-- Class LuaAction
    -- properties:
        -- real values:
            -- LuaAction:roll
            -- LuaAction:pitch
            -- LuaAction:heading
            -- LuaAction:throttle
            -- LuaAction:pitchtrim
        -- boolean values:
            -- LuaAction:firemissile

-- Function LuaBEHAVIOR
    -- LuaAction = LuaBEHAVIOR( LuaState )

local Behaviors = {}
local LuaXML = require "LuaXml"
-- Constants
local R2D       = 180/math.pi
local D2R       = 1/R2D
local FT2M      = 0.3048
local M2FT      = 1/FT2M
local KT2MS     = 0.514444444
local MS2KT     = 1/KT2MS
local MAX_TRACKS = 50

-- Function to compare two actions
function Behaviors:CompareActions( act1, act2 )
    if      (        act1.roll ~= act2.roll        ) then
        return false
    elseif  (       act1.pitch ~= act2.pitch       ) then
        return false
    elseif  (     act1.heading ~= act2.heading     ) then
        return false
    elseif  (    act1.throttle ~= act2.throttle    ) then
        return false
    elseif  (   act1.pitchtrim ~= act2.pitchtrim   ) then
        return false
    elseif  ( act1.firemissile ~= act2.firemissile ) then
        return false
    end
    return true
end

function Behaviors:LuaPlaneFire( g_luaState, maxDistance )
    g_luaAction = PlaneStoresAction()
    
    targetTrack = g_luaState.targettrack
    
    if ( g_luaState.isAlive == true ) and ( g_luaState.isTracking == true ) then
        if ( targetTrack < MAX_TRACKS ) then
            if ( g_luaState.isMissileFired == false ) and ( g_luaState.getDistanceToTracked( targetTrack ) < maxDistance ) then
                
                g_luaAction.firemissile = true
            end
        end
    end
    
    return g_luaAction
end

function Behaviors:LuaPlaneFollowEnemy( g_luaState, safe_distance )
    g_luaAction = PlaneManeuverAction()
    
    targetTrack = g_luaState.targettrack
    
    if ( g_luaState.isAlive == true ) and ( g_luaState.isTracking == true ) and ( targetTrack < MAX_TRACKS ) then
       
		pitch = -1 * g_luaState.pitch + 0.02
        if ( pitch > 0 ) then
			pitch = pitch + g_luaState.getPitchToTracked( targetTrack ) * 1
        end
        
        roll = -1 * g_luaState.roll
        roll = roll + g_luaState.getHeadingToTracked( targetTrack ) * 1
        
        if ( g_luaState.roll < -math.pi/2 ) then
            roll = -1 * g_luaState.roll - math.pi/2
        elseif ( g_luaState.roll > math.pi/2 ) then
            roll = -1 * g_luaState.roll + math.pi/2
        end
        
        if ( roll > math.pi/2 ) then
            roll = math.pi/2
        end
        if ( roll < -math.pi/2 ) then
            roll = -math.pi/2
        end      
        
        if( g_luaState.getDistanceToTracked( targetTrack ) > safe_distance ) then
            throttle = 1
            if( math.abs( g_luaState.getHeadingToTracked( targetTrack ) ) < 0.1 ) then
                if( math.abs( g_luaState.roll ) < 0.1 ) then
                    pitch = pitch + g_luaState.getPitchToTracked( targetTrack ) * 1
					--pitch = pitch + ( -0.5 * ( math.pi / 180 ) )
                end
            end
        else
            throttle = 0
        end
        
        
        g_luaAction.throttle    = throttle
        g_luaAction.roll        = roll
        g_luaAction.pitch       = pitch
    end
    
    return g_luaAction
end

local HOLDING_ALTITUDE = -1
function Behaviors:LuaPlaneFlyStraight( g_luaState, holding_altitude )
    g_luaAction = PlaneManeuverAction()
    if ( HOLDING_ALTITUDE == -1 ) then
        if ( holding_altitude == -1 ) then
            HOLDING_ALTITUDE = g_luaState.altitude
        else
            HOLDING_ALTITUDE = holding_altitude
        end
    end
    
    if ( g_luaState.isAlive ) then
        pitch = -1 * g_luaState.pitch
        
        if ( g_luaState.altitude ~= HOLDING_ALTITUDE ) then
            pitch = pitch + ( ( HOLDING_ALTITUDE - g_luaState.altitude ) / ( 10000 ) )
        end
        
        if ( g_luaState.roll > math.pi/2 or g_luaState.roll < -math.pi/2 ) then
            pitch = pitch * -1
        end
        
        roll = -0.5 * g_luaState.roll
        if ( roll > math.pi/2 ) then
            roll = math.pi/2
        end
        if ( roll < -math.pi/2 ) then
            roll = -math.pi/2
        end
        
        throttle = 0.5
        if ( g_luaState.speed < 250 ) then
            throttle = 2.5
        end
        if ( g_luaState.speed < 210 ) then
            pitch = -1
        end
        
        
        g_luaAction.heading     = g_luaState.heading
        g_luaAction.roll        = roll
        g_luaAction.pitch       = pitch
        g_luaAction.throttle    = throttle
    end
    
    return g_luaAction
end

local TURN_FINISHED = false
local PREV_HEADING = -1
function Behaviors:LuaPlaneTurn( g_luaState, goal_heading )
    g_luaAction = PlaneManeuverAction()
    
    if ( g_luaState.isAlive ) then
        if( goal_heading ~= PREV_HEADING ) then
            PREV_HEADING = goal_heading
            TURN_FINISHED = false
        end
        
        DIFF_HEADING = ( goal_heading * D2R ) - g_luaState.heading
        
        if( math.abs( DIFF_HEADING ) > 0.01 and not TURN_FINISHED ) then
            
            roll        = -1 * g_luaState.roll
            pitch       = -1 * g_luaState.pitch
            throttle    = 0
            
            if ( math.abs( DIFF_HEADING ) > 1 and math.abs( DIFF_HEADING ) < math.pi ) then
                FACTOR = math.pi/3
            elseif ( DIFF_HEADING > math.pi ) then
                FACTOR = math.pi/3 * math.abs( math.pi - DIFF_HEADING )
            else
                FACTOR = math.pi/3 * math.abs( DIFF_HEADING )
            end
            
            if ( math.abs( DIFF_HEADING ) < math.pi ) then
                if ( DIFF_HEADING > 0 ) then
                    roll = roll + FACTOR
                else
                    roll = roll - FACTOR
                end
            else
                if ( DIFF_HEADING > 0 ) then
                    roll = roll - FACTOR
                else
                    roll = roll + FACTOR
                end
            end
            
            if ( roll > math.pi/2 ) then
                roll = math.pi/3
            end
            if ( roll < -math.pi/2 ) then
                roll = -math.pi/3
            end
            
            pitch       = pitch + 15 * D2R * math.abs( DIFF_HEADING )
            throttle    = 0.5 + math.abs( roll )
            
            
            g_luaAction.roll        = roll
            g_luaAction.pitch       = pitch
            g_luaAction.throttle    = throttle
        else -- Maneuver finished
            TURN_FINISHED = true
        end
    end
    
    return g_luaAction
end

local BREAK_HEADING = -1
local stop = false
function Behaviors:LuaPlaneBreak( g_luaState, direction )
    g_luaAction = PlaneManeuverAction()
    
    if ( g_luaState.isAlive ) then
    -- if ( g_luaState.isAlive ) then
        if ( BREAK_HEADING == -1 ) then
            if ( direction == "dir" ) then
                BREAK_HEADING = g_luaState.heading + math.pi
            elseif ( direction == "esq" ) then
                BREAK_HEADING = g_luaState.heading - math.pi
            end
           
            if ( BREAK_HEADING > 2*math.pi ) then
                BREAK_HEADING = BREAK_HEADING - math.pi
			end
            if ( BREAK_HEADING < 0 ) then
                BREAK_HEADING = BREAK_HEADING + math.pi
            end
			--print(BREAK_HEADING)
        end
        if( math.abs( g_luaState.heading - BREAK_HEADING ) > 0.001 and not stop ) then
            roll        = -1 * g_luaState.roll
            pitch       = -2 * g_luaState.pitch
            throttle    = 0
            if ( direction == "dir" ) then
                roll = roll + math.pi/1.8
            elseif ( direction == "esq" ) then
                roll = roll - math.pi/1.8
            end 
             
            if ( roll > math.pi/2 ) then
                roll = math.pi/1.8
            end
            if ( roll < -math.pi/2 ) then
                roll = -math.pi/1.8
            end
            
            pitch       = pitch +  720* ( math.pi / 60 )
			pitchrate = g_luaState.pitchrate
			pitchrate = pitchrate * 2
            throttle    = 1
			
            --print(pitch)
            
            g_luaAction.roll        = roll
            g_luaAction.pitch       = pitch
			g_luaAction.pitchrate   = pitchrate
            g_luaAction.throttle    = throttle
            g_luaAction.autopilot   = 0
        else
            stop = true
            BREAK_HEADING = -1
        end

    else
        BREAK_HEADING = -1
    end
    return g_luaAction
end

local STOP_ALTITUDE = -1
function Behaviors:LuaPlaneClimbDive( g_luaState, stop_altitude )
    g_luaAction = PlaneManeuverAction()
    if ( STOP_ALTITUDE == -1 ) then
        STOP_ALTITUDE = FT2M * stop_altitude
    end
    
    if ( g_luaState.isAlive ) then
        DIFF_ALTITUDE = STOP_ALTITUDE - g_luaState.altitude
        if ( math.abs( DIFF_ALTITUDE ) > 10 ) then
            pitch = -1 * g_luaState.pitch
            
            pitch = pitch + ( DIFF_ALTITUDE / 5000 )
            throttle = 0.6 + 6 * DIFF_ALTITUDE / 5000
            
            if ( g_luaState.roll > math.pi/2 or g_luaState.roll < -math.pi/2 ) then
                pitch = pitch * -1
            end
            
            roll = -0.5 * g_luaState.roll
            if ( roll > math.pi/2 ) then
                roll = math.pi/2
            end
            if ( roll < -math.pi/2 ) then
                roll = -math.pi/2
            end
            
            
            g_luaAction.roll        = roll
            g_luaAction.pitch       = pitch
            g_luaAction.throttle    = throttle
        end
    end
    
    return g_luaAction
end

local CLIMB_DIVE_FLAG = false
local CURVE_FLAG = false
local PREV_ALTI = -1
local PREV_HEAD = -1

function Behaviors:LuaPlaneClimbDiveCurve( g_luaState, stop_altitude, goal_heading )
    g_luaAction = PlaneManeuverAction()
    
    if ( g_luaState.isAlive ) then
        
        DIFF_HEADING  = ( goal_heading * D2R ) - g_luaState.heading
        DIFF_ALTITUDE = ( stop_altitude * FT2M ) - g_luaState.altitude
        pitch = -1 * g_luaState.pitch
        pitch = pitch + ( DIFF_ALTITUDE / 10000 )
        throttle = 0.6 + 6 * DIFF_ALTITUDE / 20000
        
        if ( g_luaState.roll > math.pi/2 or g_luaState.roll < -math.pi/2 ) then
            pitch = pitch * -1
       	end
        
			roll  = -1 * g_luaState.roll

        if ( math.abs( DIFF_HEADING ) > 1 and math.abs( DIFF_HEADING ) < math.pi ) then
            FACTOR = math.pi/4
        elseif ( DIFF_HEADING > math.pi ) then
            FACTOR = math.pi/4 * math.abs( math.pi - DIFF_HEADING )
        else
            FACTOR = math.pi/4 * math.abs( DIFF_HEADING )
        end
        
        if ( math.abs( DIFF_HEADING ) < math.pi ) then
            if ( DIFF_HEADING > 0 ) then
                roll = roll + FACTOR/2
            else
                roll = roll - FACTOR/2
            end
        else
            if ( DIFF_HEADING > 0 ) then
                roll = roll - FACTOR/2
            else
                roll = roll + FACTOR/2
            end
        end

        if ( roll > math.pi/2 ) then
            roll = math.pi/2
        end
        if ( roll < -math.pi/2 ) then
            roll = -math.pi/2
        end
        
        g_luaAction.pitch       = pitch
        g_luaAction.throttle    = throttle
        g_luaAction.roll        = roll
    end
    
    return g_luaAction
end

function Behaviors:LuaPlaneAccelerate( g_luaState, goal_speed )
    g_luaAction = PlaneManeuverAction()
    
    if ( g_luaState.isAlive == true ) then
        if ( g_luaState.speed < goal_speed * KT2MS ) then
            
            g_luaAction.pitch       = -1 * g_luaState.pitch
            g_luaAction.throttle    = 10
        else
            
            g_luaAction.throttle    = 0
        end
    end
    
    return g_luaAction
end

function Behaviors:LuaPlaneAutoPilot( g_luaState, mode )
    g_luaAction = PlaneSystemsAction()
    
    if ( g_luaState.isAlive == true ) then
        g_luaAction.autopilot   = mode
    end
    
    return g_luaAction
end

function Behaviors:LuaPlaneDataLinkMessage( g_luaState, msg )
    g_luaAction = PlaneSystemsAction()
    
    message = LuaXML.new("message")
    message:append("from")[1]       = g_luaState.name
    message:append("contents")[1]   = msg
    
    g_luaAction.datalinkmessage = LuaXML.str( message )
    
    return g_luaAction
end

function Behaviors:LuaPlaneDataLinkCommand( g_luaState, cmd )
    g_luaAction = PlaneSystemsAction()
    
    command = LuaXML.new("command")
    command[1] = cmd
    
    g_luaAction.datalinkmessage = LuaXML.str( command )
    
    return g_luaAction
end

-- <report>
    -- <name></name>
    -- <lat></lat>
    -- <lon></lon>
    -- <alt></alt>
-- </report>
function Behaviors:LuaPlaneDataLinkReport( g_luaState )
    g_luaAction = PlaneSystemsAction()
    report = LuaXML.new("report")
    report:append("name")[1]    = g_luaState.name
    report:append("lat")[1]     = g_luaState.latitude
    report:append("lon")[1]     = g_luaState.longitude
    report:append("alt")[1]     = g_luaState.altitude
    
    g_luaAction.datalinkmessage = LuaXML.str( report )
    
    -- return ManeuverAction, SystemsAction, StoresAction
    return nil, g_luaAction, nil
end

return Behaviors