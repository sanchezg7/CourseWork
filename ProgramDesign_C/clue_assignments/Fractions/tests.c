/**************************************/
/*            tests.c                 */
/*     DO NOT MODIFY THIS FILE        */
/**************************************/

#include "tests.h"
#include "Fraction.h"
#include "test_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int equalFractions(Fraction R1, Fraction R2) 
{
  return (R1.numer*(R2.denom) == R2.numer*(R1.denom));
}


int test_stof(char * err_messages)
{
   int i = 0, errors = 0;
   Fraction R;

   for(i = 0; i < stof_count; i++) {
      R = string_to_fraction(stof_test_strings[i]);
      if (!equalFractions(R,stof_correctFractions[i])) {
	 if (!errors) {
	    sprintf(err_messages,"%s\n\nString to Fraction Errors:\n",err_messages);
	    errors = 1;
	 }
	 sprintf(err_messages,"%sexpected: %d/%d\nactual: %d/%d\n",err_messages,
		 stof_correctFractions[i].numer,stof_correctFractions[i].denom,R.numer,R.denom);
      }
   }
   return !errors;
}

int test_ftos(char * err_messages)
{
   int i = 0, errors = 0;
   char  stringArr[30] = {0};  /* more than enough space to hold a Fraction string */

   for(i = 0; i < stof_count; i++) {
      fraction_to_string(ftos_input[i],stringArr);

      if (strcmp(stringArr,ftos_correct_strings[i]) != 0) {
	 if (!errors) {
	    sprintf(err_messages,"%s\n\nFraction to String Errors:\n",err_messages);
	    errors = 1;
	 }
	 sprintf(err_messages,"%sexpected: %s\nactual: %s\n",err_messages,
		 ftos_correct_strings[i],stringArr);
      }
   }
   return !errors;
}

    
int test_compare(char * err_messages)
{
   Fraction left = {0,1}, right = {0,1};

   int i = 0, errors = 0, result;

   for(i = 0; i < compare_count; i++) {
      left = compare_left_args[i];
      right = compare_right_args[i];
      result = compare_fractions(left,right);

      if (result != compare_correct[i]) {
	 if (!errors) {
	    strcat(err_messages,"\n\nCompare Errors:\n");
	    errors = 1; 
	 }
	 sprintf(err_messages,"%s(%d,%d) ? (%d,%d)\nreceived %d, correct %d\n\n",
		 err_messages,left.numer,left.denom,right.numer,right.denom,
		 result,compare_correct[i]);
      }
   }
   return !errors;
}

int test_reduce(char * err_messages)
{
   int i = 0, errors = 0;
   Fraction in_fraction = {0,1};
   Fraction result = {0,1};
   Fraction correct = {0,1};

   for(i = 0; i < reduce_count; i++) {
      in_fraction = reduce_input[i];
      correct = reduce_correct[i];
      result = in_fraction;
      reduce_fraction(&result);

      if (!equalFractions(result,correct)) {
	 if (!errors) {
	    strcat(err_messages,"\n\nReduce Errors:\n");
	    errors = 1; 
	 }
	 sprintf(err_messages,"%s(%d,%d)\nreceived (%d,%d), correct (%d,%d)\n\n",
		 err_messages,in_fraction.numer,in_fraction.denom,result.numer,
		 result.denom,correct.numer,correct.denom);
      }
   }
   return !errors;
}

int test_add(char * err_messages)
{
   Fraction left, right, correct, result;

   int i = 0, errors = 0;

   for(i = 0; i < add_count; i++) {
      left = add_left_args[i];
      right = add_right_args[i];
      correct = add_correct[i];

      result = add_fractions(left,right);

      if (!equalFractions(result,correct)) {
	 if (!errors) {
	    strcat(err_messages,"\n\nAdd Errors:\n");
	    errors = 1; 
	 }
	 sprintf(err_messages,"%s(%d,%d)+(%d,%d)\nreceived (%d,%d), correct (%d,%d)\n\n",
		 err_messages,left.numer,left.denom,right.numer,right.denom,
		 result.numer,result.denom,correct.numer,correct.denom);
      }
   }
   return !errors;
}

