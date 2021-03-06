#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define jval_i(_val) _val.i
#define jval_l(_val) _val.l
#define jval_f(_val) _val.f
#define jval_d(_val) _val.d
#define jval_v(_val) _val.v
#define jval_c(_val) _val.c
#define jval_s(_val) _val.s
#define NUMBER 10

typedef union _Jval {
	int i;
	long l;
	float f;
	double d;
	void *v;
	char *s;
	char c;
} Jval;

Jval new_jval_i(int value){
	Jval temp;
	temp.i = value;
	return temp;
}

Jval new_jval_l(long value){
	Jval temp;
	temp.l = value;
	return temp;
}

Jval new_jval_f(float value){
	Jval temp;
	temp.f = value;
	return temp;
}

Jval new_jval_d(double value){
	Jval temp;
	temp.d = value;
	return temp;
}

Jval new_jval_v(void *value,size_t size){
	Jval temp;
	temp.v = malloc(size);
	memcpy(temp.v, value, size);
	return temp;
}

Jval new_jval_c(char value){
	Jval temp;
	temp.c = value;
	return temp;
}

Jval new_jval_s(char *s){
	Jval temp;
	asprintf(temp.s, "%s", s);
	return temp;
}

void exch_jval(Jval *a, Jval *b){
	Jval temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int compare_i(Jval *a, Jval *b){
	return a->i - b->i;
}

void sort_gen(Jval a[],int l,int r, int (*compare)(Jval *,Jval *)){
	if (r<=l) return;
	int i = l-1; int j=r;
	int p = l-1; int q=r;
	while (1){
		while (compare(&a[++i],&a[r]) < 0);
		while (compare(&a[--j],&a[r]) > 0) if (j == l) break;
		if (i >= j) break;
		exch_jval(&a[i],&a[j]);
		if (compare(&a[i],&a[r])==0) exch_jval(&a[++p],&a[i]);
		if (compare(&a[j],&a[r])==0) exch_jval(&a[--q],&a[j]);
	}
	exch_jval(&a[i],&a[r]);
	j = i-1;
	i = i+1;
	int k;
	for (k=l;k<=p;k++) exch_jval(&a[k],&a[j--]);
	for (k=r-1;k>=q;k--) exch_jval(&a[k],&a[i++]);
	sort_gen(a,l,j,compare);
	sort_gen(a,i,r,compare);
}

void print_jval_i(Jval a[],int size){
	int i;
	for (i=0;i<size;i++) printf("%d ",jval_i(a[i]));
	printf("\n");
}

int search_gen(Jval a[],int l, int r, Jval item, int (*compare)(Jval *,Jval*)){
	if (l>= r) return -1;
	if (compare(&a[l], &item) == 0) return l;
	if (compare(&a[r], &item) == 0) return r;
	int m = (l+r)/2;
	if (compare(&a[m], &item)==0) return m;
	else if (compare(&a[m], &item) < 0) search_gen(a, m + 1, r, item, compare);
	else if (compare(&a[m], &item) > 0) search_gen(a, l, m, item, compare);
}

int main(){
	srand(time(NULL));
	int i;
	Jval arr[NUMBER];
	for (i=0;i<NUMBER;i++){
		arr[i] = new_jval_i(rand()%NUMBER);
	}
        printf("Random series of number: ");
	print_jval_i(arr, NUMBER);
	sort_gen(arr,0,NUMBER-1, compare_i);
        printf("\nSorted: ");
	print_jval_i(arr, NUMBER);
	int index,n;
	Jval item;
	printf("\nEnter the item: ");
	scanf("%d",&n);
	item = new_jval_i(n);
	index = search_gen(arr,0,NUMBER-1,item,compare_i);
	if (index == -1) printf("Cannot find %d.\n",jval_i(item));
	else printf("%d is found at Index = %d\n",jval_i(item),index+1);
	return 0;
}
