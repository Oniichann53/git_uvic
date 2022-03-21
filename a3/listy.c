/** @file listy.c
 *  @brief Implementation of a linked list.
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ics.h"
#include "emalloc.h"
#include "listy.h"

/**
 * Function:  new_node
 * -------------------
 * @brief  Allows to dynamically allocate memory for a new node to be added to the linked list.
 *
 * This function should confir, that the argument being passed is not NULL (i.e., using the assert library). Then,
 * It dynamically allocates memory for the new node using emalloc(), and assign values to attributes associated with the node (i.e., val and next).
 *
 * @param val The value (event) to be associated with the node.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *new_node(event_t *val)
{
    assert(val != NULL);
    node_t *temp = (node_t*)emalloc(sizeof(node_t));
    temp->val = val;
    // TODO: Complete the function.
    return temp;
}

/**
 * Function:  add_inorder
 * ----------------------
 * @brief  Allows to add a new node to the list respecting the order of events.
 *
 * This function should validate the number of elements already added to the list (i.e., validate whether the list is empty, has only one item, or has multiple events).
 * Then, we need to figure out the position at which the new node should be placed. For this, we need to compare the starting date of the event comprising the node to be added
 * with each starting date of the events existing in the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *add_inorder(node_t *list, node_t *new)
{
    // TODO: Complete the function.
    if (list == NULL) {
        new->next = NULL;
        return new;
    }
    node_t *curr = list ;
    
    if (curr->next == NULL) {
        if (strcmp(curr->val->start_date, new->val->start_date) == 1) {
            return add_front(list, new);
        }
        else {
            return add_end(list, new);
        }
    }
    for (curr = list; curr->next != NULL; curr = curr->next) {
        if ((strcmp(curr->val->start_date, new->val->start_date) == -1) && (strcmp(curr->next->val->start_date, new->val->start_date) == 1)) {
            node_t *temp = curr->next;
            curr->next = new;
            new->next = temp;
            return list;
        }
    }
    return list;
}

/**
 * Function:  add_front
 * --------------------
 * @brief  Allows to add a node at the front of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the new head of the list.
 *
 */
node_t *add_front(node_t *list, node_t *new)
{
    new->next = list;
    return new;
}

/**
 * Function:  add_end
 * ------------------
 * @brief  Allows to add a node at the end of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *add_end(node_t *list, node_t *new)
{
    node_t *curr;
    if (list == NULL)
    {
        new->next = NULL;
        return new;
    }
    for (curr = list; curr->next != NULL; curr = curr->next)
        ;
    curr->next = new;
    new->next = NULL;
    return list;
}

/**
 * Function:  peek_front
 * ---------------------
 * @brief  Allows to get the head node of the list.
 *
 * @param list The list to get the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *peek_front(node_t *list)
{
    return list;
}

/**
 * Function:  remove_front
 * -----------------------
 * @brief  Allows removing the head node of the list.
 *
 * @param list The list to remove the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *remove_front(node_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->next;
}

/**
 * Function: apply
 * --------------
 * @brief  Allows to apply a function to the list.
 *
 * @param list The list (i.e., pointer to head node) where the function will be applied.
 * @param fn The pointer of the function to be applied.
 * @param arg The arguments to be applied.
 *
 */
void apply(node_t *list, void (*fn)(node_t *list, void *), void *arg)
{
    for (; list != NULL; list = list->next)
    {
        (*fn)(list, arg);
    }
}

/**
 * Function: free_list
 * ------------------
 * @brief  Allows to free the space dynamically allocated for the list.
 *
 * @param list The list (i.e., pointer to head node) to free.
 *
 */
void free_list(node_t *list)
{
    node_t *temp = NULL;

    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp->val);
        free(temp);
    }
}