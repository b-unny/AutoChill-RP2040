#ifndef LIB_H
#define LIB_H

#include"pico/stdlib.h"
#include"hardware/adc.h"
#include"hardware/pwm.h"
#include"hardware/pio.h"
#include"ws2812.pio.h"

#define BUTTON_A 5    // temperatura --
#define BUTTON_B 6    // temperatura ++
#define ADC_PIN 26    // eixo Y do joystick
#define PWM_PIN 12    // led azul (servo)
#define MATRIX_PIN 7  

void inicializar_IO();

void buttons_callback(uint pino, uint32_t events);

void obter_peso();

void config_servo(int nivel);

static uint32_t urgb_u32(uint8_t red, uint8_t green, uint8_t blue);

static void put_pixel(uint32_t pixel);

void atualizar_matriz(int nivel);

void main_loop();


#endif
