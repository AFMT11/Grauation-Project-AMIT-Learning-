# Grauation-Project (Smart Home) AMIT-Learning
![0001](https://user-images.githubusercontent.com/53840129/128654004-b7eab6b9-7468-4c7f-bc31-cb6f8a80d4c1.jpg)
# Purpose of the project
- The purpose of the project is to control 3 LED (ON/ OFF), plus the LCD, and the Buzzer.

# Components of the project
− The project consists of:
1. 1 X Controller (ATMEGA32)
2. 1 X Controller (ATMEGA328P)
3. 1 X Bluetooth module (HC-05)
4. 1 X LCD 16 X 2
5. 3 X LED 5mm
6. 1 X Buzzer

# Implementation of the project
− The controlling signal comes from the Bluetooth module whether from the Mobile, or the laptop, that signal is received by the controller ATMEGA328P which receives the signal with UART communication protocol.
− After the data has been received by the first controller ATMEGA328P, it will transfer that data to the second controller using SPI protocol, so that the controller ATMEGA328P is the Master, and ATMEGA32 is the Slave.
− After the data has been received by the second controller ATMEGA32, is will do some signal processing to check on multiple of thing:
1. if the password entered is correct or not.
2. if the character received is equal to some specific character by which we will control the LEDs.
3. to make a beep at every character entered at the password checking stage.
4. to make 3 beeps if the entered password is incorrect.
5. to display multiple of messages to the users in multiple stages at the execution of the program.
- Note that; I connected the Bluetooth module with my laptop, and sent the characters using PUTTY terminal with Baud rate 38400 bps set by default in the Bluetooth module datasheet.

# Flowchart of the main file
![Graduation Project FlowChart](https://user-images.githubusercontent.com/53840129/128654088-f80c9eaa-c9f4-49ba-8bbe-0db7a33aac4d.png)
