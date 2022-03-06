#include <atmel_start.h>
#include "touch.h"
#include "SEGGER_RTT.h"

extern qtm_touch_key_config_t    qtlib_key_configs_set1[DEF_NUM_SENSORS];

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
	uint16_t j = 0;
	while (1) {
		/* Does acquisition and post-processing */
		touch_process();

		if (measurement_done_touch == 1) {
			measurement_done_touch = 0;

			key_status0 = get_sensor_state(0) & 0x80;

			if (0u != key_status0)
				gpio_set_pin_level(LED, true);
			else
				gpio_set_pin_level(LED, false);
		}

		uint16_t val = 0;

		if(j%5000 == 0){
			SEGGER_RTT_printf(0,"----\n\n");
			for (uint8_t i= 0u; i < DEF_NUM_CHANNELS; i++) {

				SEGGER_RTT_printf(0,"Touch %d ",i);

				val = get_sensor_node_signal(i);
				SEGGER_RTT_printf(0,"Signal %d ", val);

				val = get_sensor_node_reference(i);
				SEGGER_RTT_printf(0,"Ref %d ", val);

				val = get_sensor_cc_val(i);
				SEGGER_RTT_printf(0,"CC %d ", val);
								/* Threshold */
				val = qtlib_key_configs_set1[i].channel_threshold;
				SEGGER_RTT_printf(0,"Thresh %d\n", val);
			}
		}
		j ++;
	}
}
