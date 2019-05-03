#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10


typedef struct {
  char type; // 0=fried chicken, 1=French fries
  int amount; // pieces or weight
  char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i){
  while ((first + 1) % BUFFER_SIZE == last){
    //do nothing -- no free buffer item
    printf("No free buffer item!\n");
  }
  memcpy(&buffer[first], i, sizeof(item));
  first = (first + 1) % BUFFER_SIZE;
  logValues();
}

item* consume(){
  item* i = malloc(sizeof(item));
  while (first == last){
    // do nothing -- nothing to consume
    printf("Nothing to consume!\n");
  }
  memcpy(i, &buffer[last], sizeof(item));
  last = (last + 1) % BUFFER_SIZE;
  logValues();
  return i;
}

void logValues(){
  printf("first : %d\t last : %d\n", first, last);
  return;
}

item* init(char type, int amount, char unit){
  item* i = malloc(sizeof(item));
  i->type = type;
  i->amount = amount;
  i->unit = unit;
  return i;
}

int main(){
  item* order1 = init('1',5,'0');
  item* order2 = init('0',3,'1');
  printf("Log Initialization:\nfirst : %d\tlast : %d\n\n", first, last);
  produce(order1);
  produce(order2);
  consume();
  return 0;
}
