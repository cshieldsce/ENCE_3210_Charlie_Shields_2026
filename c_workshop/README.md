# C Workshop — Warm-Up Exercises

Introductory C programming exercises completed at the start of ENCE 3210.
Workshop manual: `README.md` (this file), full details in `c_workshop/`.

---

## Exercises

### Quadratic Equation Solver
**File:** [`quadratic.c`](quadratic.c)

Solves a quadratic equation $ax^2 + bx + c = 0$ using the quadratic formula:

$$x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}$$

Uses a `struct s_Quadratic` to return both roots $x_1$ and $x_2$.
Only real roots are computed (discriminant $\geq 0$).

---

### scanf and For Loop Practice
**File:** [`scanf_for_loop.c`](scanf_for_loop.c)

Demonstrates user input with `scanf` and iterative processing using `for` loops.