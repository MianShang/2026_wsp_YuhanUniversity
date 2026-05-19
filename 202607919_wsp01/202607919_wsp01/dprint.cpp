#include "dprint.h"


void dprint(
	void*				buf__,
	int					len__
	)
{
	char* char_ptr = (char*)buf__;
	char* value_ptr = (char*)buf__;
	int count = len__/16;
	
	
	if(len__%16 != 0)
	{
		count += 1;
	}
	

	printf("Offset(h) | ");
	for (int i = 0; i < 16; i++) 
	{
		printf("%02X ", i);
	}

	printf("| String\n");

	for(int i =0; i < 95; i++)
	{
		printf("-");
	}

	printf("\n");
	
	for (int i = 0; i < count; i++)
	{
		
		printf(" %08X | ", i); 

		
		
		for (int j = 0; j < 16; j++) {
			
			if(strcmp("\0",value_ptr) != 0)
			{
				printf("%02X ", *value_ptr++);
			}
			else 
			{
				printf("%02X ", *value_ptr);
			}
		}

		printf("| ");

		for (int j = 0; j < 16; j++) {

			if (strcmp("\0", char_ptr) != 0)
			{
				printf("%c ", *char_ptr++);
			}
			else 
			{
				printf("%c ", *char_ptr);
			}
		}
		
		
		printf("\n");

	}
}