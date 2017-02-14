#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

struct node
{
	char body;
	int x;
	int y;
	node *next;
};


void display(char ** screen)
 {
 	 Sleep(10);
 	 system("cls");
 	 
 	 for(int i =0 ;i < 20 ;i++)
	  {
 		 for(int j=0 ;j<20;j++)
   		 cout<<screen[i][j];
   		 cout<<endl;
    }
 }

void generate_screen(char **screen,int max,int max1)
{
	int i,j;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		screen[i][j]=' ';
	}
}

node * increase_length(node * head)
 {
 	node * start = head;
 	/*while(temp->next!=NULL)
 	 temp=temp->next;*/
 	node * new_node = new node ;
 	new_node->body='*';
  new_node->x=start->x;
  new_node->y=start->y;
  
  
  new_node->next=start;
  start=new_node;
 	return start;
 }

node * generate_snake(int snakelen)
 {
 	int i;
 	int posx = 5 ,posy = 5;
 	node * snake = new node ;
  node * temp ,*temp1;
  snake->body='*';
  snake->x=posx;
  snake->y=posy;
  temp=snake;
  
  for(i=0;i<snakelen-2;i++)
   {
   	posy++;
   	temp1=new node;
   	temp1->body='*';
    temp1->x=posx;
    temp1->y=posy;
    temp->next=temp1;
    temp=temp->next;
	 }
	 temp1=new node;
   temp1->body='#';
   temp1->x=posx;
   temp1->y=posy;
   temp->next=temp1;
   temp=temp->next;
	 
	 temp->next=NULL;
  
	return snake;
 }

node * insert_snake(node * head , char ** screen)
  {
  	node * temp = head;
  	while(temp!=NULL)
		{
			if(temp->x>19)
			 temp->x=0;
			if(temp->y>19)
			 temp->y=0;
			if(temp->x<0)
			 temp->x=19;
			if(temp->y<0)
			 temp->y=19;
  	  screen[temp->x][temp->y]=temp->body;		
  		temp=temp->next;
		}
    return head;
	}

int check(int x, int y,node * head)
 {
 	node * temp = head ;
 	//node * pos;
 	 while(temp->next!=NULL)
 	  {
 	  	temp=temp->next;
		 }
 	  
 	  
 	if(temp->x==x && temp->y==y)
 	 	return 1;
	return 0;	 
 }

int generate_food(int max, int min ,int& i , int& j , node * head )
  {
  	int x = rand() % 20 + 1, y = rand() % 20 + 1;
  	node * temp = head ;
		while(temp->next!=NULL)
		 {
		 	if( (temp->x==i && temp->y==j) || (x==i && y==j) )
		 	 {
		 	 	 temp = head ;
		 	 	 x = rand() % 20 + 1;
				 y = rand() % 20 + 1;
				}
		 	temp=temp->next;
		 }
		i=x;j=y;
		return 1;
	}
	
int death_check(node * head)
 {
 	int flag=0;
	node * ptr = head;
	node * shead = head ;
	ptr=ptr->next;
	
	while(shead->next!=NULL)
	 shead=shead->next;
	 
	while(ptr->next!=NULL)
	{
		if(shead->x==ptr->x && shead->y==ptr->y)
		{
			flag=1;
			break;
		}
		ptr=ptr->next;
	}
	return flag;
 }

int update_food(char **screen ,int x ,int y)
  {
  	screen[x][y]='F';
	}

void snake_move(char **screen ,node * head)
 {
 	int static old=0;
 	node *temp,*temp1;
 	int foodx=0,foody=1;
 	   
			int n=6;
			while(n!=5)
			 {
			 	if(kbhit())
			 	n=getch()-'0';
			 	Sleep(200);
			 	if(n==6)
			 	 {
			 	 	 temp=head;
					 temp1=temp->next;
	    	   while(temp->next!=NULL)
						{
				     temp->x=temp1->x;
				     temp->y=temp1->y;
				     temp=temp->next;
				     temp1=temp1->next;
			      }
			      temp->y+=1;
				}

			 	if(n==8)
			 	 {
			 	 	 temp=head;
					 temp1=temp->next;
	    	   while(temp->next!=NULL)
						{
				     temp->x=temp1->x;
				     temp->y=temp1->y;
				     temp=temp->next;
				     temp1=temp1->next;
			      }
			      temp->x-=1;
				}

			 	if(n==4)
			 	 {
			 	 	 temp=head;
					 temp1=temp->next;
	    	   while(temp->next!=NULL)
						{
				     temp->x=temp1->x;
				     temp->y=temp1->y;
				     temp=temp->next;
				     temp1=temp1->next;
			      }
			      temp->y-=1;
				}

			 	if(n==2)
			 	 {
			 	 	 temp=head;
					 temp1=temp->next;
	    	   while(temp->next!=NULL)
						{
				     temp->x=temp1->x;
				     temp->y=temp1->y;
				     temp=temp->next;
				     temp1=temp1->next;
			      }
			      temp->x+=1;
				}

			  if(n==5)
			   break;
			  generate_screen(screen,20,20);
				insert_snake(head,screen);
				if(check(foodx,foody,head)==1)
				 {
				 	head=increase_length(head);
				 	generate_food(20,20,foodx,foody,head);
				 }
			  
			  if(death_check(head))
			    break;
			  update_food(screen,foodx,foody);
				display(screen); 
			  
			 }
			
 }

int main()
 {
  int snakelen=4;
	node * snakeHead;
	char **screen=new char*[20];
	for(int i=0;i<20;i++){
		screen[i]=new char[20];
	}
	
	generate_screen(screen,20,20);
	snakeHead=generate_snake(4);
	insert_snake(snakeHead,screen);

	display(screen);
	snake_move(screen,snakeHead);
 }

