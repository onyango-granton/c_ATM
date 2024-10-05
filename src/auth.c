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

void loginMenu(char a[50], char pass[50])
{
    int i = 0;
    char ch;

    clearScreen();
    printf("\n\n\n\t\tBank Management System\n\t\tUser Login\n\n\n\t\tEnter Username:");
    scanf("%s", a);

    printf("\n\t\tEnter the password to login:");
    
    while (1) {
        ch = getch();  // Cross-platform getch
        
        if (ch == 13 || ch == 10) { // Enter key (carriage return or newline)
            pass[i] = '\0';  // Null-terminate the password string
            break;
        } else if (ch == 127 || ch == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // Move the cursor back, erase the '*', and move the cursor back again
            }
        } else {
            pass[i++] = ch;  // Store the character in the password array
            printf("*");  // Display '*' to mask the input
        }
    }
}

void registerMenu(char a[50], char pass[50])
{
    FILE *fp;
    struct User u;
    int id = 0;

    system("clear");
    printf("\n\n\n\t\tBank Management System\n\t\tUser Registration\n\n\n\t\tRegister Username:");
    scanf("%s", a);

    printf("\n\t\tRegister password:");
    scanf("%s", pass);

    fp = fopen(USERS, "a+");

    if (fp == NULL)
    {
        printf("\n\t\tError opening file\n");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &u.id, u.name, u.password) != EOF)
    {
        id = u.id;
        printf("%d\n",u.id);
        if (strcmp(a, u.name) == 0){
            printf("\n\t\tUser Already Exists\n");
            exit(1);
        }
    }

    fprintf(fp, "%d %s %s\n", id + 1, a, pass);
    fclose(fp);

    printf("\n\n\n\t\tUser registered successfully!\n");
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

