#include <Arduino.h>
#include "GPIO.h"
#include "ADC.h"
#include "PWM.h"

//#define DEBUG

extern volatile uint16_t freq;
extern volatile uint16_t duty_cycle;
extern uint8_t freq_switch_state;

#define F_CPU 16000000UL // тактовая частота 16 мгц

int main(void)
{
	Serial.begin(9600);
	GPIO_init();
	ADC_init();
	PWM_init();

	while (1)
	{
		PWM_freq_switch();
		PWM_set(freq, duty_cycle);
#ifdef DEBUG
		Serial.print(String(ICR1H, BIN) + " " + String(ICR1L, BIN) + " " + String(freq, BIN) + " | ");
		Serial.print(String(OCR1AH, BIN) + " " + String(OCR1AL, BIN) + " " + String(duty_cycle, BIN));
#endif
		Serial.print(String(freq_switch_state, BIN) + " " + String(PINB, BIN));
		Serial.println();
	}
}