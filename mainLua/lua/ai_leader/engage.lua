local State 	= require "state"
local Behaviors = require "behaviors"

local stage = 0

local function enter( entity )
    print( "LUA_Agent starting engagement!" )
end

local function execute( entity )
    pMaAction = nil
    pSyAction = nil
    pStAction = nil
	
	pMaAction = Behaviors:LuaPlaneFlyStraight (entity.planeState, entity.planeState.altitude)
	
	if ( stage == 0 ) then
		pMaAction = Behaviors:LuaPlaneFollowEnemy( entity.planeState, 24000 )
        if (entity.planeState.isTracking == true ) then	
			pStAction = Behaviors:LuaPlaneFire( entity.planeState, 25000 )
        else
            stage = 1           
        end
    elseif ( stage == 1 ) then
        stage = 0
        entity.stateMachine:changeState( "navigate" )
    end
    
    return pMaAction, pSyAction, pStAction
end


local function exit( entity )
    print("LUA_Agent stopping engagement!")
end

transitions = {
        T21 = { newstate = "navigate" },
        T23 = { newstate = "evade" }
    }

local EngageState = State:new( "engage", enter, execute, exit, transitions )
return EngageState