#include "header.h"

const char *USERS = "../data/users.txt";


// Function to get a single character input on non-Windows systems
#ifndef _WIN32
char getch() {
    char ch;
    struct termios oldt, newt;
    
    // Save terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    // Disable echoing and buffering
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    // Read character
    ch = getchar();
    
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

struct User loginMenu(char name[50], char password[50])
{
    struct User u = {-1, "", ""};  // Initialize with invalid ID
    FILE *fp;
    fp = fopen("../data/users.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return u;
    }

    printf("\n\n\t\t\t\tAccount Login\n\n");
    printf("\n\n\t\t\t\tEnter Username: ");
    scanf("%s", name);
    printf("\n\n\t\t\t\tEnter Password: ");
    scanf("%s", password);

    while (fscanf(fp, "%d %s %s", &u.id, u.name, u.password) == 3)
    {
        if (strcmp(name, u.name) == 0 && strcmp(password, u.password) == 0)
        {
            fclose(fp);
            return u;
        }
    }

    fclose(fp);
    u.id = -1;  // Set ID to -1 if user not found
    return u;
}

struct User registerMenu(char name[50], char password[50])
{
    struct User u = {-1, "", ""};
    FILE *fp;
    int id = 1;

    fp = fopen("../data/users.txt", "a+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return u;
    }

    printf("\n\n\t\t\t\tRegister New Account\n\n");
    printf("\n\n\t\t\t\tEnter Username: ");
    scanf("%s", name);
    printf("\n\n\t\t\t\tEnter Password: ");
    scanf("%s", password);

    // Find the highest existing id
    while (fscanf(fp, "%d %s %s", &u.id, u.name, u.password) == 3)
    {
        if (u.id >= id)
        {
            id = u.id + 1;
        }
    }

    u.id = id;
    strcpy(u.name, name);
    strcpy(u.password, password);

    fprintf(fp, "%d %s %s\n", u.id, u.name, u.password);
    fclose(fp);

    return u;
}
const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("../data/users.txt", "r")) == NULL)
    {
        printf("\n\t\tError! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}


/*
#ifdef _WIN32
int getch(void)
{
    return _getch();
}

#else
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

#endif
*/

