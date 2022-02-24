/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_adc_sync.h>
#include <hal_ext_irq.h>

#include <hal_usart_async.h>

#include <hal_i2c_s_async.h>
#include <hal_timer.h>

#include <hal_dac_sync.h>

#include <hal_evsys.h>

#define SERCOM1_I2CS_BUFFER_SIZE 16

extern struct adc_sync_descriptor    ADC_0;
extern struct usart_async_descriptor USART;

extern struct i2c_s_async_descriptor I2C_0;
extern struct timer_descriptor       Timer;

extern struct dac_sync_descriptor DAC_0;

void ADC_0_PORT_init(void);
void ADC_0_CLOCK_init(void);
void ADC_0_init(void);

void USART_PORT_init(void);
void USART_CLOCK_init(void);
void USART_init(void);

void I2C_0_PORT_init(void);
void I2C_0_CLOCK_init(void);
void I2C_0_init(void);

void DAC_0_PORT_init(void);
void DAC_0_CLOCK_init(void);
void DAC_0_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
