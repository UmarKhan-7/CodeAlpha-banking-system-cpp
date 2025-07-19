#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Transaction {
public:
    string type;
    double amount;
    time_t timestamp;

    Transaction(const string& t, double a)
        : type(t), amount(a), timestamp(::time(nullptr)) {}

    void show() const {
        cout << type << " of " << amount
             << " at " << ctime(&timestamp);
    }
};

class Account {
public:
    int id;
    double balance;
    vector<Transaction> history;
    static int nextId;

    Account() : id(nextId++), balance(0) {}

    void deposit(double amt) {
        if (amt > 0) {
            balance += amt;
            history.emplace_back("Deposit", amt);
            cout << "Deposited " << amt << endl;
        }
    }

    void withdraw(double amt) {
        if (amt > 0 && amt <= balance) {
            balance -= amt;
            history.emplace_back("Withdrawal", amt);
            cout << "Withdrawn " << amt << endl;
        }
    }

    void transferTo(Account &dest, double amt) {
        if (amt > 0 && amt <= balance) {
            balance -= amt;
            dest.balance += amt;
            history.emplace_back("Transfer Out", amt);
            dest.history.emplace_back("Transfer In", amt);
            cout << "Transferred " << amt
                 << " to account " << dest.id << endl;
        }
    }

    void showInfo() const {
        cout << "Account #" << id << " Balance: " << balance << endl;
    }

    void showHistory() const {
        cout << "History for account #" << id << ":\n";
        for (auto &t : history) t.show();
    }
};

int Account::nextId = 1001;

class Customer {
public:
    string name;
    vector<Account> accounts;

    Customer(const string& n) : name(n) {}

    void addAccount() {
        accounts.emplace_back();
        cout << "New account #" << accounts.back().id << " created." << endl;
    }

    Account& get(int pos) {
        return accounts[pos];
    }

    void showAll() const {
        cout << "Customer: " << name << endl;
        for (auto &acc : accounts) acc.showInfo();
    }
};

int main() {
    Customer c("UMAR");
    c.addAccount();  
    c.addAccount(); 

    Account &a1 = c.get(0);
    Account &a2 = c.get(1);

    a1.deposit(300);
    a1.withdraw(50);
    a1.transferTo(a2, 100);

    c.showAll();
    a1.showHistory();
    a2.showHistory();

    return 0;
}
