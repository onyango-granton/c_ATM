#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

struct Date
{
    int month, day, year;
};

struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// Authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);

// System functions
void createNewAcc(struct User u);
void updateAccount(struct User u);
void checkAccountDetails(struct User u);
void makeTransaction(struct User u);
void removeAccount(struct User u);
void transferOwner(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);

// Utility functions
char getch(void);
void saveAccountToFile(FILE *ptr, struct User u, struct Record r);
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r);
void success(struct User u);
void stayOrReturn(int notGood, void f(struct User u), struct User u);

// Cross-platform clear screen function
void clearScreen(void);

#endif // HEADER_H