#include <stdio.h>
#include <stdlib.h>

void buy();

int main() {
    int selection;
    printf("\n\n");
    printf("                             === WELCOME TO THE SHOP ===                                       \n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("1. Buy \n");
    printf("----------------------------------------------------------------------------------------------------\n");
    scanf("%d", &selection);
    switch (selection) {
        case 1:
            buy();
    }
}

void buy() {
    printf("hello");
}