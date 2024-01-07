#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char name[50];
    float balance;
};

void createAccount() {
    FILE *file = fopen("accounts.txt", "a+");
    struct Account newAccount;

    printf("Enter pincode number: ");
    scanf("%d", &newAccount.accountNumber);

    printf("Enter name: ");
    scanf("%s", newAccount.name);

    printf("Enter initial balance: ");
    scanf("%f", &newAccount.balance);

    fprintf(file, "%d %s %.2f\n", newAccount.accountNumber, newAccount.name, newAccount.balance);

    fclose(file);
}

void displayAccount(int accountNumber) {
    FILE *file = fopen("accounts.txt", "r");
    struct Account currentAccount;

    int found = 0;
    while (fscanf(file, "%d %s %f", &currentAccount.accountNumber, currentAccount.name, &currentAccount.balance) != EOF) {
        if (currentAccount.accountNumber == accountNumber) {
            found = 1;
            printf("Pincode Number: %d\n", currentAccount.accountNumber);
            printf("Name: %s\n", currentAccount.name);
            printf("Balance: %.2f\n", currentAccount.balance);
            break;
        }
    }

    if (!found) {
        printf("Pincode not found.\n");
    }

    fclose(file);
}

void deposit(int accountNumber, float amount) {
    FILE *file = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    struct Account currentAccount;

    int found = 0;
    while (fscanf(file, "%d %s %f", &currentAccount.accountNumber, currentAccount.name, &currentAccount.balance) != EOF) {
        if (currentAccount.accountNumber == accountNumber) {
            found = 1;
            currentAccount.balance += amount;
        }
        fprintf(tempFile, "%d %s %.2f\n", currentAccount.accountNumber, currentAccount.name, currentAccount.balance);
    }

    fclose(file);
    fclose(tempFile);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        printf("Pincode not found.\n");
    } else {
        printf("Deposit successful.\n");
    }
}

void withdraw(int accountNumber, float amount) {
    FILE *file = fopen("accounts.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    struct Account currentAccount;

    int found = 0;
    while (fscanf(file, "%d %s %f", &currentAccount.accountNumber, currentAccount.name, &currentAccount.balance) != EOF) {
        if (currentAccount.accountNumber == accountNumber) {
            found = 1;
            if (currentAccount.balance >= amount) {
                currentAccount.balance -= amount;
                fprintf(tempFile, "%d %s %.2f\n", currentAccount.accountNumber, currentAccount.name, currentAccount.balance);
                printf("Withdrawal successful.\n");
            } else {
                fprintf(tempFile, "%d %s %.2f\n", currentAccount.accountNumber, currentAccount.name, currentAccount.balance);
                printf("Insufficient balance.\n");
            }
        } else {
            fprintf(tempFile, "%d %s %.2f\n", currentAccount.accountNumber, currentAccount.name, currentAccount.balance);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found) {
        printf("Pincode not found.\n");
    }
}

int main() {
    int choice, accountNumber;
    float amount;

    do {
        printf("\nATM Menu:\n");
        printf("1. Create Pincode Number\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                printf("Enter pincode number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                deposit(accountNumber, amount);
                break;
            case 3:
                printf("Enter pincode number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdraw(accountNumber, amount);
                break;
            case 4:
                printf("Enter pincode number: ");
                scanf("%d", &accountNumber);
                displayAccount(accountNumber);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
