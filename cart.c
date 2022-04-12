#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cart.h"

void breakingCart()
{
    printf("--------------------------------\n");
}

int checksIfEmptyCart(CartNode *root)
{
    if (root == NULL) return 1;
    return 0;
}

CartNode *freeMemoryCart(CartNode *root)
{
    if (!checksIfEmptyCart(root))
    {
        freeMemoryCart(root->left);
        freeMemoryCart(root->right);
        free(root);
    }
    return NULL;
}

CartNode *newlyCart(int codeprod, int qt_buy, char name[30], float price) //creates a new item
{
    CartNode *new_one = (CartNode*)malloc(sizeof(CartNode));
    new_one->info.codeprod = codeprod;
    strcpy(new_one->info.name, name);
    new_one->info.price = price;
    new_one->info.qt_buy = qt_buy;
    new_one->left = NULL;
    new_one->right = NULL;
    return new_one;
}

void printingCart(CartNode *root) //prints in order
{
    if (root == NULL) return;
    printingCart(root->left);
    printf("Id: %d\n", root->info.codeprod);
    printf("Name: %s\n", root->info.name);
    printf("Price: %.2f\n", root->info.price);
    printf("Quantity : %d\n", root->info.qt_buy);
    breakingCart();
    printingCart(root->right);
}

CartNode *searchingCart(CartNode *root, int codeprod) //searches for an item
{
    if (root == NULL || root->info.codeprod == codeprod) return root;
    else if (root->info.codeprod >= codeprod)
        return searchingCart(root->left, codeprod);
    else return searchingCart(root->right, codeprod);
}

int depthLeftCart(CartNode *root) //returns the height of the left subtree
{
	if (root == NULL) return 0;
	int n = 1 + depthLeftCart(root->left);
	return n;
}

int depthRightCart(CartNode *root) //returns the height of the right subtree
{
	if (root == NULL) return 0;
	int n = 1 + depthRightCart(root->right);
	return n;
}

int getSubTreeHeightCart(CartNode *root)
{
	if (root == NULL) return 0;
	int heightL = depthLeftCart(root->left);
	int heightR = depthRightCart(root->right);
	return 1 + ((heightL>heightR) ? heightL : heightR);
}

CartNode *llCart(CartNode *root) //LL Rotation
{
	CartNode *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

CartNode *rrCart(CartNode *root) //RR Rotation
{
	CartNode *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

CartNode *lrCart(CartNode *root) //Left-Right Rotation
{
	root->left = rrCart(root->left);
	return llCart(root);
}

CartNode *rlCart(CartNode *root) //Right-Left Rotation
{
	root->right = llCart(root->right);
	return rrCart(root);
}

CartNode *checkBalanceCart(CartNode *root)
{
    int rootBalance, childBalance;
    rootBalance = getSubTreeHeightCart(root->left)-getSubTreeHeightCart(root->right);
    if (rootBalance > 1)
    {
	    childBalance = getSubTreeHeightCart(root->left->left)-getSubTreeHeightCart(root->left->right);
	    root = (childBalance < 0) ? lrCart(root):llCart(root);
    }
    else if (rootBalance < -1)
    {
	    childBalance = getSubTreeHeightCart(root->right->left)-getSubTreeHeightCart(root->right->right);
   	    root = (childBalance < 0) ? rrCart(root):rlCart(root);
	}
    return root;
}

CartNode *insertCartNode(CartNode *root, CartNode *new_one)
{
	if (root == NULL) return new_one;
	if (root->info.name[0] >= new_one->info.name[0])
	    root->left = insertCartNode(root->left, new_one);
	else
	    root->right = insertCartNode(root->right, new_one);
    root = checkBalanceCart(root);
	return root;
}

CartNode *deletingCart(CartNode *root, int id) //deletes an item from the cart
{
    //finds the node
    if (root == NULL)
    return NULL;
    else if (root->info.codeprod > id)
        root->left = deletingCart(root->left, id);
    else if (root->info.codeprod < id)
        root->right = deletingCart(root->right, id);
    else { //once it finds the node
        if (root->left == NULL && root->right == NULL)
        { //the node does not have children
            free (root);
            root = NULL;
        }
        else if (root->left == NULL)
        { //the node has one child
           CartNode *aux = root;
           root = root->right;
           free (aux);
        }
        else if (root->right == NULL)
        {
            CartNode *aux = root;
            root = root->left;
            free(aux);
        }
        else
        { //the node has two children
            CartNode *aux = root->left;
            while (aux->right != NULL)
                aux = aux->right;
            root->info = aux->info; //exchanges informations
            aux->info.codeprod = id;
            root->left = deletingCart(root->left ,id);
        }
    }
    return root;
}
