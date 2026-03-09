# HAL Drivers — Hardware Abstraction Layer

Reusable driver modules developed and tested during ENCE 3210.

---

## Drivers

### ADC — Arduino UNO
**Folder:** `ADCs_Uno/`
Utility functions for reading analog inputs on the Arduino UNO.

### PWM — Arduino UNO
**Folder:** `PWMs_Uno/`
Utility functions for configuring and outputting PWM signals on the Arduino UNO.

### HC-SR04 Ultrasonic Sensor — v1
**Folder:** `HC_SR04_Drivers_v1/`
Basic polling-based distance measurement driver.

### HC-SR04 Ultrasonic Sensor — v2
**Folder:** `HC_SR04_Drivers_v2/`
Interrupt-driven echo timing for improved accuracy.

### HC-SR04 Ultrasonic Sensor — v3
**Folder:** `HC_SR04_Drivers_v3/`
Filtered distance output using a rolling average for noise reduction.

### MPU-6050 IMU
**Folder:** `mpu6050_test/`
I2C driver and test sketch for the MPU-6050 6-axis accelerometer/gyroscope.

### SSD1306 OLED Display
**Folder:** `SSD1306_Test/`
HAL-level driver test for the SSD1306 128×64 OLED display.