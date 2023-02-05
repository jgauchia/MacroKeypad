/**
 * @file menuicon.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  Options menu with icons.
 * @version 0.1
 * @date 2023-01-23
 */

struct menu_entry_type
{
    const uint8_t *font;
    uint16_t icon;
    const char *name;
    uint8_t option;
};

struct menu_state
{
    int16_t menu_start;     /* in pixel */
    int16_t frame_position; /* in pixel */
    uint8_t position;       /* position, array index */
};

/*
  Icon configuration
  Width and height must match the icon font size
  GAP: Space between the icons
  BGAP: Gap between the display border and the cursor.
*/
#define ICON_WIDTH 32
#define ICON_HEIGHT 32
#define ICON_GAP 10
#define ICON_BGAP 16
#define ICON_Y 32 + ICON_GAP

struct menu_state current_state = {ICON_BGAP, ICON_BGAP, 0};
struct menu_state destination_state = {ICON_BGAP, ICON_BGAP, 0};

struct menu_entry_type menu_entry_list[] =
    {
        {u8g2_font_open_iconic_app_4x_t, 65, "Select Layout", 1},
        {u8g2_font_open_iconic_embedded_4x_t, 66, "Layout Setup", 2},
        {u8g2_font_open_iconic_embedded_4x_t, 74, "Bluetooth Status", 3},
        {u8g2_font_open_iconic_arrow_4x_t, 87, "OTA Update", 4},
        {u8g2_font_open_iconic_text_4x_t, 81, "Info", 5},
        {u8g2_font_open_iconic_arrow_4x_t, 91, "Exit Menu", 6},
        {NULL, 0, NULL}};

void draw(struct menu_state *state)
{
    int16_t x;
    uint8_t i;
    x = state->menu_start;
    i = 0;
    while (menu_entry_list[i].icon > 0)
    {
        if (x >= -ICON_WIDTH && x < lcd.getDisplayWidth())
        {
            lcd.setFont(menu_entry_list[i].font);
            lcd.drawGlyph(x, ICON_Y, menu_entry_list[i].icon);
        }
        i++;
        x += ICON_WIDTH + ICON_GAP;
    }
    lcd.drawRFrame(state->frame_position - 3, ICON_Y - ICON_HEIGHT - 3, ICON_WIDTH + 6, ICON_WIDTH + 6, 4);
}

void to_right(struct menu_state *state)
{
    if (menu_entry_list[state->position + 1].font != NULL)
    {
        if ((int16_t)state->frame_position + 2 * (int16_t)ICON_WIDTH + (int16_t)ICON_BGAP < (int16_t)lcd.getDisplayWidth())
        {
            state->position++;
            state->frame_position += ICON_WIDTH + (int16_t)ICON_GAP;
        }
        else
        {
            state->position++;
            state->frame_position = (int16_t)lcd.getDisplayWidth() - (int16_t)ICON_WIDTH - (int16_t)ICON_BGAP;
            state->menu_start = state->frame_position - state->position * ((int16_t)ICON_WIDTH + (int16_t)ICON_GAP);
        }
    }
}

void to_left(struct menu_state *state)
{
    if (state->position > 0)
    {
        if ((int16_t)state->frame_position >= (int16_t)ICON_BGAP + (int16_t)ICON_WIDTH + (int16_t)ICON_GAP)
        {
            state->position--;
            state->frame_position -= ICON_WIDTH + (int16_t)ICON_GAP;
        }
        else
        {
            state->position--;
            state->frame_position = ICON_BGAP;
            state->menu_start = state->frame_position - state->position * ((int16_t)ICON_WIDTH + (int16_t)ICON_GAP);
        }
    }
}

uint8_t towards_int16(int16_t *current, int16_t dest)
{
    if (*current < dest)
    {
        (*current)++;
        return 1;
    }
    else if (*current > dest)
    {
        (*current)--;
        return 1;
    }
    return 0;
}

uint8_t towards(struct menu_state *current, struct menu_state *destination)
{
    uint8_t r = 0;
    r |= towards_int16(&(current->frame_position), destination->frame_position);
    r |= towards_int16(&(current->frame_position), destination->frame_position);
    r |= towards_int16(&(current->menu_start), destination->menu_start);
    r |= towards_int16(&(current->menu_start), destination->menu_start);
    return r;
}

void draw_menu()
{
    int8_t event;
    do
    {
        lcd.clearBuffer();
        draw(&current_state);
        lcd.setFont(u8g2_font_7x14_tf);
        lcd.setCursor((lcd.getDisplayWidth() - lcd.getStrWidth(menu_entry_list[destination_state.position].name)) / 2, lcd.getDisplayHeight() - 5);
        lcd.print(menu_entry_list[destination_state.position].name);
        lcd.sendBuffer();
        delay(10);
        event = get_enc_dir();
        if (event == RIGHT)
            to_right(&destination_state);
        if (event == LEFT)
            to_left(&destination_state);
    } while (towards(&current_state, &destination_state));
}
