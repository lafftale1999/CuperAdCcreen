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

    millis_t start = millis_get();

    // one company in this assignment had special demands, therefore we are checking if the advertiser is
    // regular then they go through the regular switch case
    if(company->getDemand() == REGULAR)
    {
      switch(company->getMessages().getMessage(messageIndex).getEffect())
      {
        case PLAIN:
          WriteText(company->getMessages().getMessage(messageIndex).getText());
          while((millis_get() - start) < AD_LENGTH);
          break;

        case SCROLL:
          ScrollText(company->getMessages().getMessage(messageIndex).getText(), strlen(company->getMessages().getMessage(messageIndex).getText()));
          break;

        case BLINK:
          BlinkText(company->getMessages().getMessage(messageIndex).getText());
          break;
      }
    }

    // otherwhise we check if they are special
    else if(company->getDemand() == SPECIAL)
    { 
      // the special demand was to write out certain messages depending if the minutes was even / uneven
      uint32_t isEven = (millis_get() / 60000) % 2;

      if(!isEven)
      {
        ScrollText(company->getMessages().getMessage(0).getText(), strlen(company->getMessages().getMessage(0).getText()));
      }

      else
      {
        WriteText(company->getMessages().getMessage(1).getText());
        while((millis_get() - start) < AD_LENGTH);
      }  
    }

    // if none of the above has been assigned , something is wrong
    else
    {
      WriteText("SOMETHING WENT WRONG!");
      while((millis_get() - start) < AD_LENGTH);
    }
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

void HD44780::BlinkText(const char *text)
{
  uint16_t adLengthMS = AD_LENGTH;
  const uint8_t blinkLengthMS = 250;

  uint16_t loops = adLengthMS / (blinkLengthMS * 2);

  millis_t start = millis_get();

  while((millis_get() - start) < AD_LENGTH)
  { 
    millis_t delay = millis_get();

    WriteText(text);
    while((millis_get() - delay) < blinkLengthMS);

    Clear();
    delay = millis_get();
    while((millis_get() - delay) < blinkLengthMS);
  }
}

void HD44780::ScrollText(const char *text, uint8_t textLen){
  const uint8_t slideDelayMS = 100;
  const uint32_t minimumAdTime = 2000;
  const uint8_t screenSize = 32;
  char currText[screenSize + 1];

  millis_t startOfFunction = millis_get();
  millis_t start = millis_get();

  // make sure we dont have any scrap-values in our temporary string
  for (uint8_t i = 0; i <= screenSize; i++)
  {
    currText[i] = '\0';
  }

  // write out the text
  for (uint8_t i = 0; i < textLen; i++)
  {
    char reverseIndex = i;

    for (uint8_t j = 0; j < i+1; j++)
    {
      currText[j] = text[textLen - 1 - reverseIndex--]; 
    }

    Clear();
    WriteText(currText);

    start = millis_get();
    while((millis_get() - start) < slideDelayMS);
  }

  start = millis_get();
  // IF it took less than half the adtime - the minimum ad time (1000ms) to write out the ad
  if((millis_get() - startOfFunction) <= (AD_LENGTH / 2 - minimumAdTime))
  {
    // show the ad for ad lenght - the time it takes to write it out / remove
    while((millis_get() - start) < (AD_LENGTH - ((start - startOfFunction) * 2)));
  }

  // let the ad show for at least 1000ms
  else
  {
    while((millis_get() - start) < minimumAdTime);
  }

  // remove text
  for (uint8_t e = 0; e <= textLen; e++)
  {
    for (uint8_t i = 0; i < textLen; i++)
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
    start = millis_get();
    while((millis_get() - start) < slideDelayMS);
  }
}

// Sending command to the LCD
void HD44780::WriteCommand(unsigned char cmd) {
  OutNibble(cmd >> 4);
  OutNibble(cmd);
  _delay_us(50);
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

void HD44780::Clear(void) {
  WriteCommand(HD44780_CLEAR);
  _delay_ms(2);
}

void HD44780::Home(void) {
  WriteCommand(HD44780_HOME);
  _delay_ms(2);
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
    // create the company logo bitmap
    this->CreateChar(0, company->getLogo().getBitMap());

    this->Clear();

    // write out the logotype
    this->WriteData(0);

    // write out the company name
    for (uint8_t i = 0; i < strlen(company->getName()) && i < 32; i++) {
        if (i == 15) GoTo(0, 1);
        WriteData(company->getName()[i]);
    }

    // write out the logotype
    this->WriteData(0);

    millis_t start = millis_get();
    while((millis_get() - start) < COMPANY_NAME_TIME);
}