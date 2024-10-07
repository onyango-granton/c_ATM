# Bank Management System

## Overview
This Bank Management System is a console-based application written in C. It provides basic banking operations for users, including account creation, transactions, and account management.

## Features
- User Registration and Login
- Create New Bank Account
- Update Account Information
- Check Account Details
- View All Owned Accounts
- Make Transactions (Deposit/Withdraw)
- Remove Existing Account
- Transfer Account Ownership

## System Requirements
- C Compiler (GCC recommended)
- Windows or Linux Operating System

## Setup and Compilation

### On Linux:
1. Clone the repo
   ```bash
   git clone https://github.com/onyango-granton/c_ATM.git
   ```
2. Open a terminal in the project directory.
   ```bash
   cd c_ATM
   ```
3. Compile the program using GCC:
   ```bash
   gcc  main.c auth.c system.c -o bank_system
   ```
4. Run the program:
   ```bash
   ./bank_system
   ```

### On Windows:
1. Clone the repo
   ```bash
   git clone https://github.com/onyango-granton/c_ATM.git
   ```
2. Open a terminal in the project directory.
   ```bash
   cd c_ATM
   ```
3. Compile the program using GCC (ensure MinGW is installed):
   ```bash
   gcc main.c auth.c system.c -o bank_system.exe 
   ```
4. Run the program:
   ```bash
   bank_system.exe
   ```

## Usage
1. When you run the program, you'll be presented with a login/register menu.
2. If you're a new user, choose the register option to create an account.
3. Once logged in, you'll see the main menu with various banking operations.
4. Choose the operation you want to perform by entering the corresponding number.
5. Follow the on-screen prompts to complete each operation.

## File Structure
- `src/main.c`: Contains the main function and menu logic
- `src/auth.c`: Handles user authentication (login/register)
- `srcsystem.c`: Implements banking operations
- `src/header.h`: Header file with structure definitions and function prototypes
- `data/users.txt`: Stores user login information
- `data/records.txt`: Stores account records

## Security Note
This system is for educational purposes only. In a real-world scenario, additional security measures would be necessary, such as encryption for sensitive data and secure password handling.