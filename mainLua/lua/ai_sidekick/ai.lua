local StateMachine = require "statemachine"
local NavigateState = require "ai_sidekick/navigate"
local InterceptState = require "ai_sidekick/intercept"
local EvadeState = require "ai_sidekick/evade"

local AI = {}

function AI:new()
    local ai = {}
    ai.planeState = {}
    ai.stateMachine = StateMachine:new( ai, NavigateState, nil )
    -- ai.stateMachine:addState( InterceptState )
    ai.stateMachine:addState( EvadeState )
    ai.stateMachine.curState.enter( ai )

    function ai:update( transitions )
        return ai.stateMachine:update( transitions )
    end

    return ai
end

return AI