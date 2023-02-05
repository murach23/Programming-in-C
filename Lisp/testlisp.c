//The code works properly. The code passes all asserstions tests until it meets extension.

//I have run the code for all tests possible "testlinked, testlinked_s and testlinked_v".

//All of them had failed when they meet extensions tests.

#include "specific.h"

#define LISTSTRLEN 1000



lisp* lisp_atom(const atomtype a){

  lisp *n = (lisp *)ncalloc(1, sizeof(lisp));

  n->value = a;

  n->car=NULL;

  n->cdr=NULL;

  return n;

}



lisp* lisp_cons(const lisp* l1,  const lisp* l2){

  //create new lisp

  lisp* pbc = (lisp *)ncalloc(1,sizeof(lisp));

  pbc->car = (lisp*) l1;

  pbc->cdr = (lisp*) l2;

  return pbc;

}



int lisp_length(const lisp* l){

    if(l==NULL){

      return 0;

    }

    //If points to car pointer add one

    if(l->car != NULL){

      return 1+lisp_length(l->cdr);

    }

    //If points to cdr pointer add one

    if(l->cdr != NULL){

      return 1+lisp_length(l->cdr);

    }

    return 0;

}



atomtype lisp_getval(const lisp* l){

  if(l != NULL){

    return l->value;

  }

  return 0;

}



void lisp_tostring(const lisp* l, char* str){

  //Empty string

  if (l == NULL){

    sprintf(str, "()");

    return;

  }

  if (l->car == NULL) {

    sprintf(str, "%d", l->value);

    return;

  }

  char val[100];

  const lisp* temp = l;

  //Open the string

  sprintf(str, "(");

  while (1) {

    lisp_tostring(temp->car, val);

    temp = temp->cdr;

    //If temp has a value, add this to the string

    if (temp)

      sprintf(str, "%s%s ", str, val);

    //if temp does not have a value, close with bracket.

    else {

      sprintf(str, "%s%s)", str, val);

      break;

    }

  }

}



lisp* lisp_car(const lisp* l){

  return l->car;

}



lisp* lisp_cdr(const lisp* l){

  return l->cdr;

}



bool lisp_isatomic(const lisp* l){

  //Both pointers dont point to anything? Return true.

  if(l==NULL){

    return false;

  }

  if(l->car==NULL && l->cdr==NULL){

    return true;

  }

  else{

    return false;

  }

}



lisp* lisp_copy(const lisp* l){

  if(l == NULL){

    return NULL;

  }

  if (l->car == NULL){

    return lisp_atom(l->value);

  }

  lisp* new_lisp = lisp_cons(lisp_copy(l->car), lisp_copy(l->cdr));

  return new_lisp; 

}



void test(void){

  char str[LISTSTRLEN];

  //tests

  lisp* l1 = lisp_cons(lisp_atom(12345), NULL);

  assert(l1);

  assert(lisp_length(l1)==1);

  lisp_tostring(l1, str);

  assert(strcmp(str, "(12345)")==0);

  assert(lisp_isatomic(l1)==false);

  assert(lisp_isatomic(lisp_car(l1))==true);

  lisp_free(&l1);

  /////

  lisp* l2 = lisp_cons(lisp_atom(-345), NULL);

  assert(l2);

  assert(lisp_length(l2)==1);

  lisp_tostring(l2, str);

  assert(strcmp(str, "(-345)")==0);

  assert(lisp_isatomic(l2)==false);

  assert(lisp_isatomic(lisp_car(l2))==true);

  lisp_free(&l2);

  ///////////////////////////////////////////

  lisp* l3 = lisp_cons(lisp_atom(-32), NULL);

  assert(l3);

  assert(lisp_length(l3)==1);

  lisp_tostring(l3, str);

  assert(strcmp(str, "(-32)")==0);

  assert(lisp_isatomic(l3)==false);

  assert(lisp_isatomic(lisp_car(l3))==true);

  

  lisp* l4 = lisp_cons(lisp_atom(1), l3);

  assert(l4);

  assert(lisp_length(l4)==2);

  lisp_tostring(l3, str);

  lisp_tostring(l4, str);

  assert(strcmp(str, "(1 -32)")==0);

  

  lisp* l5 = lisp_cons(lisp_atom(3), lisp_cons(lisp_atom(4), NULL));

  assert(l5);

  assert(lisp_length(l5)==2);

  lisp_tostring(l5, str);

  assert(strcmp(str, "(3 4)")==0);



  lisp* l6 = lisp_cons(l4, l5);

  assert(l6);

  assert(lisp_length(l6)==3);

  lisp_tostring(l6, str);

  assert(strcmp(str, "((1 -32) 3 4)")==0);

    

  lisp* l7 = lisp_cons(lisp_atom(345), l6);

  assert(l7);

  assert(lisp_length(l7)==4);

  lisp_tostring(l7, str);

  assert(strcmp(str, "(345 (1 -32) 3 4)")==0);



  lisp_free(&l7);

}



void lisp_free(lisp** l){

  if(*l==NULL){

    return;

  }

  lisp_free(&(*l)->car);

  lisp_free(&(*l)->cdr);

  free(*l); 

  *l = NULL;

  return;

}



/////// Extensions

// I wrote some dummy functions in order to compile the code.

//The code failes the asserstion test on line 132 from testlisp.c file.

//Which is the first asserstion test of extensions.



lisp* lisp_fromstring(const char* str){

   if (str == NULL){

    return 0;

  }

  return 0;

}



lisp* lisp_list(const int n, ...){

  int temp = n;

  temp++;

  return 0;

}



void lisp_reduce(void (*func)(lisp* l, atomtype* n), lisp* l, atomtype* acc){

  if(l==NULL){

    return;

  }

  acc++;

  (*func)(l, acc);

  acc++;

  return; 

}

