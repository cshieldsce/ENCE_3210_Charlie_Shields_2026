# ENCE 3210 - Microprocessor Systems I
All my labs, projects, and drivers for Microprocessor Systems I, Winter 2026.

---

## Project Documentation

### Documentation B - DAC Prototype & KiCad
> 📁 [`Documentation_B/`](Documentation_B/README.md)

![DAC circuit simulated in Falstad](https://github.com/cshieldsce/ENCE_3210_Charlie_Shields_2026/raw/main/Documentation_B/DAC_Prototype/images/falstad_circuit.png)

- 5-bit R-2R DAQ prototype built in lab and verified on oscilloscope
- Falstad circuit simulation
- KiCad schematic and PCB layout files for the Arduino UNO Shield

### Documentation C - DSP Shield
> 📁 [`Documentation_C/`](Documentation_C/README.md)

![DAC board 3d model](https://github.com/cshieldsce/ENCE_3210_Charlie_Shields_2026/raw/main/Documentation_B/KiCad/images/pcb_3d_view.png)

![PCB routing](https://github.com/cshieldsce/ENCE_3210_Charlie_Shields_2026/raw/main/Documentation_B/KiCad/images/pcb_kicad_editor.png)

Full documentation for the DSP Shield design and fabrication.

- Shield specifications and block diagram
- 10-bit R-2R Ladder DAC design and prototype
- KiCad PCB schematic, layout, 3D renders, and gerber files
- Interactive BOM
- Live demo videos of firmware running on the shield

---

## Labs

### Lab 1 — More C Practice
> 📁 [`lab1_embedded_c/`](labs/lab1_embedded_c/README.md)

Exercises practicing fundamental C programming concepts on embedded targets.

- Calculate twice the square of integers 0–511
- Cosine calculation for degrees 0–360 (results stored in array)
- Find the second maximum value in a 50-element integer array

---

### Lab 2 — Interrupts
> 📁 [`lab2_interrupts/`](labs/lab2_interrupts/README.md)

C programs using Interrupt Service Routines (ISRs) on the Arduino UNO.

- **Button Counter:** Count presses of two buttons via ISR; drive RGB LED based on difference
- **LED Sequence Control:** Cycle through R → RG → RGB → GB → B → RB on button press
- **Simple Calculator:** ISR-driven arithmetic operations
- **Filtering Operation:** Basic signal filtering using interrupts

---

### Lab 3 — Asynchronous Tasks with Interrupt Timers
> 📁 [`lab3_async_tasks/`](labs/lab3_async_tasks/README.md)

Two background tasks and one foreground task running concurrently using hardware timers.

| Task | Frequency | Timer | Responsibility |
|---|---|---|---|
| Task 1 | 1 Hz | Timer 1 | Blink Green LED, increment main-task counter |
| Task 2 | 10 Hz | Timer 2 | Additional async operation |
| Main | — | — | Foreground logic driven by Task 1 counter |

Also includes a **5-bit R-2R DAQ circuit** built and tested with oscilloscope verification.

---

### Lab 4 — Firmware Engineering
> 📁 [`lab4_firmware/`](labs/lab4_firmware/README.md)

Firmware design exercises built and tested on the DSP Shield.

- **Exercise 2 — Solar Charger:** Firmware for a solar charging control system
- **Exercise 4 — Fan Controller:** PWM-based fan speed controller with block diagram

> Demo videos for both projects available in [`Documentation_C/`](Documentation_C/README.md#shield-demos)

---

## HAL Drivers
> 📁 [`HAL_Drivers/`](HAL_Drivers/README.md)

Reusable hardware abstraction layer drivers developed during the course.

| Driver | Description |
|---|---|
| `ADCs_Uno/` | ADC read utilities for Arduino UNO |
| `PWMs_Uno/` | PWM output utilities for Arduino UNO |
| `HC_SR04_Drivers_v1/` | HC-SR04 ultrasonic sensor driver (v1) |
| `HC_SR04_Drivers_v2/` | HC-SR04 driver with interrupt support (v2) |
| `HC_SR04_Drivers_v3/` | HC-SR04 driver with filtered output (v3) |
| `MPU6050_Test/` | MPU-6050 IMU (I2C) test and driver |
| `SSD1306_Test/` | SSD1306 OLED HAL driver test |

---

## C Workshop
> 📁 [`c_workshop/`](c_workshop/README.md)

Warm-up C programming exercises completed at the start of the course.

- `quadratic.c` — Solve quadratic equations using a struct to return both roots
- `scanf_for_loop.c` — User input processing with for loops
