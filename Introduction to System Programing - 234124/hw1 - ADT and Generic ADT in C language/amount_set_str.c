#include "amount_set_str.h"
#include "amount_set_str_node.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

struct AmountSet_t {
    Node head;
    Node iterator;
};
AmountSet asCreate() {
    AmountSet set = malloc(sizeof (*set));
    if (set == NULL)
        return NULL;
    assert(set);

    set->head = NULL;
    set->iterator = NULL;

    return set;
}
void asDestroy(AmountSet set) {
    if (set == NULL)
        return;
    assert(set);

    ndDestroy(set->head);
    set->head = NULL;
    free(set);
    set = NULL;
}
char* asGetFirst(AmountSet set) {
    if (set == NULL)
        return NULL;
    assert(set);

    set->iterator = set->head;
    if (set->iterator == NULL)
        return NULL;

    return set->iterator->item;
}
char* asGetNext(AmountSet set) {
    if (set == NULL)
        return NULL;
    assert(set);

    if (set->iterator == NULL)
        return NULL;

    set->iterator = set->iterator->next;

    if (set->iterator == NULL)
        return NULL;

    return set->iterator->item;
}
AmountSet asCopy(AmountSet toCopy) {
    if (toCopy == NULL)
        return NULL;
    assert(toCopy);

    asGetFirst(toCopy);
    AmountSet set = asCreate();
    if (set == NULL) {
        toCopy->iterator = NULL;
        return NULL;
    }
    assert(set);

    set->head = lsCopy(toCopy->head);

    set->iterator = NULL; // added new
    toCopy->iterator = NULL; // added new
    return set;
}
int asGetSize(AmountSet set) {
    if (set == NULL)
        return -1;
    assert(set);

    return ndGetSize(set->head);
}
bool asContains(AmountSet set, const char* element) {
    if (set == NULL || element == NULL)
        return false;
    assert(set && element);

    if(set->head == NULL)
        return false;
    assert(set->head);

    return ndContains(set->head, element);
}
AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount) {
    if (set == NULL || element == NULL || outAmount == NULL || set->head == NULL)
        return AS_NULL_ARGUMENT;
    if (!asContains(set, element))
        return AS_ITEM_DOES_NOT_EXIST;
    assert(set && set->head && element && outAmount && asContains(set, element));

    Node save_iterator = set->iterator;
    asGetFirst(set);
    while (set->iterator && set->iterator->item) {
        if (strcmp(set->iterator->item, element) == 0)
            break;
        asGetNext(set);
    }
    *outAmount = set->iterator->amount;
    set->iterator = save_iterator;
    return AS_SUCCESS;
}
AmountSetResult asChangeAmount(AmountSet set, const char* element, double amount) {
    if(!set || !element)
        return AS_NULL_ARGUMENT;
    if (!set->head || !asContains(set, element))
        return AS_ITEM_DOES_NOT_EXIST;
    assert(set || set->head || element || asContains(set, element));

    if (amount == 0)
        return AS_SUCCESS;

    Node save_iterator = set->iterator;
    asGetFirst(set);
    while (set->iterator && set->iterator->item) {
        if (strcmp(set->iterator->item, element) == 0)
            break;
        asGetNext(set);
    }

    if (set->iterator->amount + amount < 0)
        return AS_INSUFFICIENT_AMOUNT;

    set->iterator->amount += amount;
    assert(set->iterator->amount >= 0);

    set->iterator = save_iterator;
    return AS_SUCCESS;

}
AmountSetResult asDelete(AmountSet set, const char* element) {
    if (!set || !element) {
        if (set)
            set->iterator = NULL;
        return AS_NULL_ARGUMENT;
    }
    set->iterator = NULL;
    if (!asContains(set, element)) {
        set->iterator = NULL;
        return AS_ITEM_DOES_NOT_EXIST;
    }
    assert(set && asContains(set, element));

    if(asGetSize(set) == 1){
        ndDelete(set->head);
        set->head = NULL;
        set->iterator = NULL;
        return AS_SUCCESS;
    }

    asGetFirst(set);
    int size = asGetSize(set);
    Node prev = NULL;
    Node current = set->iterator;
    int isLast = 1;

    while (strcmp(current->item, element) != 0){
        isLast++;
        prev = current;
        current = current->next;
    }

    if(asGetSize(set) == 1){
        ndDelete(set->head);
        set->head = NULL;
        set->iterator = NULL;
        return AS_SUCCESS;
    }

    if (isLast == 1){
        Node toDel = set->head;
        set->head = set->head->next;
        ndDelete(toDel);
        toDel = NULL;
        set->iterator = NULL;
        return AS_SUCCESS;
    }

    if (size == isLast){
        ndDelete(current);
        prev->next = NULL;
        set->iterator = NULL;
        return AS_SUCCESS;
    }

    prev->next = current->next;
    ndDelete(current);
    set->iterator = NULL;
    return AS_SUCCESS;
}
AmountSetResult asRegister(AmountSet set, const char* element) {
    if(!set || !element) {
        if (set)
            set->iterator = NULL;
        return AS_NULL_ARGUMENT;
    }
    set->iterator = NULL;
    if (asContains(set, element)) {
        set->iterator = NULL;
        return AS_ITEM_ALREADY_EXISTS;
    }
    assert(set && element && !asContains(set, element));

    Node toAdd = ndCreate();
    if (toAdd == NULL)
        return AS_OUT_OF_MEMORY;
    ndSetItem(toAdd,element);
    if (toAdd->item == NULL){
        ndDelete(toAdd);
        toAdd = NULL;

        set->iterator = NULL; // added new
        return AS_OUT_OF_MEMORY;
    }
    assert(toAdd && toAdd->item);

    // case if set's size is 0 (empty set)
    if (asGetSize(set) == 0){
        set->head = toAdd;
        set->iterator = set->head;

        set->iterator = NULL;
        return AS_SUCCESS;
    }

    asGetFirst(set);

    // case if need to add to the 1st
    if (strcmp(set->iterator->item, toAdd->item) > 0){
        toAdd->next = set->iterator;
        set->head = toAdd;
        set->iterator = set->head;

        set->iterator = NULL; // added new
        return AS_SUCCESS;
    }


    while(strcmp(set->iterator->item, toAdd->item) < 0)
    {
        // case if need to add to the last
        if(set->iterator->next == NULL){
            set->iterator->next = toAdd;
            asGetNext(set);

            set->iterator = NULL; // added new
            return AS_SUCCESS;
        }

            // case if need to add between 2 nodes
        else if (strcmp(set->iterator->next->item, toAdd->item) > 0) {
            toAdd->next = set->iterator->next;
            set->iterator->next = toAdd;

            set->iterator = NULL; // added new
            return AS_SUCCESS;
        }
        asGetNext(set);
    }

    set->iterator = NULL; // added new
    return AS_SUCCESS;
}
AmountSetResult asClear(AmountSet set) {
    if (!set)
        return AS_NULL_ARGUMENT;
    assert(set);

    ndDestroy(set->head);
    set->head = NULL;
    set->iterator = NULL;
    return AS_SUCCESS;
}
