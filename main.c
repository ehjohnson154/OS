

void *myalloc(int size);
void myfree(void *p);

struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
}

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



void *heap = mmap(NULL, 1024, PROT_READ|PROT_WRITE,
                  MAP_ANON|MAP_PRIVATE, -1, 0);

    //ARGUMENTS ARE:
    // NULL: I don't care what virtual address the block is assigned.
    // 1024: I want this many bytes. (The OS will likely round this up to its memory page size).
    // PROT_READ|PROT_WRITE: I want R/W permission on the memory.
    // MAP_ANON|MAP_PRIVATE: I don't want this associated with any file on disk; I want to enable copy-on-write for any subprocesses that I fork(). (We won't fork() in this project, but it's nice to be proper.)
    // -1: This is the file descriptor for the file we're mapping. Since we're not mapping a file (MAP_ANON), we set this to -1 to indicate it's unused.
    // 0: This is the offset within the file to start mapping. Since we're not mapping a file, this is unused and we set it to 0.

