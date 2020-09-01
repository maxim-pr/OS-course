#include <stdio.h>
#include <stdlib.h>

struct node
{
  int data;
  struct node* next;
};

struct linkedList
{
  int size;
  struct node* head;
};


// insert an integer value in the end of the list
void push_back(struct linkedList* list, int value)
{
  struct node* current = list->head;

  // increment 'current' until it is the last element of the list
  while (current->next != NULL) {
    current = current->next;
  }

  current->next = (struct node*)malloc(sizeof(struct node)); // create new node
  // initialize created node
  current->next->data = value;
  current->next->next = NULL;

  list->size++;

}


// insert an integer value at a specified index
void insert(struct linkedList* list, int index, int value)
{
  if (index < 0 || index > list->size) {
    printf("Index out of range\n");
    return;
  }

  struct node* current = list->head;
  // increment 'current' until it points to the node at position (index - 1)
  // if 'index' is zero, then keep 'current' pointing to head node
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  // create and setup a new node
  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  newNode->data = value;
  newNode->next = current->next;

  // point 'current' to new created node
  current->next = newNode;

  list->size++;
}


// delete list element at the specified index
void delete_node(struct linkedList* list, int index)
{
  if (index < 0 || index >= list->size) {
    printf("Index out of range\n");
    return;
  }

  struct node* current = list->head;
  // increment 'current' until it points to the node at position (index - 1)
  // if 'index' is zero, then keep 'current' pointing to head node
  for (int i = 0; i < index; i++) {
    current = current->next;
  }


  struct node* temp = current->next->next; // pointer to node at position (index + 1)
  free(current->next); // free memory of node at position 'index'
  current->next = temp;

  list->size--;
}


// print elements of list in the row
void print_list(struct linkedList* list)
{
  struct node* current = list->head;

  for (int i = 0; i < list->size; i++) {
    current = current->next;
    printf("%d ", current->data);
  }
  printf("\n");
}


// auxiliary function for freeing memory
void _free_list(struct node* node)
{
  if (node == NULL)
    return;

  _free_list(node->next);
  free(node);
}


// free memory allocated for the list
void free_list(struct linkedList* list)
{
  _free_list(list->head);
  free(list);
}



int main()
{
  // create and setup linked list
  struct linkedList* list = (struct linkedList*)malloc(sizeof(struct linkedList));
  list->size = 0;
  list->head = (struct node*)malloc(sizeof(struct node));
  list->head->next = NULL;
  list->head->data = 0;


  int request = -1;

  while (request != 0) {
    printf("Enter your request as a single integer number:\n");
    printf("0 - exit,\n");
    printf("1 - insert element in the end of the list,\n");
    printf("2 - insert element at specified index,\n");
    printf("3 - delete element at specified index\n\n");

    scanf("%d", &request);
    switch (request) {
      case 0:
        break;
      case 1:
        {
          int value;
          printf("Enter integer number to be added: ");
          scanf("%d", &value);
          push_back(list, value);
        }
        break;
      case 2:
        {
          int value, index;
          printf("Enter integer number to be added and the index: ");
          scanf("%d%d", &value, &index);
          insert(list, index, value);
        }
        break;
      case 3:
        {
          int index;
          printf("Enter index: ");
          scanf("%d", &index);
          delete_node(list, index);
        }
        break;
      default:
        break;
    }
    printf("\tList: ");
    print_list(list);
    printf("\n");
  }

  free_list(list);

  return 0;
}
