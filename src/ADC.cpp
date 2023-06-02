#include <Arduino.h>
#include "ADC.h"

void ADC_init(void)
{
    cli();
    ADMUX |= ((0<<REFS1)) |((1<<REFS0))                               //опорное напряжение от внешнего питания
    | ((0<<MUX3)) | ((0<<MUX2)) | ((0<<MUX1)) | ((0<<MUX0));          //выход АЦП ADC0 (пин PC0)
    ADCSRA |= ((1<<ADEN))                                             //включить режим АЦП
    | ((1<<ADSC))                                                     //включить преобразование аналогового сигнала в двоичный код
    | ((1<<ADIE))                                                     //включить прерывание АЦП по завершении преобразования
    | ((0<<ADPS2)) | ((1<<ADPS1)) | ((1<<ADPS0));                     //предделитель частоты АЦП: 8
    ADCSRB |= ((0<<ADTS2)) | ((0<<ADTS1)) | ((0<<ADTS0));             //прерывания при работе АЦП: свободный режим
    sei();
}

void ADC_freq_switch(void)
{
    ADMUX = 0b01000000;
}

void ADC_duty_switch(void)
{
    ADMUX = 0b01000001;
}

volatile uint16_t freq;
volatile uint16_t duty_cycle;
bool flag = true;

ISR(ADC_vect)
{
    flag = !flag;
    if(flag)
    {
        ADC_freq_switch();
        freq = int16_t(ADCL) | int16_t(ADCH << 8); // считываем в переменную значение с АЦП
    }
    else
    {
        ADC_duty_switch();
        duty_cycle = map((int16_t(ADCL) | int16_t(ADCH << 8)), 0, 1023, 1, 100);
    }

    ADCSRA |= ((1 << ADSC));
}