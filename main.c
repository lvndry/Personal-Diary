#include <stdio.h>
#include <ctype.h>

#include "diary.h"

int main(int argc, char const *argv[])
{
	user writer;
	user* writerptr = NULL;
	char c;
	
	do{
		printf("===== Welcome in your personal diary ===== \n");
		do{
			writerptr = connexion(&writer);
			printf("\n\n\n");
		}while(writerptr == NULL);
	
		printf(" What do you want to do now ? :)\n");

		do{
			int option = menu();
			useraction(writerptr, option);
		}while(writerptr->connect == 1);
		
		getchar();
		
		printf("Press q to quit and Enter to make an other action\n");
		c = getchar();

	}while(toupper(c) != 'Q');
	
	return 0;
}