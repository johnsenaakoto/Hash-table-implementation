#include <stdio.h>
#include <stdlib.h>
#define HASHTABLE_SIZE 13

typedef struct node{
  int val;
  struct node *next;
}node_t;
int search_list (node_t *head, node_t **previous, node_t **current, int data) {
  int found = 0;
  *previous = NULL;
  *current = head;
  while (*current != NULL && !found) {
    if ((*current)->val == data){
      found = 1;
    }
    else {
      *previous = *current;
      *current = (*current)->next;
    }
  }
  return(found); 
}

void delete_node(node_t** head, int val, node_t** hashtable, int location){
  node_t* previous;
  node_t* current;
  int found;

  found = search_list(*head, &previous, &current, val);

  if (found) {
    if (previous == NULL){
      *head = current->next;
      hashtable[location]=NULL;
    }
    else {
      previous->next = current->next;
    }
    free(current);
  }
}

void insert_new_node(node_t** head, int val){
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  new_node->val = val;
  new_node->next = NULL;

  if(*head == NULL){
    *head = new_node;
  }
  else{
    node_t* ptr =*head;

    while(ptr->next != NULL){
      ptr = ptr->next;
    }

    ptr->next = new_node;
  }
}


int get_location(int val){
  return(val % HASHTABLE_SIZE);
}

void insert_into_table(node_t** hashtable, int val){
  int location = get_location(val);

  if (hashtable[location]==NULL){
    hashtable[location] = (node_t*)malloc(sizeof(node_t));

    node_t* head = NULL;
    insert_new_node(&head, val);

    hashtable[location] = head;
  }
  else{
    node_t* head = hashtable[location];
    insert_new_node(&head, val);
    hashtable[location] = head;
  }
}

void delete_from_table(node_t** hashtable, int val){
  int location = get_location(val);
  node_t* head = hashtable[location];

  if(head == NULL){
    printf("Location is empty");
  }
  else{
    delete_node(&head, val, hashtable, location);
  }
}


node_t** get_hashtable(){
  node_t** hashtable = calloc(HASHTABLE_SIZE, sizeof(node_t*));
  return(hashtable);
}

void display_table(node_t** hashtable){
  for(int i = 0; i < HASHTABLE_SIZE; i++){
    node_t * head = hashtable[i];

    printf("%d: ", i);

    if (head == NULL){
      printf("NULL");
    }
    else{
      node_t*ptr = head;
      while (ptr != NULL){
        printf("%d ", ptr->val);
        ptr = ptr->next;
      }
    }
    printf("\n");
  }
}


int main(void) {
  node_t** table =get_hashtable();

  insert_into_table(table, 0);
  insert_into_table(table, 2);
  insert_into_table(table, 78);
  insert_into_table(table, 12);
  insert_into_table(table, 9);
  insert_into_table(table, 6);

  insert_into_table(table, 4);
  insert_into_table(table, 1);
  insert_into_table(table, 5);
  insert_into_table(table, 23);
  insert_into_table(table, 72);
  insert_into_table(table, 52);

  insert_into_table(table, 42);
  insert_into_table(table, 50);
  insert_into_table(table, 60);
  insert_into_table(table, 17);
  insert_into_table(table, 34);
  insert_into_table(table, 57);

  display_table(table);
  printf("\n");

  delete_from_table(table, 6);

  display_table(table);
  return 0;
}