#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <ctime>

using namespace std;

class ExpenseTracker {
private:
    string filename;
    vector<vector<string>> expenses;

public:
    ExpenseTracker(const string& filename = "expenses.txt") : filename(filename) {
        expenses = loadExpenses();
    }

    vector<vector<string>> loadExpenses() {
        vector<vector<string>> expenses;
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                vector<string> expense;
                size_t pos = 0;
                while ((pos = line.find(',')) != string::npos) {
                    expense.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                expense.push_back(line); // Adding the last part after the last comma
                expenses.push_back(expense);
            }
            file.close();
        }
        return expenses;
    }

    void saveExpenses() {
        ofstream file(filename);
        for (const auto& expense : expenses) {
            for (size_t i = 0; i < expense.size(); ++i) {
                file << expense[i];
                if (i < expense.size() - 1) {
                    file << ',';
                }
            }
            file << '\n';
        }
        file.close();
    }

    void addExpense(const string& category, float amount) {
        time_t t = time(0);
        tm* now = localtime(&t);
        char date[11];
        strftime(date, sizeof(date), "%Y-%m-%d", now);

        vector<string> expense = {date, category, to_string(amount)};
        expenses.push_back(expense);
        saveExpenses();

        cout << "Expense added:\nDate: " << date << "\nCategory: " << category << "\nAmount: RS" << amount << endl;
    }

    void viewExpenses() {
        if (expenses.empty()) {
            cout << "No expenses recorded." << endl;
        } else {
            cout << "{:<10} {:<12} {:<20} {:<10}\n" << "Index" << "Date" << "Category" << "Amount";
            for (size_t index = 0; index < expenses.size(); ++index) {
                const auto& expense = expenses[index];
                cout << "{:<10} {:<12} {:<20} {:<10}\n" << index + 1 << expense[0] << expense[1] << "RS" << expense[2];
            }
        }
    }

    float calculateTotalExpenses() {
        float totalExpenses = 0.0f;
        for (const auto& expense : expenses) {
            totalExpenses += stof(expense[2]);
        }
        return totalExpenses;
    }

    void expenseCategoriesSummary() {
        unordered_map<string, float> categoryTotals;
        for (const auto& expense : expenses) {
            categoryTotals[expense[1]] += stof(expense[2]);
        }

        cout << "Expense Categories Summary:\n";
        for (const auto& pair : categoryTotals) {
            cout << pair.first << ": RS" << pair.second << endl;
        }
    }

    void monthlyExpenseSummary() {
        time_t t = time(0);
        tm* now = localtime(&t);
        char currentMonth[8];
        strftime(currentMonth, sizeof(currentMonth), "%Y-%m", now);

        vector<vector<string>> monthlyExpenses;
        for (const auto& expense : expenses) {
            if (expense[0].rfind(currentMonth, 0) == 0) {
                monthlyExpenses.push_back(expense);
            }
        }

        if (monthlyExpenses.empty()) {
            cout << "No expenses recorded for the month " << currentMonth << "." << endl;
        } else {
            cout << "{:<10} {:<12} {:<20} {:<10}\n" << "Index" << "Date" << "Category" << "Amount";
            for (size_t index = 0; index < monthlyExpenses.size(); ++index) {
                const auto& expense = monthlyExpenses[index];
                cout << "{:<10} {:<12} {:<20} {:<10}\n" << index + 1 << expense[0] << expense[1] << "RS" << expense[2];
            }
        }
    }

    void deleteExpense(size_t index) {
        if (index >= 1 && index <= expenses.size()) {
            auto deletedExpense = expenses[index - 1];
            expenses.erase(expenses.begin() + index - 1);
            saveExpenses();

            cout << "Expense deleted:\nDate: " << deletedExpense[0] << "\nCategory: " << deletedExpense[1] << "\nAmount: RS" << deletedExpense[2] << endl;
        } else {
            cout << "Invalid index. Please enter a valid index." << endl;
        }
    }
};

int main() {
    ExpenseTracker expenseTracker;

    while (true) {
        cout << "\n1. Add Expense\n2. View Expenses\n3. Calculate Total Expenses\n4. Expense Categories Summary\n5. Monthly Expense Summary\n6. Delete Expense\n7. Quit" << endl;
        cout << "Enter your choice (1/2/3/4/5/6/7): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string category;
                float amount;
                cout << "Enter the expense category: ";
                cin >> category;
                cout << "Enter the expense amount: ";
                cin >> amount;
                expenseTracker.addExpense(category, amount);
                break;
            }
            case 2:
                expenseTracker.viewExpenses();
                break;
            case 3: {
                float totalExpenses = expenseTracker.calculateTotalExpenses();
                cout << "Total Expenses: RS" << totalExpenses << endl;
                break;
            }
            case 4:
                expenseTracker.expenseCategoriesSummary();
                break;
            case 5:
                expenseTracker.monthlyExpenseSummary();
                break;
            case 6: {
                size_t index;
                cout << "Enter the index of the expense to delete: ";
                cin >> index;
                expenseTracker.deleteExpense(index);
                break;
            }
            case 7:
                cout << "Saving expenses and exiting the Expense Tracker. Goodbye!" << endl;
                return 0;
            default:
                        
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}

