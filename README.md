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