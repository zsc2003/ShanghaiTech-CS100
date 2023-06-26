#include <stdio.h>
#include <stdlib.h>


int main()
{
   char str1[10], str2[10], str3[10];
   int year;
   FILE * fp=fopen ("file.txt", "w+");

   fprintf(fp, "%s %s %s %d", "We", "are", "in", 2022);
   //what if change the fp to stdout?
   rewind(fp);

   fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);
   //what if change the fp to stdin?
   printf("Read String1 |%s|\n", str1 );
   printf("Read String2 |%s|\n", str2 );
   printf("Read String3 |%s|\n", str3 );
   printf("Read Integer |%d|\n", year );

   fclose(fp);
   
   return(0);
}