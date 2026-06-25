#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

// Generates a unique ID based on the number of existing accounts
int generate_id(void) {
    FILE *fp = fopen(DATABASE, "r");
    if (!fp) return 1001;
    Account acc;
    int count = 0;
    while (fread(&acc, sizeof(Account), 1, fp)) count++;
    fclose(fp);
    return 1001 + count;
}

// Saves a new account (added to the end of the file)
void save_account(Account *acc) {
    FILE *fp = fopen(DATABASE, "ab");
    if (!fp) { printf("Error: Unable to open the database.\n"); return; }
    fwrite(acc, sizeof(Account), 1, fp);
    fclose(fp);
}

// Find an account by ID and copy it to *acc
int find_account(int id, Account *acc) {
    FILE *fp = fopen(DATABASE, "rb");
    if (!fp) return 0;
    while (fread(acc, sizeof(Account), 1, fp)) {
        if (acc->id == id && acc->active) { fclose(fp); return 1; }
    }
    fclose(fp);
    return 0;
}

// Updates an existing account in the file
void update_account(Account *updated) {
    FILE *fp = fopen(DATABASE, "r+b");
    if (!fp) return;
    Account acc;
    while (fread(&acc, sizeof(Account), 1, fp)) {
        if (acc.id == updated->id) {
            fseek(fp, -(long)sizeof(Account), SEEK_CUR);
            fwrite(updated, sizeof(Account), 1, fp);
            break;
        }
    }
    fclose(fp);
}

void create_account(void) {
    Account acc;
    acc.id     = generate_id();
    acc.active = 1;

    printf("\n=== Create an account ===\n");
    printf("Full name    : "); scanf(" %49[^\n]", acc.name);
    printf("Email          : "); scanf(" %49s", acc.email);
    printf("Password   : "); scanf(" %29s", acc.password);
    printf("Initial deposit  : $"); scanf("%lf", &acc.balance);

    if (acc.balance < 0) { printf("The deposit cannot be negative.\n"); return; }

    save_account(&acc);
    printf("\n✅ Account successfully created! Your ID : %d\n", acc.id);
}

void deposit(void) {
    int id; double amount; Account acc;
    printf("\n=== Deposit ===\n");
    printf("Account ID : "); scanf("%d", &id);
    if (!find_account(id, &acc)) { printf("Account not found.\n"); return; }
    printf("Amount to be deposited : $"); scanf("%lf", &amount);
    if (amount <= 0) { printf("Invalid amount.\n"); return; }
    acc.balance += amount;
    update_account(&acc);
    printf("✅ Deposit made. New balance : $%.2f\n", acc.balance);
}

void withdraw(void) {
    int id; double amount; Account acc;
    printf("\n=== Withdrawal ===\n");
    printf("Account ID: "); scanf("%d", &id);
    if (!find_account(id, &acc)) { printf("Account not found.\n"); return; }
    printf("Amount to withdraw : $"); scanf("%lf", &amount);
    if (amount <= 0)             { printf("Invalid amount.\n"); return; }
    if (amount > acc.balance)    { printf("Insufficient funds.\n"); return; }
    acc.balance -= amount;
    update_account(&acc);
    printf("✅ Withdrawal completed. New balance : $%.2f\n", acc.balance);
}

void check_balance(void) {
    int id; Account acc;
    printf("\n=== Balance ===\n");
    printf("Account ID : "); scanf("%d", &id);
    if (!find_account(id, &acc)) { printf("Account not found.\n"); return; }
    printf("Owner : %s | Balance : $%.2f\n", acc.name, acc.balance);
}

void close_account(void) {
    int id; Account acc;
    printf("\n=== Account closure ===\n");
    printf("Account ID : "); scanf("%d", &id);
    if (!find_account(id, &acc)) { printf("Account not found.\n"); return; }
    if (acc.balance > 0) { printf("Balance not zero ($%.2f). Withdraw your funds first.\n", acc.balance); return; }
    acc.active = 0;
    update_account(&acc);
    printf("✅ Account %d closed.\n", id);
}
