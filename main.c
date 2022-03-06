#include <atmel_start.h>
#include "touch.h"
#include "SEGGER_RTT.h"

extern volatile uint8_t measurement_done_touch;

int main(void)
{
	SEGGER_RTT_Init();
	uint8_t key_status0 = 0;

	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* If the self-capacitance button is touched, the LED is turned ON
	 * When touch is released, the LED is turned OFF
	 */
	while (1) {
		/* Does acquisition and post-processing */
		SEGGER_RTT_printf(0,"Printf test 1\n");
		//printf("Printf test 2 \n");
		touch_process();

		if (measurement_done_touch == 1) {
			measurement_done_touch = 0;

			key_status0 = get_sensor_state(0) & 0x80;

			if (0u != key_status0)
				gpio_set_pin_level(LED, true);
			else
				gpio_set_pin_level(LED, false);
		}
	}
}
