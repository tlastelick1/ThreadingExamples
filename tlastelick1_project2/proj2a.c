#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


#define MAX_THREADS 512

void *compute_pi( void * );


int sample_points;
int total_hits;
int total_misses;
int hits[ MAX_THREADS ];
int sample_points;
int sample_points_per_thread;
int num_threads;



int main( int argc, char *argv[] )
{
  /* local variables */
  int ii;
  int retval;
  pthread_t p_threads[MAX_THREADS];
  pthread_attr_t attr;
  double computed_pi;

  /* initialize local variables */
  retval = 0;

  // Initialize an attribute to the default value.
  pthread_attr_init( &attr );
  
  // PTHREAD_SCOPE_SYSTEM - New thread is unbound - not permanently attached to LWP.
  // Use unbound threads even when you expect all threads to be active simultaneously. 
  // Use bound threads only when a thread needs resources that are available only through the underlying LWP.
  pthread_attr_setscope( &attr, PTHREAD_SCOPE_SYSTEM );

  /* parse command line arguments into sample points and number of threads */
  /* there is no error checking here!!!!! */
  // sample_points = atoi(argv[1]);
  // num_threads = atoi(argv[2]);

  // Prompt user for number of sample points/
  // Prompt user for number of threads.
  printf( "Enter number of sample points: " );
  scanf( "%d", &sample_points );
  printf( "Enter number of threads: " );
  scanf( "%d", &num_threads );
  
  // Find number of sample points to assign to each thread.
  total_hits = 0;
  sample_points_per_thread = sample_points / num_threads;

  // Create thread # , initialize it to be unbound, and to run the compute_pi function,
  // and pass that function the variable &hits[ii].
  for( ii=0; ii<num_threads; ii++ )
    {
      hits[ii] = ii;
      pthread_create( &p_threads[ ii ], &attr, compute_pi, (void *) &hits[ii]);
    }

  // Make sure every thread runs till the end and calculate the total hits
  for( ii=0; ii<num_threads; ii++ )
    {
       pthread_join( p_threads[ ii ], NULL );
       total_hits += hits[ ii ];
    }

   // Part of the monte carlo algorithm, computes pi from the data we got from threads. 
   computed_pi = 4.0 * (double) total_hits / ((double) (sample_points));


   // Display pi.
   printf( "Computed PI = %lf\n", computed_pi );


  // Return to calling environment 
  return( retval );
}



// Takes as an argument the number of threads that is continually incremented. 
void *compute_pi( void *s )
{
  int seed;
  int ii;
  int *hit_pointer;  
  int local_hits;
  double rand_no_x;
  double rand_no_y;

  hit_pointer = (int *) s;
  seed = *hit_pointer;
  local_hits = 0;

  // Calculate if the sample point was either a hit or miss for each thread.
  for( ii=0; ii < sample_points_per_thread; ii++ )
    {

      // &seed is an integer pointer, RAND_MAX is a number at least 32,167
      // rand_r returns a random integer.
      // rand_r(unsigned int *seed)  // Unsigned int is just a non-negative int. 
      // Generate random x, y pairs. 
      rand_no_x = (double) (rand_r( &seed ))/(double)RAND_MAX;
      rand_no_y = (double) (rand_r( &seed ))/(double)RAND_MAX;
      
      // Check if randomly generated x,y pairs < 0.25
      if(((rand_no_x - 0.5) * (rand_no_x - 0.5) +
	  (rand_no_y - 0.5) * (rand_no_y - 0.5)) < 0.25)
    
      // If yes, we increment the number of points that appears inside the circle.  
	  local_hits++;

      // Updating the seed creates a new sequence of 'random' numbers.
      // 0-5 will have the same sequence as 0-100.
      // Although 0-100 will share the first 5 numbers as 0-5, it will add an additional 95 numbers. 
      seed *= ii;
    }

  // Point to the number of hits in the circle.
  *hit_pointer = local_hits;
  pthread_exit(0);
}