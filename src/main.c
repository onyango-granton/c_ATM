#include "header.h"

#ifdef _WIN32
void clearScreen(){
    system("cls");
}
#else
void clearScreen(){
    system("clear");
}
#endif

void mainMenu(struct User u)
{
    int option;
    clearScreen();
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check account details\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    printf("\n\t\tEnter Your Choice: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAccount(u);
        break;
    case 3:
        checkAccountDetails(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        makeTransaction(u);
        break;
    case 6:
        removeAccount(u);
        break;
    case 7:
        transferOwner(u);
        break;
    case 8:
        printf("\n\n\nThank You. Bank on us again \n");
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
}

void initMenu(struct User *u)
{
    int r = 0;
    int option;
    clearScreen();
    printf("\n\n\t\t======= ATM2 =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    printf("\n\t\tEnter Your Choice: ");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\n\t\tPassword Match!");
                r = 1;
            }
            else
            {
                printf("\n\t\tWrong password!! or User Name\n Retry Login \n");
                exit(1);
            }
            break;
        case 2:
            registerMenu(u->name, u->password);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("\n\t\tInsert a valid operation! Bye\n");
            exit(1);
        }
    }
}

int main()
{
    struct User u;
    initMenu(&u);
    mainMenu(u);
    return 0;
}