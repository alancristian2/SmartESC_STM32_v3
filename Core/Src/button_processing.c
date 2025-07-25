/*
 * m365
 *
 * Copyright (c) 2021 Francois Deslandes
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "button_processing.h"
#include "main.h"
#include "config.h"
#include "motor.h"

static uint8_t power_button_state = 0;

uint8_t buttonState() {
  static const uint32_t DEBOUNCE_MILLIS = 20;
  static uint8_t stable_state = 0;
  static uint8_t last_read_state = 0;
  static uint32_t last_toggle_time = 0;

  uint8_t current_state = (HAL_GPIO_ReadPin(PWR_BTN_GPIO_Port, PWR_BTN_Pin) == GPIO_PIN_SET) ? 1 : 0;
  uint32_t now = HAL_GetTick();

  if (current_state != last_read_state) {
    last_toggle_time = now;
    last_read_state = current_state;
  }

  if ((now - last_toggle_time) > DEBOUNCE_MILLIS) {
    stable_state = current_state;
  }

  return stable_state;
}

// NOTE: VERY_LONG_PRESS will only happen if brake is also pressed (to avoid user mistake with LONG_PRESS)
eButtonEvent getButtonEvent(M365State_t *p_M365State)
{
  static const uint32_t DOUBLE_GAP_MILLIS_MAX     = 250;
  static const uint32_t SINGLE_PRESS_MILLIS_MAX 	= 800;
  static const uint32_t VERY_LONG_PRESS_MILLIS_MAX 	  = 5000;

  static uint32_t button_down_ts = 0;
  static uint32_t button_up_ts = 0;
  static bool double_pending = false;
  static bool button_down = false;

  eButtonEvent button_event = NO_PRESS;
  uint32_t now = HAL_GetTick();

  if (button_down != buttonState()) {
    button_down = !button_down;
    if (button_down) {
      button_down_ts = now;
    } else {
      button_up_ts = now;
      if (double_pending) {
        button_event = DOUBLE_PRESS;
        double_pending = false;
      } else {
        double_pending = true;
      }
    }
  }

  if (!button_down && double_pending && now - button_up_ts > DOUBLE_GAP_MILLIS_MAX) {
    double_pending = false;
    button_event = SINGLE_PRESS;
  } else if (button_down &&
    (now - button_down_ts >= SINGLE_PRESS_MILLIS_MAX) &&
      ((now - button_down_ts <= VERY_LONG_PRESS_MILLIS_MAX) || p_M365State->brake_active == false)) {
    double_pending = false;
    button_event = LONG_PRESS;
  } else if (button_down && now - button_down_ts > VERY_LONG_PRESS_MILLIS_MAX) {
    double_pending = false;
    button_event = VERY_LONG_PRESS;
  }

  return button_event;
}

void checkButton(M365State_t *p_M365State) {
  static uint32_t counter = 0;

  // Increment shutdown counter solo si modo apagado activo (bit 4)
  if ((p_M365State->mode & (1 << 4)) != 0) {
    if (p_M365State->shutdown < 3000) // evitar overflow
      p_M365State->shutdown++;
  } else {
    p_M365State->shutdown = 0;
  }

  counter++;
  if ((counter % 2) == 0) { // cada 20ms si checkButton se llama cada 10ms
    switch (getButtonEvent(p_M365State)) {
      case NO_PRESS:
        break;

      case SINGLE_PRESS:
        p_M365State->light = !p_M365State->light;
        break;

      case VERY_LONG_PRESS:
        p_M365State->mode &= ~(1 << 4); // clear "off" bit
        p_M365State->shutdown = 0;
        break;

      case LONG_PRESS:
        p_M365State->mode |= (1 << 4); // set "off" bit

        if (p_M365State->shutdown == 0) {
          p_M365State->shutdown = 1;
          p_M365State->beep = 1;
        }
        break;

      case DOUBLE_PRESS:
        p_M365State->mode = p_M365State->mode + 2;
        if (p_M365State->mode > 4)
          p_M365State->mode = 0;
        set_mode(p_M365State);
        break;
    }
  }

  // Apaga el dispositivo si shutdown pasa 250 (5 segundos)
  if ((p_M365State->shutdown > 250) && ((p_M365State->mode & (1 << 4)) != 0)) {
    power_control(DEV_PWR_OFF);
  }
}

void PWR_init() {
  /* Check button pressed state at startup */
  power_button_state = buttonState();

  /* Power ON board temporarily, ultimate decision to keep hardware ON or OFF is made later */
  power_control(DEV_PWR_ON);
}

void power_control(uint8_t pwr)
{
  if (pwr == DEV_PWR_ON) {
    /* Turn the PowerON line high to keep the board powered on even when
     * the power button is released
     */
    HAL_GPIO_WritePin(TPS_ENA_GPIO_Port, TPS_ENA_Pin, GPIO_PIN_SET);
  } else if (pwr == DEV_PWR_OFF) {

    //motors_free(0, NULL);
    //sleep_x_ticks(2000);
    //stop_motors();

    while(HAL_GPIO_ReadPin(PWR_BTN_GPIO_Port, PWR_BTN_Pin)); // espera soltar botón
    HAL_GPIO_WritePin(TPS_ENA_GPIO_Port, TPS_ENA_Pin, GPIO_PIN_RESET);
    while(1); // bloqueo infinito para simular apagado
  } else if(pwr == DEV_PWR_RESTART) {

    //motors_free(0, NULL);
    //sleep_x_ticks(2000);
    //stop_motors();

    /* Restart the system */
    NVIC_SystemReset();
  }
}

void set_mode(M365State_t *p_M365State) {

  switch (p_M365State->mode & 0x07) { // solo bits bajos 3
    case eco:
      p_M365State->phase_current_limit = PH_CURRENT_MAX_ECO;
      p_M365State->speed_limit = SPEEDLIMIT_ECO;
      break;

    case normal:
      p_M365State->phase_current_limit = PH_CURRENT_MAX_NORMAL;
      p_M365State->speed_limit = SPEEDLIMIT_NORMAL;
      break;

    case sport:
      p_M365State->phase_current_limit = PH_CURRENT_MAX_SPORT;
      p_M365State->speed_limit = SPEEDLIMIT_SPORT;
      break;
  }
}
