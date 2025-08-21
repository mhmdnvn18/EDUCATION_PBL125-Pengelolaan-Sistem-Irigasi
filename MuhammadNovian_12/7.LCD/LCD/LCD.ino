#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

void setup()
{
    lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
    lcd.backlight();
}

void loop()
{
    lcd.setCursor(0, 0); // Or setting the cursor in the desired position.
    lcd.print("MUHAMMAD NOVIAN"); // You can make spaces using well... spaces
    lcd.setCursor(5, 1); // Or setting the cursor in the desired position.
    lcd.print("World!");
    delay(500);



    lcd.backlight();
    lcd.clear();
    delay(500);
}
