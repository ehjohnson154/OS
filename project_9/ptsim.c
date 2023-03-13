#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MEM_SIZE 16384  // MUST equal PAGE_SIZE * PAGE_COUNT
#define PAGE_SIZE 256  // MUST equal 2^PAGE_SHIFT
#define PAGE_COUNT 64
#define PAGE_SHIFT 8  // Shift page number this much

#define PTP_OFFSET 64 // How far offset in page 0 is the page table pointer table

// Simulated RAM
unsigned char mem[MEM_SIZE];

//
// Convert a page,offset into an address
//
int get_address(int page, int offset)
{
    return (page << PAGE_SHIFT) | offset;
}

//
// Initialize RAM
//
void initialize_mem(void)
{
    memset(mem, 0, MEM_SIZE);

    int zpfree_addr = get_address(0, 0);
    mem[zpfree_addr] = 1;  // Mark zero page as allocated
}

//
// Get the page table page for a given process
//
unsigned char get_page_table(int proc_num)
{
    int ptp_addr = get_address(0, PTP_OFFSET + proc_num);
    return mem[ptp_addr];
}

//returns a free page to allocate
int allocate_page(void){

    for (int i = 0; i < PAGE_COUNT; i++){
        int addr = get_address(0, i); //should this be by pointer offset
        if (mem[addr] == 0){
            mem[addr] = 1;
            return addr;
        }

    }

    return 0xff;

}


//
// Allocate pages for a new process
//
// This includes the new process page table and page_count data pages.
//
void new_process(int proc_num, int page_count)
{

        // Get the page table page
        //Think of this as our index
    int page_table = allocate_page(); 
    
        // If the initial page table allocation fails (due to out-of-memory), the function should print:
        if (page_table == 0xff){
            printf("OOM: proc %d: page table\n", proc_num);
        }

    // Set this process's page table pointer in zero page
    mem[PTP_OFFSET + proc_num] = page_table;

    // Allocate data pages
    for (int i = 0; i < page_count; i++){ //for each requested page, allocate and assign.

        int new_page = allocate_page(); //makes page for first requested page

        // If any of the subsequent page allocations fail, it should print:
        if (new_page == 0xff){
            printf("OOM: proc %d: data page\n", proc_num);
        }

        // Set the page table to map virt -> phys
        // Virtual page number is i
        // Physical page number is new_page

        int pt_addr = get_address(page_table, i); //gets "pointer" to fit with index
        mem[pt_addr] = new_page; //allocates pointer to index
    }

}

//
// Print the free page map
//
// Don't modify this
//
void print_page_free_map(void)
{
    printf("--- PAGE FREE MAP ---\n");

    for (int i = 0; i < 64; i++) {
        int addr = get_address(0, i);

        printf("%c", mem[addr] == 0? '.': '#');

        if ((i + 1) % 16 == 0)
            putchar('\n');
    }
}

//
// Print the address map from virtual pages to physical
//
// Don't modify this
//
void print_page_table(int proc_num)
{
    printf("--- PROCESS %d PAGE TABLE ---\n", proc_num);

    // Get the page table for this process
    int page_table = get_page_table(proc_num);

    // Loop through, printing out used pointers
    for (int i = 0; i < PAGE_COUNT; i++) {
        int addr = get_address(page_table, i);

        int page = mem[addr];

        if (page != 0) {
            printf("%02x -> %02x\n", i, page);
        }
    }
}

//
// Main -- process command line
//
int main(int argc, char *argv[])
{

    assert(PAGE_COUNT * PAGE_SIZE == MEM_SIZE);

    if (argc == 1) {
        fprintf(stderr, "usage: ptsim commands\n");
        return 1;
    }
    
    initialize_mem();

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "pfm") == 0) { //command to print free table
            print_page_free_map();
        }
        else if (strcmp(argv[i], "ppt") == 0) { //command to print table
            int proc_num = atoi(argv[++i]);
            print_page_table(proc_num);
        }

        // TODO: more command line arguments
        else if (strcmp(argv[i], "np") == 0){ //(new process) with (n) allocation of (m) pages)
            int proc_num = atoi(argv[i+1]);
            int page_count = atoi(argv[i+2]);
            new_process(proc_num, page_count);
            i = i + 2;
        }
    }
}
