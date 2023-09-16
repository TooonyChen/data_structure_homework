#include<stdio.h>
#include<stdlib.h>
#include <time.h>

struct node
{
    int data;
    struct node *next;
};

struct node *generateLinkedList(){
    //generate a random data linked list with 3 nodes

    /* Initialize nodes */
    struct node *head;
    struct node *one = NULL;
    struct node *two = NULL;
    struct node *three = NULL;

    /* Allocate memory */
    one = malloc(sizeof(struct node));
    two = malloc(sizeof(struct node));
    three = malloc(sizeof(struct node));

    /* Assign data values */
    int upper = 1001;
    upper++;
    // generate random number from 0 to 1000
    srand(time(NULL)); // set the seed of random number by time
    one->data = (rand() % upper);
    two->data = (rand() % upper);
    three->data = (rand() % upper);

    /* Connect nodes */
    one->next = two;
    two->next = three;
    three->next = NULL;

    /* Save address of first node in head */
    head = one;
    return head;
}

void printLinkedList(struct node *p){
    printf("printed linked list: ");
    while (p != NULL){
        printf("%d --> ", p->data);
        p = p->next;
    }
    printf("\n");
}

void insertNode(struct node **head, int position, int data){

    /* initialize newNode */
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode->data = data;

    if (position == 1) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct node *temp = *head;
        int i = 1;
        while (i < position-1 && temp != NULL) {
            temp = temp->next;
            i++;
        }
        if (temp == NULL) return;
        newNode->next = temp->next;
        temp->next = newNode;
    }
    printf("inserted node at position %d, with the data: %d\n", position, data);
}

void changeNodeData(struct node **head, int position, int newData){
    struct node *temp = *head;
    int i = 1;
    while(i < position && temp != NULL){
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Position is invalid\n");
        return;
    }

    temp->data = newData;

    printf("changed node data to %d at position %d\n", newData, position);

}

void deleteNode(struct node *head, int position){
    struct node *temp = head;

    if (position == 1) {
        *head = *temp->next;
    } else {
        for (int i = 2; i < position; i++) { // find node
            if (temp->next != NULL){
                temp = temp->next;
            }
        }
        temp->next = temp->next->next; // delete
    }
    printf("deleted node position: %d\n", position);
}

void sortLinkedList(struct node *head){
    int n = 0;
    struct node *ptr;

    // find length
    ptr = head;
    while(ptr != NULL){
        n++;
        ptr = ptr->next;
    }

    // bubble sort initialize
    int i, j;
    struct node *p, *q;

    // bubble sort
    for (i = 0; i < n-1 ; i++){
        p = head;
        for (j = 0; j < n-i-1 ; j++){
            q = p->next;
            if(p->data > q->data){
                int temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
            p = p->next;
        }
    }
    printf("linked list sorted.\n");
}

void mergeLinkedList(struct node* front, struct node* end) {
    struct node* tail = front; // track tail

    // find tail
    while (tail->next != NULL) {
        tail = tail->next;
    }

    // append end list to tail
    tail->next = end;
    printf("two linked lists merged.\n");
}

int main(){

    struct node *head = generateLinkedList();
    printf("first linked list generated: \n");
    printLinkedList(head);

    insertNode(&head, 1, 123);
    printLinkedList(head);
    insertNode(&head, 3, 234);
    printLinkedList(head);

    deleteNode(head, 1);
    printLinkedList(head);
    deleteNode(head, 3);
    printLinkedList(head);

    changeNodeData(&head, 2, 6666);
    printLinkedList(head);

    sortLinkedList(head);
    printLinkedList(head);

    struct node *new = generateLinkedList();
    printf("second linked list generated: \n");
    printLinkedList(new);


    mergeLinkedList(head, new);
    printLinkedList(head);

    sortLinkedList(head);
    printLinkedList(head);

}
