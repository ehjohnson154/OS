#include "llist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX 2048
//Took heavy help from https://www.learn-c.org/en/Linked_lists


void llist_insert_head(struct node **head, struct node *n){
    //set next of new node to current head, assign head to n.
    n->next = *head;
    *head = n;

}

struct node *llist_delete_head(struct node **head){
    //check if list exists. If it does, move next node to head, free head, and set next node to head.
    struct node * next_node = NULL;
    if (*head == NULL) {
        return NULL;
    }

    next_node = (*head)->next;
    node_free(*head);
    *head = next_node;

    return *head;

}

void llist_insert_tail(struct node **head, struct node *n){
    //if list is not empty, search through list until you find end, then add n
    if(*head == NULL){
         *head = n;
    }
    else{
        struct node * current = (*head);
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = n;
    }

}

void llist_print(struct node *head){
    //iterate through pointers and print out current val
    struct node * current = head;

    if(current == NULL){
        printf("\nEmpty list!\n");
    }

    while (current != NULL) {
        printf(" -> %d ", current->value);
        current = current->next;
    }

}

void llist_free(struct node **head){
    //iterate through pointers and free up all
    struct node * current = (*head);
    while (*head != NULL){
        current = (*head);
        *head = (*head) -> next;
        node_free(current);
    }

}

struct node *node_alloc(int value){
    // new node, allocate memory using malloc(), assign val and null ptr.
    struct node * temp  = (struct node *)malloc(sizeof(struct node)); 
    temp->value = value;
    temp->next = NULL;
    return temp;

}

void node_free(struct node *n){
    free(n);
}

int main(int argc, char *argv[])
{
    //create new list
    struct node * linked_list = node_alloc(-1);
    llist_free(&linked_list);

    int i = 1; //set to 1 to avoid initial command
    while(i != (argc)){//check current command and follow instructions.
        if(strcmp(argv[i], "ih")==0){
            i++;
            int val = atoi(argv[i]);
            struct node * temp = node_alloc(val);
            llist_insert_head(&linked_list, temp);
            i++;
        }
        if(strcmp(argv[i], "it")==0){
            i++;
            int val = atoi(argv[i]);
            struct node * temp = node_alloc(val);
            llist_insert_tail(&linked_list, temp);
            i++; 
        }
        if(strcmp(argv[i], "dh")==0){
            llist_delete_head(&linked_list);
            i++;
        }
        if(strcmp(argv[i], "f")==0){
            llist_free(&linked_list);
            i++;
        }
        if(strcmp(argv[i], "p")==0){
            llist_print(linked_list);
            i++;   
        }

        //printf("inside loop!");
    }

    return 0;

}