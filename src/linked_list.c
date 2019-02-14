/*
 * file: linked_list.h
 * description: This file implements a very rudimentary linked list for storing a sequence of servo positions
 * author: Cody Nettesheim
 */
#include "linked_list.h"

void add_node(node *current_node, int data[]) {
    //allocate memory
    node *next_node = (node*) malloc(sizeof(node));
    //add data
    next_node->data    = data;
    //point to new node
    current_node->next = next_node;
}
