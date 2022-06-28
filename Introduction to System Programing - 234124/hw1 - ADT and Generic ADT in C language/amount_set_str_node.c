#include "amount_set_str_node.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

Node ndCreate() {
    Node node = malloc(sizeof (*node));
    if (node == NULL)
        return NULL;
    assert(node);

    node->item = NULL;
    node->amount = 0;
    node->next = NULL;

    return node;
}
void ndSetItem(Node node, const char *str){
    if (node == NULL || str == NULL)
        return;
    assert(node);

    node->item = malloc(sizeof (char) * (strlen(str)) + 1);
    if (node->item == NULL)
        return;
    assert(node->item);

    strcpy(node->item, str);
//    strcat(node->item,"\0");
}
void ndSetAmount(Node node, double value){
    if (node == NULL)
        return;
    assert(node);

    node->amount = value;
}
void ndDelete(Node node) {
    if (node == NULL)
        return;
    assert(node);

    free(node->item);
    free(node);
}
void ndDestroy(Node head) {
    if (head == NULL) {
        return;
    }
    assert(head);

    Node current = head;
    Node next = NULL;
    while (current != NULL) {
        next = current->next;
        ndDelete(current);
        current = next;
    }
}
Node ndCopy(Node toCopy) {
    if (toCopy == NULL)
        return NULL;
    Node node = ndCreate();
    if (node == NULL)
        return NULL;
    assert(toCopy && node);

    ndSetItem(node, toCopy->item);
    ndSetAmount(node, toCopy->amount);

    return node;
}
Node lsCopy(Node head) {
    if (head == NULL)
        return NULL;
    assert(head);

    Node node = ndCreate();
    node->amount = head->amount; /***********************/
    ndSetItem(node, head->item);
    node->next = lsCopy(head->next);

    return node;
}
int ndGetSize(Node head) {
    int counter = 0;
    if (head == NULL)
        return counter;
    assert(head);

    while (head != NULL)
    {
        counter++;
        head = head->next;
    }
    return counter;
}
bool ndContains(Node head, const char* element) {
    if (head == NULL || head->item == NULL)
        return false;
    assert(head && head->item);

    while (head) {
        if (strcmp(head->item,element) == 0)
            return true;
        head = head->next;
    }
    return false;
}
