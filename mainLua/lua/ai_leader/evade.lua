local State = require "state"
local Behaviors = require "behaviors"

local stage = 0
local breaktime = 0

local function enter( entity )
    print( "LUA_Agent starting evasive maneuver!" )
end

local function execute( entity )
    pMaAction = nil
    pSyAction = nil
    pStAction = nil
    
    
    if ( stage == 0 ) then
        if ( breaktime < 16 ) then
            pMaAction = Behaviors:LuaPlaneBreak( entity.planeState, "dir" )
            breaktime = breaktime + __DT -- __DT is the elapsed time between calls of this function
        else
			stage = 1
            breaktime = 0
        end
    elseif ( stage == 1 ) then
        DIFF_ALTITUDE = ( 5000 * 0.3048 ) - entity.planeState.altitude
        if ( math.abs( DIFF_ALTITUDE ) > 500 ) then
            pMaAction = Behaviors:LuaPlaneClimbDive( entity.planeState, 12000 )
			breaktime = breaktime + __DT
			if (breaktime > 30) then
				stage = 2
			end
        else
            stage = 2
        end
    elseif ( stage == 2 ) then
        stage = 0
        print(" Breaktime complete ")
		entity.stateMachine:changeState( "navigate" )
    end
    
    return pMaAction, pSyAction, pStAction
end

local function exit( entity )
    print("LUA_Agent stopping evasive maneuver!")
end

transitions = {
        T31 = { newstate = "navigate" },
        T32 = { newstate = "engage" }
    }

local EvadeState = State:new( "evade", enter, execute, exit, transitions )
return EvadeState