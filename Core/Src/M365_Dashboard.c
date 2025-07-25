/*
 * M365_Dashboard.c
 *
 *  Created on: Nov 27, 2021
 *      Author: stancecoke
 */

#include "main.h"
#include "config.h"
#include "stm32f1xx_hal.h"
#include "print.h"
#include "M365_Dashboard.h"
#include "M365_memory_table.h"
#include "decr_and_flash.h"
#include "stm32f1xx_hal_flash.h"

// --- Fix: Definición de estados de error ---
#define ERROR_NONE  0
#define ERROR_BRAKE 1

enum { STATE_LOST, STATE_START_DETECTED, STATE_LENGTH_DETECTED };

UART_HandleTypeDef huart3;
static uint8_t ui8_rx_buffer[132];
static uint8_t ui8_dashboardmessage[132];
static uint8_t enc[128];
static char buffer[64];
static uint8_t	ui8_tx_buffer[96];// = {0x55, 0xAA, 0x08, 0x21, 0x64, 0x00, 0x01, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static uint8_t ui8_oldpointerposition=64;
static uint8_t ui8_recentpointerposition=0;
static uint8_t ui8_messagestartpos=255;
static uint8_t ui8_messagelength=0;
static uint8_t ui8_state= STATE_LOST;
static uint32_t ui32_timeoutcounter=0;
static uint16_t ui16_update_size=0;
static uint32_t flashstartaddress = 0x08008400;
static uint32_t updateflagaddress = 0x0800FC00;
static uint32_t sysinfoaddress = 0x0800F800;
static uint32_t proc_ID_address = 0x1FFFF7E8;
char sys_info[512] = {
		// (datos omitidos por brevedad, deja tu original aquí)
};

char *target;
char *source;
static uint8_t ui8_target_offset;
static uint8_t ui8_source_offset;

M365_menory_table_t MT;

enum bytesOfMessage65 {
	Throttle = 7,
	Brake = 8,
} msg65;

enum bytesOfMessage64 {
	Speed = 10,
	Mode = 6,
	SOC = 7,
	Light = 8,
	Beep = 9,
	errorcode = 11
} msg64;

enum bytesOfGeneralMessage {
	msglength = 2,
	receiver = 3,
	command = 4,
	startAddress = 5,
	payloadLength = 6
} gen_msg;

void M365Dashboard_init(UART_HandleTypeDef huart1) {
    // ... tu código original ...
}

void search_DashboardMessage(M365State_t* p_M365State, UART_HandleTypeDef huart1) {
    // ... tu código original ...
}

void process_DashboardMessage(M365State_t* p_M365State, uint8_t *message, uint8_t length, UART_HandleTypeDef huart1) {
	//if(!checkCRC(message, length)){
	//... tu código original...

	switch (message[command]) {

		case 0x64: {
			//... tu código original ...
		}
		break;

		// --- Aquí va el fix para el case 0x65 ---
		case 0x65:
		  if (message[Brake] < (BRAKEOFFSET >> 1)) { // freno desconectado o error
		    p_M365State->error_state = ERROR_BRAKE;
		  } else if (p_M365State->error_state == ERROR_BRAKE) { // error de freno resuelto
		    p_M365State->error_state = ERROR_NONE;
		  }

		  int32_t regen_current = map(message[Brake], BRAKEOFFSET, BRAKEMAX, 0, p_M365State->regen_max_current);

		  if (regen_current > 0) { // frenando
		    if (p_M365State->speed > 2) {
		      p_M365State->i_q_setpoint_target = -map(p_M365State->battery_voltage, BATTERYVOLTAGE_MAX - 1000, BATTERYVOLTAGE_MAX, regen_current, 0);
		      p_M365State->brake_active = true;
		    } else {
		      p_M365State->i_q_setpoint_target = 0;
		      p_M365State->brake_active = true;
		    }
		  } else { // no frenando
		    p_M365State->i_q_setpoint_target = map(message[Throttle], THROTTLEOFFSET, THROTTLEMAX, 0, p_M365State->phase_current_limit);
		    p_M365State->brake_active = false;
		  }
		break;

		case 0x61: {
			//... tu código original ...
		}
		break;

		case 0x03: {
			//... tu código original ...
		}
		break;

		case 0x0A: {
			//... tu código original ...
		}
		break;

		case 0x07: {
			//... tu código original ...
		}
		break;

		case 0x08: {
			//... tu código original ...
		}
		break;

		case 0x09: {
			//... tu código original ...
		}
		break;

		default: {
			//... tu código original ...
		}
		break;
	} // fin switch
}

void addCRC(uint8_t * message, uint8_t size){
    //... tu código original ...
}

int16_t checkCRC(uint8_t * message, uint8_t size){
    //... tu código original ...
}
