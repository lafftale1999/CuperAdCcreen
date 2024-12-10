// lcd.h
#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "company.h"
#include "millis.h"

// Pin configuration
#define LCD_RS_DIR DDRD
#define LCD_RS_PORT PORTD
#define LCD_RS (1 << PD2)

#define LCD_E_DIR DDRD
#define LCD_E_PORT PORTD
#define LCD_E (1 << PD3)

#define LCD_DB4_DIR DDRD
#define LCD_DB4_PORT PORTD
#define LCD_DB4 (1 << PD4)

#define LCD_DB5_DIR DDRD
#define LCD_DB5_PORT PORTD
#define LCD_DB5 (1 << PD5)

#define LCD_DB6_DIR DDRD
#define LCD_DB6_PORT PORTD
#define LCD_DB6 (1 << PD6)

#define LCD_DB7_DIR DDRD
#define LCD_DB7_PORT PORTD
#define LCD_DB7 (1 << PD7)



// HD44780 commands
#define HD44780_CLEAR 0x01
#define HD44780_HOME 0x02
// ... [rest of the command set]

#define AD_LENGTH 5000
#define COMPANY_NAME_TIME 3000

// HD44780 LCD class
class HD44780 {
public:
  HD44780();
  void ShowAd(Company *company, int messageIndex);
  void WriteCommand(unsigned char cmd);
  void WriteData(unsigned char data);
  void WriteText(const char *text);
  void GoTo(unsigned char x, unsigned char y);
  void Clear(void);
  void Home(void);
  void ScrollText(const char *text, uint8_t textLen);
  void Initialize(void);
  void CreateChar(uint8_t location, uint8_t charArray[]);
  void BlinkText(const char *text);
  void WriteCompany(Company *company);

private:
  int position_x;
  int position_y;
  void OutNibble(unsigned char nibble);
  void Write(unsigned char byte);
};

#endif /* LCD_H_ */