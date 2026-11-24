#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include <string>
#include <vector>
using namespace std;

// Stores one income record
struct Income {
    string date;       // Format: YYYY-MM-DD
    string source;
    double amount;
};

// Stores one expense record
struct Expense {
    string date;       // Format: YYYY-MM-DD
    string category;
    string description;
    double amount;
};

// Stores a monthly budget for one category
struct Budget {
    string month;      // Format: YYYY-MM
    string category;
    double amount;
};

class ExpenseManager {
private:
    vector<Income> incomes;
    vector<Expense> expenses;
    vector<Budget> budgets;

    void loadData();
    void saveData();

public:
    ExpenseManager();

    void recordIncome();
    void addExpense();
    void editExpense();
    void deleteExpense();
    void showExpenses();
    void setBudget();
    void showMonthlyReport();
    void showSavingsReport();
};

#endif
