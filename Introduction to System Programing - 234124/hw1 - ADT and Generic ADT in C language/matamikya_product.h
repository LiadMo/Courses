#include "matamikya.h"
#include "amount_set.h"

#ifndef PRODUCT_H
#define PRODUCT_H


/**
 *
 * Represent Product object
 *
 * The following functions are available:
 *
 * pdCreate                     - Creates a new empty Product
 * pdGetAmountType              - Return the amount type of a product
 * pdGetID                      - Return the ID of a product
 * pdGetAmount                  - Return the amount of a product in the warehouse
 * pdSetAmount                  - Change the amount of a product in the warehouse
 * pdGetProduct                 - the function return product reference
 * pdRemoveProductFromInventory - the function remove product from inventory (AmountSet)
 * pdSetProfit                  - the function set the new profit for product
 * pdGetName                    - the function return the name of the product (pointer, not copy)
 * pdGetPricePerUnit            - the function return the price per ONE unit of the product
 * pdGetPrice                   - the function calculate and return the total price of products
 * pdGetTotalIncome             - the function return the income from the product
 * pdCopy                       - the function return copy of a product
 * pdFree                       - the function delete the product element
 * pdCompare                    - the function compare TWO products by there ID's
 */

/** Type for representing a Matamikya Product */
typedef struct product_h *Product;


/**
 * pdCreate - The function create a new Product and return a pointer to him
 * @param id - the id of the product
 * @param name - product name
 * @param amount - amount of the product in the warehouse
 * @param amountType - the type of the product amount (Integer , any amount etc ..)
 * @param customData - pointer for additional data of the product
 * @param copyData - pointer to function that copy the product
 * @param freeData - pointer to function that free the product
 * @param prodPrice - pointer to function that calculate the product price
 * @return a pointer to a new Product, if where is fail, return NULL
 */
Product pdCreate(const unsigned int id, const char *name, const double amount,
                 const MatamikyaAmountType amountType, const MtmProductData customData,
                 MtmCopyData copyData, MtmFreeData freeData, MtmGetProductPrice prodPrice);


/**
 * pdGetID - the function return the id of the product.
 * @param product - the product that you want to get his id.
 * @return the id of the product (unsigned int).
 */
unsigned int pdGetID(Product product);


/**
 * pdGetAmountType - the function return the amount type of the product.
 * @param product - the product that you want to get his amount type (Integer, half integer, etc ..)
 * @return the type of the amount (ENUM - MatamikyaAmountType)
 */
MatamikyaAmountType pdGetAmountType(Product product);


/**
 *  pdGetAmount - the function return the amount of the product.
 * @param product - the product that you want to get his amount in the warehouse.
 * @return the amount of the product (double)
 */
double pdGetAmount(Product product);


/**
 * pdSetAmount - the function add / sub the amount of the product
 * @param product - the product you want to modify his amount
 * @param different - the amount you want to add / sub form the current amount
 */
void pdSetAmount(Product product, double different);


/**
 * pdGetProduct - the function return product reference if the product exists, if not return NULL
 * @param inventory - the inventory of a warehouse
 * @param product_id - Product ID
 * @return - Product reference with the same ID if exists, if not return NULL
 */
Product pdGetProduct(AmountSet inventory, unsigned int product_id);


/**
 * pdRemoveProductFromInventory - the function remove product from inventory (AmountSet)
 * @param inventory - the inventory you want to delete from him
 * @param product - the product you want to delete
 * @return return false if got null arguments, true if success
 */
bool pdRemoveProductFromInventory(AmountSet inventory, Product product);


/**
 * pdSetProfit - the function set the new profit for product
 * @param product - the product to set his profit
 * @param amount - the amount you sold the product
 */
void pdSetProfit(Product product, double amount);


/**
 * pdGetName - the function return the name of the product (pointer, not copy)
 * @param product - the product to get his name
 * @return NULL if get null argument, else pointer to the product name
 */
char* pdGetName(Product product);


/**
 * pdGetPricePerUnit - the function return the price per ONE unit of the product
 * @param product  - the product you want to get his price
 * @return the price per ONE unit
 */
double pdGetPricePerUnit(Product product);


/**
 * pdGetPrice - the function calculate and return the total price of products
 * @param product - the product you want to get his price * amount
 * @param amount - the amount of product you want to buy
 * @return - the total price
 */
double pdGetPrice(Product product, double amount);


/**
 * pdGetTotalIncome - the function return the income from the product
 * @param product - the product you want get his income until now
 * @return - the income from the product
 */
double pdGetTotalIncome(Product product);


/**
 * pdCopy - the function return copy of a product
 * @param toCopy - product to copy
 * @return return copy of product (in ASElement pointer)
 */
ASElement pdCopy(ASElement toCopy);


/**
 * pdFree - the function delete the product element
 * @param toFree - the product you want to delete
 */
void pdFree(ASElement toFree);


/**
 * pdCompare - the function compare TWO products by there ID's
 * @param pd1  - the first product to compare
 * @param pd2 - the second product to compare
 * @return 0 if there equals, 1 if the first is bigger, -1 if the second is bigger
 */
int pdCompare(ASElement pd1, ASElement pd2);

#endif //PRODUCT_H
