#include <stdio.h>  
#include "mmemory.h"
void main(void)                
{
	VA va1;
	_init(1, 10);
	_malloc(&va1, 5);
	VA va2;
	_malloc(&va2, 2);
	VA va3;
	_malloc(&va3, 3);
	//_free(va2);
	//char* buf = 'ddd';
	//_write(&va1, buf, 3);
	print_list();
	//printf("%c", va);   

	system("pause");
}