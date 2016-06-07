local State 	= require "state"
local Behaviors = require "behaviors"

local stage = 0

local function enter( entity )
    print( "LUA_Agent starting interception!" )
end

local function execute( entity )
    pMaAction = nil
    pSyAction = nil
    pStAction = nil
	
	if ( stage == 0 ) then
        DIFF_HEADING  = ( 0 * math.pi/180 ) - entity.planeState.heading
        DIFF_ALTITUDE = ( 10000 * 0.3048 ) - entity.planeState.altitude
        if ( math.abs( DIFF_HEADING ) > 0.1 or math.abs( DIFF_ALTITUDE ) > 100 ) then
            pMaAction = Behaviors:LuaPlaneFollowEnemy( entity.planeState, 5000 )
        else
            stage = 1            
        end
    elseif ( stage == 1 ) then
            pMaAction = Behaviors:LuaPlaneClimbDiveCurve( entity.planeState, 15000, 90 )
		if ( g_luaState.isTracking ) then	
			pStAction = Behaviors:LuaPlaneFire( entity.planeState, 25000 )
        else
            stage = 2            
        end
    elseif ( stage == 2 ) then
        stage = 0
        entity.stateMachine:changeState( "navigate" )
    end
    
    return pMaAction, pSyAction, pStAction
end


local function exit( entity )
    print("LUA_Agent stopping interception!")
end

transitions = {
        T21 = { newstate = "navigate" },
        T23 = { newstate = "evade" }
    }

local InterceptState = State:new( "intercept", enter, execute, exit, transitions )
return InterceptState