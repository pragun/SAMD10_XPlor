
/*============================================================================
Filename : datastreamer_UART_sam.c
Project : QTouch Modular Library
Purpose : Provides the datastreamer protocol implementation, transmission of
          module data to data visualizer software using UART port.

This file is part of QTouch Modular Library 7.5 application.

Important Note: Do not edit this file manually.
                Use QTouch Configurator within Atmel Start to apply any
                modifications to this file.

Usage License: Refer license.h file for license information
Support: Visit http://www.microchip.com/support/hottopics.aspx
               to create MySupport case.

------------------------------------------------------------------------------
Copyright (c) 2021 Microchip. All rights reserved.
------------------------------------------------------------------------------
============================================================================*/
/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "datastreamer.h"
#include "driver_init.h"

#if (DEF_TOUCH_DATA_STREAMER_ENABLE == 1u)

/*----------------------------------------------------------------------------
 *     defines
 *----------------------------------------------------------------------------*/

#define FREQ_HOP_AUTO_MODULE_OUTPUT 1u

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/
extern qtm_acquisition_control_t qtlib_acq_set1;
extern qtm_touch_key_control_t   qtlib_key_set1;
extern qtm_touch_key_config_t    qtlib_key_configs_set1[DEF_NUM_SENSORS];

extern qtm_freq_hop_autotune_control_t qtm_freq_hop_autotune_control1;

extern uint8_t module_error_code;

uint8_t data[] = {
    0x5F, 0xB4, 0x00, 0x86, 0x4A, 0x03, 0xEB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0x55, 0x01, 0x6E, 0xA0};

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/
void datastreamer_transmit(uint8_t data);

/*----------------------------------------------------------------------------
 *   function definitions
 *----------------------------------------------------------------------------*/

/*============================================================================
void datastreamer_init(void)
------------------------------------------------------------------------------
Purpose: Initialization for datastreamer module
Input  : none
Output : none
Notes  :
============================================================================*/
void datastreamer_init(void)
{
	usart_async_enable(&USART);
}

/*============================================================================
void datastreamer_transmit(uint8_t data_byte)
------------------------------------------------------------------------------
Purpose: Transmits the single byte through the configured UART port.
Input  : Byte to be transmitted
Output : none
Notes  :
============================================================================*/
void datastreamer_transmit(uint8_t data_byte)
{
	/* Write the data bye */
	while (io_write(&USART.io, &data_byte, 1) != 1) {
	}

	/* wait until transmission is complete */
	while (!usart_async_is_tx_empty(&USART))
		;
}

/*============================================================================
void datastreamer_output(void)
------------------------------------------------------------------------------
Purpose: Forms the datastreamer frame based on the configured modules, Tranmits
         the frame as single packet through UART port.
Input  : none
Output : none
Notes  :
============================================================================*/
void datastreamer_output(void)
{
	int16_t           i, temp_int_calc;
	static uint8_t    sequence = 0u;
	uint16_t          u16temp_output;
	uint8_t           u8temp_output, send_header;
	volatile uint16_t count_bytes_out;

	send_header = sequence & (0x0f);
	if (send_header == 0) {
		for (i = 0; i < sizeof(data); i++) {
			datastreamer_transmit(data[i]);
		}
	}

	// Start token
	datastreamer_transmit(0x55);

	// Frame Start
	datastreamer_transmit(sequence);
	for (count_bytes_out = 0u; count_bytes_out < DEF_NUM_CHANNELS; count_bytes_out++) {

		/* Signals */
		u16temp_output = get_sensor_node_signal(count_bytes_out);
		datastreamer_transmit((uint8_t)u16temp_output);
		datastreamer_transmit((uint8_t)(u16temp_output >> 8u));

		/* Reference */
		u16temp_output = get_sensor_node_reference(count_bytes_out);
		datastreamer_transmit((uint8_t)u16temp_output);
		datastreamer_transmit((uint8_t)(u16temp_output >> 8u));

		/* Touch delta */
		temp_int_calc = get_sensor_node_signal(count_bytes_out);
		temp_int_calc -= get_sensor_node_reference(count_bytes_out);
		u16temp_output = (uint16_t)(temp_int_calc);
		datastreamer_transmit((uint8_t)u16temp_output);
		datastreamer_transmit((uint8_t)(u16temp_output >> 8u));

		/* Comp Caps */
		u16temp_output = get_sensor_cc_val(count_bytes_out);
		datastreamer_transmit((uint8_t)u16temp_output);
		datastreamer_transmit((uint8_t)(u16temp_output >> 8u));

		/* State */
		u8temp_output = get_sensor_state(count_bytes_out);
		if (0u != (u8temp_output & 0x80)) {
			datastreamer_transmit(0x01);
		} else {
			datastreamer_transmit(0x00);
		}

		/* Threshold */
		datastreamer_transmit(qtlib_key_configs_set1[count_bytes_out].channel_threshold);
	}
#if (FREQ_HOP_AUTO_MODULE_OUTPUT == 1)

	/* Frequency selection - from acq module */
	datastreamer_transmit(qtlib_acq_set1.qtm_acq_node_group_config->freq_option_select);

	for (uint8_t count = 0u; count < qtm_freq_hop_autotune_control1.qtm_freq_hop_autotune_config->num_freqs; count++) {
		/* Frequencies */
		datastreamer_transmit(qtm_freq_hop_autotune_control1.qtm_freq_hop_autotune_config->median_filter_freq[count]);
	}
#endif

	/* Other Debug Parameters */
	datastreamer_transmit(module_error_code);

	/* Frame End */
	datastreamer_transmit(sequence++);

	/* End token */
	datastreamer_transmit(~0x55);
}

#endif
