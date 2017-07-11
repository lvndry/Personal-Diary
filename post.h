#include "user.h"


typedef struct 
{
	user *creator;
	char *content;
	time_t date;
}post;

void clean_stdin(void);
void newpost(user *writer);
void seeAllPost();
void seeUserPost(char* wpseudo);
