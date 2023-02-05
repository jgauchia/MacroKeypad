/**
 * @file lcd.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  LCD Definitions
 * @version 0.1
 * @date 2023-01-15
 */

U8G2_SSD1306_128X64_NONAME_F_HW_I2C lcd(U8G2_R0, /* reset=*/U8X8_PIN_NONE);


/**
 * @brief Text Alignment functions
 * 
 */
#define LCDWidth                        lcd.getDisplayWidth()
#define ALIGN_CENTER(t)                 ((LCDWidth - (lcd.getUTF8Width(t))) / 2)
#define ALIGN_RIGHT(t)                  (LCDWidth -  lcd.getUTF8Width(t))
#define ALIGN_LEFT                      0

/**
 * @brief LCD init
 * 
 */
void init_lcd()
{
    lcd.begin();
}