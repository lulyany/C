#include "assignment.h"
#include "universal_set.h"

 void swap_double( double *x, double *y );
 void swap_int( int *x, int *y );
 void swap_char( char *x, char *y );
 int  check( void *x, uset *set );

 void newSet( uset **set, int type )
 {
     (**set).elem=calloc( INITSETSIZE, ( unsigned long ) type );
     (**set).type=type;
     (**set).card=0;
     return;
 }
 void deletSet( uset **set )
 {
     free((*set)->elem);
     free(*set);
     return;
 }
 void addElem( void *elem, uset *set )
 {
     if ( check( elem, set ) != -1 ) return;
     if ( ( ( ( set->card ) % INITSETSIZE ) == 0 ) && ( set->card != 0 ) )
         set->elem = realloc( set->elem, ( unsigned long ) ( ( unsigned long ) set->card + INITSETSIZE ) * ( unsigned long ) ( set->type ) );
     set->card++;
     switch ( ( *set ).type )
        case CHAR  {
          *( ( char * ) ( set->elem ) + ( ( set->card ) - 1 ) ) = *( char * ) elem; 
          break;
          }
        case INT  {
          *( ( int * ) ( set->elem ) + ( ( set->card ) - 1 ) ) = *( int * ) elem; 
          break;
          }
        case DOUBLE  { 
         *( ( double * ) ( set->elem ) + ( ( set->card ) - 1 ) ) = *( double * ) elem; 
         break;
         }
 }
 void remElem( void *elem, uset *set )
 {
     if ( check( elem, set ) == -1 ) 
        return;
     if ( ( ( *set ).type ) == CHAR ) 
        { swap_char( ( ( char * ) ( set->elem ) + check( elem, set ) ), ( ( char * ) ( set->elem ) + ( ( set->card ) - 1 ) ) ); }
     if ( ( ( *set ).type ) == INT ) 
        { swap_int( ( ( int * ) ( set->elem ) + check( elem, set ) ), ( ( int * ) ( set->elem ) + ( ( set->card ) - 1 ) ) ); }
     if ( ( ( *set ).type ) == DOUBLE )
        { swap_double( ( ( double * ) ( set->elem ) + check( elem, set ) ), ( ( double * ) ( set->elem ) + ( ( set->card ) - 1 ) ) ); }
     set->card--;
     if ( ( ( ( set->card ) % INITSETSIZE ) == 0 ) && ( set->card != 0 ) ) set->elem = realloc( set->elem, ( unsigned long ) ( set->card * ( set->type ) ) );
     return;
 }
 