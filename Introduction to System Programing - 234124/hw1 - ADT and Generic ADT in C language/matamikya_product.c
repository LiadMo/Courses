#include "matamikya_product.h"
#include "amount_set.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

/**
 * @param prod_name - product name
 * @param id - product id
 * @param amount - amount of the product in the warehouse
 * @param amountType - the type of the product amount (Integer , any amount etc ..)
 * @param total_income - the income that the product raise
 * @param price_per_unit - the price per one product
 * @param customData - pointer for additional data of the product
 * @param freeData - pointer to function that free the product
 * @param copyData - pointer to function that copy the product
 * @param prodPrice - pointer to function that calculate the product price
 */
struct product_h {
    char *prod_name;
    unsigned int id;
    double amount;
    MatamikyaAmountType amountType;
    double total_income;
    double price_per_unit;
    MtmProductData customData;

    MtmFreeData freeData;
    MtmCopyData copyData;
    MtmGetProductPrice prodPrice;
};


Product pdCreate(const unsigned int id, const char *name, const double amount,
                 const MatamikyaAmountType amountType, const MtmProductData customData,
                 MtmCopyData copyData, MtmFreeData freeData, MtmGetProductPrice prodPrice) {
    Product prod = malloc(sizeof (*prod));
    if (!prod)
        return NULL;
    assert(prod);

    prod->prod_name = malloc( strlen(name) + 1);
    if (!prod->prod_name) {
        free(prod);
        prod = NULL;
        return NULL;
    }
    assert(prod->prod_name);

    strcpy(prod->prod_name, name);
    prod->amount = amount;
    prod->amountType = amountType;
    prod->customData = copyData(customData);
    if (!prod->customData){
        free(prod->prod_name);
        prod->prod_name = NULL;
        free(prod);
        prod = NULL;
        return NULL;
    }
    assert(prod->customData);
    prod->id = id;
    prod->total_income = 0;
    prod->copyData = copyData;
    prod->freeData = freeData;
    prod->prodPrice = prodPrice;

    prod->price_per_unit =  prod->prodPrice(prod->customData, 1);

    return prod;
}

double pdGetPrice(Product product, double amount){
    if (!product)
        return 0;
    assert(product);
    return product->prodPrice(product->customData, amount);
}

unsigned int pdGetID(Product product){
    assert(product);
    return product->id;
}


MatamikyaAmountType pdGetAmountType(Product product){
    assert(product);
    return product->amountType;
}


double pdGetAmount(Product product){
    assert(product);
    return product->amount;
}


void pdSetAmount(Product product, double different){
    assert(product);
    product->amount += different;
}


Product pdGetProduct(AmountSet inventory, unsigned int product_id){
    assert(inventory);
    AS_FOREACH(Product, iterator, inventory) {
        if (iterator->id == product_id)
            return iterator;
    }
    return NULL;
}


void pdSetProfit(Product product, double amount){
    if (!product)
        return;
    assert(product);

    product->total_income += pdGetPrice(product, amount);
   // product->total_income += (amount * product->price_per_unit);
}


bool pdRemoveProductFromInventory(AmountSet inventory, Product product){
    if (!inventory || !product)
        return false;
    assert(inventory && product);

    asDelete(inventory, product);
    return true;
}


char* pdGetName(Product product){
    if (!product)
        return NULL;
    assert(product);

    if (!product->prod_name)
        return NULL;
    assert(product->prod_name);

    return product->prod_name;
}


double pdGetPricePerUnit(Product product){
    assert(product);

    return product->price_per_unit;
}

double pdGetTotalIncome(Product product) {
    assert(product);
    return product->total_income;
}

void pdFree(ASElement toFree) {
    if (!toFree)
        return;
    free( (((Product)toFree)->prod_name));
    ((Product)toFree)->prod_name = NULL;
    ((Product)toFree)->freeData(  ((Product)toFree)->customData  );
    free((Product)toFree);
}


int pdCompare(ASElement pd1, ASElement pd2) {
    if (((Product)pd1)->id == ((Product)pd2)->id )
        return 0;

    assert(((Product)pd1)->id != ((Product)pd2)->id);
//    assert(strcmp(((Product)pd1)->prod_name, ((Product)pd2)->prod_name) != 0);

    if (((Product)pd1)->id > ((Product)pd2)->id)
        return 1;
    return -1;
}


ASElement pdCopy(ASElement toCopy) {
    if (!toCopy)
        return NULL;
    Product prod = malloc(sizeof (*prod));
    if (!prod)
        return NULL;
    assert(prod);
    prod->prod_name = malloc(strlen(((Product)toCopy)->prod_name) + 1);
    if (!prod->prod_name) {
        free(prod);
        prod = NULL;
        return NULL;
    }
    assert(prod->prod_name);

    strcpy(prod->prod_name,  ((Product)toCopy)->prod_name);

    prod->amount =  ((Product)toCopy)->amount;
    prod->amountType =  ((Product)toCopy)->amountType;
    prod->customData =  ((Product)toCopy)->copyData( ((Product)toCopy)->customData);
    if (!prod->customData){
        free(prod->prod_name);
        prod->prod_name = NULL;
        free(prod);
        prod = NULL;
        return NULL;
    }
    assert(prod->customData);
    prod->id = ((Product)toCopy)->id;
    prod->total_income = ((Product)toCopy)->total_income;
    prod->price_per_unit = ((Product)toCopy)->price_per_unit;
    prod->copyData =  ((Product)toCopy)->copyData;
    prod->freeData =  ((Product)toCopy)->freeData;
    prod->prodPrice =  ((Product)toCopy)->prodPrice;

    return prod;
}


