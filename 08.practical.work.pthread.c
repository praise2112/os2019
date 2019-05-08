#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

pthread_t tid[2];


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

void* pthread_process(void *arg)
{
    item* order1 = init('1',5,'0');
   item* order2 = init('0',3,'1');
   item* order3 = init('1',4,'0');
   
    unsigned long i = 0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("Log Initialization:\nfirst : %d\tlast : %d\n\n", first, last);
        printf("\n First thread processing\n Producing:\n");
         produce(order1);
	 produce(order2);
	 produce(order3);
    }
    else
    {
        printf("\n Second thread processing\n Consuming:\n");
        consume();
        consume();
    }

    for(i=0; i<(0xFFFFFFFF);i++);

    return NULL;
}


int main(){
  int i = 0;
  int err;
    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &pthread_process, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }

    sleep(5);
    return 0;
}





