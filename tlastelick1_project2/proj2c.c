#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int globalCount = 1;    // Count the number of iterations to stop at the appropriate time. 
int globalSize = 0;     // Max number of iterations the threads will run. 
int itter =1;
char * characterPointer;
char * wordPointer [5][25];

// Check if the word is a vowel, if so print it, and move onto the next word. 
    void * printvowel(void * s)
    {

        characterPointer = wordPointer[itter];

        if (globalCount < globalSize)
           {
             if (characterPointer[0] == 'A' || characterPointer[0] == 'a' || characterPointer[0] == 'E' || characterPointer[0] == 'e' || characterPointer[0] == 'I' || characterPointer[0] == 'i' || characterPointer[0] == 'O' || characterPointer[0] == 'o' ||characterPointer[0] == 'U' || characterPointer[0] == 'u')
                {
                    printf("vow: %s\n", wordPointer[itter]);
                    itter++;
                    globalCount++;
                }
                               
           }

        pthread_exit(0);
    }

// Check if the word is a consonant, if so print it, and move onto the next word. 
    void * printcons(void * s)
    {
  
        characterPointer = wordPointer[itter];

        if (globalCount < globalSize)
        {
            if (characterPointer[0] != 'A' && characterPointer[0] != 'a' && characterPointer[0] != 'E' && characterPointer[0] != 'e' && characterPointer[0] != 'I' && characterPointer[0] != 'i' && characterPointer[0] != 'O' && characterPointer[0] != 'o' && characterPointer[0] != 'U' && characterPointer[0] != 'u')
                {
                    printf("con: %s\n", wordPointer[itter]);
                    itter++;
                    globalCount++;
                }
        }

        pthread_exit(0);
    }

int main(int argc, char *argv[]) {

   // Create a terminal-input specified number of threads. 
    int SIZE = atoi(argv[1]);
    pthread_t t1;
    pthread_t t2;

    // Copy the number of words in the array. 
    globalSize = argc;

    // Create a copy of all commands (words) from terminal input. 
    for (int i=0; i<argc; i++)
    {
        strcpy(wordPointer[i], argv[i]);
    }

    // Print the terminal input, labelling the vowels and cons appropriately.  
    for (int i = 0; i < argc; i++)
    {
    pthread_create(&t1, NULL, printvowel, NULL);
    pthread_create(&t2, NULL, printcons, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    }
    
    return 0;

}