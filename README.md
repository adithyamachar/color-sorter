# color-sorter

Color Sorter Manipulator – Arduino + OpenCV

This project is a color-sorting robotic manipulator built using:

Arduino

NEMA steppers + A4988 drivers

Servo motor

Webcam

OpenCV (Python)

Serial communication (Python → Arduino)

The system detects the color of an object using a webcam and then moves the manipulator to sort it into the correct position.

⭐ Features

Real-time color detection using webcam (OpenCV).

Detects: Red, Green, White.

Sends color data to Arduino through serial at 1,000,000 baud.

Arduino controls:

2 stepper motors via A4988

1 servo gripper

Three actions:

mov1() → For Red

mov2() → For Green

Default → White

🛠 Hardware Used

Arduino Uno / Nano

NEMA23 Stepper + A4988 Driver

NEMA17 Stepper + A4988 Driver

9G Servo Motor

Webcam (USB)

12V Power Supply

A4988 Microstepping Pins (MS1, MS2, MS3)

🧩 Wiring Summary
Stepper 1 (NEMA23)
Signal	Arduino Pin
EN	A1
DIR	13
STEP	2
MS1	4
MS2	6
MS3	7
Stepper 2 (NEMA17)
Signal	Arduino Pin
EN	3
DIR	8
STEP	5
MS1	10
MS2	11
MS3	12
Servo
Signal	Arduino Pin
Servo	A0








How the System Works
1. Python Script

Reads webcam feed.

Converts each frame to HSV.

Checks the center pixel of the image.

Determines color: Red, Green, White.

Sends the color to Arduino through serial:

arduino.write("Red\n".encode())

2. Arduino Behavior

When it receives:

“Red” → executes mov1()

“Green” → executes mov2()

“White” → does nothing (default)

Movement functions control both stepper motors and the servo.

🚀 How to Run the Project
Step 1 – Upload Arduino Code

Open Arduino IDE

Load color_sorter.ino

Select correct COM port

Upload

Step 2 – Run Python Color Detection

Open terminal:

python color_detect.py

Step 3 – Place Objects Under Webcam

The manipulator will automatically execute sorting actions.

📸 Color Detection Explanation

Colors are detected using HSV ranges:

COLOR_RANGES = {
    "Red": [...],
    "Green": [...],
    "White": [...]
}


A simple center-pixel sampling method is used:

h, s, v = hsv_frame[center_y, center_x]
