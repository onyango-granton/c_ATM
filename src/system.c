#include "header.h"

const char *RECORDS = "../data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    int result = fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType);
    
    if (result == EOF) return 0;
    
    // Basic data validation
    /*if (r->deposit.month < 1 || r->deposit.month > 12 ||
        r->deposit.day < 1 || r->deposit.day > 31 ||
        r->deposit.year < 1900 || r->deposit.year > 2100 ||
        r->amount < 0) {
        printf("Warning: Invalid data detected for account %d\n", r->accountNbr);
        return 0;
    }*/
    
    return 1;
}

void verifyAndCorrectUserIds()
{
    FILE *recordsFile = fopen(RECORDS, "r");
    FILE *usersFile = fopen("../data/users.txt", "r");
    FILE *tempFile = fopen("temp_records.txt", "w");
    
    struct Record r;
    struct User u;
    char userName[50];

    // Read all users into a hash table or array for quick lookup
    // This is a simplified example; you'd need to implement a proper data structure
    struct User users[100];  // Assuming max 100 users
    int userCount = 0;
    while (fscanf(usersFile, "%d %s %s", &u.id, u.name, u.password) != EOF) {
        users[userCount++] = u;
    }

    while (getAccountFromFile(recordsFile, userName, &r)) {
        // Find the correct user ID for this username
        int correctUserId = -1;
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].name, userName) == 0) {
                correctUserId = users[i].id;
                break;
            }
        }

        if (correctUserId != -1 && correctUserId != r.userId) {
            printf("Correcting user ID for account %d: %d -> %d\n", r.accountNbr, r.userId, correctUserId);
            r.userId = correctUserId;
        }

        // Write the (possibly corrected) record to the temp file
        fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                r.id, r.userId, userName, r.accountNbr,
                r.deposit.month, r.deposit.day, r.deposit.year,
                r.country, r.phone, r.amount, r.accountType);
    }

    fclose(recordsFile);
    fclose(usersFile);
    fclose(tempFile);

    // Replace the old records file with the corrected one
    remove(RECORDS);
    rename("temp_records.txt", RECORDS);

    printf("User ID verification and correction completed.\n");
}


void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        clearScreen();
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        clearScreen();
        mainMenu(u);
    }
    else
    {
        clearScreen();
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    clearScreen();
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    clearScreen();
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void updateAccount(struct User u)
{
    int choice, accountNbr;
    FILE *pf, *tempFile;
    struct Record r;
    char userName[50];

    pf = fopen(RECORDS, "r");
    tempFile = fopen("temp.txt", "w");

    printf("\nEnter account number to update: ");
    scanf("%d", &accountNbr);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNbr)
        {
            printf("\nWhat do you want to update?");
            printf("\n1. Country");
            printf("\n2. Phone");
            printf("\nEnter your choice (1-2): ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("\nEnter new country: ");
                scanf("%s", r.country);
                break;
            case 2:
                printf("\nEnter new phone number: ");
                scanf("%d", &r.phone);
                break;
            default:
                printf("\nInvalid choice!");
                fclose(pf);
                fclose(tempFile);
                remove("temp.txt");
                return;
            }
        }
        saveAccountToFile(tempFile, u, r);
    }

    fclose(pf);
    fclose(tempFile);

    remove(RECORDS);
    rename("temp.txt", RECORDS);

    success(u);
}


void checkAllAccounts(struct User u)
{
    FILE *pf;
    struct Record r;
    char userName[50];
    int found = 0;

    pf = fopen(RECORDS, "r");

    printf("\n\t\t====== All Accounts of User %s ======\n\n", u.name);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("Account Number: %d\n", r.accountNbr);
            printf("Deposit Date: %d/%d/%d\n", r.deposit.month, r.deposit.day, r.deposit.year);
            printf("Country: %s\n", r.country);
            printf("Phone: %d\n", r.phone);
            printf("Amount: $%.2lf\n", r.amount);
            printf("Account Type: %s\n\n", r.accountType);
            found = 1;
        }
    }

    fclose(pf);

    if (!found)
    {
        printf("No accounts found for this user.\n");
    }

    stayOrReturn(1, checkAllAccounts, u);
}

void makeTransaction(struct User u)
{
    int choice, accountNbr;
    double amount;
    FILE *pf, *tempFile;
    struct Record r;
    char userName[50];
    int found = 0;

    pf = fopen(RECORDS, "r");
    tempFile = fopen("temp.txt", "w");

    printf("\nEnter account number for transaction: ");
    scanf("%d", &accountNbr);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNbr)
        {
            found = 1;
            printf("\n1. Deposit");
            printf("\n2. Withdraw");
            printf("\nEnter your choice (1-2): ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("\nEnter amount to deposit: $");
                scanf("%lf", &amount);
                r.amount += amount;
                break;
            case 2:
                printf("\nEnter amount to withdraw: $");
                scanf("%lf", &amount);
                if (amount > r.amount)
                {
                    printf("\nInsufficient balance!");
                    fclose(pf);
                    fclose(tempFile);
                    remove("temp.txt");
                    stayOrReturn(1, makeTransaction, u);
                    return;
                }
                r.amount -= amount;
                break;
            default:
                printf("\nInvalid choice!");
                fclose(pf);
                fclose(tempFile);
                remove("temp.txt");
                stayOrReturn(1, makeTransaction, u);
                return;
            }
        }
        saveAccountToFile(tempFile, u, r);
    }

    fclose(pf);
    fclose(tempFile);

    if (found)
    {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\nTransaction successful!");
    }
    else
    {
        remove("temp.txt");
        printf("\nAccount not found!");
    }

    stayOrReturn(found, makeTransaction, u);
}

void removeAccount(struct User u)
{
    int accountNbr;
    FILE *pf, *tempFile;
    struct Record r;
    char userName[50];
    int found = 0;

    pf = fopen(RECORDS, "r");
    tempFile = fopen("temp.txt", "w");

    printf("\nEnter account number to remove: ");
    scanf("%d", &accountNbr);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNbr)
        {
            found = 1;
            printf("\nAccount with number %d will be removed.", accountNbr);
            continue;
        }
        saveAccountToFile(tempFile, u, r);
    }

    fclose(pf);
    fclose(tempFile);

    if (found)
    {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\nAccount removed successfully!");
    }
    else
    {
        remove("temp.txt");
        printf("\nAccount not found!");
    }

    stayOrReturn(found, removeAccount, u);
}

void transferOwner(struct User u)
{
    int accountNbr;
    char newOwner[50];
    FILE *pf, *tempFile;
    struct Record r;
    char userName[50];
    int found = 0;

    pf = fopen(RECORDS, "r");
    tempFile = fopen("temp.txt", "w");

    printf("\nEnter account number to transfer: ");
    scanf("%d", &accountNbr);

    printf("\nEnter new owner's name: ");
    scanf("%s", newOwner);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNbr)
        {
            found = 1;
            printf("\nTransferring account %d to %s", accountNbr, newOwner);
            strcpy(userName, newOwner);
        }
        saveAccountToFile(tempFile, u, r);
    }

    fclose(pf);
    fclose(tempFile);

    if (found)
    {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\nAccount transferred successfully!");
    }
    else
    {
        remove("temp.txt");
        printf("\nAccount not found!");
    }

    stayOrReturn(found, transferOwner, u);
}



void checkAccountDetails(struct User u)
{
    int accountNbr;
    FILE *pf;
    struct Record r;
    char userName[50];
    int found = 0;

    pf = fopen(RECORDS, "r");
    if (pf == NULL)
    {
        printf("\nError! Unable to open file.\n");
        exit(1);
    }

    printf("\nEnter the account number you want to check: ");
    scanf("%d", &accountNbr);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNbr)
        {
            found = 1;
            printf("\n\t\t====== Account Details ======\n");
            printf("\nAccount Number: %d", r.accountNbr);
            printf("\nDeposit Date: %d/%d/%d", r.deposit.month, r.deposit.day, r.deposit.year);
            printf("\nCountry: %s", r.country);
            printf("\nPhone Number: %d", r.phone);
            printf("\nAccount Type: %s", r.accountType);
            printf("\nCurrent Balance: $%.2f", r.amount);
            
            if (strcmp(r.accountType, "saving") == 0)
            {
                float interest = 0.07 * r.amount;
                printf("\nYearly Interest (7%%): $%.2f", interest);
            }
            else if (strncmp(r.accountType, "fixed", 5) == 0)
            {
                int years = r.accountType[5] - '0';
                float interest = (0.04 * years) * r.amount;
                printf("\nTotal Interest for %d year(s) (4%% per year): $%.2f", years, interest);
            }
            
            break;
        }
    }

    fclose(pf);

    if (!found)
    {
        printf("\nAccount number %d not found or doesn't belong to you!", accountNbr);
    }

    stayOrReturn(found, checkAccountDetails, u);
}