#include "matamikya_order.h"
#include "amount_set.h"
#include "stdlib.h"
#include "assert.h"
#include "matamikya_product.h"
#include "set.h"

/**
 * @param order_items - Amount Set of Product (copy of them)
 * @param id - order ID ( > 0 )
 */
struct order_h{
    AmountSet order_items;
    unsigned int id;
};

Order odCreate(unsigned int id) {
    Order order = malloc(sizeof(*order));
    if (!order)
        return NULL;
    assert(order);

    order->order_items = asCreate(pdCopy, pdFree, pdCompare);
    if (!order->order_items) {
        free(order);
        return NULL;
    }
    assert(order->order_items);

    order->id = id;
    return order;
}

unsigned int odGetID(Order order){
    assert(order);
    return order->id;
}


Order odGetOrder(Set orders, unsigned int order_id){
    assert(orders);
    SET_FOREACH(Order, iterator, orders) {
        if (odGetID(iterator) == order_id)
            return iterator;
    }
    return NULL;
}

Product odGetProductInOrder(Order order, unsigned int productID){
    if (!order)
        return NULL;
    assert(order);

    AS_FOREACH(Product , iterator, order->order_items) {
        if (pdGetID(iterator) == productID)
            return iterator;
    }
    return NULL;

}

OrderResult odAddProductToOrder(Order order, Product product){
    if (!order || !product)
        return ORDER_NULL_ARGUMENT;
    if (!order->order_items)
        return ORDER_NULL_ARGUMENT;
    asRegister(order->order_items, product);
    return ORDER_SUCCESS;
}

OrderResult odRemoveProductFromOrder(Order order, Product product) {
    if (!order || !product)
        return ORDER_NULL_ARGUMENT;

    assert(order && product);
    if (!order->order_items)
        return ORDER_NULL_ARGUMENT;

    if (asDelete(order->order_items, product) == AS_SUCCESS)
        return ORDER_SUCCESS;
    return ORDER_NULL_ARGUMENT;
}

OrderResult odValidAmountsInOrder(AmountSet inventory, Order order){
    if (!inventory)
        return ORDER_NULL_ARGUMENT;
    assert(inventory);

    AS_FOREACH(Product , prod_in_order, order->order_items) {
        AS_FOREACH(Product , prod_in_inv, inventory) {
            if(pdGetID(prod_in_order) == pdGetID(prod_in_inv))
                if (pdGetAmount(prod_in_order) > pdGetAmount(prod_in_inv)) {
                    return ORDER_INSUFFICIENT_AMOUNT;
                }
        }
    }
    return ORDER_SUCCESS;
}


OrderResult odUpdateAmountWarehouse (AmountSet inventory, Order order) {
    if (!inventory)
        return ORDER_NULL_ARGUMENT;
    assert(inventory);

    AS_FOREACH(Product , prod_in_order, order->order_items) {
        AS_FOREACH(Product , prod_in_inv, inventory) {
            if(pdGetID(prod_in_order) == pdGetID(prod_in_inv)) {
                pdSetAmount(prod_in_inv, -pdGetAmount(prod_in_order));
                pdSetProfit(prod_in_inv, pdGetAmount(prod_in_order));
            }
        }
    }
    return ORDER_SUCCESS;
}

AmountSet odGetProductAS(Order order) {
    if (!order)
        return NULL;
    assert(order);

    return order->order_items;
}

SetElement odCopy(SetElement toCopy) {
    if (!toCopy)
        return NULL;
    assert(toCopy);
    Order send = malloc(sizeof (*send));
    send->id =  ((Order)toCopy)->id;
    assert(send);
    send->order_items = asCopy( ((Order)toCopy)->order_items );

    return send;
}

void odFree(SetElement toFree) {
    if (!toFree)
        return;
    assert(toFree);

    asDestroy(   ((Order)toFree)->order_items    );
    ((Order)toFree)->order_items = NULL;
    free(toFree);
    toFree = NULL;
}

int odCompare(SetElement od1, SetElement od2) {
    assert(od1 && od2);
    if (   ((Order)od1)->id == ((Order)od2)->id    )
        return 0;
    if ( ((Order)od1)->id > ((Order)od2)->id)
        return -1;
    return 1;
}
