#include "customer.h"
#include "product.h"

struct productAndCustomer
{
    ProductNode *rootP;
    CustomerNode *rootC;
};

typedef struct productAndCustomer ProductCustomer;

void breaking();
void initializer(ProductCustomer *root);
ProductCustomer *chooseProduct(CustomerNode *customer, ProductCustomer *pC);
ProductCustomer *removesAnItem(CustomerNode *customer, ProductCustomer *pC);
ProductCustomer *buy(CustomerNode *customer, ProductCustomer *pC);
ProductCustomer *signedIn(CustomerNode *customer, ProductCustomer *pC);
void mainPage();