#include "my_malloc.h"

#include <stdio.h>
#include <sys/mman.h>


#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))
#define PADDED_SIZE(x) ((x) + GET_PAD(x))
//move a fix number of bytes, not a fixed number of ints
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset))) 
#define NEG_PTR_OFFSET(p, offset) ((void*)((char *)(p) - (offset))) 

struct block *head = NULL;  // Head of the list, empty. Defining global variable?


//OVERVIEW
    // If this is the first call, mmap() to get some space.
    //     At the same time, build a linked-list node inside the new space indicating its size and "in-use" status.
    // Walk the linked list in a loop and look for the first node that is:
    //     Not in-use
    //     Big enough to hold the requested amount (plus padding)
    // If the block is found:
    //     Mark it in-use.
    //     Return a pointer to the user data just after the linked list node (plus padding)).
    // If no such block is found:
    //     Return NULL

//WHAT WE WANT TO BE ABLE TO WRITE
//int *p = myalloc(sizeof(int) * 5);  // Allocate space for 5 ints


//COPIED FROM THING
void print_data(void) //make head global or add it here
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }
        b = b->next;
    }

    printf("\n");
}

void split_space(struct block *cur_node, int req_size)
{

    // TO BE IN SPLIT SPACE:
    // We know the size of node, and size of requested size. 
    // size - requested size + padding +-offset = new region size   

    //size of space - (struct + padding)
    //set cur to padded data size
    //set cur to used
    //ptr offset macro + padded size of data
    //make new struct block at new location. //KEEP TRACK OF PADDED SIZES

    int new_size = (cur_node->size - (PADDED_SIZE(sizeof(struct block)) + PADDED_SIZE(req_size))); //calculates size of new empty space
    
    cur_node->size = PADDED_SIZE(req_size); //sets size of original to new requested size
    cur_node->in_use = 1;

    struct block *new = PTR_OFFSET(cur_node, (PADDED_SIZE(sizeof(struct block)) + cur_node->size)); // pointer offset by size of block + size of cur_node
    new->in_use = 0;
    new->size = new_size;

    cur_node->next = new;

        
}

struct block *find_space(struct block *head, int size_needed){

    int pad_size_needed = (PADDED_SIZE(sizeof(struct block)) + PADDED_SIZE(size_needed)); //Calculate new space needed for split
    struct block * n = head;

    //walking through linked list for a free node
    while (n != NULL) {
        
        if ((n->size >= size_needed) && !(n->in_use)){ //Check if n's size is big enough for user request AND if its free

            if(n->size >= pad_size_needed){
                split_space(n,size_needed);
                return n;

            }
            else{
                n->in_use = 1; //mark as in use? 1 or 0?
                return n; //return address of n's data
            }
        }

        n = n->next; //move to next item
    }

    return NULL; //returns null if it did not return with address in loop
}


void *myalloc(int size){

    struct block *cur;

    //calling mmap to get space for heap.

    //pointer arithmetic
    //mmap gives us void pointers
    //need type for pointer arithmetic


    //creating linked list node inside of space (?)
    if (head == NULL) {
        head = mmap(NULL, 1024, PROT_READ|PROT_WRITE,
                    MAP_ANON|MAP_PRIVATE, -1, 0);
        head->next = NULL;
        head->size = 1024 - PADDED_SIZE(sizeof(struct block)); //Size becomes 1008?
        head->in_use = 0; //0 or 1 for in use?
    }

    //call algorithm to return the right address that can satisfy the memory required?
    cur = find_space(head, size);

    //copied from assignment.
    int padded_block_size = PADDED_SIZE(sizeof(struct block)); //Is this supposed to be int?
    return PTR_OFFSET(cur, padded_block_size);

}

// //PART 2
void myfree(void *p){
    //assign data as not in use
    //find memory with same length? But what if >1 assignments have equal memory allocation?
    
    // STEPS:
    // Find what section of data ptr points to //HOW TO DO POINTER SUBTRACTION FOR THIS?
    // flip in_use tag
    // set next to next->next->next

    //IS THIS INCORRECT?
    struct block *temp = (NEG_PTR_OFFSET(p, PADDED_SIZE(sizeof(struct block)))); //Finds position of linked list start
    temp->in_use = 0;

    //COALESCING:
    //From left to right, check what positions are free.
    //If current and next pos is free, merge current and next
    //If current or next are not free, walk.
    //Continue throughout
    //No need to check for initially requested free, as thats already done that above

    struct block * cur = head;

    while (cur != NULL){

        if(cur->next == NULL){
            break;
        }

        if((cur->next->in_use == 0) && (cur->in_use==0)){
            //makes size equal to itself + next blocks size + size of struct
            cur->size = cur->size + cur->next->size + PADDED_SIZE(sizeof(struct block)); 
            cur->next = cur->next->next;
        }
        else{
            cur = cur->next;
        }
    }
}


//MAIN//
int main (){

    //WHAT WE ARE LOOKING TO RUN
    // void *p;

    // print_data();
    // p = myalloc(64);
    // print_data();

    void *p, *q, *r, *s;

    p = myalloc(10); print_data();
    q = myalloc(20); print_data();
    r = myalloc(30); print_data();
    s = myalloc(40); print_data();

    myfree(q); print_data();
    myfree(p); print_data();
    myfree(s); print_data();
    myfree(r); print_data();

}


//Questions:


//I'm confused on how to place the heap and our head together.
//How does the heap connect to the head?
//Is 1 or 0 for in use? Confused by the mmap having -1 as the "not in use" condition.
//What type of function should our find space algorithm be? Is it not returning the pointer to struct block of the next in the link list?



//PART 2 questions:
//How do we reach the struct to assign the ptr as not in use?
//How do we split the data? How do i carve out data from one struct and add it to another?
//How do we find the data to "free"? If we search by Len, what if two items have identical len? How to do pointer subtraction?




//Maybe ANSWERED QUESTIONS:
//How many regions to we split up the block into? //Answer. We do not?
//How do we grab from multiple blocks? //Answer: We don't yet?
//How do we apply the padding? //Just on return statement I guess?