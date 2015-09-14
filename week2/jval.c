#include<stdio.h>
#include<stdlib.h>

typedef union{
  int i;
  long l;
  float f;
  double d;
  void *v;
  char *s;
  char c;
} jval;

int search_generic(jval a[], int l, int r, jval item, int (*compare)(jval *, jval *)){

}
