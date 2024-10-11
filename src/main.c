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
            *u = loginMenu(u->name, u->password);  // Update this line
            if (u->id != -1)  // Check if login was successful
            {
                printf("\n\n\t\tLogin successful!");
                r = 1;
            }
            else
            {
                printf("\n\t\tWrong password or User Name\n Retry Login \n");
            }
            break;
        case 2:
            *u = registerMenu(u->name, u->password);  // Update this line
            if (u->id != -1)  // Check if registration was successful
            {
                printf("\n\n\t\tRegistration successful!");
                r = 1;
            }
            else
            {
                printf("\n\t\tRegistration failed. Please try again.\n");
            }
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("\n\t\tInsert a valid operation!\n");
        }
    }
}

int main()
{
    struct User u = {-1, "", ""};  // Initialize with invalid ID
    initMenu(&u);
    printf("Debug: User ID after initMenu: %d\n", u.id);
    mainMenu(u);
    return 0;
}