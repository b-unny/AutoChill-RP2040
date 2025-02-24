#include"lib.h"

int main()
{
	stdio_init_all();
	inicializar_IO();
	
	while(true)
	{
		obter_peso();
		main_loop(); 
		inspeciona();
	}
}
