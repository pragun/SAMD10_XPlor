/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

#include <hpl_adc_base.h>
#include <hpl_rtc_base.h>

/*! The buffer size for USART */
#define USART_BUFFER_SIZE 16

struct usart_async_descriptor USART;
struct timer_descriptor       Timer;

static uint8_t USART_buffer[USART_BUFFER_SIZE];

struct adc_sync_descriptor ADC_0;

struct i2c_s_async_descriptor I2C_0;
uint8_t                       SERCOM1_i2c_s_buffer[SERCOM1_I2CS_BUFFER_SIZE];

struct dac_sync_descriptor DAC_0;

void ADC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA15, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA15, PINMUX_PA15B_ADC_AIN7);
}

void ADC_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, ADC);
	_gclk_enable_channel(ADC_GCLK_ID, CONF_GCLK_ADC_SRC);
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC, (void *)NULL);
}

void EXTERNAL_IRQ_0_init(void)
{
	_gclk_enable_channel(EIC_GCLK_ID, CONF_GCLK_EIC_SRC);

	// Set pin direction to input
	gpio_set_pin_direction(PA17, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA17,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA17, PINMUX_PA17A_EIC_EXTINT1);

	// Set pin direction to input
	gpio_set_pin_direction(PA02, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA02,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA02, PINMUX_PA02A_EIC_EXTINT2);

	// Set pin direction to input
	gpio_set_pin_direction(PA31, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA31,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA31, PINMUX_PA31A_EIC_EXTINT3);

	// Set pin direction to input
	gpio_set_pin_direction(PA24, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PA24,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA24, PINMUX_PA24A_EIC_EXTINT4);

	ext_irq_init();
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_CLOCK_init()
{

	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM0);
	_gclk_enable_channel(SERCOM0_GCLK_ID_CORE, CONF_GCLK_SERCOM0_CORE_SRC);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_PORT_init()
{

	gpio_set_pin_function(PA10, PINMUX_PA10C_SERCOM0_PAD2);

	gpio_set_pin_function(PA11, PINMUX_PA11C_SERCOM0_PAD3);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_init(void)
{
	USART_CLOCK_init();
	usart_async_init(&USART, SERCOM0, USART_buffer, USART_BUFFER_SIZE, (void *)NULL);
	USART_PORT_init();
}

void I2C_0_PORT_init(void)
{

	gpio_set_pin_pull_mode(PA22,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA22, PINMUX_PA22C_SERCOM1_PAD0);

	gpio_set_pin_pull_mode(PA23,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PA23, PINMUX_PA23C_SERCOM1_PAD1);
}

void I2C_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM1);
	_gclk_enable_channel(SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC);
	_gclk_enable_channel(SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC);
}

void I2C_0_init(void)
{
	I2C_0_CLOCK_init();
	i2c_s_async_init(&I2C_0, SERCOM1, SERCOM1_i2c_s_buffer, SERCOM1_I2CS_BUFFER_SIZE);
	I2C_0_PORT_init();
}

/**
 * \brief Timer initialization function
 *
 * Enables Timer peripheral, clocks and initializes Timer driver
 */
static void Timer_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBA, RTC);
	_gclk_enable_channel(RTC_GCLK_ID, CONF_GCLK_RTC_SRC);
	timer_init(&Timer, RTC, _rtc_get_timer());
}

void DAC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(PA03, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PA03, PINMUX_PA03B_DAC_VREFP);
}

void DAC_0_CLOCK_init(void)
{

	_pm_enable_bus_clock(PM_BUS_APBC, DAC);
	_gclk_enable_channel(DAC_GCLK_ID, CONF_GCLK_DAC_SRC);
}

void DAC_0_init(void)
{
	DAC_0_CLOCK_init();
	dac_sync_init(&DAC_0, DAC);
	DAC_0_PORT_init();
}

void EVENT_SYSTEM_0_init(void)
{

	hri_pm_set_APBCMASK_EVSYS_bit(PM);

	event_system_init();
}

/**
 * \brief PTC initialization function
 *
 * Enables PTC peripheral, clocks and initializes PTC driver
 */
static void PTC_clock_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, PTC);
	_gclk_enable_channel(PTC_GCLK_ID, CONF_GCLK_PTC_SRC);
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA09

	gpio_set_pin_level(LED,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(LED, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(LED, GPIO_PIN_FUNCTION_OFF);

	ADC_0_init();
	EXTERNAL_IRQ_0_init();

	USART_init();

	I2C_0_init();

	Timer_init();

	DAC_0_init();

	EVENT_SYSTEM_0_init();

	PTC_clock_init();
}
