/**************************************/
/*             main.c                 */
/*     DO NOT MODIFY THIS FILE        */
/**************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tests.h"

int getChoice()
{
   int n;
   
   printf("Please enter a function testing choice\n");
   printf("Enter 0 to test all of the functions\n");
   printf("Enter 1 to test string_to_fraction\n");
   printf("Enter 2 to test fraction_to_string\n");
   printf("Enter 3 to test compare_fractions\n");
   printf("Enter 4 to test reduce_fraction\n");
   printf("Enter 5 to test add_fraction\n");

   scanf("%d",&n);
   printf("\n");
   return n;
}

int main()
{
   FILE *errF = NULL;
   FILE *reportF = NULL;
   char rnom[20] = "TestResults_";
   char enom[20] = "ErrorFile_";
   char errBuffer[2000] = "\nFraction Test Errors\n";
   int choice;
   const char *choice_str[6] ={"all","stof","ftos","compare","reduce","add"};

   printf("\nWelcome to the Fractions Module Test Program\n\n");
   printf("Tests results can be found in file TestResults\n");
   printf("and error reports in file errorFile\n\n");
   
   choice = getChoice();
   while(choice < 0 || choice > 5) {
     printf("\nInvalid choice; must be between 0 and 5, inclusive\n");
     choice = getChoice();
   }
   
   strcat(rnom,choice_str[choice]);
   strcat(enom,choice_str[choice]);

   if ((reportF = fopen(rnom,"w")) == NULL) {
      printf("Unable to open TestResults for writing\n");
      exit(1);
   }
  
   fprintf(reportF,"\nFractions Test Report\n");

   if (choice == 1 || choice == 0)
      fprintf(reportF,"string_to_fraction: %s\n",test_stof(errBuffer)? "pass" : "fail");
   if (choice == 2 || choice == 0)
      fprintf(reportF,"fraction_to_string: %s\n",test_ftos(errBuffer)? "pass" : "fail");
   if (choice == 3 || choice == 0)
      fprintf(reportF,"compare__fractions: %s\n",test_compare(errBuffer)? "pass" : "fail");
   if (choice == 4 || choice == 0)
      fprintf(reportF,"reduce_fraction: %s\n",test_reduce(errBuffer)? "pass" : "fail");
   if (choice == 5 || choice == 0)
      fprintf(reportF,"add_fraction: %s\n",test_add(errBuffer)? "pass" : "fail");

   fclose(reportF);

   if (strcmp(errBuffer,"\nFraction Test Errors\n") != 0) {
      printf("Errors found; consult TestResults and Error file\n");
      if ((errF = fopen(enom,"w")) == NULL) {
	 printf("Unable to open errorFile for writing\n");
      }
      fprintf(errF,"%s",errBuffer);
      fclose(errF);
   } else 
      printf("No errors detected\n\n");
   
   printf("Normal termination\n\n");

   return 0;
}
