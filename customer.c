#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

void breakingC()
{
    printf("--------------------------------\n");
}

int checksIfEmptyC(CustomerNode *root)
{
    if (root == NULL) return 1;
    return 0;
}

CustomerNode *freeMemoryC(CustomerNode *root)
{
    if (!checksIfEmptyC(root))
    {
        freeMemoryC(root->left);
        freeMemoryC(root->right);
        free(root);
    }
    return NULL;
}

CustomerNode *searchingC(CustomerNode *root, char name[60]) //searches for a node with parameter name
{
    if (checksIfEmptyC(root) || strcmp(root->info.name, name) == 0) return root;
    else if (root->info.name[0] >= name[0])
        return searchingC(root->left, name);
    else return searchingC(root->right, name);
}

CustomerNode *searchingCId(CustomerNode *root, char name[60], int id)
{
    if (checksIfEmptyC(root) || root->info.id == id) return root;
    else if (root->info.name[0] >= name[0])
        return searchingC(root->left, name);
    else return searchingC(root->right, name);
}

int idC (CustomerNode *root, char name[60])
{ //gets customer's id
    int id;
    while (1==1)
    {
        printf("Id: ");
        scanf("%d", &id);
        if (checksIfEmptyC(searchingCId(root, name, id))) return id;
        printf("This id has already been used.\n");
        breakingC();
    }
}

CustomerNode *newlyC(CustomerNode *root)
{ //creates a new customer
    CustomerNode *new_one = (CustomerNode*)malloc(sizeof(CustomerNode));
    while (1==1) //makes sure the name has not been used yet
    {
        char name[60];
        printf("Name: ");
        scanf("%s", name);
        if (checksIfEmptyC(searchingC(root, name)))
        {
            strcpy(new_one->info.name, name);
            break;
        }
        printf("This name has already been used.\n");
        breakingC();
    }
    new_one->info.id = idC(root, new_one->info.name);
    printf("CPF: ");
    scanf("%s", new_one->info.cpf);
    printf("Password: ");
    scanf("%s", new_one->info.password);
    printf("Email: ");
    scanf("%s", new_one->info.email);
    new_one->info.cart.root = NULL;
    new_one->info.totalCost = 0;
    new_one->left = NULL;
    new_one->right = NULL;
    return new_one;
}

void printingC(CustomerNode *root)
{ //prints in order
    if (checksIfEmptyC(root)) return;
    printingC(root->left);
    printf("Id: %d\n", root->info.id);
    printf("Name: %s\n", root->info.name);
    printf("CPF: %s\n", root->info.cpf);
    printf("Password: %s\n", root->info.password);
    printf("Email: %s\n", root->info.email);
    breakingC();
    printingC(root->right);
}

void printingSpecificCustomer(CustomerNode *customer)
{
    breakingC();
    printf("Name: %s\n", customer->info.name);
    printf("CPF: %s\n", customer->info.cpf);
    printf("Password: %s\n", customer->info.password);
    printf("Email: %s\n", customer->info.email);
}

int depthLeftC(CustomerNode *root)
{ //returns the height of the left subtree
	if (checksIfEmptyC(root)) return 0;
	int n = 1 + depthLeftC(root->left);
	return n;
}

int depthRightC(CustomerNode *root)
{ //returns the height of the right subtree
	if (checksIfEmptyC(root)) return 0;
	int n = 1 + depthRightC(root->right);
	return n;
}

int getSubTreeHeightC(CustomerNode *root)
{
	if (checksIfEmptyC(root)) return 0;
	int heightL = depthLeftC(root->left);
	int heightR = depthRightC(root->right);
	return 1 + ((heightL>heightR) ? heightL : heightR);
}

CustomerNode *llC(CustomerNode *root)
{ //LL Rotation
	CustomerNode *newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

CustomerNode *rrC(CustomerNode *root)
{ //RR Rotation
	CustomerNode *newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

CustomerNode *lrC(CustomerNode *root)
{ //Left-Right Rotation
	root->left = rrC(root->left);
	return llC(root);
}

CustomerNode *rlC(CustomerNode *root)
{ //Right-Left Rotation
	root->right = llC(root->right);
	return rrC(root);
}

CustomerNode *checkBalanceC(CustomerNode *root)
{
    int rootBalance, childBalance;
    rootBalance = getSubTreeHeightC(root->left)-getSubTreeHeightC(root->right);
    if (rootBalance > 1)
    {
	    childBalance = getSubTreeHeightC(root->left->left)-getSubTreeHeightC(root->left->right);
	    root = (childBalance < 0) ? lrC(root):llC(root);
    }
    else if (rootBalance < -1)
    {
	    childBalance = getSubTreeHeightC(root->right->left)-getSubTreeHeightC(root->right->right);
   	    root = (childBalance < 0) ? rrC(root):rlC(root);
	}
    return root;
}

CustomerNode *insertCustomerNode(CustomerNode *root, CustomerNode *new_one)
{
	if (checksIfEmptyC(root)) return new_one;
	if (root->info.name[0] >= new_one->info.name[0])
	    root->left = insertCustomerNode(root->left, new_one);
	else
	    root->right = insertCustomerNode(root->right, new_one);
    root = checkBalanceC(root);
	return root;
}

CustomerNode *deletingC(CustomerNode *root, char name[60])
{ //deletes a customer
    //finds the node
    if (checksIfEmptyC(root)) return NULL;
    else if (root->info.name[0] > name[0])
        root->left = deletingC(root->left, name);
    else if (root->info.name[0] < name[0])
        root->right = deletingC(root->right, name);
    else { //once it finds the node
        if (checksIfEmptyC(root->left) && checksIfEmptyC(root->right)) //the node does not have children
        {
            free (root);
            root = NULL;
        }
        else if (checksIfEmptyC(root->left))
        { //the node has one child
           CustomerNode *aux = root;
           root = root->right;
           free (aux);
        }
        else if (checksIfEmptyC(root->right))
        {
            CustomerNode *aux = root;
            root = root->left;
            free(aux);
        }
        else
        { //the node has two children
            CustomerNode *aux = root->left;
            while (!checksIfEmptyC(aux->right))
                aux = aux->right;
            root->info = aux->info; //exchanges informations
            strcpy(aux->info.name, name);
            root->left = deletingC(root->left, name);
        }
    }
    return root;
}

CustomerNode *searchSignIn(CustomerNode *root, char name[60], char password[7]) //checks if the name and password match to the correct informations given
{
    CustomerNode *aux = searchingC(root, name);
    if (checksIfEmptyC(aux)) return NULL;
    else {
        if (strcmp(aux->info.password, password) == 0)
            return aux;
        return NULL;
    }
}

CustomerNode *signingIn(CustomerNode *root)
{
    CustomerNode *aux;
    char name[60], password[7];
    int i = 0;
    for (; i < 3; i++) //a customer can only try thrice signing in
    {
        printf("Name: ");
        scanf("%s", name);
        printf("Password: ");
        scanf("%s", password);
        aux = searchSignIn(root, name, password);
        if (checksIfEmptyC(aux))
        {
            breakingC();
            printf("There is no customer with this name or wrong password.\n");
            breakingC();
        }
        else return aux;
    }
    printf("You've run out of tries.\n");
    printf("Leaving current page.");
    return aux;
}

CustomerNode *checksIfCustomerExists(CustomerNode *root)
{
    CustomerNode *aux;
    char name[60];
    printf("Name: ");
    scanf("%s", name);
    aux = searchingC(root, name);
    if (checksIfEmptyC(aux))
    {
        breakingC();
        printf("There is no customer with this name.\n");
        breakingC();
        return NULL;
    }
    return aux;
}

CustomerNode *customersPage(CustomerNode *root)
{
    CustomerNode *aux;
    int option;
    while (1==1)
    {
        printf("1-Insert a new customer\n2-List every customer\n3-Search for a customer\n4-Remove a customer\n0-Leave\n-> ");
        scanf("%d", &option);
        breakingC();
        if (option == 0)
        {
            printf("Leaving current page.\n");
            breakingC();
            return root;
        }
        else if (option == 1)
        {
            root = insertCustomerNode(root, newlyC(root));
            breakingC();
        }
        else if (option == 2)
        {
            if (checksIfEmptyC(root))
            {
                printf("There is no customer.\n");
                breakingC();
            }
            else printingC(root);
        }
        else if (option == 3)
        {
            aux = checksIfCustomerExists(root);
            if (!checksIfEmptyC(aux))
                printingSpecificCustomer(aux);
            breakingC();
        }
        else if (option == 4)
        {
            aux = checksIfCustomerExists(root);
            if (!checksIfEmptyC(aux))
            {
                root = deletingC(root, aux->info.name);
                breakingC();
                printf("The customer was successfully removed.\n");
            }
             breakingC();
        }
        else
        {
            printf("This option is not available.\n");
            breakingC();
        }
    }

}
