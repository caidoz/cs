# Weapon attachment and damage feedback pacing

A changed weapon spends 36 simulation ticks orbiting and spinning once above the hero, then snaps toward the hand over 10 ticks. At tick 46 the actual costume weapon changes and an attachment flash appears. Eight settle ticks complete the 54-tick sequence before attack motion can advance. This applies to landed weapon changes, individual sword attacks and restoration of the best equipped weapon. Unchanged weapons skip the sequence. The overhead position stays below the stage HUD on short screens.

Each damage number lives for 72 ticks. A shared feedback gate holds the next action or turn for 84 ticks after damage: 72 for the number and 12 for a final breath. Native attack and enemy recovery animations complete normally; changing actor, enemy counterattack and turn completion wait until feedback clears. Damage still applies exactly once at impact.

Validation: unit checks for orbit/attachment order and feedback expiry; native combat/turn model checks; runtime costume captures at 640x850 and 640x1408, plus actual companion/hero attacks and enemy turn sequencing. Normal Debug Win32 cs.exe updated.
