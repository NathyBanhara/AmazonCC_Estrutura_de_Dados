struct productInfo
{
    int id;
    char name[30];
    float price;
    int qt_stock;
};

struct productNode
{
    struct productInfo info;
    struct productNode *left, *right;
};

typedef struct productInfo ProductInfo;
typedef struct productNode ProductNode;

void breakingP();
ProductNode *freeMemoryP(ProductNode *root);
int checksIfEmptyP(ProductNode *root);
ProductNode *searchingP(ProductNode *root, int id);
ProductNode *searchingPName(ProductNode *root, int id, char name[30]);
int idP (ProductNode *root);
float checksPrice();
int checksproductQuantity();
ProductNode *newlyP(ProductNode *root);
void printingP(ProductNode *root);
void printingSpecificProduct(ProductNode *product);
int depthLeftP(ProductNode *root);
int depthRightP(ProductNode *root);
int getSubTreeHeightP(ProductNode *root);
ProductNode *llP(ProductNode *root);
ProductNode *rrP(ProductNode *root);
ProductNode *lrP(ProductNode *root) ;
ProductNode *rlP(ProductNode *root);
ProductNode *checkBalanceP(ProductNode *root);
ProductNode *insertProductNode (ProductNode *root, ProductNode *new_one);
ProductNode *deletingP(ProductNode *root, int id);
ProductNode *productQuantity(ProductNode *root);
ProductNode *checksIfProductExists(ProductNode *root);
ProductNode *productsPage(ProductNode *root);