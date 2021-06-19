# 7 Segment Clock Arduino Android
This is an digital 7 segment clock controlled with an Arduino and an android smartphone via Bluetooth. You don't need a real time clock module.

## Required Components:
  1. Arduino Nano or similar
  2. Low Energy Bluetooth Module (HC-05 oder similar)
  3. 220Ω resistor
  4. 12V power supply with Terminal
  5. 1.5m WS2811 LED-Strip
  6. wires
  7. 4 nails
  8. 16 M3*5+ bolts with nuts


## Step by step guide:
  1. 3D print the clock
      - Black:
        - 1 * MainLO.stl ①
        - 1 * MainLI.stl
        - 1 * MainRI.stl
        - 1 * MainRO.stl
        - 2 * Middle.stl
      - White:
        - 30 * Segment.stl (Layer Height = 0.1mm && Vase Mode on)
  3. Upload the Arduino Sketch to the Arduino.
  4. solder the components as shown in the following picture:

![PlanFinal](https://user-images.githubusercontent.com/69114845/122635437-38437d00-d0e4-11eb-9e60-0bb8e9e43dc1.jpg)

4. Download the Android App from the Google Play Store:
https://play.google.com/store/apps/details?id=com.JanFehnl.Uhr

5. If the time is not exact, then change the value of the variable "TimeCorrection" in the Arduino Sketch so that the deviation of the time is as small as possible. If the clock is slow, then increase the value slightly, if the clock is fast, then decrease the value of the variable.


① If you have the Arduino outside the clock and only need the three cables to the LED strip, then use V1. If you want to mount the Arduino and the terminal of the 12V power supply inside the clock, then print V2 to be able to lead the two cables into the clock.
