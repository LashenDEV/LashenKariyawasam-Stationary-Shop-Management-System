#include <stdio.h>
#include <stdlib.h>

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
};

void buy();

void purchase();

void itemList();

int bill();

int itemNo();

void addItems();

int main() {
    int selection;
    printf("\n\n");
    printf("                   === WELCOME TO THE SHOP ===                        \n");
    printf("\n--------------------------------------------------------------------\n");
    printf("1. Buy \n");
    printf("2. Login as Admin \n");
    printf("\n--------------------------------------------------------------------\n");
    printf("Enter your selection : ");
    scanf("%d", &selection);
    switch (selection) {
        case 1:
            buy();
            break;
//        case 2:
//            addItems();
//            break;
    }
}


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

void buy() {
    int selection;
    do {
        purchase();
        printf("\nSelect 0 for exit or 1 for continue");
        scanf("%d",&selection);
    } while (selection != 0);

    bill();
//    main();
}


void addItems() {
    int selection = 1;
    FILE *itemfp;
    struct p_items p_item;
    itemfp = fopen("purchasedata.txt", "a+");

    if (itemfp == NULL) {
        printf("Couldn't open\n");
    } else {
        do {
            p_item.itemID = itemNo();
            printf("%d", p_item.itemID);
            printf("Enter item name:");
            scanf(" %s", &p_item.itemName);
            printf("Enter item price:");
            scanf(" %d", &p_item.price);
            fprintf(itemfp, "%d %s %d\n", p_item.itemID, p_item.itemName, p_item.price);
            printf("*** Add Item Successfully ***");
            printf("\nDo you want to add another Item (1)");
            printf("\nor exit(0)");
            scanf("%d", &selection);
        } while (selection);
    }


    fclose(itemfp);

    main();

}


int bill() {
    //billing function
}

int itemNo() {
    int itemID, allocated;
    printf("Enter item number:");
    scanf(" %d", &itemID);
    FILE *itemfp;
    itemfp = fopen("itemdata.txt", "r");
    struct items item;
    while (fscanf(itemfp, "%d %s %d", &item.itemID, item.itemName, &item.price) != EOF) {
        if (item.itemID == itemID) {
            allocated = 1;
        }
    }
    fclose(itemfp);
    if (allocated == 0)
        return itemID;
    else
        return itemNo();
}

void purchase() {
    FILE *itemfp;
    struct items item;
    int sele_itm, selection, total, quan;
    itemfp = fopen("itemdata.txt", "r");
    FILE *p_file;
    struct p_items p_item;
    p_file = fopen("purchase_data.txt", "a");
    itemList();
    printf("Enter the item : ");
    scanf("%d", &sele_itm);
    if (itemfp) {
        while (fscanf(itemfp, "%d %s %d", &item.itemID, item.itemName, &item.price) == 3) {
            if (item.itemID == sele_itm) {
                printf("%s", item.itemName);
                printf("\nEnter the quantity : ");
                scanf("%d", &quan);
                total = quan * item.price;
                fprintf(p_file, "%d %s %d %d\n", item.itemID, item.itemName, item.price, quan);
            }
        }
        fclose(itemfp);
    }


//    if (p_file == NULL) {
//        printf("Couldn't open\n");
//    } else {
//
//    }

    printf("Total is %d", total);
}