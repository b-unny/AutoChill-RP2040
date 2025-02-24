#include"lib.h"

int main()
{
	stdio_init_all();
	inicializar_IO();
	sleep_ms(2000);
	
	while(true)
	{
		obter_peso();
		main_loop(); 
		inspeciona();
	}
}
