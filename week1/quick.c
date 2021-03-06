#include<stdio.h>
#include<time.h>
#define MAX 10
void sort(int a[], int r, int l);
void exch(int a[], int i, int j);

void main(){
  srand(time(NULL));
  int i;
  int a[MAX];
  for(i = 0; i < MAX; i++){
    a[i] = 1+rand()%10;
  }

  sort(a,0,MAX-1);

  for(i = 0; i < MAX; i++){
    printf("%d\n", a[i]);
  }
}


void sort(int a[], int r, int l){
  if(r <= l) return;
  int i = l - 1; int j = r;
  int p = l - 1; int q = r;
  int k;
  while(1){
    while(a[++i] < a[r]);
    while(a[r] < a[--j]) if(j == l) break;
    if(i >= j) break;
    exch(a,i,j);
    if(a[i] == a[r]) exch(a, ++p, i);
    if(a[j] == a[r]) exch(a, --q, j);
  }

  exch(a,i,r);
  j = i - 1;
  i = i + 1;
  for(k = l; k <= p; k++) exch(a,k,j--);
  for(k = r - 1; k >= q; k--) exch(a,k,i++);
  sort(a,l,j);
  sort(a,i,r);
}

void exch(int a[], int i, int j){
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}

