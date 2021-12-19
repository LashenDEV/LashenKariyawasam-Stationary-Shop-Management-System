#include <stdio.h>
#include <stdlib.h>

struct items {
    int itemID;
    char itemName[20];
    int price;
};

void buy();
void itemList();
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
        case 2:
            addItems();
            break;
    }
}


void itemList(){
    FILE *itemsfp;
    struct items item;
    itemsfp = fopen("itemdata.txt", "r");
    if (itemsfp == NULL) {
        printf("Couldn't open\n");
    } else {
        printf("\n--------------------------------------------------------------------\n");
        printf("                 itemID\t    itemName\tprice\n");
        printf("--------------------------------------------------------------------");
        while (fread(&item, sizeof(item), 1, itemsfp)) {
            printf("\n                   %-10d%-12s%-6d                          ", item.itemID, item.itemName, item.price);
        }
        fclose(itemsfp);
        printf("\n--------------------------------------------------------------------\n");
    }
}

void buy() {
    itemList();
    main();
}


void addItems(){
    itemList();
    FILE *itemfp;
    int number = 0;
    struct items item;
    itemfp = fopen("itemdata.txt","a");

    if(itemfp==NULL){
        printf("Couldn't open\n");
    } else{
        printf("How much item you add:");
        scanf("%d",&number);
        for (int i=0;i<number;++i){
            printf("Enter item number:");
            scanf(" %d",&item.itemID);
            printf("Enter item name:");
            scanf(" %s",&item.itemName);
            printf("Enter item price:");
            scanf(" %d",&item.price);
            fwrite( &item,sizeof(item),1,itemfp );
        }

    }

    fclose(itemfp);
    main();
}