#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intset.h"

intset *
intset_alloc ()
{	
	intset * s = (intset *) malloc(sizeof(intset)) ;
	s->n_elems = 0 ;
	s->elems = 0x0 ;
	return s ;
}

intset * 
intset_clone (intset * orig) 
{
	if (orig == 0x0)
		return 0x0 ;

	intset * s = intset_alloc() ;
	
	s->n_elems = orig->n_elems ;
	s->elems = 0x0 ;
	if (s->n_elems > 0) {
		s->elems = (int *) calloc(s->n_elems, sizeof(int)) ;
		memcpy(s->elems, orig->elems, s->n_elems * sizeof(int)) ;
	}
	return s ;
}

void
intset_print (FILE * fp, intset * s)
{
	fprintf(fp, "{") ;
	for (int i = 0 ; i < s->n_elems ; i++) {
		char * delim = (i > 0) ? ", " : "" ;
		fprintf(fp, "%s%d", delim, s->elems[i]) ;
	}
	fprintf(fp, "}") ;
}

void
intset_free (intset * s) 
{
	free(s->elems) ;
	free(s) ;
}

int
intset_size (intset * s) 
/*
 * returns the number of elements contained in s.
 */
{
	int re=s->n_elems;
    return re;
}

int
intset_add(intset* s, int e)
/*
 * insert a new integer value e to s.
 * return 0 if succeeded. return 1 if it fails.
 *
 * hint: use realloc. note that s->elems is NULL when it has no element.
 */
{
   if (s->n_elems != 0) {
      for (int i = 0; i < s->n_elems; i++) {
         if (e == s->elems[i]) {//already e is exist
            return 1;
         }
      }
   }
   
   //e is not in s
   s->n_elems = s->n_elems + 1;
   s->elems = (int*)realloc(s->elems, (s->n_elems) * sizeof(int));
   s->elems[((s->n_elems) - 1)] = e;
   return 0;

}

int
intset_remove (intset * s, int e) 
/*
 * remomve e from s.
 * return 0 if succeeded. return 1 if failed.
 *
 * s->elems must be set to NULL if s->n_elems == 0.
 *
 * hint: use realloc.
 */
{
	if(s->n_elems==0)return 1;//없으면
    else{
        for(int i=0;i<s->n_elems;i++){
            if(e==s->elems[i]){
                if(s->n_elems==0){//첫번째면
                    s->elems=NULL;
                    s->n_elems=0;
                    return 0;
                }
                else{
                    //memcpy(s->elems+i*4,s->elems+(i+1)*4,(s->n_elems-i)*sizeof(int));//중간또는 끝이면, 개수만 줄어듬
                    //중간또는 끝이면, 개수만 줄어듬
                    for(int a=i;a<s->n_elems;a++){
                        s->elems[a]=s->elems[a+1];
                    }
                    s->n_elems=s->n_elems-1;
                    s->elems=(int *)realloc(s->elems,(s->n_elems)*sizeof(int));
                    return 0;
                }
            }
        }
    }
    return 1;
}


int
intset_contains (intset * s, int e) 
/*
 * return 1 if e is contained in s. return 0 otherwise.
 */
{
	for(int i=0;i<s->n_elems;i++){
        if(s->elems[i]==e){
            return 1;
        }
    }
    return 0;
}


int
intset_equals (intset *s1, intset *s2) 
/*
 * return 1 if two sets s1 and s2 are equivalent.
 * return 0 otherwise.
 */
{
    if(s1->n_elems!=s2->n_elems)return 0;//개수 다르면 0
    int count=0;
	for(int y=0;y<s1->n_elems;y++){
        for(int x=0;x<s2->n_elems;x++){
            if(s1->elems[y]==s2->elems[x]){
                count++;
            }
        }
    }
    if(count==s1->n_elems)return 1;//똑같다.
    else return 0;//개수는 같지만 원소는 다르면
}


intset *
intset_union (intset *s1, intset *s2) 
/*
 * return a new intset object that contains the result of
 * the union of s1 and s2.
 *
 * return NULL if the operation fails.  ???
 */
{
    if(s1==NULL || s2==NULL)return NULL;

	intset * s = intset_alloc() ;
    int i;
    for(i=0;i<s1->n_elems;i++){
        intset_add(s,s1->elems[i]);
    }
    for(i=0;i< s2->n_elems ;i++){
        intset_add(s,s2->elems[i]);
    }
	return s;
}


intset *
intset_intersection (intset *s1, intset *s2) 
/*
 * return a new intset object that contains the result of
 * the intersection of s1 and s2.
 *
 * return NULL if the operation fails.
 */
{
    if(s1==NULL && s2==NULL)return NULL;

	intset * s = intset_alloc() ;
    int count=0;
    int arr[3000];
	for(int y=0;y<s1->n_elems;y++){
        for(int x=0;x<s2->n_elems;x++){
            if(s1->elems[y]==s2->elems[x]){
                arr[count]=s1->elems[y];
                count++;
            }
        }
    }
    s->n_elems=count;
    s->elems = (int *) calloc(s->n_elems, sizeof(int)) ;
    for(int i=0;i<count;i++){
        s->elems[i]=arr[i];
    }
    return s;
}


intset *
intset_difference (intset *s1, intset *s2) 
/*
 * return a new intset object that contains the result of
 * the set difference of s1 and s2 (i.e., s1 \ s2).
 *
 * return NULL if the operation fails.
 */
{
    if(s1==NULL &&  s2==NULL)return NULL;

	intset * s = intset_alloc() ;
    int count=0;
    int data[s1->n_elems];
    for(int i=0;i<s1->n_elems;i++){
        data[i]=0;
    }
	for(int y=0;y<s1->n_elems;y++){
        for(int x=0;x<s2->n_elems;x++){
            if(s1->elems[y]==s2->elems[x]){
                data[y]=1;
                count++;
            }
        }
    }
    s->n_elems=s1->n_elems-count;
    s->elems = (int *) calloc(s->n_elems, sizeof(int)) ;
    int a=0;
    for(int i=0;i<s1->n_elems;i++){
        if(data[i]!=1){
            s->elems[a]=s1->elems[i];
            a++;
        }
    }
    return s;
}


intset**
intset_subsets(intset* s, size_t k, size_t* n_subsets)
/*
 * return a new intset array that contains all distinct subsets
 * of s having k elements. The size of the result array must be
 * given to n_subsets.
 *
 * this operation must be implemented with a recursion.
 *
 * return NULL if the operation fails.
 */
{
   
   if (s == NULL) return NULL;
   if (s->n_elems == k) {
      intset** re = (intset**)malloc(sizeof(intset*));
      re[0] = intset_alloc();
      re[0] = s;
      *n_subsets = 1;
      return re;
   }
   
   if (k == 0) {
      
      intset** s=(intset**)malloc(sizeof(intset *) );
      s[*n_subsets]=intset_alloc();
      return s;
   }
   intset** re = (intset**)malloc(sizeof(intset*) * 1000);
   intset** Return = (intset**)malloc(sizeof(intset*) * 1000);

   if (k == 1) {
      for (int f = 0; f < s->n_elems; f++) {
         re[f] = intset_alloc();
         intset_add(re[f], s->elems[f]);
         *n_subsets = f+1;
      }
      /*
      for (int o = 0; o < s->n_elems; o++) {
         printf("re[%d]", o);
         intset_print(stderr, re[o]);
      }
      */
      return re;
   }
   int i;
   int n = 0;
   for (i = 0; i < s->n_elems; i++) {
      
      if(i==0)*n_subsets = 0;
      int e = s->elems[i];
      intset* clo = intset_clone(s);
      intset_remove(clo, e);;
      re=(intset_subsets(clo, k - 1, n_subsets)); 

      if (*n_subsets >= 2) {
         //e랑 더하기
         for (int f = 0; f < *n_subsets; f++) {
            intset_add(re[f], e);
         }

         
         for (int i = 0; i < *n_subsets; i++) {
            int flag = 0;
            for (int p = 0; p < n; p++) {
               if (intset_equals(Return[p], re[i]) == 1) {
                  flag = 1;
                  break;
               }
            }
            if (flag == 0) {
               Return[n] = re[i];
               n++;
            }
            
         }
         /*
         for (int o = 0; o < n; o++) {
            printf("Re[%d]", o);
            intset_print(stderr, Return[o]);
         }
         */
      }
      else {
         //중복제거 필요없음, 공집합에 넣은것
         intset_add(re[i], e);
         *n_subsets = i + 1;

         Return[i] = re[i];
      }
   }

   //return
   if (n > * n_subsets) {
      *n_subsets = n;
   }
   return Return;

}


intset**
intset_powerset(intset* s, size_t* n_subsets)
/*
 * return a new intset array that contains all distinct subsets
 * of s having. The size of the result array must be given to
 * n_subsets.
 *
 * this operation must be implemented with a recursion.
 *
 * return NULL if the operation fails.
*/
{
   if (s == NULL)return NULL;

   if (s->n_elems == 0) {

      intset** s = (intset**)malloc(sizeof(intset*));
      s[*n_subsets] = intset_alloc();
      *n_subsets = *n_subsets + 1;
      return s;
   }
   intset** re = (intset**)malloc(sizeof(intset*) * 1000);
   intset** Return = (intset**)malloc(sizeof(intset*) * 1000);

   
   int i;
   int n = 0;
   for (i = 0; i < s->n_elems; i++) {

      if (i == 0)*n_subsets = 0;
      int e = s->elems[i];
      intset* clo = intset_clone(s);
      intset_remove(clo, e);
      re = intset_powerset(clo, n_subsets);
      /*
      for (int i = 0; i < *n_subsets; i++) {
         printf("re[%d]: ", i);
         intset_print(stderr, re[i]);
         printf("\n");
      }
      */
      intset* myself = intset_clone(s);
      re[*n_subsets] = myself;
      *n_subsets = *n_subsets + 1;
         for (int i = 0; i < *n_subsets; i++) {
            int flag = 0;
            for (int p = 0; p < n; p++) {
               if (intset_equals(Return[p], re[i]) == 1) {
                  flag = 1;
                  break;
               }
            }
            if (flag == 0) {
               Return[n] = re[i];
               n++;
            }

         }
         /*
         for (int o = 0; o < n; o++) {
            printf("Re[%d]", o);
            intset_print(stderr, Return[o]);
         }
         */
   }

   //return
   if (n > * n_subsets) {
      *n_subsets = n;
   }

   free(re);

   return Return;
   
}
