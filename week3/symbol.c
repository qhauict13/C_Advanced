#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_SIZE 10
#define INCREMENTAL_SIZE 10

typedef struct {
  void* key;
  void* value;
} entry;

typedef struct {
  entry *entries;
  int size, total;
  entry (*make_node)(void*, void*);
  int (*compare)(void*, void*);
} symbolTable;

int compare(void* a, void* b){
  return strcmp((char*)a, (char*)b);
}

entry make_node(void *a, void *b){
  if(a == NULL || b == NULL){
    fprintf(stderr,"Error in %s, line %d\n", __FILE__, __LINE__);
    exit(1);
  }
  entry temp;
  temp.key = (char*)malloc(sizeof(char)*(strlen((char*)a))+1);
  strcpy((char*)temp.key, (char*)a);
  temp.value = b;
  return temp;
}

//-----------------------------------------------------
symbolTable create_table(entry (*make_node)(void*, void*), int (*compare)(void*, void*)){
  symbolTable table;
  table.size = INITIAL_SIZE;
  table.total = 0;
  table.make_node = make_node;
  table.compare = compare;
  table.entries = (entry*)malloc(sizeof(entry)*table.size);

  if(table.entries == NULL){
    fprintf(stderr,"Error in %s, line %d\n", __FILE__, __LINE__);
    exit(1);
  }

  return table;
}
//----------------------------------------------------
void add_entry(void* key, void* value, symbolTable *table){
  entry *tempEntries;
  int i;
  if(key == NULL || value == NULL){
    fprintf(stderr, "Error in %s, line %d\n",__FILE__, __LINE__);
    exit(1);
  }

  if(table->entries == NULL){
    fprintf(stderr, "Error in %s, line %d\n",__FILE__, __LINE__);
    exit(1);
  }

  if((table->total+1) >= table->size){
    table->size += INCREMENTAL_SIZE;
    tempEntries = (entry*)realloc(table->entries, sizeof(entry)*table->size);

    if(tempEntries != NULL){
      table->entries = tempEntries;
    }
    else {
      fprintf(stderr, "Error in %s, line %d\n",__FILE__, __LINE__);
      exit(1);
    }
  }

  table->entries[table->total] = table->make_node(key,value);

  (table->total)++;
}
//-----------------------------------------------------
entry *get_entry(void* key, symbolTable *table){
  if(key == NULL || table->entries == NULL){
    fprintf(stderr,"Error in %s, line %d\n", __FILE__, __LINE__);
    exit(1);
  }

  int i = 0;
  for(i = 0; i < table->total; i++){
    if((table->compare(table->entries[i].key, key)) == 0) return &(table->entries[i]);
  }

  return NULL;
}
//-------------------------------------------------------
void drop_table(symbolTable *table){
  if(table == NULL){
    fprintf(stderr, "Error in %s, line %d\n",__FILE__, __LINE__);
    exit(1);
  }

  if(table->entries != NULL){
    int i = 0;
    while(i < table->total){
      free(table->entries[i].key);
      free(table->entries[i].value);
      i++;
    }
    free(table->entries);
  }

  table->total = 0;
  table->size = INITIAL_SIZE;
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
  symbolTable table;
  table = create_table(make_node, compare);
  char tempName[80], *searchName;
  long tempNum;
  entry* searchEntry = NULL;
  int i;
  for(;;){
    switch(get_menu()){
    case 1:
      printf("Enter a phone number: ");
      scanf("%ld", &tempNum);
      printf("Enter a name: ");
      flush_buffer();
      scanf("%[^\n]", tempName);
      add_entry((void*)tempName, (void*)tempNum, &table);
      printf("\n");

      break;

    case 2: printf("Enter a name: ");
      flush_buffer();
      scanf("%[^\n]", searchName);
      searchEntry = get_entry((void*)searchName, &table);
      if(searchEntry == NULL) printf("Contact not found!\n");
      else printf("%s\n", (char*)searchEntry->key);
      break;

    case 3: for(i = 0; i < table.total; i++){
        printf("%s - %ld\n", (char*)table.entries[i].key, (long)table.entries[i].value);
      }
      break;
    case 0:
      return 0;
    }
  }

  return 0;
}
