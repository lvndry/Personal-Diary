#include <time.h> //for struct tm

#include "user.h"

typedef struct 
{
	user *creator;
	char *content;
	int day;
	int month;
	int year;
}post;

int check(int i, struct tm *dates, struct tm ptime);
int compareDates(const void *d1, const void *d2);
void dateOrder(); //print post sorted by date
int getNumOfPost(FILE *postfile); //returns the number of post
void insertsort(time_t arr[], int size); //Insertion sort 
void newpost(user *writer); //create a new post
void readPost(FILE *postfile); ///read a post
void seeAllPost(); //print all posts
void seeUserPost(char* wpseudo); //print posts of a particular user
