#include <stdio.h>


void addbook(char titles[][50], float prices[], int isbns[], int bookquantity[], int *bookcount) {
    printf("Enter the book ISBN number you want to add: \n");
    int bookisbn;
    scanf("%d", &bookisbn);

    
    for (int i = 0; i < *bookcount; i++) { 
        if (isbns[i] == bookisbn) {
            printf("Duplicate ISBN -- Book Already Exists --\n");
            return;
        }
    }

    isbns[*bookcount] = bookisbn;

    printf("Please Enter Book Name: \n");
    scanf(" %[^\n]", titles[*bookcount]);  

    printf("Please Enter Book Price in RS: \n");
    scanf("%f", &prices[*bookcount]);

    printf("Please Enter the Number of Books: \n");
    scanf("%d", &bookquantity[*bookcount]);

    printf("\n====== New Book Added ========\n");
    printf("ISBN   : %d\n", isbns[*bookcount]);
    printf("Name   : %s\n", titles[*bookcount]);
    printf("Price  : %.1f\n", prices[*bookcount]);
    printf("Qty    : %d\n\n", bookquantity[*bookcount]);

    (*bookcount)++; 
}




void saleprocess(char titles[][50], float prices[], int isbns[], int bookquantity[], int *bookcount) {
    printf("Please Enter the ISBN Number: ");
    int bookisbn;
    scanf("%d", &bookisbn);

    int found = 0;
    int num = 0;

    for (int i = 0; i < *bookcount; i++) {
        if (bookisbn == isbns[i]) {
            found = 1;

            printf("How many copies will be sold: ");
            scanf("%d", &num);

            if (num <= bookquantity[i]) {
                bookquantity[i] -= num;

                printf("\n====== Book Sold ========\n");
                printf("ISBN           : %d\n", isbns[i]);
                printf("Name           : %s\n", titles[i]);
                printf("Price (each)   : %.1f\n", prices[i]);
                printf("Remaining Qty  : %d\n\n", bookquantity[i]);
            } else {
                printf("Error: Not enough stock available. Only %d left.\n\n", bookquantity[i]);
            }
            return; 
        }
    }

    if (found == 0) {
        printf("Error: Book with ISBN %d not found in inventory.\n\n", bookisbn);
    }
}




void stock(char titles[][50], int isbns[], int bookquantity[], int *bookcount) {
    printf("\n======= Low Stock Report =======\n");

    if (*bookcount == 0) {
        printf("No books in inventory yet.\n\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < *bookcount; i++) {
        if (bookquantity[i] < 5) {
            found = 1;
            printf("Name          : %s\n", titles[i]);
            printf("ISBN          : %d\n", isbns[i]);
            printf("Remaining Qty : %d\n\n", bookquantity[i]);
        }
    }

    if (!found) {
        printf("All books are sufficiently stocked.\n\n");
    }
}






int main(void) {
    int isbns[100], bookquantity[100];
    char titles[100][50];
    float prices[100];
    int bookcount = 0;   
    int menu;

    printf("WELCOME TO THE BOOK MANAGEMENT SYSTEM\n\n");
    
    do {
        printf("Select which operation you want to perform\n");
        printf("1. Add a new book\n");
        printf("2. Process a sale\n");
        printf("3. Generate low-stock report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menu);
     
        switch(menu) {
            case 1:
                addbook(titles, prices, isbns, bookquantity, &bookcount);
                break;
            case 2:
                saleprocess(titles, prices, isbns, bookquantity, &bookcount);
                break;
            case 3:
                stock(titles, isbns, bookquantity, &bookcount);
                break;
            case 4:
                printf("\nExiting.. Thank you for using the system!\n");
                break;
            default:
                printf("Incorrect option. Please try again.\n");
        }
    
    } while(menu != 4);

    return 0;
}
