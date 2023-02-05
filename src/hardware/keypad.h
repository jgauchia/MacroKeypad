/**
 * @file keypad.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  Keypad Definitions
 * @version 0.1 * @date 2023-01-15
 */

I2CKeyPad keyPad(KEYPAD_ADDRESS);

/**
 * @brief Keypad Mapping
 * 
 */
char keys[] = "321N654N987NBA0N F";  // N = NoKey, F = Fail

/**
 * @brief Keypad Init
 *
 */
void init_keypad()
{
    debug->println("Init Keypad");
    Wire.begin();
    Wire.setClock(400000);
    if (keyPad.begin() == false)
    {
        debug->println("ERROR: cannot communicate to keypad. Please reboot.");
    }
}

char get_key()
{
    uint8_t index = keyPad.getKey();
    return keys[index];
}