local StateMachine = {}

function StateMachine:new(entity, currentState, previousState)
    --only entity and currentState required
    local stateMachine = {}
    stateMachine.curState = currentState
    stateMachine.prevState = previousState

    local states = {}

    states[currentState.name] = currentState
    if previousState then
        states[previousState.name] = previousState
    end
    
    function stateMachine:update( transitions )
        -- attempt to change state
        local i = 1
        while transitions[ i ] do
            if ( self.curState.transitions[ transitions[ i ] ] ~= nil ) then
                self:changeState( self.curState.transitions[ transitions[ i ] ].newstate )
            end
            i = i + 1
        end
        return self.curState.execute(entity)
    end

    function stateMachine:addState(newState)
        states[newState.name] = newState
    end

    function stateMachine:changeState(newStateName)
        if ( newStateName ~= self.curState.name ) then
            self.prevState = self.curState
            self.curState.exit(entity)
            self.curState = states[newStateName]
            self.curState.enter(entity)
        end
    end

    function stateMachine:revertState()
        self:changeState(self.prevState.name)
    end

    function stateMachine:isInState(stateName)
        return stateName == self.curState.name
    end

    return stateMachine

end

return StateMachine