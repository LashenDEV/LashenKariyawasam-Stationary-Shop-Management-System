#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


struct items {
    int itemID;
    char itemName[20];
    int price;
};

struct p_items {
    int itemID;
    char itemName[20];
    int price;
    int quantity;
    int amount;
    int total_amount;
};

void buy();

void purchase();

void itemList();

void bill();

int itemNo();

void addItems();

void date();

int main() {
    int selection;
    printf("\n\n");
    printf("                   === Welcome to Richard Bookstore ===                        \n");
    printf("                             Better For You                        \n");
    printf("RICHARD PIERIS DISTRIBUTORS LTD.\n");
    printf("No.17, Yakkala Road, Gampaha.\n");
    printf("Tel:0334672571 Fax:0334672574\n");
    printf("\n--------------------------------------------------------------------\n");
    printf("1. Buy \n");
    printf("2. View the bill \n");
    printf("\n--------------------------------------------------------------------\n");
    printf("Enter your selection : ");
    scanf("%d", &selection);
    switch (selection) {
        case 1:
            buy();
            break;
        case 2:
            bill();
            break;
    }
}

//To display the list of items
void itemList() {
    FILE *itemsfp;
    struct items item;
    itemsfp = fopen("itemdata.txt", "r");
    if (itemsfp == NULL) {
        printf("Couldn't open\n");
    } else {
        printf("\n--------------------------------------------------------------------\n");
        printf("itemID\t  itemName  price\n");
        printf("--------------------------------------------------------------------\n");
        while (fscanf(itemsfp, "%d %s %d", &item.itemID, item.itemName, &item.price) != EOF) {
            printf("%-10d%-10s%-10d\n", item.itemID, item.itemName, item.price);
        }
        fclose(itemsfp);
        printf("\n--------------------------------------------------------------------\n");
    }
}

//buy function
void buy() {
    purchase();
    bill();
}


//void addItems() {
//    int selection = 1;
//    FILE *itemfp;
//    struct p_items p_item;
//    itemfp = fopen("purchasedata.txt", "a+");
//
//    if (itemfp == NULL) {
//        printf("Couldn't open\n");
//    } else {
//        do {
//            p_item.itemID = itemNo();
//            printf("%d", p_item.itemID);
//            printf("Enter item name:");
//            scanf(" %s", &p_item.itemName);
//            printf("Enter item price:");
//            scanf(" %d", &p_item.price);
//            fprintf(itemfp, "%d %s %d\n", p_item.itemID, p_item.itemName, p_item.price);
//            printf("*** Add Item Successfully ***");
//            printf("\nDo you want to add another Item (1)");
//            printf("\nor exit(0)");
//            scanf("%d", &selection);
//        } while (selection);
//    }
//
//
//    fclose(itemfp);
//
//    main();
//
//}

//billing function
void bill() {
    int rest, cash, cash_add;
    int total_amount = 0;
    FILE *p_file;
    struct p_items p_item;
    p_file = fopen("purchase_data.txt", "r");
    if (p_file == NULL) {
        printf("Couldn't open\n");
    } else {
        date();
        printf("\n------------------------------------------------------ \n");
        printf("itemID\t  itemName  price quantity  amount\n");
        printf("\n-------------------------------------------------------\n");
        while (fscanf(p_file, "%d %s %d %d %d", &p_item.itemID, p_item.itemName, &p_item.price, &p_item.quantity,&p_item.amount) != EOF) {
            printf("%-10d%-10s%-10d%-10d%-100d\n", p_item.itemID, p_item.itemName, p_item.price,  p_item.quantity,
                p_item.amount);
            total_amount = total_amount + p_item.amount;
        }
        printf("\n------------------------------------------------------\n");
        printf("                        Total Amount    %d", total_amount);
        printf("\n------------------------------------------------------\n");
        printf("\n***************** Your Bill Is Ready *****************\n");
        fclose(p_file);
        printf("Cash                                    ");
        scanf("%d", &cash);
        
        check:
        rest = cash - total_amount ;
        
        if (cash >= total_amount)
        {
            printf("-------------------------------------------------------\n");
            printf("Balance                                 %d\n",rest);
        }
        else
        {
            printf("\nCash is not enough!\n");
            printf("Cash                                    ");
            scanf("%d", &cash_add);
            cash = cash + cash_add;
            goto check;
        }
        
        date();
        printf("\n\n");
    }
}


//int itemNo() {
//    int itemID, allocated, selection;;
//    printf("Enter item number:");
//    scanf(" %d", &itemID);
//    FILE *itemfp;
//    itemfp = fopen("itemdata.txt", "r");
//    struct items item;
//    while (fscanf(itemfp, "%d %s %d", &item.itemID, item.itemName, &item.price) != EOF) {
//        if (item.itemID == itemID) {
//            allocated = 1;
//        }
//    }
//    fclose(itemfp);
//    if (allocated == 0)
//        return itemID;
//    else
//        return itemNo();
//}

//purchase handler
void purchase() {
    int sele_itm, selection, amount, quan, total_amount;;
    FILE *p_file;
    p_file = fopen("purchase_data.txt", "w");
    do {
        FILE *itemfp;
        struct items item;
        itemfp = fopen("itemdata.txt", "r");
        itemList();
        printf("Enter the item : ");
        scanf("%d", &sele_itm);
        if (itemfp) {
            while (fscanf(itemfp, "%d %s %d", &item.itemID, item.itemName, &item.price) == 3) {
                if (item.itemID == sele_itm) {
                    printf("%s", item.itemName);
                    printf("\nEnter the quantity : ");
                    scanf("%d", &quan);
                    amount = quan * item.price;
                    fprintf(p_file, "%d %s %d %d %d\n", item.itemID, item.itemName, item.price, quan, amount);
                }
            }
            fclose(itemfp);
        }
        printf("\nSelect 0 for exit or 1 for continue:");
        scanf("%d", &selection);
    } while (selection != 0);
    fclose(p_file);
}

void date() 
{
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    int m;
    printf("\nDate: %d-", tm.tm_mday);
    m = tm.tm_mon+1;
    switch(m)
    {
        case 1:
            printf("Jan-");
            break;
        case 2:
            printf("Feb-");
            break;
        case 3:
            printf("Mar-");
            break;
        case 4:
            printf("Apr-");
            break;
        case 5:
            printf("May-");
            break;
        case 6:
            printf("June-");
            break;
        case 7:
            printf("July-");
            break;
        case 8:
            printf("Aug-");
            break;
        case 9:
            printf("Sep-");
            break;
        case 10:
            printf("Oct-");
            break;
        case 11:
            printf("Nov-");
            break;
        case 12:
            printf("Dec-");
            break;
    }
    printf("%d  ", tm.tm_year+1900);

    
    printf("Time: ");
    if(tm.tm_hour>=12)
    {
        if(tm.tm_hour==12)
            printf("12");
        else
            printf("%d", tm.tm_hour-12);
        printf(":%d PM\n", tm.tm_min);
    }
    else
        printf("%d:%d AM\n", tm.tm_hour, tm.tm_min);
}