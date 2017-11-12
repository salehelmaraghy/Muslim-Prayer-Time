# Muslim Prayer Time

This project is to determine muslim prayer time based on the current user’s location,for any date and to notify the user when the prayer time comes.

==========================================================================================

Microcontroller:ATmega32.

.external pheriphrals:

GPS "SKM53": to get the user location longitute and latituite.

Real time clock RTC "DS1307": to store the time.

Keypad: to enter the date and for user interface.

LCD "LM016": to display the prayer time.

Buzzer: to notify when the prayer time equals the time in the RTC.

Buttons:for user interface.

===========================================================================================

.Internal pheriphrals:

UART:to communicate with the GPS.

I2C:to communicate with the RTC.

timer:to get the time every 30 seconds from the RTC and compare it with the.

EEPROM:to save the longitute and latitute in it,in case the power is cutoff.

===========================================================================================

Pin configration:

LCD: 	  Port B- B4,B5,B6,B7 with the data pins.
     	  Port C- C6:RS  C7:EN.


Keypad: Port A4 A3 A2 for row 1,2,3
	      Port A5 A6 A7 for col 1,2,3
	      Port A1 for 0 "as I have used 3*3 keypad,so I added external button to work as zero"

GPS:	  Port D0 D1 for UART tx and RX.

RTC:	  Port C0 C1 for I2C clk and data.

Buzzer: Port D5 to notify whn prayer time comes.

Led :	  Port D4 to blink while GPS processing.

Buttons:Port D2 D3 for user interface.

============================================================================================
Application:

1-At this project, first it will ask if you want to enter the date or depend on the date saved on the RTC,so it can calculate the Julian data.

2-Using this Julian date it will make some astronomical calculations(get the equation of time and declination angle of the sun).

3-Then the GPS will received data (UART interrupt enabled) until it receives the GPGGA frame (at this point the GPS must be faced to the sky).

4-After receiving the frame it will be parsed to get the longitute and latitute of the user's current location.

5-Based on this location, the five prayer time will be calculated (the user must add manually to the code two things 1-the timezone of his country(due to GMT) 
to send it to zohr function and update the RTC by the current time before burning the code.

6-The user now can use the Buttons to switch between the prayer times.

7-At the background Timer 1 is working in free running mode each 30 seconds it get the time from the RTC and compare it with the prayer times,if it match 

the LCD will display the prayer time and the buzzer will notify the user with it.

8-After pasring the longitute and latitute numbers it will be saved to the EEPROM,so if the power is unplugged from the microcontroller the GPS don't work

again,so it can work indoor,but only after burning the code the GPS have to be faced to the sky.

==============================================================================================

Refrences:

1-http://praytimes.org/wiki/Prayer_Times_Calculation.

2-http://www.electronicwings.com/avr-atmega/gps-module-interfacing-with-atmega1632.

3-Jean.Meeus_Astronomical.Algorithms "Book".
