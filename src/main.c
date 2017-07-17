#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

#include "diary.h"

#ifdef _WIN32	//If in windows
	#define CLEAR system("cls");
#else 
	#define CLEAR system("clear");	//If linux/Mac
#endif

int main(int argc, char const *argv[])
{
	user writer;
	user* writerptr = NULL;
	char c;
	
	do{
		CLEAR
		
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
		
		printf("Press q to quit and Enter to reconnect\n");
		c = getchar();
		getchar();
	}while(c != 'q' && c != 'Q');
	printf("See you soon !\n");
	return 0;
}
