/**
 * @file encoder.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  Encoder Definitions
 * @version 0.1
 * @date 2023-01-15
 */

ESP32Encoder encoder;
int old_enc_pos = 0;
#define RIGHT 1
#define LEFT -1
#define NONE 0

/**
 * @brief Encoder init
 *
 */
void init_encoder()
{
   debug->println("Init Encoder");
   encoder.attachSingleEdge(ENC_A, ENC_B);
   encoder.setCount(0);
   encoder.setFilter(1023);
}

/**
 * @brief Get the encoder direction
 *
 * @return CW ->   1
 *         CCW -> -1
 */
int get_enc_dir()
{
   if (encoder.getCount() > old_enc_pos)
   {
      old_enc_pos = encoder.getCount();
      return RIGHT;
   }
   else if (encoder.getCount() < old_enc_pos)
   {
      old_enc_pos = encoder.getCount();
      return LEFT;
   }
   else
      return NONE;
}