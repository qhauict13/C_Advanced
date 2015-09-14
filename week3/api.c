#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 5
#define INCREMENTAL_SIZE 10

typedef struct{
  long number;
  char name[80];
} phone;

typedef struct{
  phone *entry;
  int total;
  int size;
} phoneBook;

void add_phone_number(long number, char *name, phoneBook* book){
  int i;
  phone *tempBook = NULL;
  if(book->total == 0){
    book->entry = (phone*)malloc(sizeof(phone)*INITIAL_SIZE);
    book->size = INITIAL_SIZE;
  }
  else if ((book->total+1) >= book->size){
    book->size += INCREMENTAL_SIZE;
    tempBook = (phone*)realloc(book->entry, sizeof(phone)*(book->size));

    if(tempBook != NULL){
      book->entry = tempBook;
    }
  }

  for(i = 0; i < book->total; i++){
    if((book->entry[i].number == number) && !strcmp(book->entry[i].name, name))
      {
        printf("Contact exist!\n");
        return;
      }
  }



  strcpy(book->entry[book->total].name, name);
  book->entry[book->total].number = number;
  book->total++;
}

char* get_phone_number(long number, phoneBook *book){
  int i;
  char *found = malloc(sizeof(char)*80);
  for(i = 0; i < book->total; i++){
    if(book->entry[i].number == number){
      strcpy(found, book->entry[i].name);
    }
  }
  return found;
}

int get_menu(){
  int option;
  printf("------------------------\n");
  printf("1.Enter new contact\n");
  printf("2.Search contact\n");
  printf("3.Print contact list\n");
  printf("0.Exit\n");
  printf("------------------------\n");
  printf("Your choice: ");
  scanf("%d", &option);
  printf("\n");
  return option;
}

void flush_buffer(){
  while(getchar() != '\n');
}
int main(){
  phoneBook book;
  long tempNum;
  char tempName[80], *searchName;
  int i;
  book.total = 0;
  for(;;){
    switch(get_menu()){
    case 1:
      printf("Enter a phone number: ");
      scanf("%ld", &tempNum);
      printf("Enter a name: ");
      flush_buffer();
      scanf("%[^\n]", tempName);
      add_phone_number(tempNum, tempName, &book);
      printf("\n");
      break;

    case 2: printf("Enter a phone number: ");
      scanf("%ld", &tempNum);
      searchName = get_phone_number(tempNum, &book);
      if(searchName == NULL) printf("Contact not found!\n");
      else printf("%s\n", searchName);
      break;

    case 3: for(i = 0;i < book.total; i++){
        printf("%ld - %s\n", book.entry[i].number,book.entry[i].name);
      }
      break;
    case 0: free(book); return 0;
    }
  }

  return 0;
}
