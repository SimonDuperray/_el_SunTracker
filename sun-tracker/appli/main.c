/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "macro_types.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "sun_tracker.h"

static bool_e readButton(void);
void useless_function(void);

int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
	HAL_Init();


	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);


	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	SUN_TRACKER_init();

	while(1)
	{
		SUN_TRACKER_process_main();
	}
}


static bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}


volatile uint32_t e;	//variable accessible depuis l'onglet expressions

//cette fonction ne sert à rien d'autre qu'à montrer le rôle des opérateurs en C et s'entrainer à utiliser le débogueur
void useless_function(void)
{
	static uint32_t n = 0;
	volatile uint8_t a = 0xCA;
	volatile bool_e b;
	volatile uint32_t d;
	volatile uint8_t c;

	b = 0b10101010 || 0b11110000;
	b = 0b10101010 && 0b11110000;
	b = !42;
	b = !0;

	c = 0b10101010 & 0b11110000;
	c = 0b10101010 ^ 0b11110000;
	c = 0b10101010 | 0b11110000;
	c = ~0b00001111;
	c ^= c;

	d = (0xFE << 16);
	d |= ((uint32_t)(a))<<24;
	d |= a;
	d += 0xDE << 8;

	e = 2976579765;

	while(1)
	{
		b = readButton();
		if(b)
		{
			n++;
		}
	}
}





