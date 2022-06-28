#ifndef MATAMIKYA_ORDER_H
#define MATAMIKYA_ORDER_H
#include "list.h"
#include "set.h"
#include "matamikya.h"
#include "matamikya_product.h"


/**
 *
 * Represent Order object
 *
 * The following functions are available:
 *
 * odCreate                 - Creates a new empty Order
 * pdGetAmountType          - Return the amount type of a product
 * odGetID                  - Return the ID of a Order
 * odGetOrder               - the function return order reference
 * odGetProductInOrder      - check if product exists in order
 * odAddProductToOrder      - the function add a product to order
 * odRemoveProductFromOrder - the function remove a product from order
 * odValidAmountsInOrder    - the function check if all products in the order is in stock
 * odUpdateAmountWarehouse  - the function update the new amount and profit in the warehouse after shipping the order
 * odGetProductAS           - the function return the products in the order (pointer)
 * odCopy - pdCopy          - the function return copy of a order
 * odFree                   - the function delete the order element
 * odCompare                - the function compare TWO order by there ID's
 */

/** Type for representing a Matamikya Order */
typedef struct order_h *Order;


typedef enum OrderResult_t{
    ORDER_SUCCESS = 0,
    ORDER_NULL_ARGUMENT,
//    ORDER_OUT_OF_MEMORY,
//    ORDER_INVALID_NAME,
//    ORDER_INVALID_AMOUNT,
//    ORDER_ALREADY_EXIST,
//    ORDER_NOT_EXIST,
//    ORDER_NOT_EXIST,
    ORDER_INSUFFICIENT_AMOUNT = 8,
}OrderResult;

/**
 * odCreate - The function create a new Order and return a pointer to him
 * @param id - the ID of the order
 * @return return a pointer to to order if success, if isn't return NULL
 */
Order odCreate(unsigned int id);


/**
 * odGetID - the function return the ID on the order
 * @param order - the order that you want to get her ID
 * @return - the ID of the order (unsigned int > 0)
 */
unsigned int odGetID(Order order);


/**
 * odGetOrder - the function return order reference if the order exists, if not return NULL
 * @param orders - list of orders in the warehouse
 * @param order_id - the wanted order ID
 * @return Order reference with the same ID if exists, if not return NULL
 */
Order odGetOrder(Set orders, unsigned int order_id);


/**
 * odGetProductInOrder - check if product exists in order
 * @param order - the order
 * @param productID - the product ID
 * @return product reference if exists, NULL if not
 */
Product odGetProductInOrder(Order order, unsigned int productID);


/**
 * odAddProductToOrder - the function add a product to order
 * @param order - the order
 * @param product - the product you add to the order
 * @return  ORDER_SUCCESS or ORDER_NULL_ARGUMENT
 */
OrderResult odAddProductToOrder(Order order, Product product);


/**
 * odRemoveProductFromOrder - the function remove a product from order
 * @param order - the order
 * @param product - the product to remove
 * @return ORDER_SUCCESS or ORDER_NULL_ARGUMENT
 */
OrderResult odRemoveProductFromOrder(Order order, Product product);

/**
 * odValidAmountsInOrder - the function check if all products in the order is in stock
 * @param inventory - the warehouse inventory
 * @param order - the order to check
 * @return ORDER_NULL_ARGUMENT - if get null argument, ORDER_INSUFFICIENT_AMOUNT - if the amount isn't good, ORDER_SUCCESS - if all success
 */
OrderResult odValidAmountsInOrder(AmountSet inventory, Order order);


/**
 * odUpdateAmountWarehouse - the function update the new amount and profit in the warehouse after shipping the order
 * @param inventory - the inventory of the warehouse
 * @param order - the order have benn shipped
 * @return ORDER_NULL_ARGUMENT - if get null argument, ORDER_SUCCESS - if all success
 */
OrderResult odUpdateAmountWarehouse (AmountSet inventory, Order order);


/**
 * odGetProductAS - the function return the products in the order (pointer)
 * @param order - the order that you get where products
 * @return NULL if get null argument, else return the AmountSet (the products of the order)
 */
AmountSet odGetProductAS(Order order);


/**
 * odCopy - pdCopy - the function return copy of a order
 * @param toCopy - order to copy
 * @return return copy of order (in SetElement pointer)
 */
SetElement odCopy(SetElement toCopy);


/**
 * odFree - the function delete the order element
 * @param toFree the order you want to delete
 */
void odFree(SetElement toFree);


/**
 * odCompare - the function compare TWO order by there ID's
 * @param od1 - the first order to compare
 * @param od2 - the second order to compare
 * @return 0 if there equals, 1 if the first is bigger, -1 if the second is bigger
 */
int odCompare(SetElement od1, SetElement od2);


#endif //MATAMIKYA_ORDER_H
