(deftemplate behavior
    ; Behavior
    (slot name
        (type SYMBOL)
    )
    ; General SLOTS
    (slot vote
        (type INTEGER)
        (default 1)
        (range 1 65535)
    )
    (slot voteOnIncomingMissile
        (type INTEGER)
        (default 1)
        (range 1 65535)
    )
    (slot voteOnCriticalAltitude
        (type INTEGER)
        (default 1)
        (range 1 65535)
    )
    (slot criticalAltitude
        (type FLOAT)
        (default 3000.0)
    )
    ; Optional parameters for behaviors
    (multislot optParams)
    
    ; Parameters that are passed via a Eaagles::Basic::PairStream.
    ; By now, it is only used by LuaBehaviors.
    (multislot optPairStream
        ; MANDATORY WHEN BEHAVIOR IS LUA
        ; THESE SLOTS MUST BE THE FIRST TWO
        ; 
        ; luaFileName       STRING
        ; 
        ; luaFunctionName   STRING
        ; 
        ; FOLLOWING A LIST OF OPTIONAL PARAMETERS
        ; TO BE PASSED TO THE LUA FUNCTION
    )
)

(defrule remover
    ?rmv    <- (remover ?name)
    ?which  <- (behavior (name ?name))
=>
    (retract ?which)
    (retract ?rmv)
)

; (defrule limpar
    ; ?fact   <- (limpar yes)
; =>
    ; (assert (remover))
    ; (retract ?fact)
; )

; (defrule nottracking
    ; (is-tracking no)
; =>
    ; (assert 
        ; (behavior (name LuaBehavior)
            ; (vote 1)
            ; (luaParams
                ; luaFileName "scripts/combat.lua"
                ; luaFunctionName "LuaPlaneTurn"
                ; 1
            ; )
        ; )
    ; )
; )

; (defrule curvar-direita
    ; (heading-to-tracked-is ?x & :(< ?x 0))
; =>
    ; (assert 
        ; (behavior (name LuaBehavior)
            ; (vote 3)
            ; (luaParams
                ; luaFileName "scripts/combat.lua"
                ; luaFunctionName "LuaPlaneTurn"
                ; 1
            ; )
        ; )
    ; )
; )

; (defrule curvar-esquerda
    ; (heading-to-tracked-is ?x & :(> ?x 0))
; =>
    ; (assert 
        ; (behavior (name LuaBehavior)
            ; (vote 3)
            ; (luaParams
                ; luaFileName "scripts/combat.lua"
                ; luaFunctionName "LuaPlaneTurn"
                ; -1
            ; )
        ; )
    ; )
; )

(defrule start
=>
    (assert 
        (behavior (name LuaBehavior)
            (vote 2)
            
            (optParams
                luaFunctionName "LuaPlaneFollowEnemy"
                luaFileName "lua/mainBasic.lua"
            )
            
            (optPairStream 
                float 5000
            )
        )
    )
    (assert 
        (behavior (name LuaBehavior)
            (vote 1)
            
            (optParams
                luaFunctionName "LuaPlaneFlyStraight"
                luaFileName "lua/mainBasic.lua"
            )
            
            (optPairStream 
                float -1
            )
        )
    )
    (assert 
        (behavior (name PlaneFire)
            (vote 4)
            (voteOnIncomingMissile 5)
            (optParams
                maxDistance 25000.0
            )
        )
    )
)