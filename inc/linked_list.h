/*
 * file: linked_list.h
 * description: This file implements a very rudimentary linked list for storing a sequence of servo positions
 * author: Cody Nettesheim
 */
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

//Node that holds data and a pointer to the next node in the list
typedef struct {
    int data[5];
    struct node *next;
} node;

/**
 *
 * Paramenters: current node and new data
 * Returns:     none
 */
void add_node(node*, int[]);

#endif
