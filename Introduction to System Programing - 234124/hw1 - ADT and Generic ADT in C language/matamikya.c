#include "math.h"
#include "matamikya.h"
#include "stdlib.h"
#include "assert.h"
#include "amount_set.h"
#include "matamikya_product.h"
#include "matamikya_order.h"
#include "matamikya_print.h"

struct Matamikya_t{
    AmountSet inventory;
    Set orders;
    unsigned int num_of_orders;
};


/**
 * function the chek if the amount is valid or not (valid amount is define in the .h file)
 * @param amountType - the amount type of the product
 * @param amount - the amount to add / sub
 * @return True if the amount is valid and mach to the amount type, False if isn't
 */
static bool isValidAmountType(const MatamikyaAmountType amountType, const double amount) {
    double diff = fabs(amount - round(amount));
    if ((amountType == MATAMIKYA_INTEGER_AMOUNT) && fabs(diff) - 0.000001 > 0.001)
        return false;

    if (( amountType == MATAMIKYA_HALF_INTEGER_AMOUNT) && (fabs(diff) - 0.000001 > 0.001  && fabs(fabs(diff) - 0.5) - 0.000001 > 0.001))
        return false;
    return true;
}

Matamikya matamikyaCreate() {
    Matamikya warehouse = malloc(sizeof (*warehouse));
    if (!warehouse)
        return NULL;
    assert(warehouse);

    AmountSet inv = asCreate(pdCopy, pdFree, pdCompare);
    if (!inv){
        free(warehouse);
        return NULL;
    }
    assert(inv);
    warehouse->inventory = inv;

    Set orders = setCreate(odCopy, odFree, odCompare);
    if (!orders) {
        free(inv);
        inv = NULL;
        free(warehouse);
        warehouse = NULL;
        return NULL;
    }
    assert(orders);
    warehouse->orders = orders;

    assert(warehouse && inv && orders);
    warehouse->num_of_orders = 0;


    return warehouse;
}

void matamikyaDestroy(Matamikya matamikya) {
    asDestroy(matamikya->inventory);
    setDestroy(matamikya->orders);
    free(matamikya);
}

MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice)
{

    if (!matamikya || !name || !customData || !copyData || !freeData || !prodPrice)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya && name && customData && copyData && freeData && prodPrice);

    if (!(( name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a' && name[0] <= 'z') || (name[0] >= '0' && name[0] <= '9')))
        return MATAMIKYA_INVALID_NAME;

    if (amount < 0)
        return MATAMIKYA_INVALID_AMOUNT;

    if(!isValidAmountType(amountType, amount))
        return MATAMIKYA_INVALID_AMOUNT;

    Product product = pdCreate(id, name, amount, amountType, customData, copyData, freeData, prodPrice);

    if (!product)
        return MATAMIKYA_OUT_OF_MEMORY;
    assert(product);


    if (asContains(matamikya->inventory, product)) {
        pdFree(product);
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    AmountSetResult res = asRegister(matamikya->inventory, product);
    if (res != AS_SUCCESS){
        pdFree(product);
        if (res == AS_OUT_OF_MEMORY)
            return MATAMIKYA_OUT_OF_MEMORY;
        if (res == AS_NULL_ARGUMENT)
            return MATAMIKYA_NULL_ARGUMENT;
        if (res == AS_ITEM_ALREADY_EXISTS)
            return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    pdFree(product);
    assert(res == AS_SUCCESS);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount) {
    if (!matamikya)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya);

    Product elem = pdGetProduct(matamikya->inventory, id);

    if(elem == NULL || !asContains(matamikya->inventory, elem))
        return MATAMIKYA_PRODUCT_NOT_EXIST;

    if (!isValidAmountType(pdGetAmountType(elem), amount) || !isValidAmountType(pdGetAmountType(elem), amount + pdGetAmount(elem)))
        return MATAMIKYA_INVALID_AMOUNT;

    if((pdGetAmount(elem) + amount) < 0)
        return MATAMIKYA_INSUFFICIENT_AMOUNT;


    pdSetAmount(elem, amount);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id) {
    if (!matamikya)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya);

    Product product = pdGetProduct(matamikya->inventory, id);
    if (!product)
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    assert(product);

    // delete from all orders
    SET_FOREACH(Order , iterator, matamikya->orders) {
        Product to_delete = odGetProductInOrder(iterator, id);

        if (to_delete != NULL) {
            odRemoveProductFromOrder(iterator, to_delete);
            to_delete = NULL;
        }
    }

    // delete from inventory
    bool res = pdRemoveProductFromInventory(matamikya->inventory, product);
    if (!res)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(res);

    return MATAMIKYA_SUCCESS;

}

unsigned int mtmCreateNewOrder(Matamikya matamikya) {
    if (!matamikya)
        return 0;
    assert(matamikya);

    if(!matamikya->orders)
        return 0;
    assert(matamikya->orders);

    matamikya->num_of_orders += 1;
    unsigned int id = matamikya->num_of_orders;
    Order od = odCreate(id);
    if (!od)
        return 0;
    assert(od);

    setAdd(matamikya->orders, od);
    odFree(od);
    return id;
}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
                                              const unsigned int productId, const double amount) {
    if (!matamikya)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya);
    if (orderId == 0)
        return MATAMIKYA_ORDER_NOT_EXIST;
    Order order = odGetOrder(matamikya->orders, orderId);
    if (!order)
        return MATAMIKYA_ORDER_NOT_EXIST;
    assert(order);

    Product product = pdGetProduct(matamikya->inventory, productId);
    if (!product)
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    assert(product);

    if (!isValidAmountType(pdGetAmountType(product), amount))
        return MATAMIKYA_INVALID_AMOUNT;

    Product if_exist = odGetProductInOrder(order, productId);
    if (!if_exist) {
        if (amount <= 0)
            return MATAMIKYA_SUCCESS;
        else {
            OrderResult res = odAddProductToOrder(order, product);
            if (res != ORDER_SUCCESS)
                return MATAMIKYA_NULL_ARGUMENT;
            if_exist = odGetProductInOrder(order, productId);
            pdSetAmount(if_exist, amount-pdGetAmount(if_exist));
            return MATAMIKYA_SUCCESS;
        }
    }
    assert(if_exist);

    pdSetAmount(if_exist, amount);
    if (pdGetAmount(if_exist) <= 0)
        odRemoveProductFromOrder(order, if_exist);

    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId) {
    if (!matamikya)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya);

    Order order = odGetOrder(matamikya->orders, orderId);
    if (!order)
        return MATAMIKYA_ORDER_NOT_EXIST;
    assert(order);

    OrderResult result = odValidAmountsInOrder(matamikya->inventory, order);
    if (result != ORDER_SUCCESS) {
        if (result == ORDER_INSUFFICIENT_AMOUNT)
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        return MATAMIKYA_NULL_ARGUMENT;
    }

    assert(result == ORDER_SUCCESS);

    result = odUpdateAmountWarehouse(matamikya->inventory, order);
    assert(result == ORDER_SUCCESS);

    setRemove(matamikya->orders,order);


    return MATAMIKYA_SUCCESS;
}


MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId){
    if (!matamikya)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya);

    Order order = odGetOrder(matamikya->orders, orderId);
    if (!order)
        return MATAMIKYA_ORDER_NOT_EXIST;
    assert(order);

    setRemove(matamikya->orders, order);
    return MATAMIKYA_SUCCESS;
}


MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output) {
    if (!matamikya || !output)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya && output);

    fprintf(output,"Inventory Status:\n");
    AS_FOREACH(Product, product, matamikya->inventory) {
        mtmPrintProductDetails(pdGetName(product), pdGetID(product), pdGetAmount(product), pdGetPricePerUnit(product), output);
    }

    return MATAMIKYA_SUCCESS;
}


//MatamikyaResult mtmPrintInventory(Matamikya matamikya) {
//    if (!matamikya)
//        return MATAMIKYA_NULL_ARGUMENT;
//    assert(matamikya);
//
//    printf("Inventory Status:\n");
//    AS_FOREACH(Product, product, matamikya->inventory) {
//        printf("name: %s, id: %d, amount: %.3f, price: %.3f\n", pdGetName(product), pdGetID(product), pdGetAmount(product),
//               pdGetPricePerUnit(product));
//    }
//
//    return MATAMIKYA_SUCCESS;
//}


MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output) {
    if (!matamikya || !output)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya && output);

    Order order = odGetOrder(matamikya->orders, orderId);
    if (!order)
        return MATAMIKYA_ORDER_NOT_EXIST;
    assert(order);

    double totalOrderPrice = 0;
    mtmPrintOrderHeading(orderId, output);
    AS_FOREACH(Product, product, odGetProductAS(order)) {
        mtmPrintProductDetails(pdGetName(product), pdGetID(product), pdGetAmount(product),
                               pdGetPrice(product, pdGetAmount(product)), output);
        totalOrderPrice +=  pdGetPrice(product, pdGetAmount(product));
    }
    mtmPrintOrderSummary(totalOrderPrice, output);
    return MATAMIKYA_SUCCESS;
}


//MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId) {
//    if (!matamikya)
//        return MATAMIKYA_NULL_ARGUMENT;
//    assert(matamikya);
//
//    Order order = odGetOrder(matamikya->orders, orderId);
//    if (!order)
//        return MATAMIKYA_ORDER_NOT_EXIST;
//    assert(order);
//
//    double totalOrderPrice = 0;
//    mtmPrintOrderHeading1(orderId);
//    AS_FOREACH(Product, product, odGetProductAS(order)) {
//        mtmPrintProductDetails1(pdGetName(product), pdGetID(product), pdGetAmount(product),
//                               pdGetPricePerUnit(product) * pdGetAmount(product));
//        totalOrderPrice += pdGetPricePerUnit(product) * pdGetAmount(product);
//    }
//    mtmPrintOrderSummary1(totalOrderPrice);
//    return MATAMIKYA_SUCCESS;
//}


MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output) {
    if (!matamikya || !output)
        return MATAMIKYA_NULL_ARGUMENT;
    assert(matamikya && output);

    fprintf(output,"Best Selling Product:\n");
    if (asGetSize(matamikya->inventory) == 0) {
        fprintf(output, "none\n");
        return MATAMIKYA_SUCCESS;
    }

    Product bestSelling = asGetFirst(matamikya->inventory);
        AS_FOREACH(Product, product, matamikya->inventory) {
            if (pdGetTotalIncome(product) > pdGetTotalIncome(bestSelling))
                bestSelling = product;
            if (pdGetTotalIncome(product) == pdGetTotalIncome(bestSelling))
                if (pdGetID(product) < pdGetID(bestSelling))
                    bestSelling = product;
    }
    if (pdGetTotalIncome(bestSelling) == 0)
    {
        fprintf(output, "none\n");
        return MATAMIKYA_SUCCESS;
    }
    mtmPrintIncomeLine(pdGetName(bestSelling), pdGetID(bestSelling), pdGetTotalIncome(bestSelling), output);
    return MATAMIKYA_SUCCESS;
}

