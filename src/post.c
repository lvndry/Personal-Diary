#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "post.h"

void clean_stdin(){ //clean the buffer
    int c;
 
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int check(int i, struct tm *dates, struct tm ptime){
	if(dates[i].tm_year == ptime.tm_year && dates[i].tm_mon == ptime.tm_mon && dates[i].tm_mday == ptime.tm_mday && dates[i].tm_hour == ptime.tm_hour && dates[i].tm_min == ptime.tm_min)
		return 1;
	return 0;
}

int compareDates(const void *d1, const void *d2){
	struct tm date_1 = *(const struct tm *)d1;
	struct tm date_2 = *(const struct tm *)d2;

	double d = difftime(mktime(&date_1), mktime(&date_2));

	return (d < 0) - (d > 0);
}

void dateOrder(){ //print the post sorted by date

	FILE *postfile = fopen("post.txt", "r");

	int numofpost = getNumOfPost(postfile);
	struct tm dates[numofpost];
	int pseudolen = 0, i = 0;

	struct tm ptime;

	char *elt = malloc(5*sizeof(char));
	char *pseudo = malloc(20*sizeof(char));
	char *dref = "Date"; //Word to find to get the date
	char *href = "Heure"; //Word to find to get hour
	char c = 'c';
	
	rewind(postfile);

	while(!feof(postfile)){
			
		fscanf(postfile, "%s", elt);

		if(strcmp(elt, dref) == 0){
			fseek(postfile, 3, SEEK_CUR);
			fscanf(postfile, "%d/%d/%d", (int)&(ptime.tm_mday), (int)&(ptime.tm_mon), (int)&(ptime.tm_year));

			dates[i].tm_year = ptime.tm_year;
			dates[i].tm_mon = ptime.tm_mon;
			dates[i].tm_mday = ptime.tm_mday;
		}

		if(strcmp(elt, href) == 0){
			fseek(postfile, 3, SEEK_CUR);
			fscanf(postfile, "%d:%d", (int)&(ptime.tm_hour), (int)&(ptime.tm_min));

			dates[i].tm_hour = ptime.tm_hour;
			dates[i++].tm_min = ptime.tm_min;
		}
	}

	size_t num_dates = sizeof(dates)/sizeof(*dates);
	qsort(dates, num_dates, sizeof(*dates), compareDates);

	for(int i = 0; i < numofpost; i++){
		c = 'c';
		rewind(postfile);
		
		while(!feof(postfile) && c != 24){ //We read the file until the end c is equal to 24 only if a already founded the wanted post

			fscanf(postfile, "%s", elt);
			
			if(strcmp(elt, "Pseudo") == 0){
				fseek(postfile, 3, SEEK_CUR);
				fscanf(postfile, "%s", pseudo);
				pseudolen = strlen(pseudo);
			}

			if(strcmp(elt, dref) == 0){
				fseek(postfile, 3, SEEK_CUR);
				fscanf(postfile, "%d/%d/%d", (time_t)&(ptime.tm_mday), (time_t)&(ptime.tm_mon), (time_t)&(ptime.tm_year));
			}

			if(strcmp(elt, href) == 0){
				fseek(postfile, 3, SEEK_CUR);
				fscanf(postfile, "%d:%d", (time_t)&(ptime.tm_hour), (time_t)&(ptime.tm_min));
			}

			if(check(i, dates, ptime)){ //check look if the member of struct are the same in dates ans ptime
				fseek(postfile, -40, SEEK_CUR);
				fseek(postfile, -pseudolen, SEEK_CUR);
				
				while(c != 24){
					c = fgetc(postfile);
					
					if(c == 24)
						continue;
					printf("%c", c);
				}
			}

			if(ftell(postfile)+15 < feof(postfile)) //If it is not the last post
				fseek(postfile, 15, SEEK_CUR); //I go to next post*
		}
		printf("\n\n\n\n");
	}
	
	fclose(postfile);
	printf("\n\n");	
}

int getNumOfPost(FILE *postfile){ //returns the number of post
	char c;
	int count = 0;

	while(!feof(postfile)){
		c = fgetc(postfile);
		
		if(c == 24)
			count++;
	}

	return count;
}

void newpost(user *writer){ //create a new post
	FILE *postfile = fopen("post.txt", "a+");
	char content[150] = "";
	char conf[500] = "";
	
	post writerpost; //struct
	writerpost.creator = writer;

	time_t mtime;                       
	time(&mtime);
	struct tm *lt = localtime(&mtime); //returns the localtime

	writerpost.day = (int)lt->tm_mday;
	writerpost.month = (int)lt->tm_mon+1;
	writerpost.year =  (int)lt->tm_year+1900;

	fprintf(postfile, "Pseudo : %s Date : %d/%d/%d Heure : %d:%d\n", writer->pseudo, writerpost.day, writerpost.month, writerpost.year, (int)lt->tm_hour, (int)lt->tm_min);

	printf("Welcome in your personal editor\nHere you can write anything you want your secret will stay secret\n");
	printf("You can start writing and press CTRL + X on a new line when finished\n");

	clean_stdin();

	while(*content != 24){ //Enable user to write until he types CTRL + X
		fgets(content, sizeof(content), stdin);
		strcat(conf, content);
	}

	writerpost.content = conf;
	
	conf[strlen(conf)-2] = '\0';  /*also CTRL + X is not printed in the post*/
	
	printf("\n\n\n");
	printf("Your post : \n%s\n", conf);
	fprintf(postfile, "Post :\n%s\n-- END --\n\n\n\n\n", writerpost.content);
	
	fclose(postfile);
}

void seeAllPost(){  //print all posts
	FILE *postfile = fopen("post.txt", "r");

	char *line;
	char c;
	size_t len = 0;

	rewind(postfile);

	while(!feof(postfile)){
		c = fgetc(postfile);
		putchar(c);
	}

	fclose(postfile);
	getchar();
}

void seeUserPost(char *wpseudo){ //prit user a particular user posts
	FILE *postfile = fopen("post.txt", "r");

	char *pseudo = malloc(20*sizeof(char));
	char c = 'c';

	int line = 0, count = 0;
	int cmp;

	rewind(postfile);

	while(!feof(postfile)){
		
		fscanf(postfile, "%s", pseudo);
		cmp = strcmp(wpseudo, pseudo);
		
		if(cmp == 0){
			fseek(postfile, -(strlen(pseudo)), SEEK_CUR);
			fseek(postfile, -9, SEEK_CUR);
			count++;
			
			if(feof(postfile))
				break;

		    readPost(postfile);

			c = 'c'; //Otherwise c will be equal to 24 next loop

			printf("\n\n\n\n");

			if(ftell(postfile)+13 < feof(postfile)) //If it is not the last post
				fseek(postfile, 13, SEEK_CUR); //I go to next post
		}	
	}

	if(count == 0)
		printf("No post founded\n");
	else {
		printf("Press enter to continue\n");
		getchar();
	}
	
	free(pseudo);
	fclose(postfile);
	getchar();
}

void readPost(FILE *postfile){
	char c = 'c';

	while(c != 24){
		c = fgetc(postfile);
		
		if(c == 24)
			continue;
		printf("%c", c);
	}
}
