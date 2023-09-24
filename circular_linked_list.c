#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *generateLinkedList(){
    //generate a random data linked list with 3 nodes

    /* Initialize nodes */
    struct node *head = NULL;
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

    /* Save address of first node in head */
    head = one;

    /* Connect nodes to make a circular */
    one->next = two;
    two->next = three;
    three->next = head;

    return head;
}

void printLinkedList(struct node *p){
    struct node *current = p;

    do {
        printf("%d --> ", current->data);
        current = current->next;
    } while(current != p); // detect if the current one is the head of the circular linked list
    printf("\n");
}

struct node * insertNode(struct node *head, int position, int data) {
    //create a new node
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;

    //if list is empty
    if(head == NULL) {
        head = newNode;
        newNode->next = head;
        return head;
    }

    //if insert at the head
    if(position == 1) {
        //store old head
        struct node *oldHead = head;

        //update head
        newNode->next = oldHead;
        head = newNode;

        //find tail and link to new head
        struct node *current = oldHead;
        while(current->next != oldHead) {
            current = current->next;
        }
        current->next = head;
        printf("inserted node at position %d, with the data: %d\n", position, data);
        return head;
    }

    //find node before insertion point
    struct node *current = head;
    int i;
    for(i = 0; i < position - 2; i++) {
        current = current->next;
    }

    //insert new node
    newNode->next = current->next;
    current->next = newNode;
    printf("inserted node at position %d, with the data: %d\n", position, data);
    return head;
}

struct node * deleteNode(struct node *head, int position) {

    //if empty list
    if(head == NULL) {
        return NULL;
    }

    //if deleting head node
    if(position == 1) {
        struct node *temp = head;
        head = head->next;

        //find tail and update next
        struct node *current = head;
        while(current->next != temp) {
            current = current->next;
        }
        current->next = head;

        free(temp);

        printf("deleted node position: %d\n", position);
        return head;

    }

    //if other position
    struct node *current = head;

    for(int i=0; i<position-2; i++) {
        current = current->next;
    }

    struct node *temp = current->next;
    current->next = temp->next;
    free(temp);

    printf("deleted node position: %d\n", position);
    return head;

}

struct node * changeNodeData(struct node *head, int position, int newData){

    if(position == 1) {
        head->data = newData;
        printf("changed node data to %d at position %d\n", newData, position);
        return head;
    }

    struct node *current = head;

    for(int i=0; i<position-1; i++) {
        current = current->next;
    }
    current->data = newData;
    printf("changed node data to %d at position %d\n", newData, position);
    return head;
}

struct node * sortLinkedList(struct node *head){
    struct node * current = head;
    int n = 0;

    do {
        current = current->next;
        n++;
    } while (current != head);

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

    current = head;
    for (i = 0; i < n-1 ; i++){
        current = current->next;
    }
    current->next = head;
    printf("linked list sorted.\n");
    return head;
}

struct node *mergeLinkedList(struct node *first, struct node *second) {

    struct node *newHead = malloc(sizeof(struct node));

    struct node *firstTail = first;
    struct node *secondTail = second;

    //find tail of first list
    while(firstTail->next != first) {
        firstTail = firstTail->next;
    }

    //find tail of second list
    while(secondTail->next != second) {
        secondTail = secondTail->next;
    }

    //merge both lists
    newHead->data = first->data;
    newHead->next = first->next;
    firstTail->next = second;
    secondTail->next = newHead;

    printf("two linked lists merged\n");
    return newHead;

}

int main(){

    struct node *head = generateLinkedList();
    printf("first circular linked list generated: \n");
    printLinkedList(head);

    head = insertNode(head,1,666);
    head = insertNode(head, 3, 333);
    printLinkedList(head);

    head = deleteNode(head,1);
    printLinkedList(head);

    head = changeNodeData(head,4,123);
    printLinkedList(head);

    head = sortLinkedList(head);
    printLinkedList(head);

    struct node * tail = generateLinkedList();
    printf("second circular linked list generated: \n");
    printLinkedList(tail);

    head = mergeLinkedList(head,tail);
    printLinkedList(head);

    head = sortLinkedList(head);
    printLinkedList(head);

}