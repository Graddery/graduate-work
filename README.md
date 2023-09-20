# graduate-work
Final qualifying work (diploma)

This is a graduation paper on the topic of GPS tracker for people with disabilities.<br>
A prototype has been assembled.

I used the following components

      Arduino UNO (main electronic board)
      SIM800L (gps module)
      MPU6500 (Six Axis Gyro+Accel Motion Tracking)
      Pulse Sensor
      OLED Display 128x64
      FM4256 (2S Charger)
      LM2596 (DC-DC converter)

This device has the purpose of tracking a person's condition, as well as simplifying his communication in case of an emergency.<br>
The device sends SMS, reads the pulse and counts the steps.<br>
These are only small features of this GPS tracker. If desired, you can add a call function or collect / transmit additional data, since the boards still have a lot of functionality.<br>

The code is written in C++. <br>
The i2c data bus was used to connect the components.<br>
The price at the time of assembly was $26. All components are purchased in China.<br>

Special thanks to Gyver for the excellent display management library.
