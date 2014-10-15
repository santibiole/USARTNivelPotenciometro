#include <stdint.h>
#include "bsp/bsp.h"
#include <stdio.h>

/**
 * @brief Delay por software
 *
 * @param nCount Numero de ciclos del delay
 */
void delay(volatile uint32_t nCount);

/**
 * @brief Se encarga de prender un led y apagarlo luego de un tiempo
 *
 * @param led    Numero de led a pulsar
 * @param tiempo Numero de ciclos del delay entre prendido y apagado
 */
void pulsoLed(uint8_t led, uint32_t tiempo);

/**
 * @brief Aplicacion principal
 */
int main(void) {
	bsp_init();
	uint16_t led;
	uint8_t *nivel, *nivel_anterior;
	char tx_buffer[24];
	int i,j;

	while (1) {

		led = vumetro();

		for (i=0;i<led;i++) {
			led_on(i);
		}
		for (i=led;i<=7;i++) {
			led_off(i);
		}

		nivel = nivel_pote();

		if (nivel!=nivel_anterior) {
			nivel_anterior=nivel;
			sprintf(tx_buffer,"\nNivel Potenciometro: %d\n", (int)nivel);
			for (j=0;j<30;j++){
				delay(10000);
				uart_tx(tx_buffer[j]);
			}
		}

	}
}


void pulsoLed(uint8_t led, uint32_t tiempo){
	led_on(led);
	delay(tiempo);
	led_off(led);
}

void delay(volatile uint32_t nCount) {
	while (nCount--) {
	}
}

void APP_ISR_sw (void){

}

void APP_ISR_1ms (void){
	static uint16_t count_1s = 1000; // static: es una variable que se declara una sola vez, se fija en 0, y luego cada vez que entramos en la funci�n, count conserva el valor anterior.
	count_1s--;
	if (!count_1s) {
		led_toggle(0);
		count_1s = 1000;
	}
}
