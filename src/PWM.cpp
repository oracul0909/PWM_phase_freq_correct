#include <Arduino.h>
#include "PWM.h"
#include "GPIO.h"

#define MAX_DUTY 100 // максимальный коэффициент заполнения (100%)

void PWM_init() // настройка ШИМ Timer1
{
	CLKPR = (1 << CLKPCE); // разрешить изменение предделителя частоты
	CLKPR = 0;			   // установить пределитель 1 и запретить изменения, если внешний кварц 2 МГц

	DDRB = (1 << DDB1); // выход ШИМ (пин D9)

	// Настройка Timer1
	TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (1 << WGM11) | (0 << WGM10); // выход ШИМ OC1A
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (1 << CS10);						  // режим Fast PWM TOP = ICR1 и делителем 256

	// TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);	// выход ШИМ OC1A
	// TCCR1B = (1<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);	// режим Phase and frequency correct PWM Top = ICR1 и делителем 8

	OCR1BH = 0x00;
	OCR1BL = 0x00;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	ICR1H = 0x00;
	ICR1L = 0x00;
	OCR1AH = 0x00;
	OCR1AL = 0x00;
}

void PWM_set(uint16_t frequency, uint16_t duty_cycle) // задать частоту и скважность
{
	ICR1H = frequency >> 8;
	ICR1L = frequency & 0x00FF;
	OCR1AH = ((frequency * duty_cycle) / MAX_DUTY) >> 8;
	OCR1AL = ((frequency * duty_cycle) / MAX_DUTY) & 0x00FF;
}

uint8_t freq_switch_state;

void PWM_freq_switch()
{
	if (freq_switch_state != PIND)
	{
		if (!(PIND & ((1 << SWITCH_PIN))))
		{
			TCCR1B = 0x00;
			TCCR1B = TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10); // режим Fast PWM TOP = ICR1 и делителем 1024
		}
		if (PIND & ((1 << SWITCH_PIN)))
		{
			TCCR1B = 0x00;
			TCCR1B = TCCR1B = (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (1 << CS10); // режим Fast PWM TOP = ICR1 и делителем 256
		}
		freq_switch_state = PIND;
	}
}
