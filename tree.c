#ifndef __stdio_h_
#include <stdio.h>
#endif

#ifndef __stdlib_h_
#include <stdlib.h>
#endif

#ifndef __string_h_
#include <string.h>
#endif

#ifndef __tree_h_
#include "tree.h"
#endif

// Allocates memory for the struct 'Performance' and initializes its values
struct Performance *newPerformance(){
    struct Performance *performance = malloc(sizeof(struct Performance));
    if(performance == NULL){
        fprintf(stderr, "The allocation of memory for the Performance Struct has failed\n");
        exit(1);
    }
    performance -> reads = 0;
    performance -> writes = 0;
    performance -> mallocs = 0;
    performance -> frees = 0;
    return performance;
}

// Allocates memory and adds a new node at the location node_ptr is pointing to
void attachNode(struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width){
    struct Node *newNode = malloc(sizeof(struct Node));
    if(newNode == NULL){
        fprintf(stderr, "attachNode: The allocation of memory forthe new node failed\n");
        free(performance);
        exit(1);
    }
    newNode -> data = malloc(width);
    if(newNode -> data == NULL){
        fprintf(stderr, "attachNode: The allocation of memory for the data inside the new node failed\n");
        free(performance);
        exit(1);
    }
    newNode -> lt = NULL;
    newNode -> gte = NULL;
    memcpy(newNode -> data, src, width);
    *node_ptr = newNode;
    performance -> mallocs += 1;
    performance -> writes += 1;
}

// Compares the node inside node_ptr to the target pointer using the given compar function
int comparNode(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target){
    performance -> reads += 1;
    return (*compar)(target, (*node_ptr) -> data);
}

// Depending on the given direction, grabs the left or right node following node_ptr's node
struct Node** next(struct Performance *performance, struct Node **node_ptr, int direction){
    if(isEmpty(performance, node_ptr)){
        fprintf(stderr, "next: The given node is empty\n");
        free(performance);
        exit(1);
    }

    performance -> reads += 1;

    if(direction < 0){
        return &((*node_ptr) -> lt);
    }else{
        return &((*node_ptr) -> gte);
    }
}

// Reads the node inside node_ptr and places its data into the dest pointer
void readNode(struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width){
    if (isEmpty(performance, node_ptr)){
        fprintf(stderr, "readNode: The given node is empty\n");
        free(performance);
        exit(1);
    }
    memcpy(dest, (*node_ptr) -> data, width);
    performance -> reads += 1;
}

// Detaches node_ptr's node from the tree and frees its memory
void detachNode(struct Performance *performance, struct Node **node_ptr){
    if (isEmpty(performance, node_ptr)){
        fprintf(stderr, "detachNode: The given node is empty\n");
        free(performance);
        exit(1);
    }
    free((*node_ptr) -> data);
    free(*node_ptr);
    *node_ptr = NULL;
    performance -> frees += 1;
}

// Returns 1 if the given pointer is empty, returns 0 otherwise
int isEmpty(struct Performance *performance, struct Node **node_ptr){
    if(*node_ptr == NULL){
        return 1;
    }
    return 0;
}

// Adds an items to the correct place within the tree
void addItem(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width){
    while(!isEmpty(performance, node_ptr)){
        node_ptr = next(performance, node_ptr, comparNode(performance, node_ptr, *compar, src));
    }
    attachNode(performance, node_ptr, src, width);
}

// Frees all nodes inside the tree
void freeTree(struct Performance *performance, struct Node **node_ptr){
    if(!isEmpty(performance, node_ptr)){
        freeTree(performance, next(performance, node_ptr, -1));
        freeTree(performance, next(performance, node_ptr, 1));
        detachNode(performance, node_ptr);
    }
}

// Searches for the target pointer within the tree by use of the given compar function
int searchItem(struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width){
    int comparison;
    while(!isEmpty(performance, node_ptr)){
        comparison = comparNode(performance, node_ptr, *compar, target);
        if(comparison == 0){
            readNode(performance, node_ptr, target, width);
            return 1;
        }
        node_ptr = next(performance, node_ptr, comparison);
    }
    return 0;
}
