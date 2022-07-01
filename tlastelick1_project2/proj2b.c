#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void * createFibonacci(void * s);
void * printFibonacci(void * s);

int * globalSize = NULL; // = &SIZE;
int * fibSequence;

int main( int argc, char *argv[] )
{
    pthread_t mythread;
    pthread_t thread2;

    // Convert terminal input (number just after program call) into an integer.
    int SIZE = atoi(argv[1]);
    
    // Check the sequence is at least 1 number long.
    if (SIZE == 0)
    {
        printf("Sequence cannot be less than 1.\n");
        printf("Please re-enter the length of the fibonacci sequence you want to see: ");
        scanf( "%d", &SIZE );
    }

    // Point to the address of SIZE. 
    globalSize = &SIZE; 
    
    // Create a thread to generate the fibonacci sequence.
    pthread_create(&mythread, NULL, createFibonacci, NULL);
    pthread_join(mythread, NULL);

    // Create a thread to display the fibonacci sequence.
    pthread_create(&thread2, NULL, printFibonacci, NULL);
    pthread_join(thread2, NULL);

return 0;
}

// Requires a void * argument simply as a place holder.
// The global variable globalSize must first be initialized with the size the sequence is going to be.
// Computes the fibonacci algorithm, placing each generated number in a new element in global variable fibSequence.
void * createFibonacci(void * s)
{

// Allocate memory for the fibonacci sequence.
fibSequence = malloc(*globalSize * sizeof(int));

// Generate fibonacci sequence
int a = 0, b = 1, c, i;

    // Create a fibonacci sequence one number long.
    if (*globalSize == 1)
    {
        fibSequence[0] = 0;
    }
    
    // Create a fibonacci sequence two numbers long.
    else if (*globalSize == 2)
    {
    fibSequence[0] = 0;
    fibSequence[1] = 1;
    }
    
    // Create a fibonacci sequence three or greater numbers long.
    else
    {
        fibSequence[0] = 0;
        fibSequence[1] = 1;
    
        for (i = 2; i <= *globalSize; i++) 
        {
            c = a + b;
            a = b;
            b = c;
            fibSequence[i] = b;
        }
    }
        
    return NULL;
}

// Requires a pointer to an integer array.
// Prints every eleemetn of the integer array on a new line. 
void * printFibonacci(void * s)
{
    // Display the fibonacci sequence.
    for (int i=0; i<*globalSize; i++)
    {
        printf("Fib sequence %d: %d\n", i+1, fibSequence[i]);
    }
    return NULL;
}
