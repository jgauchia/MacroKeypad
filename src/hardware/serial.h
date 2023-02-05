/**
 * @file serial.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief Serial output functions (debug)
 * @version 0.1
 * @date 2023-01-15
 */

HardwareSerial *debug = &Serial;

/**
 * @brief Serial port init (debug)
 *
 */
void init_serial()
{
    debug->begin(BAUDRATE);
}