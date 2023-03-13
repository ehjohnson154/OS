#include <stdio.h>
#include <sys/mman.h> //mmap()


MEM
<points down>
+----------------------------------------------+
    |100 bytes| | 200 bytes |
+----------------------------------------------+
^              ^
n 

struct node {
    int len;
    struct node *next;
};

int main(void)
{
    void *mem = mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);

    //PART 2

    char *s = mem;
    char *p = s + 3;

    struct node *n = (struct node *)p; //

    n->len = 100;
    n->next = NULL;










    //PART 1
    //map private means child would get its own copy of it (?)

    // struct node n = { .len=100, .next=NULL};

    // memcpy(mem, &n, sizeof n);

    // printf("%d\n", mem->len);
    // printf("%p\n", n.next);

    // struct node *p = mem;
    // int *i = mem;

    // *i = 200;

    // // p->len = 100;
    // // p ->next = NULL;

    // printf("%d\n", p->len);
    // printf("%p\n", p->next);
}