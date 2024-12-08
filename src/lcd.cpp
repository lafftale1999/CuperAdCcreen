#include "../include/lcd.h"
#include <string.h>

// Constructor for HD44780 class
HD44780::HD44780() {
  position_x = 0;
  position_y = 0;
  Initialize();
}

void HD44780::ShowAd(Company *company, int messageIndex)
{
    this->Clear();
    
    this->WriteCompany(company);

    this->Clear();

    switch(company->getMessages().getMessage(messageIndex).getEffect())
    {
        case PLAIN:
            WriteText(company->getMessages().getMessage(messageIndex).getText());
            _delay_ms(AD_LENGTH);
            break;

        case SCROLL:
            Slide(company->getMessages().getMessage(messageIndex).getText(), strlen(company->getMessages().getMessage(messageIndex).getText()));
            break;

        case BLINK:
            BlinkText(company->getMessages().getMessage(messageIndex).getText());
            break;
    }
}

// Sending command to the LCD
void HD44780::WriteCommand(unsigned char cmd) {
  OutNibble(cmd >> 4);
  OutNibble(cmd);
  _delay_us(50);
}

void HD44780::WriteText(const char *text) {
  int charCount = 0; // Track the number of characters printed
  
  while (*text) {
    if (charCount == 16) { // Move to the second line after 16 characters
      GoTo(0, 1);
    }

    WriteData(*text++);
    charCount++;
  }
}

// Writes Data to the LCD
void HD44780::WriteData(unsigned char data) {
  // Sets Register Select-pin to (1) to signal that the HD44780 is receiving data
  LCD_RS_PORT |= LCD_RS;

  // Writes the data
  Write(data);

  // Sets RS-pin to (0) for receiving commands
  LCD_RS_PORT &= ~LCD_RS;
}

// Sends half-bytes
void HD44780::Write(unsigned char byte) {
  OutNibble(byte >> 4); // 
  OutNibble(byte);
}

void HD44780::GoTo(unsigned char x, unsigned char y) {
  unsigned char addr = 0x80 + x + (0x40 * y);
  WriteCommand(addr);
}

void HD44780::BlinkText(const char *text)
{
  uint16_t adLengthMS = AD_LENGTH;
  const uint8_t blinkLengthMS = 250;

  uint16_t loops = adLengthMS / (blinkLengthMS * 2);

  for(int i = 0; i < loops; i++)
  {
    WriteText(text);
    _delay_ms(blinkLengthMS);

    Clear();
    _delay_ms(blinkLengthMS);
  }
}

void HD44780::Clear(void) {
  WriteCommand(HD44780_CLEAR);
  _delay_ms(2);
}

void HD44780::Home(void) {
  WriteCommand(HD44780_HOME);
  _delay_ms(2);
}

void HD44780::Slide(const char *text, uint8_t textLen){
  const uint8_t slideTime = 100;
  const uint16_t adTime = AD_LENGTH;
  const uint8_t screenSize = 32;
  char currText[screenSize + 1];

  for (size_t i = 0; i <= screenSize; i++)
  {
    currText[i] = '\0';
  }

  for (size_t i = 0; i < textLen; i++)
  {
    char reverseIndex = i;

    for (size_t j = 0; j < i+1; j++)
    {
      currText[j] = text[textLen - 1 - reverseIndex--]; 
    }

    Clear();
    WriteText(currText);
    _delay_ms(slideTime);
  }

  _delay_ms(adTime);

  for (size_t e = 0; e <= textLen; e++)
  {
    for (size_t i = 0; i < textLen; i++)
    {
      if(currText[0] == '\0')
      {
        Clear();
        return;
      }

      currText[i] = currText[i+1];
      Clear();
      WriteText(currText);
    }
    _delay_ms(slideTime);
  }
}

void HD44780::Initialize(void) {
  // Configure pins as output
  LCD_RS_DIR |= LCD_RS;
  LCD_E_DIR |= LCD_E;
  LCD_DB4_DIR |= LCD_DB4;
  LCD_DB5_DIR |= LCD_DB5;
  LCD_DB6_DIR |= LCD_DB6;
  LCD_DB7_DIR |= LCD_DB7;

  // Initialization sequence
  _delay_ms(15);
  OutNibble(0x03);
  _delay_ms(5);
  OutNibble(0x03);
  _delay_us(100);
  OutNibble(0x03);
  OutNibble(0x02);

  WriteCommand(0x28); // Function set: 4-bit mode, 2 lines
  WriteCommand(0x0C); // Display ON, Cursor OFF, Blink OFF
  Clear();
  WriteCommand(0x06); // Entry mode: Increment cursor

  _delay_us(25); //safety delay
  uint8_t customChar[] = customA;
  CreateChar(0, customChar);
  uint8_t customCharTwo[] = hourglass;
  CreateChar(1, customCharTwo);
  uint8_t leftHour[] = leftSideHourglass;
  CreateChar(2, leftHour);
  uint8_t rightHour[] = rightSideHourglass;
  CreateChar(3, rightHour);
}

void HD44780::OutNibble(unsigned char nibble) {
  // BIT 0
  if (nibble & 1)
    LCD_DB4_PORT |= LCD_DB4;
  else
    LCD_DB4_PORT &= ~LCD_DB4;
  
  // BIT 1
  if (nibble & 2)
    LCD_DB5_PORT |= LCD_DB5;
  else
    LCD_DB5_PORT &= ~LCD_DB5;
  
  // BIT 2
  if (nibble & 4)
    LCD_DB6_PORT |= LCD_DB6;
  else
    LCD_DB6_PORT &= ~LCD_DB6;
  
  // BIT 3
  if (nibble & 8)
    LCD_DB7_PORT |= LCD_DB7;
  else
    LCD_DB7_PORT &= ~LCD_DB7;

  // sets Enable-pin to (1) to signal to LCD screen that there is data to be read
  LCD_E_PORT |= LCD_E;

  // short break for security
  _delay_us(1);

  // sets Enable-pin to (0)
  LCD_E_PORT &= ~LCD_E;
}

#define LCD_SETCGRAMADDR 0x40
void HD44780::CreateChar(uint8_t location, uint8_t charArray[]) {
  location &= 0x7;
  WriteCommand(LCD_SETCGRAMADDR | (location << 3));
  for (uint8_t i = 0; i < 8; i++) {
    WriteData(charArray[i]);
  }
}

void HD44780::WriteCompany(Company* company)
{
    // Hämta bitmap och namn
    uint8_t* bitmap = company->getLogo().getBitMap();
    const char* name = company->getName();

    this->CreateChar(0, bitmap);

    // Rensa skärmen
    this->Clear();

    // Skriv ut logotyp (anpassat tecken)
    this->WriteData(0);

    // Skriv ut företagsnamn
    uint8_t nameLen = strlen(name);
    for (uint8_t i = 0; i < nameLen && i < 32; i++) {
        if (i == 15) GoTo(0, 1); // Flytta till rad 2
        WriteData(name[i]);
    }

    this->WriteData(0);

    // Fördröjning
    _delay_ms(3000);
}