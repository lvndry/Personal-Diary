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
int getNumOfPost(FILE *postfile);
void newpost(user *writer);
void seeAllPost();
void seeUserPost(char* wpseudo);
int getNumOfPost(FILE *postfile);
void readPost(FILE *postfile);
void dateOrder();
void sort(int n, int m, int array[m][n]);
void insertsort(unsigned int arr[], int size);
