#include <atmel_start.h>
#include "touch.h"
#include "SEGGER_RTT.h"

extern qtm_touch_key_config_t    qtlib_key_configs_set1[DEF_NUM_SENSORS];

extern volatile uint8_t measurement_done_touch;

/**
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	adc_sync_enable_channel(&ADC_0, 7);
}

static void button_on_PA17_pressed(void)
{
}

static void button_on_PA02_pressed(void)
{
}

static void button_on_PA31_pressed(void)
{
}

static void button_on_PA24_pressed(void)
{
}

/**
 * Example of using EXTERNAL_IRQ_0
 */
void EXTERNAL_IRQ_0_example(void)
{

	ext_irq_register(PIN_PA17, button_on_PA17_pressed);
	ext_irq_register(PIN_PA02, button_on_PA02_pressed);
	ext_irq_register(PIN_PA31, button_on_PA31_pressed);
	ext_irq_register(PIN_PA24, button_on_PA24_pressed);
}


static struct io_descriptor *io;
/*
static void I2C_0_rx_complete(const struct i2c_s_async_descriptor *const descr)
{
	uint8_t c;
	io_read(io, &c, 1);
}

void I2C_0_example(void)
{
	i2c_s_async_get_io_descriptor(&I2C_0, &io);
	i2c_s_async_register_callback(&I2C_0, I2C_S_RX_COMPLETE, I2C_0_rx_complete);
	i2c_s_async_set_addr(&I2C_0, 0x55);
	i2c_s_async_enable(&I2C_0);
}
*/

int main(void)
{
	uint8_t adc_buffer[2];
	SEGGER_RTT_Init();
	uint8_t key_status0 = 0;

	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	//I2C_0_example();
	EXTERNAL_IRQ_0_example();

	/* If the self-capacitance button is touched, the LED is turned ON
	 * When touch is released, the LED is turned OFF
	 */
	uint16_t j = 0;
	uint16_t adc_val = 0;

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


		adc_sync_read_channel(&ADC_0, 7, &adc_val, 2);


		uint16_t val = 0;

		if(j%2000 == 0){
			SEGGER_RTT_printf(0,"----\n\n");
			SEGGER_RTT_printf(0, "ADC: %d \n", adc_val);

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
