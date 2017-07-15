#include "user.h"


typedef struct 
{
	user *creator;
	char *content;
	int day;
	int month;
	int year;
}post;

void clean_stdin(); ///clean stdin buffer
void dateOrder(); //print post sorted by date
int getNumOfPost(FILE *postfile); //returns the number of post
void insertsort(unsigned long long int arr[], int size); //Insertion sort 
void newpost(user *writer); //create a new post
void readPost(FILE *postfile); ///read a post
void seeAllPost(); //print all posts
void seeUserPost(char* wpseudo); //print posts of a particular user
