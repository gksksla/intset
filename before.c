#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "intset.h"

void
test1 (){

    intset * s1 = intset_alloc() ;
   intset * s2 = intset_alloc() ;

   intset_add(s1, 1) ;
   intset_add(s1, 2) ;
   intset_add(s1, 3) ;
   intset_add(s1, 4) ;
   intset_add(s1, 5) ;
   intset_add(s1, 6) ;
   intset_add(s1, 7) ;
   intset_add(s1, 8) ;


    intset_add(s2, 2) ;
   intset_add(s2, 1) ;
   intset_add(s2, 5) ;
   intset_add(s2, 6) ;
   printf("s1 : ");
    intset_print(stderr, s1);
   printf("\n");

      printf("s2 : ");
    intset_print(stderr, s2);
   printf("\n");

   intset * uni = intset_union(s1,s2);
   printf("uni : ");
   intset_print(stderr,uni);
   printf("Uni size : %d\n", intset_size(uni));

   intset * inter = intset_intersection(s1,s2);
   printf("inter:");
   intset_print(stderr,inter);
   printf("Inter size : %d\n", intset_size(inter));
   printf("\n");


   intset * diff = intset_difference(s1,s2);
   printf("diff\n");
   intset_print(stderr,diff);
   printf("diff size : %d\n", intset_size(diff));
   printf("\n");
   
}

int
main ()
{
	//test1() ;
   intset * s = intset_alloc() ;

	intset_add(s, 1) ;
	intset_add(s, 2) ;
	intset_add(s, 3) ;
	intset_add(s, 4) ;
	intset_remove(s, 2) ;

	assert(intset_size(s) == 3) ;
	assert(intset_contains(s, 4) == 1) ;
	assert(intset_contains(s, 2) == 0) ;

	intset_print(stderr, s) ; fprintf(stderr, "\n") ;

}