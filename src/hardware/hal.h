/**
 * @file hal.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  Pin definitions
 * @version 0.1
 * @date 2023-01-15
 */

/**
 * @brief Encoder Pin definition
 * 
 */
#define ENC_A  2
#define ENC_B  32
#define ENC_SW 15

/**
 * @brief Keypad PCF8574 address
 * 
 */
const uint8_t KEYPAD_ADDRESS = 0x20;