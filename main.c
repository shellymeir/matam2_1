#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;

typedef enum {
    SUCCESS = 0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
    NULL_ARGUMENT,
} ErrorCode;

int getListLength(Node list) {
    int count = 0;
    while (list) {
        count++;
        list = list->next;
    }
    return count;
}

bool isListSorted(Node list) {
    if (list == NULL) {
        return true;
    }
    int prev = list->x;
    list = list->next;
    while (list != NULL) {
        if (prev > list->x) {
            return false;
        }
        prev = list->x;
        list = list->next;
    }
    return true;
}

Node copyNode(Node node, ErrorCode *n)
{
    Node new_node = malloc(sizeof(*node));
    if (!new_node)
    {
        *n = MEMORY_ERROR;
        return NULL;
    }
    new_node->x = node->x;
    return new_node;
}

void destroy(Node head) {
    Node iterator, temp;
    iterator = head;
    while (iterator != NULL)
    {
        temp = iterator->next;
        free(iterator);
        iterator = temp;
    }
}

ErrorCode mergeSortedLists(Node list1, Node list2, Node *merged_out)
{
    ErrorCode flag;
    Node merged_list = malloc(sizeof(*merged_list));
    *merged_out = merged_list;
    if (!merged_out)
        return NULL_ARGUMENT;
    bool empty_list = false;
    if (getListLength(list1) == 0 || getListLength(list2) == 0)
    {
        empty_list = true;
    }

    while (list1 && list2) {
        if (list1->x <= list2->x)
        {
            merged_list = copyNode(list1, &flag);
            if (flag == MEMORY_ERROR) {
                destroy(*merged_out);
                return MEMORY_ERROR;
            }
            list1 = list1->next;
        }
        else {
            merged_list = copyNode(list2, &flag);
            if (flag == MEMORY_ERROR) {
                destroy(*merged_out);
                return MEMORY_ERROR;
            }
            list2 = list2->next;
        }
        printf("%d", (merged_list)->x);
        merged_list->next = malloc(sizeof(*merged_list));
        if (!merged_list->next)
        {
            destroy(*merged_out);
            return MEMORY_ERROR;
        }
        merged_list = merged_list->next;
    }
    while (!list1 && list2)
    {
        merged_list = copyNode(list2, &flag);
        if (flag == MEMORY_ERROR)
        {
            destroy(*merged_out);
            return MEMORY_ERROR;
        }
        list2 = list2->next;
        printf("%d", merged_list->x);
        merged_list->next = malloc(sizeof(*merged_list));
        if (!merged_list->next)
        {
            destroy(*merged_out);
            return MEMORY_ERROR;
        }
        merged_list = merged_list->next;
    }
    while (list1)
    {
        merged_list = copyNode(list1, &flag);
        if (flag == MEMORY_ERROR)
        {
            destroy(*merged_out);
            return MEMORY_ERROR;
        }
        list1 = list1->next;
        printf("%d", merged_list->x);
        merged_list->next = malloc(sizeof(*merged_list));
        if (!merged_list->next)
        {
            destroy(*merged_out);
            return MEMORY_ERROR;
        }
        merged_list = merged_list->next;
    }
    if (empty_list) return EMPTY_LIST;
    return SUCCESS;

}

int main() {
    Node merged_out = NULL;
    Node head1 = malloc(sizeof(*head1));
    Node second1 = malloc(sizeof(*second1));
    Node tail1 = malloc(sizeof(*tail1));
    head1->x = 1;
    head1->next = second1;
    second1->x = 2;
    second1->next = tail1;
    tail1->x = 3;
    tail1->next = NULL;
    Node head2 = malloc(sizeof(*head1));
    Node second2 = malloc(sizeof(*second1));
    Node tail2 = malloc(sizeof(*tail1));
    head2->x = 4;
    head2->next = second2;
    second2->x = 5;
    second2->next = tail2;
    tail2->x = 6;
    tail2->next = NULL;
    mergeSortedLists(head1, head2, &merged_out);
    destroy(head1);
    destroy(head2);
    while (merged_out)
    {
        printf(" %d ", merged_out->x);
        merged_out = merged_out->next;
    }
    destroy(merged_out);
    return 0;
}