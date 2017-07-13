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

int availableuser(const char *newpseudo);
void createuser(user* newuser);
int connectuser(user *newuser);
int isuser();
void registeruser();
void signup(user *newuser);
