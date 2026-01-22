# Lab 2 - More C Practice With Interrupts

More exercises solved in C but this time with Interrupts. Lab manual located in `Lab_2_Exercises.pdf`.

## Exercises

### 1. Button Counter
**File:** `question_1/question_1.ino`

Write a C program to count the difference between the number of times two different buttons are pressed. 
a) The button pressing operation should be defined in an ISR. 
b) Observe the count value from the watch window. 
c) If button 1 is pressed more than button 2, then turn on the red color LED. If the button pressed numbers is equal, then turn on the blue color LED. Otherwise, turn on the green color LED. If the button press numbers are equal, then turn on the blue color LED.

---

### 2. LED Sequence Control - With Interrupts
**Video Demo:** `images/question_2.mp4`

**File:** `question_2/question_2.c`

Turn on and off the red, green, and blue LEDs in a sequence with the following specifications:
- When the button is pressed, turn on the LEDs in the following order: **R → RG → RGB → GB → B → RB**
- This procedure repeats until the button is pressed again

<p align="center">
  <video controls width="600">
    <source src="images/question_2.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</p>

---

### 3. Simple Calculator - With Interrupts
**Video Demo:** `images/question_3.mp4`
**File:** `question_3/question_3.c`

A simple calculator with the following specifications:
- Three arrays, each with 10 elements (two with integer numbers, one empty for results)
- Button 1 pressed once: Addition operation (Red LED on)
- Button 1 pressed twice: Subtraction operation (Green LED on)
- Button 1 pressed three times: Multiplication operation (Blue LED on)
- Button 2 pressed: Apply selected operation to all array elements, save results to third array
- All LEDs turn off during operation
- All LEDs turn on when complete

<p align="center">
  <video controls width="600">
    <source src="images/question_3.mp4" type="video/mp4">
    Your browser does not support the video tag.
  </video>
</p>

---

### 1. Simple Filtering
**File:** `question_4/question_4.ino`

Write a C program such that the global integer array x with 10 elements will be filled initially. For this problem, fill it at the beginning of the code. When an interrupt comes from button 1 the ISR will be called. The ISR will calculate the global integer array y defined as 𝑦[𝑛] = 2 ∗ 𝑥[𝑛] − 𝑥[𝑛 − 1] where 𝑛 is the index for the array. In fact, this is a simple filtering operation working with interrupts. In the actual application, the interrupt should come from some other source. The array 𝑥 should also be filled by other module or a peripheral (such as ADC).