


-- DEPRECATED




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

local MAX_TRACKS = 50

function LuaPlaneFire( g_luaState, maxDistance )
    g_luaAction = LuaAction()
    g_luaAction.firemissile = false
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

function LuaPlaneFollowEnemy( g_luaState, safe_distance )
    g_luaAction = LuaAction()
    targetTrack = g_luaState.targettrack
    
    if ( g_luaState.isAlive == true ) and ( g_luaState.isTracking == true ) and ( targetTrack < MAX_TRACKS ) then
        pitch = -1 * g_luaState.pitch + 0.02
        if ( pitch > 0 ) then
            pitch = pitch * 5
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
                    pitch = pitch + ( -0.5 * ( math.pi / 180 ) )
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
function LuaPlaneFlyStraight( g_luaState, holding_altitude )
    g_luaAction = LuaAction()
    
    if ( g_luaState.isAlive ) then
        HOLDING_ALTITUDE = g_luaState.altitude
        
        if ( holding_altitude ~= -1 ) then
            HOLDING_ALTITUDE = holding_altitude
        end
        
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
            throttle = 2.0
        end
        if ( g_luaState.speed < 210 ) then
            pitch = -1
        end
        g_luaAction.heading  = g_luaState.heading
        g_luaAction.roll     = roll
        g_luaAction.pitch    = pitch
        g_luaAction.throttle = throttle
    end
    
    return g_luaAction
end

local TURN_HEADING = -1
function LuaPlaneTurn( g_luaState, goal_heading )
    g_luaAction = LuaAction()
    
    if ( g_luaState.isAlive ) then
        if ( TURN_HEADING == -1 ) then
            TURN_HEADING = goal_heading
            print( "Turn heading " .. TURN_HEADING )
            print( "Initial altitude " .. g_luaState.altitude * 3.2808399 )
        end
        
        DIFF_HEADING = math.abs( g_luaState.heading - TURN_HEADING )
        if ( DIFF_HEADING > math.pi ) then
            DIFF_HEADING = 2*math.pi - DIFF_HEADING
        end
        
        if( DIFF_HEADING > 0.01 ) then
            roll        = -1 * g_luaState.roll
            pitch       = -1 * g_luaState.pitch
            throttle    = 0
            
            roll = roll + ( math.pi/5 ) * DIFF_HEADING
             
            if ( roll > math.pi/2 ) then
                roll = math.pi/2
            end
            if ( roll < -math.pi/2 ) then
                roll = -math.pi/2
            end
            
            pitch = pitch + ( 70 * ( math.pi/180 ) * DIFF_HEADING / ( 2*math.pi ) ) * 5 * g_luaState.roll/math.pi
            throttle = 0.7 + 10*roll/math.pi
            
            g_luaAction.roll        = roll
            g_luaAction.pitch       = pitch
            g_luaAction.throttle    = throttle
        end
    else
        BREAK_HEADING = -1
    end
    return g_luaAction
end

local BREAK_HEADING = -1
-- local direction = "dir"
function LuaPlaneBreak( g_luaState, direction )
    g_luaAction = LuaAction()
    
    if ( g_luaState.isAlive and g_luaState.isIncomingMissile ) then
        if ( BREAK_HEADING == -1 ) then
            if ( direction == "dir" ) then
                BREAK_HEADING = g_luaState.heading + math.pi/2
            elseif ( direction == "esq" ) then
                BREAK_HEADING = g_luaState.heading - math.pi/2
            end
            
            if ( BREAK_HEADING > 2*math.pi ) then
                BREAK_HEADING = BREAK_HEADING - 2*math.pi
            end
            if ( BREAK_HEADING < 0 ) then
                BREAK_HEADING = BREAK_HEADING + 2*math.pi
            end
            
            print( "Breaking to heading: " .. BREAK_HEADING * ( 180 / math.pi ) )
        end
        
        if( math.abs( g_luaState.heading - BREAK_HEADING ) > 0.1 ) then
            roll        = -1 * g_luaState.roll
            pitch       = -1 * g_luaState.pitch
            throttle    = 0
            
            if ( direction == "dir" ) then
                roll = roll + math.pi/2
            elseif ( direction == "esq" ) then
                roll = roll - math.pi/2
            end 
             
            if ( roll > math.pi/2 ) then
                roll = math.pi/2
            end
            if ( roll < -math.pi/2 ) then
                roll = -math.pi/2
            end
            
            pitch       = pitch + 90 * ( math.pi / 180 )
            throttle    = 2.0
            
            g_luaAction.roll        = roll
            g_luaAction.pitch       = pitch
            g_luaAction.throttle    = throttle
        else
            print( "break" )
        end
    else
        BREAK_HEADING = -1
    end
    return g_luaAction
end

local STOP_ALTITUDE = -1
function LuaPlaneDive( g_luaState, stop_altitude )
    g_luaAction = LuaAction()
    if ( STOP_ALTITUDE == -1 ) then
        STOP_ALTITUDE = stop_altitude
    end
    
    if ( g_luaState.isAlive ) then
        DIFF_ALTITUDE = STOP_ALTITUDE - g_luaState.altitude
        if ( math.abs( DIFF_ALTITUDE ) > 100 ) then
            pitch = -1 * g_luaState.pitch
            
            pitch = pitch + ( DIFF_ALTITUDE / 5000 )
            throttle = 3 * DIFF_ALTITUDE / 5000
            
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
            
            
            g_luaAction.heading  = g_luaState.heading
            g_luaAction.roll     = roll
            g_luaAction.pitch    = pitch
            g_luaAction.throttle = throttle
        end
    end
    
    return g_luaAction
end
