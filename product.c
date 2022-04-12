#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

void breakingP()
{
    printf("--------------------------------\n");
}

ProductNode *freeMemoryP(ProductNode *root)
{
    if (!checksIfEmptyP(root))
    {
        freeMemoryP(root->left);
        freeMemoryP(root->right);
        free(root);
    }
    return NULL;
}

int checksIfEmptyP(ProductNode *root)
{
    if (root == NULL) return 1;
    return 0;
}

ProductNode *searchingP(ProductNode *root, int id)
{ //searches for a product with the same id
    if (checksIfEmptyP(root) || root->info.id == id) return root;
    else if (root->info.id >= id)
        return searchingP(root->left, id);
    else return searchingP(root->right, id);
}

ProductNode *searchingPName(ProductNode *root, int id, char name[30]) //searches for a product with the same name
{
    if (checksIfEmptyP(root) || strcmp(root->info.name, name) == 0) return root;
    else if (root->info.id >= id)
        return searchingP(root->left, id);
    else return searchingP(root->right, id);
}

int idP (ProductNode *root)
{ //gets id
    int id;
    while (1==1)
    {
        printf("Id: ");
        scanf("%d", &id);
        if (checksIfEmptyP(searchingP(root, id))) return id;
        printf("This id has already been used.\n");
        breakingP();
    }
}

float checksPrice()
{ //gets price checking if it's more than 0.1
    float price;
    while (1==1)
    {
        printf("Price: R$ ");
        scanf("%f", &price);
        if (price > 0.1) return price;
        printf("This price is not available.\n");
    }
}

int checksproductQuantity()
{ //gets quantity checking if it's more than 0
    int quantity;
    while (1==1)
    {
        printf("Stock quantity: ");
        scanf("%d", &quantity);
        if (quantity > 0) return quantity;
        printf("This quantity is not available.\n");
    }
}


ProductNode *newlyP(ProductNode *root)
{ //creates a new product
    ProductNode *new_one = (ProductNode*)malloc(sizeof(ProductNode));
    new_one->info.id = idP(root);
    while (1==1)
    { //checks if name already exists
        char name[30];
        printf("Name: ");
        scanf("%s", name);
        if (checksIfEmptyP(searchingPName(root, new_one->info.id, name)))
        {
            strcpy(new_one->info.name, name);
            break;
        }
        printf("This name has already been used.\n");
    } 
    new_one->info.price = checksPrice();
    new_one->info.qt_stock = checksproductQuantity();
    new_one->left = NULL;
    new_one->right = NULL;
    return new_one;
}

void printingP(ProductNode *root)
{ //prints products in order
    if (checksIfEmptyP(root)) return;
    printingP(root->left);
    printf("Id: %d\n", root->info.id);
    printf("Name: %s\n", root->info.name);
    printf("Price: R$ %.2f\n", root->info.price);
    printf("Stock quantity: %d\n", root->info.qt_stock);
    breakingP();
    printingP(root->right);
}

void printingSpecificProduct(ProductNode *product)
{
    printf("Id: %d\n", product->info.id);
    printf("Name: %s\n", product->info.name);
    printf("Price: R$ %.2f\n", product->info.price);
    printf("Stock quantity: %d\n", product->info.qt_stock);
}

int depthLeftP(ProductNode *root)
{ //returns the height of the left subtree
	if (checksIfEmptyP(root)) return 0;
	int n = 1 + depthLeftP(root->left);
	return n;
}

int depthRightP(ProductNode *root)
{ //returns the height of the right subtree
	if (checksIfEmptyP(root)) return 0;
	int n = 1 + depthRightP(root->right);
	return n;
}

int getSubTreeHeightP(ProductNode *root)
{
	if (checksIfEmptyP(root)) return 0;
	int heightL = depthLeftP(root->left);
	int heightR = depthRightP(root->right);
	return 1 + ((heightL>heightR) ? heightL : heightR);
}

ProductNode *llP(ProductNode *root)
{ //LL Rotation
	ProductNode *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

ProductNode *rrP(ProductNode *root)
{ //RR Rotation
	ProductNode *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

ProductNode *lrP(ProductNode *root) 
{ //Left-Right Rotation
	root->left = rrP(root->left);
	return llP(root);
}

ProductNode *rlP(ProductNode *root) 
{ //Right-Left Rotation
	root->right = llP(root->right);
	return rrP(root);
}

ProductNode *checkBalanceP(ProductNode *root)
{
    int rootBalance, childBalance;
    rootBalance = getSubTreeHeightP(root->left)-getSubTreeHeightP(root->right);
    if (rootBalance > 1)
    {
	    childBalance = getSubTreeHeightP(root->left->left)-getSubTreeHeightP(root->left->right);
	    root = (childBalance < 0) ? lrP(root):llP(root);
    }
    else if (rootBalance < -1)
    {
	    childBalance = getSubTreeHeightP(root->right->left)-getSubTreeHeightP(root->right->right);
   	    root = (childBalance < 0) ? rrP(root):rlP(root);
	}
    return root;
}

ProductNode *insertProductNode (ProductNode *root, ProductNode *new_one)
{
	if (checksIfEmptyP(root)) return new_one;
	if (root->info.id >= new_one->info.id)
	    root->left = insertProductNode(root->left, new_one);
	else
	    root->right = insertProductNode(root->right, new_one);
    root = checkBalanceP(root);
	return root;
}

ProductNode *deletingP(ProductNode *root, int id)
{ //deletes a product
    //finds the node
    if (checksIfEmptyP(root)) return NULL;
    else if (root->info.id > id)
        root->left = deletingP(root->left, id);
    else if (root->info.id < id)
        root->right = deletingP(root->right, id);
    else { //once it finds the node
        if (checksIfEmptyP(root->left) && checksIfEmptyP(root->right))
        { //the node does not have children
            free (root);
            root = NULL;
        }
        else if (checksIfEmptyP(root->left))
        { //the node has one child
           ProductNode *aux = root;
           root = root->right;
           free (aux);
        }
        else if (checksIfEmptyP(root->right))
        {
            ProductNode *aux = root;
            root = root->left;
            free (aux);
        }
        else
        { //the node has two children
            ProductNode *aux = root->left;
            while (!checksIfEmptyP(aux->right))
                aux = aux->right;
            root->info = aux->info; //exchanges informations
            aux->info.id = id;
            root->left = deletingP(root->left ,id);
        }
    }
    return root;
}

ProductNode *productQuantity(ProductNode *root)
{ //inserts a bigger quantity
    int id;
    printf("Id: ");
    scanf("%d", &id);
    ProductNode *aux = searchingP(root, id);
    if (checksIfEmptyP(aux))
    {
        printf("This product does not exist.\n");
        breakingP();
        return root;
    }
    else
    {
        aux->info.qt_stock += checksproductQuantity();
        return root;
    }
}

ProductNode *checksIfProductExists(ProductNode *root)
{
    ProductNode *aux;
    int id;
    printf("Id: ");
    scanf("%d", &id);
    breakingP();
    aux = searchingP(root, id);
    if (checksIfEmptyP(aux))
    {
        printf("There is no product with this id.\n");
        return NULL;
    }
    return aux;
}

ProductNode *productsPage(ProductNode *root)
{
    ProductNode *aux;
    int option, id;
    while (1==1)
    {
        printf("1-Insert a new product\n2-Search for a product\n3-Remove a product\n4-List every product\n5-Insert a bigger quantity\n0-Leave\n-> ");
        scanf("%d", &option);
        breakingP();
        if (option == 0)
        {
            printf("Leaving current page.\n");
            return root;
        }
        else if (option == 1)
        {
            root = insertProductNode(root, newlyP(root));
            breakingP();
        }
        else if (option == 2)
        {
            aux = checksIfProductExists(root);
            if (!checksIfEmptyP(aux))
            {
                printingSpecificProduct(aux);
            }
            breakingP();
        }
        else if (option == 3)
        {
            printf("Id: ");
            scanf("%d", &id);
            breakingP();
            if (checksIfEmptyP(searchingP(root, id))) printf("There is no product with this id.\n");
            else
            {
            root = deletingP(root, id);
            printf("The product was succesfully removed.\n");
            }
            breakingP();
        }
        else if (option == 4)
        {
            if (checksIfEmptyP(root))
            {
                printf("The list is empty.\n");
                breakingP();
            }
            else printingP(root);
        }
        else if (option == 5)
        {
            root = productQuantity(root);
            breakingP();
        }
        else
        {
            printf("This option is not available.\n");
        }
    }
}