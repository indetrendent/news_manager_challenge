#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_LEN 1000
#define MAX_NEWS_LEN 900
#define MAX_NEWS_CNT 50

#define READ_NEWS 1
#define WRITE_NEWS 2
#define EDIT_NEWS 3
#define EXIT 4


char g_buf[MAX_BUF_LEN];
char g_news[MAX_NEWS_CNT][MAX_NEWS_LEN];


void print_menu()
{
	printf("\nPlease input the command:");
	printf("\n1) Read news");
	printf("\n2) Write news");
	printf("\n3) Edit news");
	printf("\n4) Exit");
	printf("\nChoice: ");
}


void read_news()
{
	int index;
	char news[MAX_NEWS_LEN];

	/* Read message index */
	printf("\nPlease input the news index: ");
	if(fgets(g_buf, sizeof(g_buf), stdin) == NULL)
	{
		printf("Nothing has been read!");
		return;
	}
	index = atoi(g_buf);

	if(index > MAX_NEWS_CNT)
	{
		printf("Incorrect index!");
		return;
	}

	/* Print the message */
	strncpy(news, g_news[index], strlen(g_news[index]));

	printf("The news are: %s\n", news);
}


void write_news()
{
	int index;
	char news[MAX_NEWS_LEN];

	/* Read message index */
	printf("\nPlease input the news index: ");
	if(fgets(g_buf, sizeof(g_buf), stdin) == NULL)
	{
		printf("Nothing has been read!");
		return;	
	}
	index = atoi(g_buf);

	/* Write message */
	printf("Message: ");
	if(fgets(news, MAX_BUF_LEN, stdin) == NULL)
	{
		printf("Nothing has been read!");
		return;
	}

	strncpy(g_news[index], news, strlen(news));
	printf("Message stored!\n");
}


void edit_news()
{
	int index, offset;
	int news_len;
	char news[MAX_NEWS_LEN];
	char *news2 = malloc(MAX_NEWS_LEN);

	/* Read news index */
	printf("\nPlease input the news index: ");
	if(fgets(g_buf, sizeof(g_buf), stdin) == NULL)
	{
		printf("Nothing has been read!");
		return;
	}
	index = atoi(g_buf);

	if(index > MAX_NEWS_CNT)
	{
		printf("Incorrect index!");
		return;
	}

	/* Copy news to local stack buffer */
	strncpy(news, g_news[index], strlen(g_news[index]));

	/* Read news offset */
	printf("Please input the news offset: ");
	if(fgets(g_buf, sizeof(g_buf), stdin) == NULL)
	{
		printf("Nothing has been read!");
		return;
	}
	offset = atoi(g_buf);

	news_len = strlen(news);
	if(offset > news_len)
	{
		printf("Incorrect offset!");
		return;
	}

	/* Write new news*/
	printf("Message: ");
	if(fgets(news2, MAX_BUF_LEN, stdin) == NULL)
	{
		printf("Nothing has been read!");
		return;
	}

	strncpy(news + offset, news2, strlen(news2));
	strncpy(g_news[index], news, strlen(news));

	printf("Edited message was stored\n");
}


void main(int argc, char const *argv[])
{
	int exit_flag = 0;
	int command = 0;

	while(!exit_flag)
	{
		/* Print welcome message */
		printf("\n*** Welcome to the news server system ***");
		print_menu();

		/* Read command and execute handler */
		fgets(g_buf, sizeof(g_buf), stdin);
		command = atoi(g_buf);

		switch(command)
		{
			case READ_NEWS:
				read_news();
				break;
			case WRITE_NEWS:
				write_news();
				break;
			case EDIT_NEWS:
				edit_news();
				break;
			case EXIT:
				exit_flag = 1;
				break;
			default:
				printf("Wrong command, try again!");
				break;
		}		
	}

	return;
}