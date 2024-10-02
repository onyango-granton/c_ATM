#include "header.h"

const char *USERS = "../data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    int i = 0;
    char ch;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    
    while (1) {
        ch = getch();
        
        if (ch == 13 || ch == 10) { // Enter key
            pass[i] = '\0';
            break;
        } else if (ch == 127 || ch == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            pass[i++] = ch;
            printf("*");
        }
    }
}

void registerMenu(char a[50], char pass[50])
{
    FILE *fp;
    struct User u;
    int id = 0;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Registration:");
    scanf("%s", a);

    printf("\n\n\n\n\n\t\t\t\tEnter the password:");
    scanf("%s", pass);

    fp = fopen(USERS, "a+");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &u.id, u.name, u.password) != EOF)
    {
        id = u.id;
    }

    fprintf(fp, "%d %s %s\n", id + 1, a, pass);
    fclose(fp);

    printf("\n\nUser registered successfully!\n");
}

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("../data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
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


#ifdef _WIN32
int getch(void)
{
    return _getch();
}

void clearScreen(void)
{
    system("cls");
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

void clearScreen(void)
{
    system("clear");
}
#endif
