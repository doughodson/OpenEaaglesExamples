
A general purpose radar test program.

To run:
  testRadar -f filename.edl

Example Files:

    "test1.edl"  ->  Simple radar test; ownship vs. 3 targets
    
    "test2a.edl" ->  N-squared test: total 48 players (24 blue vs 24 red targets)
                  Each with a RADAR and a RWR. Plus one player with a noise jammer
                  Click on blue and red players to switch ownships.
    
    "test2b.edl" -> Multi-thread test: 72 players (24 blue vs 48 red targets)
    
    "test2c.edl" -> Multi-thread test: 96 players (48 blue vs 48 red targets)

    "test3a.edl" -> Networked test, part #a: player with a radar and missiles
    "test3b.edl" -> Networked test, part #b: target player
                   ## Change IP addresses and subnet masks in test3a.epp and test3b.epp, and run makeEdl.bat

    "test4a.edl" -> 2nd networked test, part #a: basically the same as test2a, but with DIS added
    "test4b.edl" -> 2nd networked test, part #b: basically the same as test3b
                   ## Change IP addresses and subnet masks in test3a.epp and test3b.epp, and run makeEdl.bat


Keyboard controls:

   'r' or 'R'   -- Reset simulation
   'f' or 'F'   -- Toggle simulation freeze
   'l' or 'L'   -- Launch Missile
   'a' or 'A'   -- A/A mode (TWS)
   'g' or 'G'   -- A/G mode (GMTI)
   's' or 'S'   -- Target step
   'i' or 'I'   -- Increase Range
   'd' or 'D'   -- Decrease Range
   '+'          -- Ownship step (to next local air vehicle)
   esc          -- Exit
   
Note: You can select a player as the 'ownship' focus by using the mouse
      on the situation display or by using the '+' key.

