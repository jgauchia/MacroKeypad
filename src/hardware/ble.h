/**
 * @file ble.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  BLE Definitions
 * @version 0.1
 * @date 2023-01-15
 */

/**
 * @brief BLE device name definition
 *
 */
const char *BLE_device_name = "MacroKeypad";
const char *BLE_devide_manuf = "Jordi Gauchía";

BleKeyboard bleKeyboard(BLE_device_name, BLE_devide_manuf, 100);

/**
 * @brief BLE Init
 *
 */
void init_BLE()
{
    debug->println("Starting BLE");
    bleKeyboard.begin();
    lcd.clearBuffer();
    lcd.setFont(u8g2_font_7x14_tf);
    lcd.drawStr(ALIGN_CENTER(s_noconn), 10, s_noconn);
    lcd.setFont(u8g2_font_open_iconic_www_4x_t);

    debug->println("Waiting for connection...");

    while (!bleKeyboard.isConnected())
    {
        debug->println(s_noconn);
        delay(1000);
        lcd.setCursor(50, 55);
        lcd.print(char(69));
        lcd.sendBuffer();
    }
    debug->println(s_connected);
    lcd.clearBuffer();
    lcd.setCursor(50, 55);
    lcd.print(char(79));
    lcd.setFont(u8g2_font_7x14_tf);
    lcd.drawStr(ALIGN_CENTER(s_connected), 10, s_connected);
    lcd.sendBuffer();
    delay(2000);
}