# RoboCupJunior Soccer 2024 — team XLC-Captur

This was our first RoboCupJunior Soccer robot. We built it around an **Arduino Mega**, with a BNO055
compass, a Pixy2 camera to find the goals, an SSD1306 display and a ring of TSOP IR receivers to find
the ball. We designed the electronics as three Eagle boards: a lower base, an upper base and the TSOP
sensor ring.

The firmware grew one sketch at a time, from `Code/MainCodeV1` to `Code/mainCodeV10`, which is the version
we ended with. Before putting each part into the main code, we tried it in a small sketch first: compass
rotation, dribbler, kicker, IR ball sensors and the Pixy. Those sketches are in `Code/test_code/`.

| Folder | Contents |
|---|---|
| `Code/` | Main firmware V1–V10 and the test sketches |
| `PCBs/` | Eagle schematics and boards |
| `Photo/` | Renders of the three boards |
| `Doc/` | Our team description paper, poster and BOM |
