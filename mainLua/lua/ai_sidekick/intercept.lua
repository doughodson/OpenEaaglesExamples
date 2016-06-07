local State = require "state"
local Behaviors = require "behaviors"

local function enter( entity )
    print( "I'm intercepting!" )
end

local function execute( entity )
    local action = {}
    
    action1 = Behaviors:LuaPlaneFollowEnemy( entity.planeState, 10000 )
    action2 = Behaviors:LuaPlaneFire( entity.planeState, 20000 )
    action = action1 + action2
    
    if ( action == nil ) then
        entity.stateMachine:changeState( "navigate" )
    end
    
    return action
end

local function exit( entity )
    print("I'm stopping intercepting!")
end

transitions = {
        T21 = { newstate = "navigate" },
        T23 = { newstate = "evade" }
    }

local InterceptState = State:new( "intercept", enter, execute, exit, transitions )
return InterceptState