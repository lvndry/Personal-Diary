#include <stdio.h>

#include "post.h"

user* connexion(user *writer);	//Sign in / Sign up
int menu();	//User options, returns chosen option
void useraction(user *writer, int option);	//Launch action depending on what the user choose
