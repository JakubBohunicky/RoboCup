# RoboCupJunior Soccer 2025 — Bari, Italy

For Bari we built a new robot, still on an **Arduino Mega**, with a BNO055 compass, a Pixy2 camera and an
SSD1306 display. It was the first generation of the robot we later took to the Slovak championship in 2026.

We started with the TSOP IR ring from 2024 (`code_original_TSOP/`). Later we built our own IR seeker board
on an ATmega328 Nano (`IR seeker v3/`, PlatformIO). The main code went
through versions V10 to V13, and `mainCodeV13/` is what we played with. We also tried a version without the
dribbler, V12.5, but we didn't use it.

Our two robots weren't quite identical, so each version has two variants: `…` and `…_Ferrari`. They differ
in motor speed, `MOTOR_OFFSET`, and how long the robot backs off when it has the ball. We wrote the
differences down in `rozdiel medzi _Ferrari a nefferari.txt`.

`test_code/` holds the sketches we used to test each part on its own: motors, kicker, line sensors and
compass. It also has the 3D-printed parts (`.3mf`): the kicker, the ball shovel, the camera holder and the
TSOP shields.
