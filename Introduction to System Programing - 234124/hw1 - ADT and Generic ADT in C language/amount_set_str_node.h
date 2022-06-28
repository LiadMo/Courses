#ifndef AMOUNT_SET_STR_NODE_H
#define AMOUNT_SET_STR_NODE_H
#include "stdbool.h"


typedef struct node_item {
    char *item;
    double amount;
    struct node_item *next;
}*Node;

Node ndCreate();
void ndSetItem(Node node, const char *str);
void ndSetAmount(Node node, double value);
// Destroy all items in the list;
void ndDestroy(Node head);
// Delete this node
void ndDelete(Node node);
Node ndCopy(Node toCopy);
Node lsCopy(Node head);
int ndGetSize(Node head);
bool ndContains(Node head, const char* element);

#endif //AMOUNT_SET_STR_NODE_H
