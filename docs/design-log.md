# Design and decision log — start 2026-11-13

Use this as the source for the eventual design-process report. **Record real dates.** Distinguish (a) original ideas discussed earlier, (b) decisions made now, (c) planned tests, and (d) observed evidence. Sketches created later must be described as later sketches/visualizations, not passed off as sketches made earlier.

## Idea history (from previous discussion, prior to Nov 13)

- **Initial concept:** A tabletop object follows a diner's location and rotates toward them. Clap toggles motion; green/red lights signal whether active. Explored as an interactive tracking centerpiece.
- **Constraint discovered:** The available starter kit has no sound sensor, so clap detection would require a new sensor. Tracking people around a cluttered dining table with one ultrasonic sensor is uncertain.
- **Simplification:** Motorized Lazy Susan for food sharing; plate can be a four-section paper/cardboard model with food drawings.
- **Interaction refinement:** Potentiometer controls rotation without attempting item recognition or digital item selection. Extra LEDs / features were judged unnecessary to the main interaction.
- **Further refinement:** Switched over to using the y axis of the joystick for more ease of use.

## 2026-11-13 — Scope and workflow decision (planning, not testing)

**Problem framing:** At a shared meal, diners might have difficulty or inconvenience reaching and physically rotating a central serving tray. The concept explores remote motorized rotation as one way to make sharing accessible. This benefit is still a hypothesis.

**Current chosen MVP:** Physical potentiometer -> Arduino analog reading -> geared stepper motor -> lightweight four-quadrant paper plate. Off-centre knob controls direction and speed. Centre stops. First return to centre after power-on to arm movement.

**Why:** Kit-compatible, achievable with a single hardware owner, easy to demonstrate, supports code contributions and automated tests without peripherals.

**Rejected/deferred in current scope:** Clap toggle (missing microphone), person tracking (complex/unreliable in a meal scene), food-specific electronic selection (no identification/angle sensing), LED indicators (unnecessary if plate motion is visible), heavy real food tray (motor insufficient without mechanical engineering).

**Unvalidated risks:** Does a manual potentiometer that doesn't self-center actually improve convenience? Does the motor move the plate reliably? Does using a remote control meaningfully improve diners' experience compared with a normal tray? These should be tested rather than asserted.

**Current evidence:** Team conversation and software scaffolding. Physical results: **none recorded yet**. A host-only unit test passing does NOT mean motor motion was tested.

**AI contribution note:** ChatGPT contributed implementation planning, initial C++ scaffold, test and documentation drafts. Team members must review, adapt and independently verify them; cite AI use according to course requirements.


## Hardware status (November 13, 2026):
- Arduino UNO, ULN2003 driver, and stepper motor connected.
- Joystick VRy connected to Arduino A0.
- Firmware uploaded and motor control working.
- Physical serving plate not yet constructed.
- Desktop controller tests pass in GitHub Actions.
- Windows local test setup has not been verified.