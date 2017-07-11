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
	char conf[500] = "";
	
	/*struc*/post writerpost;
	writerpost.creator = writer;

	time_t mtime;
	time(&mtime);
	struct tm *lt = localtime(&mtime);

	writerpost.day = (int)lt->tm_mday;
	writerpost.month = (int)lt->tm_mon+1;
	writerpost.year =  (int)lt->tm_year+1900;

	fprintf(postfile, "Pseudo : %s Date : %d/%d/%d Heure : %d:%d\n", writer->pseudo, writerpost.day, writerpost.month, writerpost.year, (int)lt->tm_hour, (int)lt->tm_min);

	printf("Welcome in your personal editor\nHere you can write anything you want your secret will stay secret\n");
	printf("You can start writing and type CTRL + X when finished\n");

	clean_stdin();

	while(*content != 24){
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

void seeUserPost(char *wpseudo){
	char *pseudo = malloc(20*sizeof(char));
	char c;

	FILE *postfile = fopen("post.txt", "r");
	int line = 0, count = 0;
	int cmp;

	fseek(postfile, 0, SEEK_END);
	int eof = ftell(postfile);

	rewind(postfile);

	while(ftell(postfile) < eof){
		do{
			fscanf(postfile, "%s", pseudo);
			cmp = strcmp(wpseudo, pseudo);
		}while(cmp != 0 && ftell(postfile) < eof-10);

		if(cmp == 0)
			count++;
		
		fseek(postfile, -(strlen(pseudo)), SEEK_CUR);
		fseek(postfile, -9, SEEK_CUR);
		
		c = 'c';
		
		if(cmp == 0)
			while(c != 24){
				c = fgetc(postfile);
				if(c == 24)
					continue;
				printf("%c", c);
		}
		
		fseek(postfile, 13, SEEK_CUR);
		printf("\n\n\n\n");
	}
	if(count == 0)
		printf("No post founded\n");

	printf("Press enter to continue\n");
	free(pseudo);
	fclose(postfile);
	getchar();
}
