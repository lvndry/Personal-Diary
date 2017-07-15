#include "user.h"

int availableuser(const char *pseudo){ //Check if pseudo already exists
	char taken[20],  takenpass[20], username[20];

	int age;
	FILE* pseudofile = fopen("users.txt", "r");

	while(!feof(pseudofile)){
		fscanf(pseudofile, "%s %s %s %d", taken, takenpass, username, &age);
		
		if(strcmp(pseudo, taken) == 0){
			fclose(pseudofile);
			return 0;
		}
	}

	fclose(pseudofile);
	return 1;
}

int connectuser(user *connecteduser){ //Connect the user
	char pseudo[20], password[20];
	connecteduser->pseudo = malloc(20*sizeof(char));
	connecteduser->password = malloc(20*sizeof(char));
	

	printf("Pseudo : ");
	scanf("%s", pseudo);
	getchar();
	printf("Password : ");
	scanf("%s", password);
	getchar();
	printf("\n\n\n\n");
	
	if(isuser(pseudo, password)){
		strcpy(connecteduser->pseudo, pseudo);
		strcpy(connecteduser->password, password);
		connecteduser->connect = 1;

		return 1;
	}

	else return 0;
}

void createuser(user *newuser){ //Create a new user

	newuser->name = (char *)malloc(20*sizeof(char));
	newuser->forename = (char *)malloc(20*sizeof(char));
	newuser->pseudo = (char *)malloc(20*sizeof(char));
	char confirm[20];

	printf("\n");
	printf("Sign in : \n");
	printf("Sexe (M for male, F for female, O for other) : ");
	scanf("%c", &(newuser->sexe));
	getchar();

	while(toupper(newuser->sexe) != 'M' && toupper(newuser->sexe) != 'F' && toupper(newuser->sexe) != 'O' ){
		printf("Non valid sexe\nSexe : ");
		scanf("%c", &(newuser->sexe));
		getchar();
	}

	printf("Age : ");

	while(scanf("%d", &(newuser->age)) != 1){
		printf("Non valid age\nAge : ");
		getchar();
	}

	printf("Forename : ");
	scanf("%s", newuser->forename);
	printf("Name : ");
	scanf("%s", newuser->name);
	getchar();
	printf("Pseudo : ", newuser->pseudo);
	scanf("%s", newuser->pseudo);
	getchar();

	while(!availableuser(newuser->pseudo)){
		printf("Pseudo already taken\nPlease choose an other one : ");
		scanf("%s", newuser->pseudo);
		getchar();
	}
	
	printf("Password : ");
	scanf("%s", newuser->password);
	getchar();
	printf("Confirm password : ");
	scanf("%s", &confirm);
	confirm[strlen(confirm)] = '\0';

	while(strcmp(newuser->password, confirm) != 0){
		printf("The passwords are not the same\nPlease rewrite them \nPassword : ");
		scanf("%s", newuser->password);
		getchar();
		printf("Confirm : \n");
		scanf("%s", confirm);
		getchar();
	}
}

int isuser(const char* pseudo, const char* password){ //Check if the user exists 
	char takenpseudo[20], takenpass[20];

	FILE* pseudofile = fopen("users.txt", "r");

	while(!feof(pseudofile)){
		fscanf(pseudofile, "%s %s", takenpseudo, takenpass);
		if(strcmp(pseudo, takenpseudo) == 0 && strcmp(password, takenpass) == 0){
			fclose(pseudofile);
			return 1;
		}
	}

	fclose(pseudofile);
	return 0;
}

void registeruser(user *newuser){ //register a new user
	FILE *pseudo = fopen("users.txt", "a+");

	fprintf(pseudo, "%s %s %s %d\n", newuser->pseudo, newuser->password, newuser->forename, newuser->age);
}   

void signup(user *newuser){ //Sign up a new user and connect him
	createuser(newuser);
	registeruser(newuser);
	newuser->connect = 1;
}
    