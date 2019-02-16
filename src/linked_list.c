/*
 * file: linked_list.h
 * description: This file implements a very rudimentary linked list for storing a sequence of servo positions
 * author: Cody Nettesheim
 */
#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

void add_node(node *current_node, int data[]) {
    //allocate memory
    node *next_node = (node*) malloc(sizeof(node));
    next_node->next = 0;
    //add data
    memcpy(next_node->data, data, 5 * sizeof(int));
    //point to new node
    current_node->next = next_node;
}
