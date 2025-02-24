#include"lib.h"

const uint16_t wrap = 4096;
const float clkdiv = 4.0;
volatile int8_t temp = 0;
volatile uint8_t peso = 0;
const uint8_t peso_max = 10;
volatile uint32_t ultimo_tempo = 0;


void inicializar_IO()
{
	for(int i=5; i<7; i++)
	{
		gpio_init(i);
		gpio_set_dir(i, GPIO_IN);
		gpio_pull_up(i);
		gpio_set_irq_enabled_with_callback(i, GPIO_IRQ_EDGE_FALL, true, &buttons_callback);
	} // inicializa BUTTON_A e BUTTON_B
	
	adc_init();
	adc_gpio_init(ADC_PIN);
	
	gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
	uint slice = pwm_gpio_to_slice_num(PWM_PIN);
	pwm_set_clkdiv(slice, clkdiv);
	pwm_set_wrap(slice, wrap);
	pwm_set_enabled(slice, true);

	PIO pio = pio0;
	int sm = 0;
	uint offset = pio_add_program(pio, &ws2812_program);
	ws2812_program_init(pio, sm, offset, MATRIX_PIN, 800000, false);
}

void buttons_callback(uint pino, uint32_t events)
{ 
	uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

	if(tempo_atual - ultimo_tempo >= DEBOUNCE_TIME)
	{ 
		(temp -10 && temp < 40) ? ((pino == BUTTON_A) ? temp-=5 : temp+=5) : (void)0; 
		ultimo_tempo = tempo_atual;
	}
}

void obter_peso()
{
	adc_select_input(0);
	peso = (adc_read() / 4095) * peso_max;
}

void config_servo(int nivel)
{
	float pulso = (float)(1.0+(nivel-1)*0.2); 
	uint16_t duty = (uint16_t)((pulso/20.0)*4096);
	pwm_set_gpio_level(PWM_PIN, duty);
    	printf("Paasando por config_servo: pulso = %f, duty = %d\n", pulso, duty);
}

void main_loop()
{
    int matrizNiveis[4][3] = {
        {1, 2, 3}, // temp < 10
        {2, 3, 4}, // 10 < temp < 20
        {4, 5, 6}, // 20 < temp < 30
        {5, 6, 6}  // 30 < temp < 40
    };

    int faixaTemp = (temp < 10) ? 0 :
                    (temp < 20) ? 1 :
                    (temp < 30) ? 2 : 3;

    int faixaPeso = (peso > 0 && peso < 4) ? 0 :
                    (peso > 3 && peso < 7) ? 1 :
                    (peso > 6 && peso < 11) ? 2 : -1;

    int nivel = matrizNiveis[faixaTemp][faixaPeso];
    
    if(nivel != -1)
    { 
        config_servo(nivel);
	atualizar_matriz(nivel-1);
    }
}

static uint32_t urgb_u32(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 8) | (green << 16) | blue;
}

void put_pixel(uint32_t pixel)
{
	pio_sm_put_blocking(pio0, 0, pixel << 8u);
}

void atualizar_matriz(int nivel)
{

	static const uint8_t numeros[6][25]=
	{
	    { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0 }, // 1
            { 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0 }, // 2
            { 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0 }, // 3
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 }, // 4
            { 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0 }, // 5
            { 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0 }, // 6
        };
	
	uint32_t rosa = urgb_u32(64, 50, 55);
    
	for(int i=0; i < 25; i++)
		put_pixel((numeros[nivel-1][i]) ? rosa : 0);

}

void inspeciona()
{
	printf("Temperatura: %dºC\n", temp);
	printf("Peso: %dkg \n\n", peso);
	sleep_ms(1000);

}

