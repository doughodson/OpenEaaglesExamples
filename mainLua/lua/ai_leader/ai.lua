local StateMachine 		= require "statemachine"
local NavigateState 	= require "ai_leader/navigate"
--local InterceptState	= require "ai_leader/intercept"
local EngageState 		= require "ai_leader/engage"
local EvadeState 		= require "ai_leader/evade"

local AI = {}

function AI:new()
    local ai = {}
    ai.planeState = {}
    ai.stateMachine = StateMachine:new( ai, NavigateState, nil )
	-- ai.stateMachine:addState( InterceptState )
    ai.stateMachine:addState( EngageState )
    ai.stateMachine:addState( EvadeState )
    ai.stateMachine.curState.enter( ai )

    function ai:update( transitions )
        return ai.stateMachine:update( transitions )
    end

    return ai
end

return AI