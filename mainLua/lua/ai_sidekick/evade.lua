local State = require "state"
local Behaviors = require "behaviors"

local function enter( entity )
    print( "I'm evading!" )
end

local function execute( entity )
    local action = {}
    
    action1 = Behaviors:LuaPlaneFlyStraight( entity.planeState, -1 )
    action2 = Behaviors:LuaPlaneClimbDive( entity.planeState, 1000 )
    action3 = Behaviors:LuaPlaneBreak( entity.planeState, "esq" )
    
    if ( action == nil ) then
        entity.stateMachine:changeState( "navigate" )
    end
    
    return action3
end

local function exit( entity )
    print("I'm stopping evading!")
end

transitions = {
        T31 = { newstate = "navigate" },
        T32 = { newstate = "intercept" }
    }

local EvadeState = State:new( "evade", enter, execute, exit, transitions )
return EvadeState