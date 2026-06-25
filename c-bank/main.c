#include <stdio.h>
#include <stdlib.h>
#include "account.h"

void display_menu(void) {
    printf("\n╔══════════════════════════╗\n");
    printf("║        C-BANK            ║\n");
    printf("╠══════════════════════════╣\n");
    printf("║ 1. Create an account     ║\n");
    printf("║ 2. Deposit funds         ║\n");
    printf("║ 3. Withdraw funds        ║\n");
    printf("║ 4. Check the balance     ║\n");
    printf("║ 5. Close an account      ║\n");
    printf("║ 6. Leave                 ║\n");
    printf("╚══════════════════════════╝\n");
    printf("Choice : ");
}

int main(void) {
    int choice;
    printf("Welcome to C-Bank 🏦\n");
    do {
        display_menu();
        if (scanf("%d", &choice) != 1) { while(getchar() != '\n'); continue; }
        switch (choice) {
            case 1: create_account();  break;
            case 2: deposit();         break;
            case 3: withdraw();        break;
            case 4: check_balance();   break;
            case 5: close_account();   break;
            case 6: printf("Goodbye !\n"); break;
            default: printf("Invalid Option.\n");
        }
    } while (choice != 6);
    return 0;
}
