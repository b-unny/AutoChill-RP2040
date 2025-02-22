#include"lib.h"

int main()
{
	stdio_init_all();
	inicializar_IO();
	
	while(true)
	{
		obter_peso();
		// obter temperatura():  aqui esta sendo substituida pelos 
		// push buttons que estao sendo tratatos por IRQ
		main_loop(); 
	}
}
