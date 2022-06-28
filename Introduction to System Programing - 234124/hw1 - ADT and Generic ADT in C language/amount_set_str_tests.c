#include "amount_set_str.h"
#include "amount_set_str_tests.h"

bool testAsCreateEmptySet() {
    AmountSet as = asCreate();
    ASSERT_OR_DESTROY(NULL != as);

    asDestroy(as);
    return true;
}

bool testAsDeleteEmptySet() {
    AmountSet as = asCreate();
    ASSERT_OR_DESTROY(NULL != as);
    ASSERT_OR_DESTROY(asGetSize(as) == 0);

    asDestroy(as);
    return true;
}


bool testAsAddingToSet() {
    AmountSet as = asCreate();
    ASSERT_OR_DESTROY(NULL != as);

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Apple"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Banana"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Lemon"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Mango"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Papaya"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Peach"));
    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asRegister(NULL,NULL));
    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asRegister(NULL,"BlaBlaBla"));
    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asRegister(as,NULL));
    ASSERT_OR_DESTROY( AS_ITEM_ALREADY_EXISTS == asRegister(as,"Apple"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,""));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"123"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"  "));
    ASSERT_OR_DESTROY( AS_ITEM_ALREADY_EXISTS == asRegister(as,"  "));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as," ' "));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as," NULL "));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"    ")); // Tab
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"\n"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"!@#"));


    asDestroy(as);
    return true;
}


bool testAsCopySet() {
    AmountSet as = asCreate();
    ASSERT_OR_DESTROY(NULL != as);

    AmountSet copy = asCopy(as);
    ASSERT_OR_DESTROY(NULL != copy);
    asDestroy(copy);

    ASSERT_OR_DESTROY(asCopy(NULL) == NULL);

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Apple"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Banana"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Lemon"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,""));
    ASSERT_OR_DESTROY( AS_ITEM_ALREADY_EXISTS == asRegister(as,""));
    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asRegister(as,NULL));
    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asRegister(NULL,NULL));
    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asRegister(NULL,"not_exist"));
    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asRegister(NULL,"Apple"));





    copy = asCopy(as);
    ASSERT_OR_DESTROY(NULL != copy);

    ASSERT_OR_DESTROY(asGetSize(copy) == asGetSize(as));
    ASSERT_OR_DESTROY(asContains(copy, "Apple"));
    ASSERT_OR_DESTROY(asContains(copy, "Banana"));
    ASSERT_OR_DESTROY(asContains(copy, "Lemon"));
    ASSERT_OR_DESTROY(asContains(copy, ""));

    ASSERT_OR_DESTROY(asGetSize(as) == asGetSize(copy));



    asDestroy(copy);
    asDestroy(as);
    return true;
}

bool testAsSize() {
    AmountSet as = NULL;
    ASSERT_OR_DESTROY(asGetSize(as) == -1);

    as = asCreate();
    ASSERT_OR_DESTROY(NULL != as);
    ASSERT_OR_DESTROY(asGetSize(as) == 0);

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Apple"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Banana"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Lemon"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,""));
    ASSERT_OR_DESTROY( AS_ITEM_ALREADY_EXISTS == asRegister(as,""));
    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asRegister(as,NULL));

    ASSERT_OR_DESTROY(asGetSize(as) == 4);
    asDestroy(as);

    return true;


}

bool testAsContains() {
    AmountSet as = NULL;
    as = asCreate();
    ASSERT_OR_DESTROY(NULL != as);


    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Apple"));
    ASSERT_OR_DESTROY(true == asContains(as, "Apple"));

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,""));
    ASSERT_OR_DESTROY(true == asContains(as, ""));

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"123"));
    ASSERT_OR_DESTROY(true == asContains(as, "123"));

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"  "));
    ASSERT_OR_DESTROY( true == asContains(as, "  "));
    ASSERT_OR_DESTROY(true == asContains(as, " "" "));


    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as," ' "));
    ASSERT_OR_DESTROY(true == asContains(as, " ' "));

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"    ")); // Tab
    ASSERT_OR_DESTROY(true == asContains(as, "    ")); // Tab

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"\n"));
    ASSERT_OR_DESTROY(true == asContains(as, "\n"));

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"!@#"));
    ASSERT_OR_DESTROY(true == asContains(as, "!@#"));

    asDestroy(as);
    return true;
}

bool testAsIteratorInvalid() {
    AmountSet as = asCreate();
    AmountSet as2 = asCopy(as);
    ASSERT_OR_DESTROY(asGetNext(NULL) == NULL);

    ASSERT_OR_DESTROY(asGetNext(as) == NULL);
    ASSERT_OR_DESTROY(asGetNext(as2) == NULL);

    AmountSet as3 = asCreate();
    ASSERT_OR_DESTROY(asGetNext(as3) == NULL);
    asRegister(as3,"test");
    ASSERT_OR_DESTROY(asGetNext(as3) == NULL);

    asGetFirst(as3);
    ASSERT_OR_DESTROY(asGetNext(as3) == NULL);
    asGetFirst(as3);
    asRegister(as3,"test2");
    ASSERT_OR_DESTROY(asGetNext(as3) == NULL);

    asGetFirst(as3);
    asRegister(as3,"test2");
    ASSERT_OR_DESTROY(asGetNext(as3) == NULL);

    asGetFirst(as3);
    asRegister(as3,NULL);
    ASSERT_OR_DESTROY(asGetNext(as3) == NULL);

    asGetFirst(as3);
    ASSERT_OR_DESTROY(asGetNext(as3) != NULL);


    AmountSet as4 = asCopy(as3);
    ASSERT_OR_DESTROY(asGetNext(as3) == NULL);
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);

    asGetFirst(as4);
    ASSERT_OR_DESTROY(asGetNext(as4) != NULL);
    asDelete(as4,"test2");
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);

    asRegister(as4,"123");
    asRegister(as4,"456");
    asGetFirst(as4);
    ASSERT_OR_DESTROY(asGetNext(as4) != NULL);
    asDelete(as4,"test2");
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);

    asGetFirst(as4);
    asDelete(as4,"000");
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);

    asGetFirst(as4);
    ASSERT_OR_DESTROY(asGetNext(as4) != NULL);
    asDelete(as4,NULL);
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);

    asGetFirst(as4);
    ASSERT_OR_DESTROY(asGetNext(as4) != NULL);
    asDelete(as4,"123");
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);

    asGetFirst(as4);
    ASSERT_OR_DESTROY(asGetNext(as4) != NULL);
    asDelete(as4,"345");
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);

    asGetFirst(as4);
    ASSERT_OR_DESTROY(asGetNext(as4) != NULL);
    asDelete(as4,"test");
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);


    asClear(as4);
    ASSERT_OR_DESTROY(asGetNext(as4) == NULL);

    asClear(as3);
    ASSERT_OR_DESTROY(asGetNext(as3) == NULL);

    asClear(as2);
    ASSERT_OR_DESTROY(asGetNext(as2) == NULL);

    asClear(as);
    ASSERT_OR_DESTROY(asGetNext(as) == NULL);



    asDestroy(as);
    asDestroy(as2);
    asDestroy(as3);
    asDestroy(as4);

    return true;
}

bool testAsClear() {
    AmountSet as = asCreate();
    ASSERT_OR_DESTROY( AS_SUCCESS == asClear(as));

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Apple"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asClear(as));

    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Apple"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Banana"));
    ASSERT_OR_DESTROY( AS_SUCCESS == asClear(as));

    ASSERT_OR_DESTROY( AS_NULL_ARGUMENT == asClear(NULL));

    asDestroy(as);
    return true;
}

bool testAsAmount() {
    AmountSet as = asCreate();
    ASSERT_OR_DESTROY( AS_SUCCESS == asRegister(as,"Apple"));
    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", 0));
    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", -0));
    ASSERT_OR_DESTROY(AS_ITEM_DOES_NOT_EXIST == asChangeAmount(as, "apple", 0));



    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", 1));

    ASSERT_OR_DESTROY(AS_NULL_ARGUMENT == asChangeAmount(NULL, "Apple", 1));
    ASSERT_OR_DESTROY(AS_NULL_ARGUMENT == asChangeAmount(as, NULL, 1));
    ASSERT_OR_DESTROY(AS_NULL_ARGUMENT == asChangeAmount(NULL, NULL, 4));
    ASSERT_OR_DESTROY(AS_NULL_ARGUMENT == asChangeAmount(NULL, "apple", -5));

    ASSERT_OR_DESTROY(AS_ITEM_DOES_NOT_EXIST == asChangeAmount(as, "apple", -4));

    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple",- 1));
    ASSERT_OR_DESTROY(AS_INSUFFICIENT_AMOUNT == asChangeAmount(as, "Apple",- 1));
    ASSERT_OR_DESTROY(AS_INSUFFICIENT_AMOUNT == asChangeAmount(as, "Apple",- 100));

    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", 0.0001));
    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", 0));
    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", -0));


    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", 0.0001));
    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", -0.0001));
    ASSERT_OR_DESTROY(AS_INSUFFICIENT_AMOUNT == asChangeAmount(as, "Apple", -0.0002));
    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", -0.0001));

    double amount;
    ASSERT_OR_DESTROY(AS_SUCCESS == asGetAmount(as,"Apple",&amount));
    ASSERT_TEST(amount == 0);

    ASSERT_OR_DESTROY(AS_SUCCESS == asChangeAmount(as, "Apple", 0.0001));
    ASSERT_OR_DESTROY(AS_SUCCESS == asGetAmount(as,"Apple",&amount));
    ASSERT_TEST(amount == 0.0001);

    ASSERT_OR_DESTROY(AS_NULL_ARGUMENT == asGetAmount(NULL,"not",&amount));
    ASSERT_OR_DESTROY(AS_NULL_ARGUMENT == asGetAmount(as,NULL,&amount));
    ASSERT_OR_DESTROY(AS_NULL_ARGUMENT == asGetAmount(as,"not exsit",NULL));

    ASSERT_OR_DESTROY(AS_ITEM_DOES_NOT_EXIST == asGetAmount(as,"apple",&amount));


    asDestroy(as);
    return true;
}