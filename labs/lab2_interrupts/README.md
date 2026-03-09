# Lab 2 — More C Practice With Interrupts

C programs leveraging Interrupt Service Routines (ISRs) on the Arduino UNO.
Lab manual: `Lab_2_Exercises.pdf`

---

## Exercises

### 1. Button Counter
**File:** `question_1/question_1.ino`

Count the difference between the number of times two different buttons are pressed.

- Button presses are registered inside an ISR
- Counter value is observable from the watch window
- RGB LED output logic:
  - Button 1 pressed more → 🔴 Red LED on
  - Counts equal → 🔵 Blue LED on
  - Button 2 pressed more → 🟢 Green LED on

---

### 2. LED Sequence Control with Interrupts
**File:** `question_2/question_2.c`
**Video Demo:** `images/question_2.mp4`

Cycle through LED states on each button press using an ISR.

**Sequence:** R → RG → RGB → GB → B → RB → _(repeat)_

---

### 3. Simple Calculator with Interrupts
**File:** `question_3/question_3.ino`

ISR-driven calculator that performs arithmetic operations based on button input.

<img src="images/question_3.gif">

---

### 4. Simple Filtering Operation with Interrupts
**File:** `question_4/question_4.ino`

Implements a basic signal filtering operation triggered by an interrupt timer.