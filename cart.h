struct cartInfo
{
    int codeprod;
    int qt_buy;
    char name[30];
    float price;
};

struct cartNode
{
    struct cartInfo info;
    struct cartNode *left, *right;
};

struct cartTree
{
    struct cartNode *root;
};

typedef struct cartInfo CartInfo;
typedef struct cartNode CartNode;
typedef struct cartTree CartTree;

void breakingCart();
int checksIfEmptyCart(CartNode *root);
CartNode *freeMemoryCart(CartNode *root);
CartNode *newlyCart(int codeprod, int qt_buy, char name[30], float price);
void printingCart(CartNode *root);
CartNode *searchingCart(CartNode *root, int codeprod);
int depthLeftCart(CartNode *root);
int depthRightCart(CartNode *root);
int getSubTreeHeightCart(CartNode *root);
CartNode *llCart(CartNode *root);
CartNode *rrCart(CartNode *root);
CartNode *lrCart(CartNode *root);
CartNode *rlCart(CartNode *root);
CartNode *checkBalanceCart(CartNode *root);
CartNode *insertCartNode(CartNode *root, CartNode *new_one);
CartNode *deletingCart(CartNode *root, int id);