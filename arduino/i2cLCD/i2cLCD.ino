 
#include "Arduino.h"
#include "Wire.h"
 
#include "lcd_I2C.h"
 
/**
 * The Streaming library must be included in order to use "operator<<"        
 * It can be find at the following address :
 * https://arduiniana.org/libraries/streaming/
 * I am not the author of it but it is a must-have
 */
#include "Streaming.h"
 
 
LCD_I2C lcd(0x00, 4, 20);
 
 
void setup()
{
  lcd.begin();
}
 
 
void loop() {
        uint32_t ui32_lcd_delay = 3000;
 
        uint8_t uc_val = 0xFF;
        int32_t i32_val = -456798;
        uint32_t ui32_val = 0xFFFFFFFF;
        float f_val = 1234.89;
 
        lcd.clear();
        lcd << "-- Operator << --" << endl;
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd.println(F("Const char in flash"));
        lcd.println(F("I am in flash !"));
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd.println(F("-- Print String --"));
        String string("I am a string !");
        lcd << string << endl;
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "-- Print char --" << endl;
        lcd << "char : " << 'a' << endl;
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "-- Print number --" << endl;
        lcd << "uint8_t: " << uc_val << endl;
        lcd << "uint8_t: 0x" << _HEX(uc_val) << endl;
        lcd << "uint8_t: 0b" << _BIN(uc_val) << endl;
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "-- Print number --" << endl;
        lcd << "int32_t: " << i32_val << endl;
        lcd << "int32_t: 0x" << _HEX(i32_val) << endl;
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "-- Print float --" << endl;
        lcd << "float: " << f_val << endl;
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "-- Backlight OFF --" << endl;
        lcd.backlight(false);
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "-- Backlight ON --" << endl;
        lcd.backlight(true);
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "-- CursorXY (5,3) --" << endl;
        lcd.cursorXY(5, 3);
        lcd << 'X';
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "- CursorXY (10,2) -" << endl;
        lcd << _XY(10, 2) << 'X';
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd.print("-- Cursor OFF --");
        lcd.cursor(false);
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd.print("-- Cursor ON --");
        lcd.cursor(true);
        delay(ui32_lcd_delay);
 
        lcd.clear();
        lcd << "-- Cursor Home --" << endl;
        lcd.home();
        delay(ui32_lcd_delay);
}
