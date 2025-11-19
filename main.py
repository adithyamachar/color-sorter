import cv2
import numpy as np
import serial
import time

# Initialize serial communication with Arduino
arduino = serial.Serial('COM3', 1000000)  # Replace 'COM3' with your Arduino's port
time.sleep(2)

# Define color ranges in HSV
COLOR_RANGES = {
    "Red": [(0, 50, 50), (10, 255, 255), (170, 50, 50), (180, 255, 255)],  # Two ranges for red
    "Yellow": [(20, 100, 100), (30, 255, 255)],
    "Blue": [(90, 50, 50), (130, 255, 255)],  # Includes purple as blue
    "Green": [(35, 50, 50), (85, 255, 255)],
    "White": [(0, 0, 200), (180, 20, 255)],
}

def get_color_name(h, s, v):
    if s < 20 and v > 200:
        return "White"
    if v < 20:
        return "Black"
    for color, ranges in COLOR_RANGES.items():
        for lower, upper in zip(ranges[0::2], ranges[1::2]):
            if lower[0] <= h <= upper[0] and lower[1] <= s <= upper[1] and lower[2] <= v <= upper[2]:
                return color
    return "White"

def detect_color(frame):
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    h, s, v = hsv_frame[frame.shape[0] // 2, frame.shape[1] // 2]
    color_name = get_color_name(h, s, v)
    return color_name

def main():
    cap = cv2.VideoCapture(0)  # Change the index if you have multiple cameras

    if not cap.isOpened():
        print("Error: Could not open the camera.")
        return

    while True:
        ret, frame = cap.read()

        if not ret:
            print("Error: Failed to capture image")
            break

        color_name = detect_color(frame)
        try:
            if color_name in ["Red", "Green", "White"]:
                arduino.write(f"{color_name}\n".encode())  # Add newline character for better separation
                time.sleep(0.1)  # Small delay to prevent overflow
        except Exception as e:
            print("Error sending data to Arduino:", e)

        cv2.putText(frame, f'Color: {color_name}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 2, cv2.LINE_AA)
        cv2.imshow('Color Detection', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
