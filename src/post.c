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

void insert(int member, unsigned int arr[], int size)
{
    int i,j;

    for(i=0;i<size;i++)
    {
        if(member< arr[i])
        {
            for( j=0;j<size-i;j++)
            {
                arr[size-j]=arr[size-j-1];
            }
            arr[i]=member;
            break;
         }
    }     
}

void insertsort(unsigned int arr[], int size)
{
    int i=1, member;

    for(i=1; i < size; i++){
    	member = arr[i];
    	insert(member,arr,i);
    }
}

int getNumOfPost(FILE *postfile){
	char c;
	int count = 0;

	while(!feof(postfile)){
		c = fgetc(postfile);
		
		if(c == 24)
			count++;
	}

	return count;
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

void readPost(FILE *postfile){
	char c = 'c';

	while(c != 24){
		c = 'c';
		c = fgetc(postfile);
		
		if(c == 24)
			continue;
		printf("%c", c);
	}
}

void seeUserPost(char *wpseudo){
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

/*
int gateDates(FILE *postfile){


		free(elt);
	
	else return 0;

	return tabdate;
}
*/
void dateOrder(){

	FILE *postfile = fopen("post.txt", "r");
	unsigned int numofpost = getNumOfPost(postfile);
	unsigned int datetab[numofpost];
	unsigned int tabdate;
	unsigned int jour, mois, annee, heure, minutes, i = 0;
	char* elt = malloc(5*sizeof(char));
	char* dref = "Date";
	char* href = "Heure";
	char c = 'c';

	char *pseudo = malloc(20*sizeof(char));
	int pseudolen = 0;

	rewind(postfile);

	while(!feof(postfile)){
			
		fscanf(postfile, "%s", elt);

		if(strcmp(elt, dref) == 0){
			fseek(postfile, 3, SEEK_CUR);
			fscanf(postfile, "%u/%u/%u", &jour, &mois, &annee);
		}

		if(strcmp(elt, href) == 0){
			fseek(postfile, 3, SEEK_CUR);
			fscanf(postfile, "%u:%u", &heure, &minutes);

			tabdate = annee;
			tabdate += mois;
			tabdate += jour;
			tabdate += heure;
			tabdate += minutes;
			
			datetab[i++] = tabdate;

		}
	}

	int tablen =  sizeof(datetab)/sizeof(datetab[0]);
	
	insertsort(datetab, tablen);
	//printf("Tablen : %d\n", tablen);
	for(int i = 0; i < tablen; i++)
		printf("%d\n", datetab[i]);

	/*for(int i = 0; i < tablen; i++){

		rewind(postfile);
		printf("%d\n", datetab[i]);

		while(!feof(postfile)){

			fscanf(postfile, "%s", elt);

			if(strcmp(elt, "Pseudo") == 0){
				fseek(postfile, 3, SEEK_CUR);
				fscanf(postfile, "%s", elt);
	
				pseudolen = strlen(elt);
			}

			//fscanf(postfile, "%s", elt);

			if(strcmp(elt, dref) == 0){
				fseek(postfile, 3, SEEK_CUR);
				fscanf(postfile, "%u/%u/%u", &jour, &mois, &annee);
			}

			if(strcmp(elt, href) == 0){
				fseek(postfile, 3, SEEK_CUR);
				fscanf(postfile, "%u:%u", &heure, &minutes);

				tabdate = annee;
				tabdate += mois;
				tabdate += jour;
				tabdate += heure;
				tabdate += minutes;
			}

			if(tabdate == datetab[i]){
				printf("tabdate : %d datetab[i] : %d\n", tabdate, datetab[i]);
				//printf("ftell : %d\n", ftell(postfile));
				fseek(postfile, -39, SEEK_CUR);
				fseek(postfile, -pseudolen, SEEK_CUR);
				//printf("ftell aftfseek : %d\n", ftell(postfile));
				
				while(c != 24){
					c = fgetc(postfile);
		
					if(c == 24){
						printf("CONTINUE BATARD\n");
						continue;
					}
					printf("%c", c);
				}
				c = 'c';
				//readPost(postfile);
			}
		}
	}
*/
	free(datetab);
	fclose(postfile);	
}