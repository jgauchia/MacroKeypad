/**
 * @file OTA.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  OTA Update
 * @version 0.1
 * @date 2023-01-24
 */

const char* ssid = "CERBERUS NET NEW";
const char* password = "+K1h42a76-";

AsyncWebServer server(80);

/**
 * @brief Start OTA Update web server
 *
 */
void start_OTA()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", BLE_device_name); });

    AsyncElegantOTA.begin(&server); 
    server.begin();

    lcd.clearBuffer();
    lcd.setFont(u8g2_font_7x14_tf);
    lcd.userInterfaceMessage("Go to:",WiFi.localIP().toString().c_str(),"/update","");
    lcd.sendBuffer();  
}