local State = {}

function State:new( name, enter, execute, exit, transitions )
    local state = {}
    state.name = name
    
    state.transitions = transitions
    -- state.transitions = { [ CONDITION ] = { NEWSTATE = "state name" }}
    
    state.enter = enter
    state.execute = execute
    state.exit = exit

    return state

end


return State