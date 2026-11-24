#include "ExpenseManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

ExpenseManager::ExpenseManager() {
    loadData();
}

// Read saved information when the program starts
void ExpenseManager::loadData() {
    ifstream inFile("incomes.txt");
    Income income;
    while (inFile >> quoted(income.date) >> quoted(income.source) >> income.amount) {
        incomes.push_back(income);
    }
    inFile.close();

    ifstream expenseFile("expenses.txt");
    Expense expense;
    while (expenseFile >> quoted(expense.date) >> quoted(expense.category)
                       >> quoted(expense.description) >> expense.amount) {
        expenses.push_back(expense);
    }
    expenseFile.close();

    ifstream budgetFile("budgets.txt");
    Budget budget;
    while (budgetFile >> quoted(budget.month) >> quoted(budget.category) >> budget.amount) {
        budgets.push_back(budget);
    }
    budgetFile.close();
}

// Save all information in text files
void ExpenseManager::saveData() {
    ofstream inFile("incomes.txt");
    for (int i = 0; i < (int)incomes.size(); i++) {
        inFile << quoted(incomes[i].date) << " "
               << quoted(incomes[i].source) << " "
               << incomes[i].amount << endl;
    }
    inFile.close();

    ofstream expenseFile("expenses.txt");
    for (int i = 0; i < (int)expenses.size(); i++) {
        expenseFile << quoted(expenses[i].date) << " "
                    << quoted(expenses[i].category) << " "
                    << quoted(expenses[i].description) << " "
                    << expenses[i].amount << endl;
    }
    expenseFile.close();

    ofstream budgetFile("budgets.txt");
    for (int i = 0; i < (int)budgets.size(); i++) {
        budgetFile << quoted(budgets[i].month) << " "
                   << quoted(budgets[i].category) << " "
                   << budgets[i].amount << endl;
    }
    budgetFile.close();
}

// MODULE 1: Record income
void ExpenseManager::recordIncome() {
    Income income;

    cout << "\nEnter date (YYYY-MM-DD): ";
    cin >> income.date;

    cout << "Enter income source: ";
    cin >> ws;
    getline(cin, income.source);

    cout << "Enter amount: Rs. ";
    cin >> income.amount;

    if (income.amount <= 0) {
        cout << "Amount must be greater than zero.\n";
        return;
    }

    incomes.push_back(income);
    saveData();
    cout << "Income recorded successfully!\n";
}

// MODULE 2: Add expense
void ExpenseManager::addExpense() {
    Expense expense;

    cout << "\nEnter date (YYYY-MM-DD): ";
    cin >> expense.date;

    cout << "Enter category (Food/Travel/Shopping/Bills/Other): ";
    cin >> ws;
    getline(cin, expense.category);

    cout << "Enter description: ";
    getline(cin, expense.description);

    cout << "Enter amount: Rs. ";
    cin >> expense.amount;

    if (expense.amount <= 0) {
        cout << "Amount must be greater than zero.\n";
        return;
    }

    expenses.push_back(expense);
    saveData();
    cout << "Expense added successfully!\n";
}

// Display all expenses with serial numbers
void ExpenseManager::showExpenses() {
    if (expenses.empty()) {
        cout << "\nNo expenses found.\n";
        return;
    }

    cout << "\n---------------- EXPENSE LIST ----------------\n";
    cout << left << setw(6) << "No." << setw(14) << "Date"
         << setw(16) << "Category" << setw(22) << "Description"
         << "Amount\n";

    for (int i = 0; i < (int)expenses.size(); i++) {
        cout << left << setw(6) << i + 1
             << setw(14) << expenses[i].date
             << setw(16) << expenses[i].category
             << setw(22) << expenses[i].description
             << fixed << setprecision(2) << expenses[i].amount << endl;
    }
}

// MODULE 2: Edit expense
void ExpenseManager::editExpense() {
    showExpenses();

    if (expenses.empty()) return;

    int number;
    cout << "\nEnter expense number to edit: ";
    cin >> number;

    if (number < 1 || number > (int)expenses.size()) {
        cout << "Invalid expense number.\n";
        return;
    }

    Expense &expense = expenses[number - 1];

    cout << "Enter new date (YYYY-MM-DD): ";
    cin >> expense.date;

    cout << "Enter new category: ";
    cin >> ws;
    getline(cin, expense.category);

    cout << "Enter new description: ";
    getline(cin, expense.description);

    cout << "Enter new amount: Rs. ";
    cin >> expense.amount;

    if (expense.amount <= 0) {
        cout << "Amount must be greater than zero. Edit cancelled.\n";
        return;
    }

    saveData();
    cout << "Expense updated successfully!\n";
}

// MODULE 2: Delete expense
void ExpenseManager::deleteExpense() {
    showExpenses();

    if (expenses.empty()) return;

    int number;
    cout << "\nEnter expense number to delete: ";
    cin >> number;

    if (number < 1 || number > (int)expenses.size()) {
        cout << "Invalid expense number.\n";
        return;
    }

    expenses.erase(expenses.begin() + number - 1);
    saveData();
    cout << "Expense deleted successfully!\n";
}

// MODULE 3: Set or update a category budget
void ExpenseManager::setBudget() {
    Budget newBudget;

    cout << "\nEnter month (YYYY-MM): ";
    cin >> newBudget.month;

    cout << "Enter expense category: ";
    cin >> ws;
    getline(cin, newBudget.category);

    cout << "Enter monthly budget: Rs. ";
    cin >> newBudget.amount;

    if (newBudget.amount <= 0) {
        cout << "Budget must be greater than zero.\n";
        return;
    }

    // If the same month and category already exist, update the budget
    for (int i = 0; i < (int)budgets.size(); i++) {
        if (budgets[i].month == newBudget.month &&
            budgets[i].category == newBudget.category) {
            budgets[i].amount = newBudget.amount;
            saveData();
            cout << "Budget updated successfully!\n";
            return;
        }
    }

    budgets.push_back(newBudget);
    saveData();
    cout << "Budget set successfully!\n";
}

// MODULE 4: Monthly income and expense summary
void ExpenseManager::showMonthlyReport() {
    string month;
    double totalIncome = 0;
    double totalExpense = 0;

    cout << "\nEnter month (YYYY-MM): ";
    cin >> month;

    for (int i = 0; i < (int)incomes.size(); i++) {
        if (incomes[i].date.substr(0, 7) == month) {
            totalIncome += incomes[i].amount;
        }
    }

    for (int i = 0; i < (int)expenses.size(); i++) {
        if (expenses[i].date.substr(0, 7) == month) {
            totalExpense += expenses[i].amount;
        }
    }

    cout << "\n========== MONTHLY SUMMARY: " << month << " ==========\n";
    cout << fixed << setprecision(2);
    cout << "Total Income  : Rs. " << totalIncome << endl;
    cout << "Total Expense : Rs. " << totalExpense << endl;
    cout << "Balance       : Rs. " << totalIncome - totalExpense << endl;

    cout << "\nCategory-wise expenses:\n";
    for (int i = 0; i < (int)expenses.size(); i++) {
        if (expenses[i].date.substr(0, 7) == month) {
            double categoryTotal = 0;
            bool alreadyShown = false;

            // Check whether this category was already printed earlier
            for (int j = 0; j < i; j++) {
                if (expenses[j].date.substr(0, 7) == month &&
                    expenses[j].category == expenses[i].category) {
                    alreadyShown = true;
                    break;
                }
            }

            if (!alreadyShown) {
                for (int j = 0; j < (int)expenses.size(); j++) {
                    if (expenses[j].date.substr(0, 7) == month &&
                        expenses[j].category == expenses[i].category) {
                        categoryTotal += expenses[j].amount;
                    }
                }
                cout << expenses[i].category << " : Rs. " << categoryTotal << endl;
            }
        }
    }

    cout << "\nBudget status:\n";
    for (int i = 0; i < (int)budgets.size(); i++) {
        if (budgets[i].month == month) {
            double spent = 0;
            for (int j = 0; j < (int)expenses.size(); j++) {
                if (expenses[j].date.substr(0, 7) == month &&
                    expenses[j].category == budgets[i].category) {
                    spent += expenses[j].amount;
                }
            }

            cout << budgets[i].category << " - Budget: Rs. " << budgets[i].amount
                 << ", Spent: Rs. " << spent;

            if (spent > budgets[i].amount)
                cout << " (Budget exceeded)";
            else
                cout << " (Within budget)";
            cout << endl;
        }
    }
}

// MODULE 4: Savings report
void ExpenseManager::showSavingsReport() {
    string month;
    double totalIncome = 0;
    double totalExpense = 0;

    cout << "\nEnter month (YYYY-MM): ";
    cin >> month;

    for (int i = 0; i < (int)incomes.size(); i++) {
        if (incomes[i].date.substr(0, 7) == month) {
            totalIncome += incomes[i].amount;
        }
    }

    for (int i = 0; i < (int)expenses.size(); i++) {
        if (expenses[i].date.substr(0, 7) == month) {
            totalExpense += expenses[i].amount;
        }
    }

    double savings = totalIncome - totalExpense;

    cout << "\n========== SAVINGS REPORT: " << month << " ==========\n";
    cout << fixed << setprecision(2);
    cout << "Income        : Rs. " << totalIncome << endl;
    cout << "Expenses      : Rs. " << totalExpense << endl;
    cout << "Savings       : Rs. " << savings << endl;

    if (totalIncome > 0) {
        cout << "Savings rate  : " << (savings / totalIncome) * 100 << "%\n";
    } else {
        cout << "Savings rate  : Not available (no income recorded)\n";
    }
}
