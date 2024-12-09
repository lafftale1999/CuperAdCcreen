# CuperAdCcreen
This is my own version of our project for our group assignment in "C/C++ programming". The assignment was to create a program that with logic can randomize ads on an Arduino Uno and write them out on a LCD-screen - without using existing Arduino Libraries.

## Key features
* Loads a list of companies in to PROGMEM and creates a pointer to them.
* Chooses a company from PROGMEM and creates an instance of the Company class.
* Writes out the company name, logo and then message according to their demands.

**Interesting solutions that saved me**
* utils.cpp -> setup_seed() uses this interesting solution i found [here](http://www.bytecruft.com/2013/03/seeding-standard-c-random-number.html) to seed srand() by ADC.
* Almighty Zak saved the day with the millis.h file found [here](https://github.com/ZakKemble/millis/tree/master).

## Prerequisites
- **Operating System** Makefile is tuned for Windows/Linux.
- **Programming Languages** C, C++ and Makefile
- **Compiler** AVR/G++
- **Libraries** only using libraries in C/C++ ISO and AVR from [here](https://blog.zakkemble.net/avr-gcc-builds/)

## I don't have an Arduino
If you don't own an Arduino, you can upload the .hex-file originally named CuperAdCcreen.hex [here](https://wokwi.com/projects/383283130065573889). Click the link and press "F1", search for "Upload Firmware and Start Simulation.." and choose the previously mentioned file.
