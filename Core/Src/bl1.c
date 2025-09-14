#include "bl1.h"
#include "logger.h"
#include "stm32f3xx.h"
#include <stdint.h>

#define FLASH_END 0x08010000
#define APP_START 0x08008000
extern uint32_t _app_start;

void bl1_read_data(void){

}

void bl1_jump_to_user_app(void){
	// Function pointer to hold the address of the reset handler of the user application
	void (*app_reset_handler)(void);

	// 1. Configure the MSP by reading the value from the base address of user app
	const uint32_t app_base = (uint32_t)&_app_start;
	uint32_t msp_value = *(volatile uint32_t*)app_base;
	LOG_debug("MSP value: %#x", msp_value);

	// 2. Fetch reset handler address of the user application from +4 address
	app_reset_handler = (void (*)(void))(*(volatile uint32_t*)(app_base + 4));

	LOG_debug("App reset handler address: %#x", app_reset_handler);

	bool appOK = bl1_verify_app();

	if(!appOK){
		LOG_error("App verification failed");
		return;
	}
	// Set MSP (CMSIS instruction)
	__set_MSP(msp_value);

	// 3. Jump to the app
	app_reset_handler();
}

bool bl1_verify_app(void){
	uint32_t storedCRC = *(uint32_t *)(FLASH_END - 4);
	uint32_t calculatedCRC = CRC_compute(APP_START, FLASH_END - 4);
	LOG_debug("Calculated CRC: 0x%08x, Stored CRC: 0x%08x", calculatedCRC, storedCRC);
	return storedCRC == calculatedCRC;
}
