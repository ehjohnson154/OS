
void *myalloc(int size);
void print_data(void);
void myfree(void *p);


struct block *find_space(struct block *head, int size_needed);

void split_space(struct block *cur_node, int req_size);

struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
};
