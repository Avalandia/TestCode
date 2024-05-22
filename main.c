#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <nrfx_rtc.h>

#define MY_GPIO_DIR_REG   0x50842500 + 0x014  ///marcon som def utgåns pinnarna
#define MY_GPIO_OUT_REG   0x50842500 + 0x004

///0101000.. = 0x50000000, enable1, unable0.
///1010000.. = 0xA0000000, -------||-------.

void main()
{
	nrfx_systick_init();  //timern startar
	*((volatile uint32_t *)(0x50842500 + 0x014)) = 0xF0000000; //1111000 sätter igång alla pinnar från 28-31

	while(1)
	{
		nrfx_systick_delay_ms(1000);
		*((volatile uint32_t *)(0x50842500 + 0x004)) = 0x50000000;
		nrfx_systick_delay_ms(1000);
		*((volatile uint32_t *)(0x50842500 + 0x004)) = 0xA0000000;

	}
}


/*#define PIN_TXD (20)
#define PIN_RXD (22)

#define LED1 (28)
#define LED2 (29)
#define LED3 (30)
#define LED4 (31)
#define BUTTON1 23
#define BUTTON2 24
#define BUTTON3 8
#define BUTTON4 9
#define LED_OFF 1
#define LED_ON 0

static nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);
static const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);
static uint8_t crap = 0;

void uarte_init(void)
{
	const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(20,22);
	nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
	if(errr != 0)
	{
		
	}
}
void rtc_init(void)
{
	nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;
	nrfx_err_t errr = nrfx_rtc_init(&rtc_instance, &config, NULL);
	nrfx_rtc_enable(&rtc_instance);
	crap = 1;
}

void init_gpio(void)
{   ///leds
	nrf_gpio_cfg_output(LED1);
	nrf_gpio_cfg_output(LED2);
	nrf_gpio_cfg_output(LED3);
	nrf_gpio_cfg_output(LED4);

	


	///buttons
	nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

}

void button_status(void)
{
	//uint8_t button_state = 0;
	char button1_pressed = (nrf_gpio_pin_read(BUTTON1) == 0);
	char button2_pressed = (nrf_gpio_pin_read(BUTTON2) == 0);
	char button3_pressed = (nrf_gpio_pin_read(BUTTON3) == 0);
	char button4_pressed = (nrf_gpio_pin_read(BUTTON4) == 0);

     if (button1_pressed) 
	 {
        
		uint8_t msg[]= "\n\r Button 1 \n\r";
		nrfx_uarte_tx(&instance, msg, sizeof(msg),0);
     } 
	 else if(button2_pressed){
		uint8_t msg[]= "\n\r Button 2 \n\r";
		nrfx_uarte_tx(&instance, msg, sizeof(msg),0);

	 }
	 else if(button3_pressed){
		uint8_t msg[]= "\n\r Button 3 \n\r";
		nrfx_uarte_tx(&instance, msg, sizeof(msg),0);

	 }
	 else if(button4_pressed){
		uint8_t msg[]= "\n\r Button 4 \n\r";
		nrfx_uarte_tx(&instance, msg, sizeof(msg),0);

	 }

	
}

int main(void)
{

	init_gpio();
    uarte_init();
	rtc_init();
	
	
	while(1)
	{ 
		
	    button_status();
		
		srand(nrfx_rtc_counter_get(&rtc_instance));
        int random_delay = rand() % 20000;

		uint32_t start_time = nrfx_rtc_counter_get(&rtc_instance);
      

		 // Slå på en slumpmässig LED
		int random_led = rand() % 4 + 1; // Generera ett slumpmässigt tal mellan 1 och 4
         // Släck alla LED efter att reaktionstiden har skickats
        nrf_gpio_pin_write(LED1, LED_OFF);
        nrf_gpio_pin_write(LED2, LED_OFF);
        nrf_gpio_pin_write(LED3, LED_OFF);
        nrf_gpio_pin_write(LED4, LED_OFF);
		
        switch (random_led)
        {
            case 1:
                nrf_gpio_pin_write(LED1, LED_ON);
				while (nrf_gpio_pin_read(BUTTON1) == 1) {}
                break;
            case 2:
                nrf_gpio_pin_write(LED2, LED_ON);
				while (nrf_gpio_pin_read(BUTTON2) == 1) {}
                break;
            case 3:
                nrf_gpio_pin_write(LED3, LED_ON);
				while (nrf_gpio_pin_read(BUTTON3) == 1) {}
                break;
            case 4:
                nrf_gpio_pin_write(LED4, LED_ON);
				while (nrf_gpio_pin_read(BUTTON4) == 1) {}
                break;
		}

        while ((nrfx_rtc_counter_get(&rtc_instance) - start_time) < random_delay)
        {
            // Wait until the random delay has passed
        }

        uint32_t end_time = nrfx_rtc_counter_get(&rtc_instance);
        uint32_t reaction_time = end_time - start_time;

        // Skicka reaktionstiden via UARTE
        char msg[30];
        snprintf(msg, 30, "\n\rReaction time: %lu ms\n\r", reaction_time);
        nrfx_uarte_tx(&instance, (uint8_t *)msg, strlen(msg), 0);

       
    }
	

}*/
