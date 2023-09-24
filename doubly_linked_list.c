#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next, *prev;
};

struct node *generateLinkedList(){
    //generate a linked list with 3 nodes

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
    one->data = 1;
    two->data = 2;
    three->data = 3;

    /* Connect nodes */
    one->next = two;
    two->next = three;
    three->next = NULL;

    three->prev = two;
    two->prev = one;
    one->prev = NULL;

    /* Save address of first node in head */
    head = one;
    return head;
}

void printLinkedList(struct node *p){
    printf("Printed doubly linked list: ");
    while (p != NULL){
        printf("%d <---> ", p->data);
        p = p->next;
    }
    printf("\n");
}

struct node * insertNode(struct node *head, int position, int data){
    /* initialize newNode */
    struct node *newNode;
    struct node *temp;
    newNode = malloc(sizeof(struct node));
    newNode->data = data;
    temp = head;


    if (position == 1) {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        newNode->next = head;
        newNode->prev = temp;
        head = newNode;
    } else {
        for(int i=1; i<position-1; i++){
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if(temp->next) temp->next->prev = newNode;
        temp->next = newNode;
        }
    printf("Inserted node in position %d, with the data: %d\n", position, data);
    return head;
}

struct node * changeNodeData(struct node *head, int position, int newData){
    struct node *temp = head;
    for(int i=0; i<position-1; i++){
        temp = temp->next;
    }
    temp->data = newData;

    printf("Changed node data to %d at position %d\n", newData, position);
    return head;
}

struct node * deleteNode(struct node *head, int position){
    struct node *temp = head;

    if (position == 1) {
        head = temp->next;
        head->prev = NULL;
        free(temp);
    } else {
        int i;
        for (i=1; i<position-1; i++) {
            temp = temp->next;
        }

        struct node *del = temp->next;
        temp->next = del->next;
        if (del->next) {
            del->next->prev = temp;
        }
        free(del);
    }
    printf("Deleted node position: %d\n", position);
    return head;
}

struct node * mergeLinkedList(struct node *first, struct node *second) {
    struct node * tail = first;

    //find the tail of the first linked list
    do {
        tail = tail->next;
    } while (tail->next != NULL);

    tail->next = second;
    second->prev = tail;
    printf("Two doubly linked lists merged.\n");
    return first;
}

struct node *sortLinkedList(struct node *head) {
    // initialize
    int n = 0;
    struct node *tail;

    // Find tail and count nodes
    tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        n++;
    }

    int i, j;
    struct node *p, *q;

    // Optimized bubble sort
    for (i = 0; i < n-1; i++) {
        p = head;
        for (j = 0; j < n-i; j++) {
            q = p->next;
            if (p->data > q->data){
                int temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
            p = p->next;
        }
    }
    printf("Linked list sorted!\n");
    return head;
}



int main(){
    struct node * head = generateLinkedList();
    printf("First doubly linked list generated.\n");
    printLinkedList(head);

    head = insertNode(head,1,234);
    printLinkedList(head);
    head = insertNode(head,4,123);
    printLinkedList(head);

    head = changeNodeData(head,5,456);
    head = changeNodeData(head, 1, 333);
    printLinkedList(head);

    head = deleteNode(head,1);
    printLinkedList(head);
    head = deleteNode(head,4);
    printLinkedList(head);

    struct node * tail = generateLinkedList();
    printf("Second doubly linked list generated.\n");
    head = mergeLinkedList(head,tail);
    printLinkedList(head);

    head = sortLinkedList(head);
    printLinkedList(head);
}
