# Space Lab Pinball (Williams)

## Spacelab/Skylab Links:

- [EM Repair](https://www.pinrepair.com/em/)
- [Pinside](https://pinside.com/pinball/machine/spacelab)
- [YouTube](https://www.youtube.com/watch?v=ZWouGSnXjZg)
- [Score Wheel](https://homepinballrepair.com/em-score-reels/#:~:text=Introduction,sensor%20switch%20is%20not%20working.)
- [IPDB Sky Lab](https://www.ipdb.org/machine.cgi?id=2202)
- [IPDB Space Lab](https://www.ipdb.org/machine.cgi?id=6620)
- [Williams 1974 Skylab  Instruction Manual](Williams_1974_Skylab_Instruction_Manual_Fixedup.pdf)
- [Williams 1977-1978 Parts Catalog](1977-1978williams.pdf)
- [Williams Introduction to Coin-Operated Amusement Games](Introduction_to_Coin_Operated_Amusement_Games_text.pdf)

## Annotated Files

* [Schematic](Williams_1974_Skylab_Schematic_submitted_by_Steve_Corley_Annotated.pdf)
* [Inside Cabinet](InsideCabinetAnnotated.png)
* [Back Cabinet](BackCabinetAnnotated.png)
* [Under Playfield](UnderPlayFieldAnnotated.png)

## Logic Simulation

* [Source Code](Skylab)

## Issues

* [Open Issues](https://github.com/cas-mls/Sky_SpaceLab/issues)
* [Closed Issues](https://github.com/cas-mls/Sky_SpaceLab/issues?q=is%3Aissue%20state%3Aclosed)

## Status:

## 16 -Jan-2026

* The 100 Point Drum is not resetting, and the score motor continues to run.
  * Fixed
    * Adjusted the Score Reset Relay Contacts.
    * Re-soldered a loose wire on the top, switched on the 100 Point Drum.
* Tilt Issue
  * Checked all of the Tilt switches.
    * Fixed
      * Not a consistent issue.
      * Found one that has insulation off and might be shorting with the other switch wire.
      * Found a Tilt Relay next to the score motor.  The front Slam and Kick sets this relay, and cannot be reset.
* Ball Count
  * The ball count adjustment is set to 5 balls.  The machine only shows 2 balls, but plays 3 balls.  Possible light bulb is burned out.
* 1000 Point Drum during reset?
  * When resetting with the credit button, or Reset Relay, maybe even when turning on.
    * This needs to be monitored.
    * It fixed itself after some time working on other issues.
    * During the reset, the first latched relay goes off and on, and the knocker is energized.
* Pressing the "S" and "K" causes the 10's drum to keep going and the Score Motor keep running.  Also, related to the 10's Drum is working if the rest of the "SKYLAB" is pressed, then the Advance Unit also runs, making a large racket.
  * Check the 50 Point Relay; it might not be shutting off. (Fixed Issue #4, Not sure if it is registering points.)
* Five balls in-line
  * Not sure if this is working correctly. (Wrote Issue #5)

## 21-Jan-2026

- Verify that the 1000 Point Continuous running has been fixed. (Close Issue #3).
- Verify that the 5 Balls In-Line is working (Close Issue #5)
- Fixed the 5-Ball Setting not working by cleaning up the Ball Stepper (Close Issue #6).
- SKYLAB causes the Score Motor to continue to work without stopping (Wrote Issue #13).
- Vacuum inside the machine; clean and wax the Playfield; clean contacts. Didn't find any lights to replace. (Issue #8)
- Playfield Inserts are loose and crooked (Wrote Issue #11)
- Right Flipper does not hold the ball.  Adjust the End of Stroke contact.  But look into rebuilding flippers. (Wrote Issue #12)
- Notice that loose legs cause the Tilt.  The research cost to fix the legs. (Wrote Issue #9)

## 30-Jan-2026

* Copied the Skylab Instruction Manual.

* Thought that this should be an easy problem, just adjust the Score Motor switch 5-C.  The 50 Point Relay, once turned on, stays on until the Score Motor cycles to the 5th position.  When the Score Motor cycles to the 50th position, the switch 5-C turns off, and the 50 Point Relay will turn off.

* Adjusted the 5-C Score Motor switch.  Managed to get the problem fixed, but the prior problem with the 50 Point Relay (Issue #4) returned.  Checked the workings of the Lock Switched on 50 Point Relay and the Skylab Relays, and verified that they worked.  Disable the Score Motor, verify that the relay turns off.  Turning on the Score Motor would cause the pinball to cycle correctly one or two times and then fail.

* Disable the Score Motor again and verify that the switch is disconnected and the relay is on.  Tapping on the relay causes it to shut.

* The problem with the pinball machine was that the Relay was stuck on.  With the pinball machine off, press the relay, and it would stick.  Cleaned the surface of the relay with sandpaper, and the Pinball Machine worked.  Which resolves Issue (#4 and #13).

* The triangle playfield inserts for the Rocket Special are warped.  Added the comment to Issue #11.

  ***Important Note: With the Score Motor OFF, the machine will register a TILT.***





