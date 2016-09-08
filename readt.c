#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE *fp;
   char str[60];

   /* opening file for reading */
   fp = fopen("TwitterDB.txt" , "r");
   if(fp == NULL) 
   {
      perror("Error opening file");
      return(-1);
   }
   while( fgets (str, 60, fp)!=NULL ) 
   {
      /* writing content to stdout */
      puts(str);
   }
   fclose(fp);
   
   return(0);
}
