#include "user.h"


typedef struct 
{
	user *creator;
	char *content;
	int day;
	int month;
	int year;
}post;

void clean_stdin(void);
void newpost(user *writer);
void seeAllPost();
void seeUserPost(char* wpseudo);
