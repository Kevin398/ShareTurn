# ShareTurn — CPSC 581 Group Project 3

A **small, working prototype** of a remote-controlled Lazy Susan for sharing food around a table. The prototype uses a lightweight rotating paper/cardboard disc divided into four illustrated food sections. No real food or dishes are carried.

## What our prototype does

1. A diner moves a joystick.
2. A plate rotates clockwise or counter-clockwise
3. Moving farther from the middle raises the motor speed gradually, up to a conservative maximum.
4. Diners use the joystick to turn the food item they want towards them.

**Not implemented in this prototype:** clapping, LEDs, ultrasonic tracking, automatic selection of a named food, LCD, web app, and full-size loaded serving tray. There is **no sensor for the plate's absolute angle**, so the prototype cannot know whether a particular food drawing is aligned with a person.

This is a **continuous manual rotation control**, not a digital four-item selector. Users visually stop the tray at the desired place.

## Final project documentation and demo

- [Watch my ShareTurn prototype video](media/shareturn-demo.mp4)
- [Group design-process report (PDF)](docs/ShareTurn-Design-Process.pdf)
- [Implementation and wiring documentation (PDF)](docs/ShareTurn-Implementation-Documentation.pdf)
- [Our project sketches (PDF)](docs/ShareTurn-Sketches.pdf)

![ShareTurn assembled Arduino, joystick, and illustrated serving plate](media/shareturn-prototype-1.jpg)

The final prototype rotates a lightweight illustrated plate with joystick control. We tested the circuit and motor on the bench, and the controller tests passed. We did **not** run a formal user study, so we cannot claim the design is easier to use than a normal Lazy Susan. The kit motor is not intended to turn a loaded serving tray.

The final report documents our work and credits: Ayushi and I contributed concepts and sketches; I assembled and tested the physical circuit and recorded photos and video; Prince worked on firmware, the simulator, automated tests, and GitHub Actions; Ayushi prepared diagrams and the final design-process report. Our report also documents the team's ChatGPT and Claude assistance.

## Parts

- ELEGOO/Arduino UNO R3
- Joystick Module
- 28BYJ-48-type 5 V stepper motor and matching ULN2003 driver (verify the kit's motor label)
- Jumper wires and breadboard (for potentiometer)
- USB cable and suitable power supply
- A light paper/cardboard plate, food illustrations, simple support/hub

## Fast start (no Arduino required)

Desktop tools: any C++11 compiler such as `g++`.

```bash
# From the repository root
bash scripts/test.sh

# Optional interactive text simulator
bash scripts/simulate.sh
```

The simulator accepts raw simulated joystick readings, 0–1023. Start by entering `512` to enable the controller, then try `800`, `1023`, `200`, `0`, `512`.

**Only** `firmware/shareturn/shareturn.ino` needs an UNO. Desktop tests use the exact same pure C++ controller code used by the sketch. GitHub Actions runs those tests for every push or pull request.

## Hardware integration

View wiring.png in docs.

## Project layout

```text
firmware/shareturn/      Arduino sketch and reusable control logic
scripts/                 Desktop commands
simulator/               Console simulator (no hardware)
tests/                   Host-side unit tests (no hardware)
docs/wiring.png          Wiring and physical construction notes
docs/test-plan.md        Unperformed test checklist and integration plans
docs/design-log.md       Design decision log
.github/workflows/       Automatic host tests
```

## Important limitations

- A 28BYJ-48 is a **small geared motor** intended for a lightweight prototype, not a loaded Lazy Susan.
- The paper disc's weight should be supported/centred without loading the motor shaft sideways.
- The Stepper library rotates with short **single-step blocking calls**, so controls are sampled between steps. For the intended low speeds, this avoids blocking an entire revolution.

