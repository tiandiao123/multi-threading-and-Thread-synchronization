#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count=0;
 
struct node
{
    char info[20];
    struct node *ptr;
}*front,*rear;


void create(){

 front=rear=NULL;
  
}

int queuelength(){
   return count;
}

void enqueue(char* data)
{   struct node* temp=NULL;
    if (rear == NULL)
    {
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        
        strncpy(rear->info,data,strlen(data)-1);
        front = rear;
    }
    else
    {
        temp=(struct node *)malloc(1*sizeof(struct node));
        rear->ptr = temp;
        strncpy(temp->info,data,strlen(data)-1);
        temp->ptr = NULL;
 
        rear = temp;
    }
    count++;
}

void display()
{
    struct node *front1 = front;
 
    if ((front1 == NULL) && (rear == NULL))
    {
        printf("Queue is empty");
        return;
    }
    while (front1 != rear)
    {
        printf("%s\n", front1->info);
        front1 = front1->ptr;
    }
    if (front1 == rear)
        printf("%s\n", front1->info);
}

void dequeue(char* str)
{
    struct node *front1 = front;
    if(front1!=NULL){
        strcpy(str,front1->info);
    }
    else {
       str=NULL;
    }
    if (front1 == NULL)
    {
        printf("\n Error: Trying to display elements from empty queue");
        return;
    }
    else
        if (front1->ptr != NULL)
        {
            front1 = front1->ptr;
           // printf("Dequed value : %s\n", front->info);
            free(front);
            front = front1;
        }
        else
        {
            //printf("Dequed value : %s\n", front->info);
            free(front);
            front = NULL;
            rear = NULL;
        }
        count--;
}
/*
int main(){
    create();
   enqueue("hello");
   enqueue("nihao");
   enqueue("nihaoma");
   display();
   printf("the size of queue is :%d\n",queuelength());
   char str[20];
   dequeue(str);
   printf("after dequeue,the str value is %s\n",str);
   display();
   printf("the size of queue is :%d\n",queuelength());


}*/
