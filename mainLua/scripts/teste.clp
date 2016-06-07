(deffunction criararquivo
    (?fname)
    (open ?fname mydata "w")
    
    (printout   mydata 
                "(ClipsArbiter" crlf 
                "clipsFileName:      \"teste.clp\"" crlf
                "clipsAncFileName:   \"bla2\"" crlf
                "behaviors:{" crlf
    )
    (close)
)

(deffunction adicionar
    (?fname ?behavior ?vote ?param1)
    (open ?fname mydata "a")
    
    (printout   mydata
                "(" ?behavior " " ?vote " " ?param1 ")" crlf
    )
    (close)
)

(deffunction fechar
    (?fname)
    (open ?fname mydata "a")
    
    (printout   mydata
                "})" crlf
    )
    (close)
)

(deffunction addbehavior
    (?behavior ?vote ?param1)
=>
    (adicionar "bla2" ?behavior ?vote ?param1)
)

(defrule fire1
    (fire no)
    (is-tracking yes)
    (distance-to-tracked-is ?x & :(< ?x 12000) & :(> ?x 5000))
    (is-missile-fired no)
=>
    (assert (fire yes))
)

(defrule fire2
    (fire yes)
=>
    (criararquivo "bla2")
    (addbehavior PlaneFire vote:3 "maxDistance:(Meters 10000)")
    (addbehavior PlaneFollowEnemy vote:2 "")
    (addbehavior PlaneFlyStraight vote:1 "")
    (fechar "bla2")
    (assert (fire no))
    (printout t "CLIPS says: Shoot! You #%$&$#!! Shoot!!" crlf)
)

(defrule flystraight1
    ?fact <- (is-tracking no)
=>
    (criararquivo "bla2")
    (addbehavior PlaneFlyStraight vote:1 "")
    (fechar "bla2")
    (printout t "CLIPS says: I'm flying straight." crlf)
)

(defrule followenemy1
    ?fact1 <- (is-tracking yes)
    ; ?fact2 <- (is-tracked-enemy yes)
=>
    (criararquivo "bla2")
    (addbehavior PlaneFollowEnemy vote:2 "")
    (addbehavior PlaneFlyStraight vote:1 "")
    (assert (fire no))
    (fechar "bla2")
    (printout t "CLIPS says: I'm going to follow that *@!*&$#!" crlf)
)