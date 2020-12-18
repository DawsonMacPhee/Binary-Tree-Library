This is a collection of functions that work together to act as a binary tree data structure.

Functions

    struct Performance *newPerformance()
        Creates a structure holding information about the efficiency of the binary tree.
        
    void attachNode(struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width)
        Allocates memory and adds a new node at the location node_ptr is pointing to.
        
    int comparNode(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target)
        Compares the node at node_ptr to the target pointer using the given compar function.
        
    struct Node** next(struct Performance *performance, struct Node **node_ptr, int direction)
        If direction is 0, returns the left node from the node_ptr.
        If direction is 1, returns the right node from the node_ptr.

    void readNode(struct Performance *performance, struct Node **node_ptr, void *dest, unsigned in width)
        Copies the node at node_ptr into the dest pointer.
        
    void detachNode(struct Performance *performance, struct Node **node_ptr)
        Detaches node_ptr from the list and frees its memory
        
    int isEmpty(struct Performance *performance, struct Node **node_ptr)
        Returns 1 if the given node is empty, otherwise returns 0.
        
    void addItem(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width)
        Adds a given src value to the tree at its correct position.
        Comparisons for left or right branching are done by the given compar function.
        
    void freeTree(struct Performance *performance, struct Node **node_ptr)
        Recursively frees all memory allocated for the tree.
        
    int searchItem(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width)
        Searches for the target pointer withing the tree by use of the given compar function.
        Returns 1 for found and 0 for not found.

Files

    tree.c
        Contains all the functions in the library
        
    tree.h
        Contains all the function declarations for the functions in tree.c
        
    ttest.c
        Contains a main function for testing the binary tree data structure
        
    names1.txt
        Text file containing values to load into the tree for testing purposes

Usage

    make all 
        Compiles all the functions for the library into an object file
        
    make tree.o
        Compiles all the functions in tree.c into an object file
        
    make ttest.o
        Creates object file ttest.o
        
    make ttest
        Creates executable file ttest
        
    make clean
        Removes the object and executable files
