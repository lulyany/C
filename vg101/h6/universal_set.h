#ifndef USET_H
#define INITSETSIZE 64 // Initial memory allocated for the set
#define CHAR 1
#define INT sizeof(int)
#define DOUBLE sizeof(double)
/* elem: list of elments; card: cardinal of the set; type: data type (CHAR INT or DOUBLE) */ 


typedef struct universalSet { 
    void *elem; 
    int card; 
    int type; 
    } uset;
/* Initialize an empty set of given type and allocate the initial memory: INITSETSIZE*type */ 

void newSet(uset **set, int type);
void deletSet(uset **set); // Free the memory allocated by newSet
/* add elem to the set: check whether it is already in the set;
resize memory if card = allocated memory; new memory = previous+64
e.g. before: mem=128, card=128, after: men=192, card=129 */
void addElem(void *elem, uset *set);
/* remove elem from the set; do nothing if the set does not contain this elem;
resize memory if "too much memory" is used; new = previous-64 e.g. before: mem=192, card=129, after: card=128, mem=128 */
void remElem(void *elem, uset *set); 

int check( void *x, uset *set )
 {
       if ( ( *set ).type == DOUBLE )
     {
         int i = 0;
         while (i < ( set )->card)
         {
             if ( ( *( double * ) x ) == *( ( double * ) ( ( set )->elem ) + i ) ) return i;
          i++;
         }
     }
     
     if ( ( ( *set ).type ) == INT )
     {
         int i = 0; 
         while ( i < ( set )->card)
         {
             if ( ( *( int * ) x ) == *( ( int * ) ( ( set )->elem ) + i ) ) return i;
            i=i+1;
         }
     }
   
    if ( ( ( *set ).type ) == CHAR )
     {
         int i = 0;
         while (  i < ( set )->card )
         {
             if ( ( *( char * ) x ) == *( ( char * ) ( ( set )->elem ) + i ) ) return i;
         i=i+1;
         }
     }
     return -1;
 }
  void swap_double( double *x, double *y )
 {
     double temp = *x;
     *x          = *y;
     *y          = temp;
     return;
 }
  void swap_int( int *x, int *y )
 {
     int temp = *x;
     *x       = *y;
     *y       = temp;
     return;
 }
 void swap_char( char *x, char *y )
 {
     char temp = *x;
     *x        = *y;
     *y        = temp;
     return;
 }

#endif