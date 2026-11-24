#include <iostream>
#include <limits>
#include "ExpenseManager.h"

using namespace std;

int main() {
    ExpenseManager manager;
    int choice;

    do {
        cout << "\n============================================\n";
        cout << "       PERSONAL EXPENSE MANAGEMENT SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Record Income\n";
        cout << "2. Add Expense\n";
        cout << "3. Edit Expense\n";
        cout << "4. Delete Expense\n";
        cout << "5. View All Expenses\n";
        cout << "6. Set Category Budget\n";
        cout << "7. Monthly Summary\n";
        cout << "8. Savings Report\n";
        cout << "0. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                manager.recordIncome();
                break;
            case 2:
                manager.addExpense();
                break;
            case 3:
                manager.editExpense();
                break;
            case 4:
                manager.deleteExpense();
                break;
            case 5:
                manager.showExpenses();
                break;
            case 6:
                manager.setBudget();
                break;
            case 7:
                manager.showMonthlyReport();
                break;
            case 8:
                manager.showSavingsReport();
                break;
            case 0:
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
