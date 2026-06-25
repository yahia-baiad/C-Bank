#ifndef ACCOUNT_H
#define ACCOUNT_H

#define MAX_NAME 50
#define MAX_EMAIL 50
#define MAX_PASSWORD 30
#define DATABASE "database.txt"

typedef struct {
    int    id;
    char   name[MAX_NAME];
    char   email[MAX_EMAIL];
    char   password[MAX_PASSWORD];
    double balance;
    int    active; // 1 = open, 0 = closed
} Account;

// Prototypes
void   create_account(void);
void   deposit(void);
void   withdraw(void);
void   check_balance(void);
void   close_account(void);
void   display_menu(void);
int    find_account(int id, Account *acc);
void   save_account(Account *acc);
void   update_account(Account *acc);
int    generate_id(void);

#endif
