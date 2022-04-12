#include "cart.h"

struct customerInfo
{
    int id;
    char name[60];
    char cpf[15];
    char password[7];
    char email[60];
    CartTree cart;
    float totalCost;
};

struct customerNode
{
    struct customerInfo info;
    struct customerNode *left, *right;
};

typedef struct customerInfo CustomerInfo;
typedef struct customerNode CustomerNode;

void breakingC();
int checksIfEmptyC(CustomerNode *root);
CustomerNode *freeMemoryC(CustomerNode *root);
CustomerNode *searchingC(CustomerNode *root, char name[60]);
CustomerNode *searchingCId(CustomerNode *root, char name[60], int id);
int idC (CustomerNode *root, char name[60]);
CustomerNode *newlyC(CustomerNode *root);
void printingC(CustomerNode *root);
void printingSpecificCustomer(CustomerNode *customer);
int depthLeftC(CustomerNode *root);
int depthRightC(CustomerNode *root);
int getSubTreeHeightC(CustomerNode *root);
CustomerNode *llC(CustomerNode *root);
CustomerNode *rrC(CustomerNode *root);
CustomerNode *lrC(CustomerNode *root);
CustomerNode *rlC(CustomerNode *root);
CustomerNode *checkBalanceC(CustomerNode *root);
CustomerNode *insertCustomerNodeC(CustomerNode *root, CustomerNode *new_one);
CustomerNode *deletingC(CustomerNode *root, char name[60]);
CustomerNode *searchSignIn(CustomerNode *root, char name[60], char password[7]);
CustomerNode *signingIn(CustomerNode *root);
CustomerNode *checksIfCustomerExists(CustomerNode *root);
CustomerNode *customersPage(CustomerNode *root);