#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "post.h"

void clean_stdin(void)
{
    int c;
 
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void newpost(user *writer){
	FILE *postfile = fopen("post.txt", "a+");
	char content[150] = "";
	char post[500] = "";
	
	time_t mtime;
	time(&mtime);
	struct tm *lt = localtime(&mtime);

	fprintf(postfile, "Pseudo : %s Date : %d/%d/%d Heure : %d:%d\n", writer->pseudo, (int)lt->tm_mday, (int)lt->tm_mon+1, (int)lt->tm_year+1900, (int)lt->tm_hour, (int)lt->tm_min);

	printf("Welcome in your personal editor\nHere you can write anything you want your secret will stay secret\n");
	printf("You can start writing and type CTRL + X when finished\n");

	clean_stdin();

	while(*content != 24){
		fgets(content, sizeof content, stdin);
		strcat(post, content);
	}

	post[strlen(post)-2] = '\0';  /*also CTRL + X is not printed in the post*/
	printf("\n\n\n");
	printf("Your post : \n%s\n", post);
	fprintf(postfile, "Post :\n%s\n-- END --\n\n\n\n\n", post);
	
	fclose(postfile);
}

void seeAllPost(){
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

void seeUserPost(user *writer){
	char *pseudo = malloc(20*sizeof(char));
	char c;

	FILE *postfile = fopen("post.txt", "r");
	int line = 0, fresult = 0;

	fseek(postfile, 0, SEEK_END);
	int eof = ftell(postfile);
	
	rewind(postfile);

	while(ftell(postfile) < eof && fresult == 0){
		do{
			fscanf(postfile, "%s", pseudo);
			printf("%s\n", pseudo);
		}while(strcmp(writer->pseudo, pseudo) != 0 && ftell(postfile) < eof);

		fseek(postfile, -(strlen(pseudo)), SEEK_CUR);
		fseek(postfile, -9, SEEK_CUR);
		
		c = 'c';
		
		while(c != 24){
			c = fgetc(postfile);
			if(c == 24)
				continue;
			printf("%c", c);
		}
		
		fseek(postfile, 13, SEEK_CUR);
		printf("\n\n\n\n");
	}
	
	free(pseudo);
	fclose(postfile);
	getchar();
}