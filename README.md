# CuperAdCcreen
This is my own version of our project for our group assignment in "C/C++ programming". The assignment was to create a program that with logic can randomize ads on an Arduino Uno and write them out on a LCD-screen - without using existing Arduino Libraries.

## Key features
* utils.cpp -> setup_seed() uses this interesting solution i found [here](http://www.bytecruft.com/2013/03/seeding-standard-c-random-number.html) to seed by ADC.
* adChooser -> chooseNextAd() generates a new company (making sure that it is not that was shown previously).
* lcd.cpp -> Slide() using logical for-loops to create the slide effect.

## Prerequisites
- **Operating System** Makefile is tuned for Windows/Linux.
- **Programming Languages** C, C++ and Makefile
- **Compiler** AVR/G++
- **Libraries** only using libraries in C/C++ ISO and AVR/G++ from [here](https://blog.zakkemble.net/avr-gcc-builds/)
