#include "productCustomer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void breaking()
{
    printf("--------------------------------\n");
}

void initializer(ProductCustomer *root)
{
    root->rootC = NULL;
    root->rootP = NULL;
}

ProductCustomer *chooseProduct(CustomerNode *customer, ProductCustomer *pC)
{
    ProductNode *product;
    int id, quantity, checkContinue;
    while (1 == 1)
    {
        printingP(pC->rootP);
        printf("Id: ");
        scanf("%d", &id);
        printf("Quantity: ");
        scanf("%d", &quantity);
        breaking();
        product = searchingP(pC->rootP, id);
        if (checksIfEmptyP(product)) //no match
            printf("There is no product with this id.\n");
        else
        {
            if (quantity < 1 || product->info.qt_stock < quantity) //checks if it's an available quantity
                printf("This quantity is not available.\n");
            else
            {
                if (searchingCart(customer->info.cart.root, id) != NULL) //if the product is already in the cart
                    customer->info.cart.root->info.qt_buy += quantity;
                else //inserts a new product in the cart
                    customer->info.cart.root = insertCartNode(
                customer->info.cart.root,
                newlyCart(product->info.id, quantity, product->info.name, product->info.price));
                customer->info.totalCost += quantity * product->info.price; //adds to totalCost
                product->info.qt_stock -= quantity; //changes the quantity available
            }
        }
        printf("Total: R$ %.2f\n", customer->info.totalCost);
        breaking();
        printf("Continue? (1: Yes) ");
        scanf("%d", &checkContinue);
        breaking();
        if (checkContinue != 1) return pC;
    }
}

ProductCustomer *buy(CustomerNode *customer, ProductCustomer *pC)
{
    int confirm;
    printf("Confirm: (1-Yes) ");
    scanf("%d", &confirm);
    if (confirm != 1) return pC;
    else {
        customer->info.totalCost = 0;
        customer->info.cart.root = freeMemoryCart(customer->info.cart.root);
    }
    return pC;
}

ProductCustomer *removesAnItem(CustomerNode *customer, ProductCustomer *pC)
{
    CartNode *auxCart;
    ProductNode *auxP;
    int id;
    printf("Id: ");
    scanf("%d", &id);
    auxCart = searchingCart(customer->info.cart.root, id);
    if (checksIfEmptyCart(auxCart))
    {
        printf("There is no product with this id.\n");
        return pC;
    }
    else
    {
        auxP = searchingP(pC->rootP, id);
        auxP->info.qt_stock += auxCart->info.qt_buy; //changes product quantity
        customer->info.totalCost -= auxCart->info.price * auxCart->info.qt_buy; //changes totalCost
        customer->info.cart.root = deletingCart(customer->info.cart.root, id); //deletes
        printf("The produt was successfully removed from the cart.\n");
    }
    return pC;
}

ProductCustomer *signedIn(CustomerNode *customer, ProductCustomer *pC)
{
    int option;
    while (1 == 1)
    {
        breaking();
        printf("1-Choose products\n2-Cart\n3-Remove an item from the cart\n4-Buy "
           "products\n0-Sign out\n-> ");
        scanf("%d", &option);
        breaking();
        if (option == 0)
        {
            printf("Leaving current page.\n");
            breaking();
            return pC;
        }
        else if (option == 1)
            pC = chooseProduct(customer, pC);
        else if (option == 2)
        {
            if (checksIfEmptyCart(customer->info.cart.root))
                printf("The cart is empty.\n");
            else
            {
                printingCart(customer->info.cart.root);
                printf("Total: R$ %.2f\n", customer->info.totalCost);
            }
        }
        else if (option == 3)
            pC = removesAnItem(customer, pC);
        else if (option == 4)
            pC = buy(customer, pC);
        else
            printf("This option is not available.\n");
  }
}

void mainPage()
{
    ProductCustomer *pC;
    pC = (ProductCustomer*)malloc(sizeof(ProductCustomer));
    initializer(pC);
    CustomerNode *customer;
    int option;
    while (1 == 1)
    {
        breaking();
        printf("Welcome to AmazonCC!\n");
        breaking();
        printf("Main page:\n1-Customers\n2-Products\n3-Sign in\n0-Leave\n-> ");
        scanf("%d", &option);
        breaking();
        if (option == 0)
        {
            printf("Leaving page.\n");
            breaking();
            freeMemoryC(pC->rootC);
            freeMemoryP(pC->rootP);
            return;
        }
        else if (option == 1)
            pC->rootC = customersPage(pC->rootC);
        else if (option == 2)
            pC->rootP = productsPage(pC->rootP);
        else if (option == 3)
        {
            customer = signingIn(pC->rootC);
            if (!checksIfEmptyC(customer))
            {
                pC = signedIn(customer, pC);
                pC->rootP = pC->rootP;
                customer = pC->rootC;
            }
        } else
        {
            printf("This option is not available.\n");
            breaking();
        }
    }
}
