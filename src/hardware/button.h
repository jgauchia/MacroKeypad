/**
 * @file button.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  Encoder button definition
 * @version 0.1
 * @date 2023-01-23
 */

/**
 * @brief   Initialize a new OneButton instance for a button
 *          which is active low and uses the internal pull-up resistor.
 *
 */
OneButton enc_but = OneButton(
    ENC_SW,
    true, // Button is active LOW
    true  // Enable internal pull-up resistor
);

/**
 * @brief Handler function for a single click
 *
 */
static void handleClick()
{
    if (is_menu == true)
    {
        if (menu_entry_list[destination_state.position].option == 6)
            is_menu = false;
         if (menu_entry_list[destination_state.position].option == 4)
            start_OTA();
    }
}

/**
 * @brief Handler function for a long click
 *
 */
static void handleLongClick()
{
    if (is_menu == false)
    {
        current_state.menu_start = ICON_BGAP;
        current_state.frame_position = ICON_BGAP;
        current_state.position = 0;
        destination_state.menu_start = ICON_BGAP;
        destination_state.frame_position = ICON_BGAP;
        destination_state.position = 0;
        is_menu = true;
    }
}

/**
 * @brief Encoder push init
 *
 */
void init_BUT()
{
    enc_but.setDebounceTicks(30);
    enc_but.setPressTicks(500);
    enc_but.attachClick(handleClick);
    enc_but.attachDuringLongPress(handleLongClick);
}
