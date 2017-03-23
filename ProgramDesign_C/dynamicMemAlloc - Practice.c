#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main ()
{
    char inputBuffer[1000];
    int length = 0;
    char* sentence = NULL;

    printf("Type a sentence:\n");
    fgets(inputBuffer, 1000, stdin);

    //echo input
    printf("You typed: \n%s\n\n", inputBuffer);
    length = strlen(inputBuffer);
    printf("Allocating %d bytes to hold the sentence \n\n", length+1);

    sentence = malloc(length+1);

    assert (sentence != NULL);
    strcpy (sentence, inputBuffer); //right to left arrow it

    //After allocation
    printf("The sentence in dynamically allocated memory: \n");
    printf("%s\n", sentence);
    getchar();
    getchar();
    return 0;
}
