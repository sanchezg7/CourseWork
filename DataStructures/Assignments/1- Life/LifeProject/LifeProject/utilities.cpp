/*
 * Name.
 * 
 * Description.
 */

#include <iostream>

using namespace std;

bool
continue_prompt()
{
   int c;
   bool initial_response = true;

   do
   {
      if (initial_response)
      {
         cout << "Continue? (y/n)" << flush;
      }

      else
      {
         cout << "Respond with either y or n: " << flush;
      }

      do
      {
         c = cin.get( );
      } while (c == '\n' || c == ' ' || c == '\t');

      initial_response = false;

   } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');

   return c == 'y' || c == 'Y';
}


/* vim: set noet sw=4 ts=4: */
