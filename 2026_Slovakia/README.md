# RoboCupJunior Soccer 2026 — Slovak national championship

This was the second generation of the Bari robot, still on an **Arduino Mega**. We kept the boards from Bari
(`PCBs/`) and continued the same firmware (`Code/Code.ino`). We tested each change separately in
`Test Code/`: compass, kicker, line sensors, motors and IR.

We finished 2nd and qualified for the world final. By then, the Mega's memory and its lack of floating-point
hardware were holding us back, so for Incheon we rebuilt the whole robot on the ESP32-S3.
See [`../2026_Korea`](../2026_Korea).
