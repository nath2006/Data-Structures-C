#include <stdio.h>
#include <stdlib.h>

/*
Struct untuk singel linkd list
*/
// struct tnode {
//   int value;
//   struct tnode *next;
// };

// struct tnode *head = 0 ;

typedef struct tnode {
  int value;
  struct tnode *next;
}Node;

Node *head = 0;

/* masukin data dari depan (dari head)*/
void masukinDataDariDepan(struct tnode **head, int x){
  //alokasikan memori untuk node baru
  struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));

  //isi data
  node->value = x;
  node->next = *head;

  //head sekarang node baru
  *head = node;
}

/*Masukin data dari belakang(dari tail)*/
void masukinDataDariBelaknag(struct tnode **head, int x){
  //alokasikan memori untuk node baru
  struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));

  if(node == NULL) return;

  node->value = x;
  node->next = NULL;

  /*jika list kosong, node langsung jadi head*/
  if (*head == NULL) {
    *head = node;
    return;
  }

  /*traverse ke node terakhir*/
  struct tnode *curr = *head;
  while (curr -> next !=NULL){
    curr = curr->next;
  }
  curr->next = node; //sambung node baru di akhir
}

/*insert di tengah */
void masukinDataDariTengah(struct tnode *prev_node, int x){
  if (prev_node == NULL) return;

  struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));

  if(node == NULL) return;
  node->value = x;

  //node baru menunjuk ke node setelah prev_node;
  node->next = prev_node->next;
  //prev_node sekarang menunjuk node baru
  prev_node->next = node;
}


void printList(struct tnode *head) {
    struct tnode *curr = head;
    while (curr != NULL) {
        printf("%d", curr->value);
        if (curr->next != NULL) {
          printf(" -> ");
        }
        curr = curr->next;
    }
    printf(" -> NULL\n");
}

int listLength(struct tnode *head){
  int count = 0;
  struct tnode *curr = head;
  while (curr != NULL){
    count++ ;
    curr = curr->next;
  }
  return count;
}

int main(){
  struct tnode *head = NULL;

  printList(head);
  masukinDataDariDepan(&head, 10);
  printList(head);
  masukinDataDariDepan(&head, 20);
    printList(head);
  masukinDataDariDepan(&head, 30);
    printList(head);
  masukinDataDariDepan(&head, 40);
    printList(head);
  masukinDataDariBelaknag(&head, 1000);
  printList(head);
  masukinDataDariTengah(head, 69);
  printList(head);

  return 0;
}
