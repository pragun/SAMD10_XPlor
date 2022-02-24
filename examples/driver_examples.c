/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable_channel(&ADC_0, 0);

	while (1) {
		adc_sync_read_channel(&ADC_0, 0, buffer, 2);
	}
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

/**
 * Example of using USART to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART[12] = "Hello World!";

static void tx_cb_USART(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void USART_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&USART, USART_ASYNC_TXC_CB, tx_cb_USART);
	/*usart_async_register_callback(&USART, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART, &io);
	usart_async_enable(&USART);

	io_write(io, example_USART, 12);
}

static struct io_descriptor *io;

static void I2C_0_rx_complete(const struct i2c_s_async_descriptor *const descr)
{
	uint8_t c;

	io_read(io, &c, 1);
}

void I2C_0_example(void)
{
	i2c_s_async_get_io_descriptor(&I2C_0, &io);
	i2c_s_async_register_callback(&I2C_0, I2C_S_RX_COMPLETE, I2C_0_rx_complete);
	i2c_s_async_enable(&I2C_0);
}

static struct timer_task Timer_task1, Timer_task2;
/**
 * Example of using Timer.
 */
static void Timer_task1_cb(const struct timer_task *const timer_task)
{
}

static void Timer_task2_cb(const struct timer_task *const timer_task)
{
}

void Timer_example(void)
{
	Timer_task1.interval = 100;
	Timer_task1.cb       = Timer_task1_cb;
	Timer_task1.mode     = TIMER_TASK_REPEAT;
	Timer_task2.interval = 200;
	Timer_task2.cb       = Timer_task2_cb;
	Timer_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&Timer, &Timer_task1);
	timer_add_task(&Timer, &Timer_task2);
	timer_start(&Timer);
}

/**
 * Example of using DAC_0 to generate waveform.
 */
void DAC_0_example(void)
{
	uint16_t i = 0;

	dac_sync_enable_channel(&DAC_0, 0);

	for (;;) {
		dac_sync_write(&DAC_0, 0, &i, 1);
		i = (i + 1) % 1024;
	}
}
