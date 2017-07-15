#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

typedef struct
{
	char *name;
	char *forename;
	char *pseudo;
	char *password;
	char sexe;
	int age;
	int connect;
}user;

int availableuser(const char *newpseudo);	//Check if pseudo already exists
int connectuser(user *newuser);	//Connect the user, returns 0 if the user can't be connected
void createuser(user *newuser);	//Create a new user
int isuser(const char* pseudo, const char* password); //Check if the user exists by checking the pseudo and password
void registeruser();  //register a new user
void signup(user *newuser); //Sign up a new user and connect him
