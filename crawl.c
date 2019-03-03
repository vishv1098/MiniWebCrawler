#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node
{
	char *data;
	struct node *next;
}node;
node *top = NULL;
void push(char *links);
void display(char *freq);
void pop();
void link(char *seed);
void open();
int wordfreq(char *word,char *linker);
int main()
{
	char word[30];
	int ch=1;
	char linker[15] = "Homepage.html";
	link(linker);
	printf("****************************************************************\n");
	printf("           Mini Project - Mini Web Crawler\n");
	printf("****************************************************************\n");
	printf("This program helps you search for a word in certain webpages.\n");
	while(ch==1)
    {
     printf("Please enter a word:");
	 scanf("%s",word);
	 printf("\n");
     display(word);
     open();
     printf("Would you like to continue searching for a different word?(1.Yes/2.No)");
     scanf("%d",&ch);
     system("cls");
    }
      while(top!=NULL)
     {
        pop();
     }
	return 0;
}
void push(char *links)
{
	node *temp;
	temp = (node*)malloc(sizeof(node));
	temp->data = (char *)malloc(sizeof(char)*strlen(links));
	temp->data = links;
	if(top == NULL)
		temp->next = NULL;
	else
		temp->next = top;
	top = temp;

}
void pop()
{
	node *temp = top;
	top = temp->next;
	free(temp);
}
void display(char *freq)
{
    int count=0;
    node *temp=top;
    while(temp!=NULL)
    {
     count+=1;
	 printf("%d.%s - %d \n",count,temp->data,wordfreq(freq,temp->data));
	 printf("\n");
	 temp = temp->next;
    }
}
int wordfreq(char *word,char *linker)
{
	int num =0;
	char string[100]={0};
	FILE *html_file = fopen(linker,"r");
	if (html_file == NULL)
	{
    	printf("Error file missing\n");
    	exit(0);
	}
	while((fgets(string,sizeof(string),html_file)) != NULL)
	{
    	if((strstr(string,word))!=NULL)
   		{
    		num++;
    	}
	}
	return num;
}
void link(char *seed)
{
	int num =0,start = 0,end = 0,i=0,j=0;
	char *word,string[100]={0},*s,*pos,*pos2;
	s = &string[0];
	FILE *html_file = fopen(seed,"r");
	if (html_file == NULL)
	{
    	printf("Error file missing\n");
	}
	while((fgets(string,sizeof(string),html_file)) != NULL)
	{
    	if((strstr(string,"<a href"))!= NULL)
    	{
	    	pos = strstr(string,"<a href");
    		pos2 = strchr(pos+10,'"');
    		start = pos - s + 9;
    		end = pos2 - s;
    		j = start;
    		word = (char*)malloc(end);
    		while(j!=end)
    		{
    			word[i]=string[j];
    			j++;
    			i++;
			}
			word[i]='\0';
			i=0;
			push(word);
	}
  }
	 fclose(html_file);
}
void open()
{
    int ch;
    node *temp=top;
 repeat: printf("Enter number beside the website you'd would like to open:");
    scanf("%d",&ch);
    if(ch>0 && ch<10)
    {
     for(int i=1;i<ch;i++)
     {
       temp = temp->next;
     }
     system(temp->data);
    }
    else
    {
     printf("Invalid Choice please try again.\n");
     goto repeat;
    }
}
