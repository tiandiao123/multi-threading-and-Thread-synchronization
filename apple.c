#include <stdlib.h>
#include <stdio.h>
#include "queue.c"
#include "makeargv.h"
#include <unistd.h>
#include <pthread.h>

struct twitterDB{
   char city[20];
   char keyword1[20];
   char keyword2[20];
   char keyword3[20];

} twitterarray[26];

pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
//int add=0;
int storedata();
int findmin(int,int);
void *child(void *arg);

int main(int argc, char *argv[]){
   //first of all, I created a queue based on argv[1];
   create();
   FILE *fp;
   char str[20];
   fp = fopen(argv[1], "r");
   if(fp == NULL) 
   {
      perror("Error opening file");
      return(-1);
   }
   while( fgets (str, 60, fp)!=NULL ) 
   {
      enqueue(str);
   }
   fclose(fp);
   display();
   //Then, I store all the data in TwitterDB.txt into the struct twitterarray[]

  int  check=storedata();
    if(check==0){
      printf("store data sucessfully\n");
     }
    else{
      fprintf(stderr,"store data failed\n");
     }

   const int num_threads=atoi(argv[2]);
   pthread_t thid[num_threads];  
   int i;
   int j;
   while(queuelength()!=0){
      int num=findmin(queuelength(),num_threads); 
      for(i=0;i<num;i++)
       {   j=i+1;
         pthread_create(&thid[i], NULL, child,&j);
       }
      for(i=0;i<num;i++)
       {
         pthread_join(thid[i],NULL);
       }

    }
   return(0);
   
}

void *child(void *arg){
   
   
   char client[20];
   pthread_mutex_lock(&lock);
    int storeadd=*(int *)arg;
    if(queuelength()>0)
      dequeue(client);
    else 
      return;
   pthread_mutex_unlock(&lock);
 
   
   FILE *fp2;
   fp2=fopen(client,"r");
   if(fp2==NULL)
   {
       perror("error opening file in the child");
       exit(1);
    }
   char cityname[30];
   if(fgets(cityname,30,fp2)==NULL){
        perror("something is wrong");
        exit(1);
     }
   
   fclose(fp2);
  
  FILE *createfile;
  char filename[35];
  strcpy(filename,client);
  //strcat(filename,".txt");
  char tempname[30];
  strcpy(tempname,filename);
  fprintf(stderr,"thread %d is handling %s\n",storeadd,tempname);
  
  strcat(filename,".result");
  createfile=fopen(filename,"w");
  int j=0;
  for(;j<26;j++){
       char tempcity[30];
      strcpy(tempcity,twitterarray[j].city);
      strcat(tempcity,"\n");
      if(strcmp(cityname,tempcity)==0)
       {
           fprintf(createfile,"%s:%s,%s,%s",twitterarray[j].city,twitterarray[j].keyword1,twitterarray[j].keyword2,twitterarray[j].keyword3);   
       } 
  }
  fprintf(stderr,"thread %d finished handling %s\n",storeadd,tempname);
 fclose(createfile);
   return NULL;
}

int storedata(){
    FILE *fp1;
   char str[80];
   char **myarray; 
   /* opening file for reading */
   fp1 = fopen("TwitterDB.txt" , "r");
   if(fp1 == NULL) 
   {
      perror("Error opening file");
      return(-1);
   }
   int i=0;
   while( fgets (str, 80, fp1)!=NULL ) 
   {
      int num=makeargv(str,",",&myarray);
       strcpy(twitterarray[i].city,myarray[0]);
       strcpy(twitterarray[i].keyword1,myarray[1]);
       strcpy(twitterarray[i].keyword2,myarray[2]);
       strcpy(twitterarray[i].keyword3,myarray[3]);
       fprintf(stderr,"%s,%s,%s,%s\n",twitterarray[i].city,twitterarray[i].keyword1,twitterarray[i].keyword2,twitterarray[i].keyword3);
       i++;
   }
   fclose(fp1);
   
   return(0);

}

int findmin(int a,int b){
   if (a<b)
      return a;
   else 
     return b;
}
