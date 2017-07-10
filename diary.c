#include "diary.h"

user* connexion(user *connecteduser){
	
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
		if(login)
	 		printf(" === Welcome %s ! ===\n\n", connecteduser->pseudo);
	 	else {
	 		printf("Connexion failed\nMaybe you should sign up first\n");

	 		return NULL;
	 	}
	}
	else signup(connecteduser);

	return connecteduser;
}

int menu(){
	int option;

	printf("\t[1] Write in my diary \n");
	printf("\t[2] See all my post\n");
	printf("\t[3] See all posts\n");
	printf("\t[4] Log out\n");
	printf("Choice : ");
	while(scanf("%d", &option) != 1|| option < 1 || option > 4){
		getchar();
		printf("This is not an option\nPlease choose a valid opiton\nChoice : ");
	}
	return option;
}

void useraction(user *writer, int option){
	switch(option){
		case 1 : 
			newpost(writer);
		break;

		case 2:
			seeUserPost(writer);
		break;

		case 3 :
			seeAllPost();
		break;

		case 4:
			printf("Disconnected\n");
			writer->connect = 0;
		break;

		default:
			printf("Unable choice\n");
		break;
	}
	printf("\n\n\n\n");
}                                                            