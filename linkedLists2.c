#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


struct alias {
	char *key;
	char *value;
  struct alias *next;
};

struct alias *alias_create(char *key, char *value){
	struct alias *alias = malloc(sizeof(struct alias));

	alias->key = malloc(strlen(key)+1);
    strcpy(alias->key, key);

	alias->value = malloc(strlen(value)+1);
    strcpy(alias->value, value);

    alias->next = NULL;

	return alias;
}

struct linkedList{
  struct alias *first;
};

struct linkedList *createLL(){
  struct linkedList *list = (struct linkedList*) malloc(sizeof(struct linkedList));
  list-> first = NULL;
  return list;
}

void printLL(struct linkedList *list){
  struct alias *ptr;
  ptr = list->first;
  if(ptr != NULL){

    printf("%s\n", "First:");
    printf("%s\n", "_________________________________");
    printf("Adress: %p\n",ptr);
    printf("%s\n", "_________________________________");
    printf(" %s\n","               |");
    printf(" %s\n","               |");
    printf(" %s\n","               V");
    int n = 0;
    while (ptr->next != NULL){
      printf("Node: %d\n", n);
      printf("%s\n", "_________________________________");
      printf("key: %s\n", ptr->key);
      printf("Value: %s\n", ptr->value);
      printf("Adress: %p\n", ptr);
      printf("Next: %p\n", ptr->next);
      printf("%s\n", "_________________________________");

      printf(" %s\n","               |");
      printf(" %s\n","               |");
      printf(" %s\n","               V");
      ptr = ptr->next;
      n++;
    }
    if(ptr != NULL){
      printf("Node: %d\n", n);
      printf("%s\n", "_________________________________");
      printf("Key: %s\n", ptr->key);
      printf("Value: %s\n", ptr->value);
      printf("Adress: %p\n", ptr);
      printf("Next: %p\n", ptr->next);
      printf("%s\n", "_________________________________");

    }

  }else{
    printf("%s\n","Error: Empty list" );
  }

}

void addNode(struct linkedList *list, char *key, char *value){
  // maak nieuwe allias
  // funtie returned wijzer naar een struct alias
  struct alias *alias = alias_create(key,value);

  //current is een wijzer naar first, first is van de vorm struct allias
  struct alias *current = list->first;

  // als first NULL is, voeg eerste alias toe
  if(current == NULL){
    // first word wijzer naar eerste alias
    list->first = alias;

  }else{
    // next is een wijzer naar de volgende allias van de huidige alias
    struct alias *next= current->next;
    // ittereert over alisassen tot next van current NULL is
    // als next NULL is, einde lijst bereikt -> voeg alias hier toe
    while(next != NULL){
      // current alias word de volgende alias
      current = next;
      next = current->next;
    }
    //  voeg nieuwe allias toe aan achetkant lijst
    current->next = alias;
  }
}

// Return the value of the element with the given key. If the given key was not
// found, the value NULL is returned.
char *alias_list_lookup(struct linkedList *list, char *key){
  // ptr is een pointer naar een struct alias
  struct alias *ptr;
  //  ptrKey is een pointer naar de key van ptr
  char *ptrKey;
  ptr = list->first;
  ptrKey = ptr->key;

  // zolang ptr niet NULL is, dus zolang de alias niet leeg is voer while lus uit
  while (ptr->next != NULL) {
    // strncmp vergelijkt 2 string met elkaar en returned 0 als ze gelijk zijn
    // strncmp neemt 3 argumentn; 2 strings en maximum te vergelijke lengte
    if (strncmp(ptrKey,key,strlen(key)+1) == 0){
      // als ptrKey gelijk is aan key return value van key
      return ptr->value;
    }else{
      // itereer naar volgende alias
      ptr = ptr->next;
      ptrKey = ptr->key;
    }
  }
  // while lus stopt bij voor laatste alias dus voor nog een keer uit vool laatste alias
  if(strncmp(ptrKey,key,strlen(key)+1) == 0){
    return ptr->value;
  }else{
    // als key niet bestaat in list return NULL
    return NULL;
  }

}

// Remove the element with given key from the given list. If the given key
// was not found, 0 is returned, otherwise 1 is returned.
int alias_list_remove(struct linkedList *list, char *key){
  // structure list:
  // ---------     -----    -----------
  // |previous| -->|ptr|--> | ptr->next|
  // ----------    -----    ------------


  // ptr is een pointer naar een struct alias
  struct alias *ptr;
  // previous is een pointer naar een struct alias
  struct alias *previous;
  // initialise previous als NULL, bij start itteratie is er nog geen vorige
  previous = NULL;
  //  ptrKey is een pointer naar de key van ptr
  char *ptrKey;
  ptr = list->first;
  ptrKey = ptr->key;

  // zolang ptr niet NULL is, dus zolang de alias niet leeg is,voer while lus uit
  while (ptr->next != NULL) {
    // strncmp vergelijkt 2 string met elkaar en returned 0 als ze gelijk zijn
    // strncmp neemt 3 argumentn; 2 strings en maximum te vergelijke lengte
    if (strncmp(ptrKey,key,strlen(key)+1) == 0){
      // 1. als previous == NULL betekent dit dat we de eerste alias in de lijst willen verwijderen
      // anders zie 2.
      if(previous == NULL){
        // list->first = list->first->next, de 2 alias van de lijst word het nieuwe begin van de lijst
        ptr = ptr->next;
        return 1;

      //2.  als 1. niet waar is dan willen we een element tussen het begin en einde van de lijst verwijderen
      // anders zie 3.
      }else{
        // ---------     -----    -----------
        // |previous| -->|ptr|--> | ptr->next|
        // ----------    -----    ------------
        // ---------       -----------
        // |previous| --> | ptr->next|
        // ----------     ------------
        // ptr word verwijderd
        previous->next = ptr->next;
        return 1;
      }

    }else{
      // update previous, previous word huide alias
      previous = ptr;
      // itereer naar volgende alias
      ptr = ptr->next;
      ptrKey = ptr->key;
    }
  }
  // LET OP: ptr is aangepast in while lus. Na while lus list->first gebruiken!!!
  if(strncmp(ptrKey,key,strlen(key)+1) == 0){
    // Als er maar een alias in de lijst zit list->first = NULL
    if(previous == NULL ){
      list->first = NULL;
      return 1;
    }else{
      // 3. uitvoering while lus stopt bij laatste alias
      // uitvoering speciaal geval voor verwijderen laatste alias
      previous->next = NULL;
      return 1;
    }

  }else{
    // als key niet bestaat in list return NULL
    return 0;
  }

}

int main(){
  struct linkedList *list = createLL();
  addNode(list,"Name","Laurens");
  addNode(list,"Age","18");
  addNode(list,"Sex","Male");
  addNode(list,"Study","Computer Science");
  printLL(list);
  alias_list_remove(list,"Sex");
  printLL(list);


}
