#include <stdio.h>
#include <string.h>

int productcodes[4] = {1, 2, 3, 4};
int productqty[4] = {50, 10, 20, 8};
float productprice[4] = {100.0, 200.0, 300.0, 150.0};
char *productname[4] = {"Apple", "Milk", "Bread", "Eggs"};

char customername[30];
char customercnic[16];

int cartitems[5];
int cartqty[5];
int cartcount = 0;
float total = 0.0;

void entercustomerinfo();
void displayinventory();
void additemtocart();
void displaytotalbill();
void showinvoice();

int main() {
    int choice;

    do {
        printf("\n--- Supermarket System Menu ---\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                entercustomerinfo();
                break;
            case 2:
                displayinventory();
                break;
            case 3:
                additemtocart();
                break;
            case 4:
                displaytotalbill();
                break;
            case 5:
                showinvoice();
                break;
            case 6:
                printf("Exiting system. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}

void entercustomerinfo() {
    printf("Enter customer name: ");
    scanf(" %[^\n]s", customername);
    printf("Enter customer CNIC: ");
    scanf(" %[^\n]s", customercnic);
    printf("Customer information saved.\n");
}

void displayinventory() {
    printf("\n--- Product List ---\n");
    printf("Code\tName\tQuantity  Price\n");

    for (int i = 0; i < 4; i++) {
        int code = productcodes[i];
        char *name = productname[i];
        int qty = productqty[i];
        float price = productprice[i];

        printf("%d\t%s\t%d\t%.2f\n", code, name, qty, price);
    }
}

void additemtocart() {
    if (cartcount >= 5) {
        printf("Cart is full! Cannot add more items.\n");
        return;
    }

    int code, qty, index = -1;
    printf("Enter product code to add to cart: ");
    scanf("%d", &code);

    for (int i = 0; i < 4; i++) {
        if (productcodes[i] == code) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Product code not found!\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &qty);

    if (qty > productqty[index]) {
        printf("Not enough stock! Available: %d\n", productqty[index]);
    } else {
        cartitems[cartcount] = index;
        cartqty[cartcount] = qty;
        cartcount++;
        productqty[index] -= qty;
        printf("%d of %s added to cart.\n", qty, productname[index]);
    }
}

void displaytotalbill() {
    if (cartcount == 0) {
        printf("No items purchased yet.\n");
        return;
    }

    total = 0.0;
    for (int i = 0; i < cartcount; i++) {
        total += productprice[cartitems[i]] * cartqty[i];
    }

    printf("Total bill without discount: %.2f\n", total);

    char code[20];
    printf("Do you have a promo code? Enter or 'no': ");
    scanf(" %s", code);
    if (strcmp(code, "Eid2025") == 0) {
        total *= 0.75;
        printf("Promo code applied! 25%% discount.\n");
    }

    printf("Total after discount (if any): %.2f\n", total);
}

void showinvoice() {
    if (cartcount == 0) {
        printf("No items purchased yet. Cannot show invoice.\n");
        return;
    }

    printf("\n--- Invoice ---\n");
    printf("Customer Name: %s\n", customername);
    printf("CNIC: %s\n", customercnic);
    printf("\nItems Purchased:\n");
    printf("Product\tQuantity\tPrice\tTotal\n");

    total = 0.0;
    for (int i = 0; i < cartcount; i++) {
        int idx = cartitems[i];
        float itemtotal = productprice[idx] * cartqty[i];
        total += itemtotal;
        printf("%s\t%d\t%.2f\t%.2f\n",
               productname[idx], cartqty[i],
               productprice[idx], itemtotal);
    }

    char code[20];
    printf("Enter promo for discount or 'no': ");
    scanf(" %s", code);
    if (strcmp(code, "Eid 2025") == 0) {
        total *= 0.75;
        printf("Promo code application success! 25%% discount.\n");
    }

    printf("Grand Total amount: %.2f\n", total);
}
