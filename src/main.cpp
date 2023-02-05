/**
 * @file main.cpp
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  ESP32 Macro Keyboard main code
 * @version 0.1
 * @date 2023-01-15
 */

bool is_menu = false;

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <BleKeyboard.h>
#include <ESP32Encoder.h>
#include <OneButton.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>


#include "I2CKeyPad.h"
#include "utils/texts.h"
#include "hardware/serial.h"
#include "hardware/lcd.h"
#include "hardware/hal.h"
#include "hardware/ble.h"
#include "hardware/encoder.h"
#include "hardware/keypad.h"
#include "gui/menuicon.h"
#include "utils/OTA.h"
#include "hardware/button.h"



void setup()
{
#ifdef DEBUG
  init_serial();
#endif
  init_lcd();
  init_encoder();
  init_keypad();
  init_BUT();
  init_BLE();

  lcd.clearBuffer();
  lcd.setFont(u8g2_font_ncenB24_tr);
  lcd.sendBuffer();
}

void loop()
{
  if (is_menu == false)
  {
    lcd.clearBuffer();
    lcd.setFont(u8g2_font_ncenB24_tr);
    lcd.setCursor(40, 50);
    lcd.print(get_key());
    lcd.sendBuffer();
  }
  else
  {
    draw_menu();
  }

  enc_but.tick();
}