#include "diary.h"

user* connexion(user *connecteduser){ //Sign in / Sign up, returns a user
	
	unsigned short connexion;

	printf("1. Sign in\n2. Sign up\n\nChoice : ");

	while(scanf("%hi", &connexion) != 1 || connexion < 1 || connexion > 2){
		getchar(); 
		printf("Unable choice\nPlease choose option 1 or 2 only\nChoice : ");
	}
	getchar();
	
	if(connexion == 1){
		printf("\n");
		int login = connectuser(connecteduser);

		if(login){ //--> if(login == 1)
	 		printf(" === Welcome %s ! ===\n\n", connecteduser->pseudo);
		} 
		else {
	 		printf("Connexion failed\nMaybe you should sign up first\n");
	 		return NULL;
	 	}
	}
	else signup(connecteduser);

	return connecteduser;
}

int menu(){ //User options, returns chosen option
	int option;

	printf("\t[1] Write in my diary \n");
	printf("\t[2] See all my posts\n");
	printf("\t[3] See all posts\n");
	printf("\t[4] See all posts sorted by day (from the oldest to the most recent)\n");
	printf("\t[5] See all <username> posts\n");
	printf("\t[6] Log out\n\n");
	printf("Choice : ");

	while(scanf("%d", &option) != 1 || option < 1 || option > 6){ //--> while this isn't a number (scanf return 1 if it is a number), or while the number isn't correct..
		getchar();
		printf("This is not an option\nPlease choose a valid opiton\nChoice : ");
	}
	printf("\n\n\n\n");
	return option;
}

void useraction(user *writer, int option){ //Launch action depending on what the user choose
	char pseudo[20];

	switch(option){
		case 1 : 
			newpost(writer);
		break;

		case 2:
			seeUserPost(writer->pseudo);
		break;

		case 3 :
			seeAllPost();
			getchar();
		break;

		case 4:
			dateOrder();
			getchar();
		break;

		case 5:
			printf("Type the pseudo of the user you want to see the posts\n");
			scanf("%s", pseudo);
			getchar();
			printf("\n\n\n");
			seeUserPost(pseudo);
		break;

		case 6:
			printf("Disconnected\n");
			writer->connect = 0;
		break;

		default:break;
	}
	printf("\n\n\n\n");
}      
