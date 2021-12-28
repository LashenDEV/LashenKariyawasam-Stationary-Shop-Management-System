#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

//Global variable
int paid;

//Struct
struct items {
    int itemID;
    char itemName[20];
    float price;
    int quantity;
};

struct p_items {
    int itemID;
    char itemName[20];
    float price;
    int quantity;
    float amount;
};

//Define colors
#define BLUE 1
#define CYAN 3
#define RED 4
#define LIGHTCYAN 11

//Declare functions
void buy();

void purchase();

void itemList();

void bill();

void date();

int getSize(const char *string);

void setColor(int color);

//Main function
int main() {
    int selection;
    setColor(BLUE);
    //Menu for user
    printf("\n\n");
    printf("                   === Welcome to TWELVE STORE ===                        \n");
    printf("                             Better For You                        \n");
    printf("TWELVE STORE DISTRIBUTORS PVT LTD\n");
    printf("No.17, Temple Road, Badulla.\n");
    printf("Tel:0554672571 Fax:0554672574\n");
    printf("\n--------------------------------------------------------------------\n");
    printf("1. Buy \n");
    printf("2. View the bill \n");
    printf("3. Exit \n");
    printf("\n--------------------------------------------------------------------\n");
    printf("Enter your selection: ");
    scanf("%d", &selection);
    //Take users selection
    switch (selection) {
        case 1:
            buy();
            break;
        case 2:
            bill();
            break;
        case 3:
            exit(0);
    }
}

//To display the list of items
void itemList() {
    FILE *itemsfp;
    struct items item;
    itemsfp = fopen("itemdata.txt", "r");
    // Check whether the file is present or not
    if (itemsfp == NULL) {
        printf("Couldn't open\n");
    } else {
        setColor(CYAN);
        printf("\n--------------------------------------------------------------------\n");
        printf("itemID\t  itemName  price  quantity\n");
        printf("--------------------------------------------------------------------\n");
        while (fscanf(itemsfp, "%d %s %f %d", &item.itemID, item.itemName, &item.price, &item.quantity) != EOF) {
            printf("%-10d%-10s%-10.2f%2d\n", item.itemID, item.itemName, item.price, item.quantity);
        }
        fclose(itemsfp);
        printf("\n--------------------------------------------------------------------\n");
    }
}

//buy function
void buy() {
    purchase();
    bill();
    main();
}

//billing function
void bill() {
    setColor(LIGHTCYAN);
    //Declare local variables
    int payment;
    float cash_add, rest, cash, total_amount = 0;
    FILE *p_file;
    struct p_items p_item;
    //Purchased file ,read mode
    p_file = fopen("purchase_data.txt", "r");
    // Check whether the file is present or not
    if (p_file == NULL) {
        printf("\n\nCouldn't open\n");
    } else {
        // Check whether the file is empty or not
        if (getSize("purchase_data.txt") == 0) {
            printf("\n\t\t     *** You have no unpaid bills ***\n");
        } else {
            //Open file for checking payment status
            FILE *paidfp;
            paidfp = fopen("paid.txt", "r");
            while (fscanf(paidfp, "%d", &payment) != EOF) {
                paid = payment;
            }
            //Bill preview
            printf("\n***************** Your Bill Is Ready *****************\n");
            //Calling the date function
            date();
            printf("\n------------------------------------------------------ \n");
            printf("itemID\t  itemName  price   quantity    amount\n");
            printf("\n-------------------------------------------------------\n");
            //Show purchased items, price, quantity and amount.
            while (fscanf(p_file, "%d %s %f %d %f", &p_item.itemID, p_item.itemName, &p_item.price, &p_item.quantity,
                          &p_item.amount) != EOF) {
                printf("%-10d%-10s%-10.2f%-10d%-100.2f\n", p_item.itemID, p_item.itemName, p_item.price,
                       p_item.quantity,
                       p_item.amount);
                total_amount = total_amount + p_item.amount;
            }
            printf("\n------------------------------------------------------\n");
            printf("                        Total Amount    %.2f", total_amount);
            printf("\n------------------------------------------------------\n");
            fclose(p_file);
            //Check the payment state, continue with payment or not
            if (paid == 0) {
                //Cash input
                printf("Cash                                    ");
                scanf("%f", &cash);
                check:
                rest = cash - total_amount;
                //Check whether the cash sufficient.
                if (cash >= total_amount) {
                    printf("\n-------------------------------------------------------\n");
                    printf("Balance                                 %.2f\n", rest);
                    paidfp = fopen("paid.txt", "w");
                    fprintf(paidfp, "%d", 1);
                    fclose(paidfp);
                } else {
                    //if cash is not enough get cash again
                    printf("\nCash is not enough!\n");
                    printf("Cash                                    ");
                    scanf("%f", &cash_add);
                    cash = cash + cash_add;
                    goto check;
                }
            } else if (paid == 1) {
                setColor(RED);
                printf("\t\t\tPAID\n");
                setColor(LIGHTCYAN);
//                paidfp = fopen("paid.txt", "w");
//                fprintf(paidfp, "%d", 0);
//                fclose(paidfp);
                p_file = fopen("purchase_data.txt", "w");
                fclose(p_file);
            }
            date();
            printf("\n\t\tThank you! Come again...");
            printf("\n\n");
        }
    }
    main();
}

//purchase handler
void purchase() {
    int sele_itm, selection, quan, f_item;
    float amount, total;
    FILE *p_file, *paidfp;
    p_file = fopen("purchase_data.txt", "w");
    //reset the payment file
    paidfp = fopen("paid.txt", "w");
    fprintf(paidfp, "%d", 0);
    fclose(paidfp);
    do {
        FILE *itemfp, *copy_itemfp;
        struct items item;
        //itemlist read mode
        sele_itm:
        itemfp = fopen("itemdata.txt", "r");
        copy_itemfp = fopen("copy.txt", "w");
        itemList();

        printf("Enter the item: ");
        scanf("%d", &sele_itm);
        f_item = 0;
        if (itemfp) {
            while (fscanf(itemfp, "%d %s %f %d", &item.itemID, item.itemName, &item.price, &item.quantity) != EOF) {
                if (item.itemID == sele_itm) {
                    f_item = 1;
                    printf("%s", item.itemName);
                    quantity:
                    printf("\nEnter the quantity: ");
                    scanf("%d", &quan);
                    if (quan <= item.quantity) {
                        item.quantity = item.quantity - quan;
                        //Update file for quantity
                        fprintf(copy_itemfp, "%d %s %.2f %d\n", item.itemID, item.itemName, item.price, item.quantity);
                    } else {
                        printf("Sorry we have only %d items in stocks", item.quantity);
                        goto quantity;
                    }
                    amount = quan * item.price;
                    fprintf(p_file, "%d %s %.2f %d %.2f\n", item.itemID, item.itemName, item.price, quan, amount);
                } else {
                    //Append item to copy.txt
                    fprintf(copy_itemfp, "%d %s %.2f %d\n", item.itemID, item.itemName, item.price, item.quantity);
                }
            }
            if (f_item == 0) {
                setColor(RED);
                printf("\nItem is not found\n");
                setColor(CYAN);
                goto sele_itm;
            }
            fclose(itemfp);
            fclose(copy_itemfp);
            //clear itemdata.txt
            itemfp = fopen("itemdata.txt", "w");
            fclose(itemfp);
            //open itemdata.txt in write mode and copy.txt in read mode
            itemfp = fopen("itemdata.txt", "w");
            copy_itemfp = fopen("copy.txt", "r");
            while (fscanf(copy_itemfp, "%d %s %f %d\n", &item.itemID, item.itemName, &item.price, &item.quantity) !=
                   EOF) {
                //copy the copy.txt into itemdata.txt
                fprintf(itemfp, "%d %s %.2f %d\n", item.itemID, item.itemName, item.price, item.quantity);
            }
            fclose(itemfp);
            fclose(copy_itemfp);
            remove("copy.txt");
        }
        total = total + amount;
        printf("Total upto now %.2f", total);
        sel:
        printf("\nSelect 0 for exit or 1 for continue: ");
        scanf("%d", &selection);
        if (selection > 1) {
            setColor(RED);
            printf("\nInvalid selection");
            setColor(CYAN);
            goto sel;
        }
    } while (selection != 0);
    fclose(p_file);
}

//Date function
void date() {
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    int m;
    printf("\nDate - %d/", tm.tm_mday);
    m = tm.tm_mon + 1;
    switch (m) {
        case 1:
            printf("Jan/");
            break;
        case 2:
            printf("Feb/");
            break;
        case 3:
            printf("Mar/");
            break;
        case 4:
            printf("Apr/");
            break;
        case 5:
            printf("May/");
            break;
        case 6:
            printf("June/");
            break;
        case 7:
            printf("July/");
            break;
        case 8:
            printf("Aug/");
            break;
        case 9:
            printf("Sep/");
            break;
        case 10:
            printf("Oct/");
            break;
        case 11:
            printf("Nov/");
            break;
        case 12:
            printf("Dec/");
            break;
    }
    printf("%d  ", tm.tm_year + 1900);

    //Setting up the time AM PM
    printf("Time - ");
    if (tm.tm_hour >= 12) {
        if (tm.tm_hour == 12)
            printf("12");
        else
            printf("%02d", tm.tm_hour - 12);
        printf(":%02d PM\n", tm.tm_min);
    } else
        printf("%02d:%02d AM\n", tm.tm_hour, tm.tm_min);
}

int getSize(const char *file_name) {
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

void setColor(int color) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}