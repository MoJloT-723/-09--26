#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Функция для задачи 1
void task1() {
    int n;
    cin >> n;
    int product = 1;
    while (n > 0) {
        product *= n % 10;
        n /= 10;
    }
    cout << product << endl;
}

// Функция для задачи 2
void task2() {
    string n;
    cin >> n;
    int sum_even = 0;
    int sum_odd = 0;
    for (char c : n) {
        int digit = c - '0';
        if (digit % 2 == 0) {
            sum_even += digit;
        } else {
            sum_odd += digit;
        }
    }
    cout << sum_even << sum_odd << endl;
}

// Функция для задачи 3
void task3() {
    int n;
    cin >> n;
    int sum = 0;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x % 3 == 0) {
            sum += x;
            count++;
        }
    }
    if (count > 0) {
        cout << (double)sum / count << endl;
    } else {
        cout << -1 << endl;
    }
}

// Функция для задачи 4
void task4() {
    int a;
    cin >> a;
    int f1 = 1, f2 = 1, n = 2;
    while (f2 < a) {
        int temp = f2;
        f2 = f1 + f2;
        f1 = temp;
        n++;
    }
    if (f2 == a) {
        cout << n << endl;
    } else {
        cout << -1 << endl;
    }
}

// Функция для задачи 5
void task5() {
    int n;
    cin >> n;
    int p = 1;
    while (p <= n) {
        cout << p << " ";
        p *= 2;
    }
    cout << endl;
}

// Функция для задачи 6
void task6() {
    int n;
    cin >> n;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x > 0) {
            count++;
        }
    }
    cout << count << endl;
}

// Функция для задачи 7
void task7() {
    int x;
    int max_val = -1;
    int count = 0;
    while (cin >> x && x != 0) {
        if (x > max_val) {
            max_val = x;
            count = 1;
        } else if (x == max_val) {
            count++;
        }
    }
    cout << count << endl;
}

// Задача 8: Класс Laptop
class Laptop {
public:
    string brand;
    string model;
    double price;
    string laptop_name_attr;

    Laptop(string brand, string model, double price) 
        : brand(brand), model(model), price(price) {
        laptop_name_attr = brand + " " + model;
    }

    string laptop_name() {
        return laptop_name_attr;
    }
};

// Задача 9: Экономические отношения
class Promise {
public:
    int id;
    double salary;
    bool fulfilled;

    Promise(int id, double salary) : id(id), salary(salary), fulfilled(false) {}
};

class Person {
public:
    string first_name;
    string second_name;
    int id;
    Promise promise;

    Person(string first_name, string second_name, int id, double salary)
        : first_name(first_name), second_name(second_name), id(id), promise(id, salary) {}
};

class Director : public Person {
public:
    Director(string first_name, string second_name, int id, double salary)
        : Person(first_name, second_name, id, salary) {}

    bool check_promises() {
        return promise.fulfilled;
    }
};

class Employee : public Person {
public:
    Employee(string first_name, string second_name, int id, double salary)
        : Person(first_name, second_name, id, salary) {}
};

class Company {
private:
    double balance;
    double profit;
    unique_ptr<Director> dir;
    vector<Employee> employees;

public:
    Company(double balance) : balance(balance), profit(0), dir(nullptr) {}

    void create_director(string first_name, string second_name, int id, double salary) {
        dir = make_unique<Director>(first_name, second_name, id, salary);
    }

    void create_employee(string first_name, string second_name, int id, double salary) {
        employees.emplace_back(first_name, second_name, id, salary);
    }

    void set_profit(double p) {
        profit = p;
        balance += profit;
    }

    bool fulfill_promise() {
        double total_salary = 0;
        if (dir) total_salary += dir->promise.salary;
        for (const auto& emp : employees) {
            total_salary += emp.promise.salary;
        }

        if (balance >= total_salary) {
            balance -= total_salary;
            if (dir) dir->promise.fulfilled = true;
            for (auto& emp : employees) {
                emp.promise.fulfilled = true;
            }
            return true;
        } else {
            if (dir) dir->promise.fulfilled = false;
            for (auto& emp : employees) {
                emp.promise.fulfilled = false;
            }
            return false;
        }
    }

    Director& director() {
        return *dir;
    }
};


int main() {
    int choice;
    cout << "Выберите задачу (1-9): ";
    if (!(cin >> choice)) return 0;

    switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        case 6: task6(); break;
        case 7: task7(); break;
        case 8: {
            Laptop laptop("Apple", "MacBook", 1500.0);
            cout << laptop.laptop_name() << endl;
            break;
        }
        case 9: {
            Company vk(50);
            vk.create_director("Владимир", "Кириенко", 1, 15);
            vk.create_employee("Елена", "Иванова", 2, 8);
            vk.create_employee("Виктор", "Кузнецов", 3, 6);

            vk.set_profit(145.12);
            vk.fulfill_promise();

            auto& director = vk.director();
            cout << "Promises fulfilled (true/false): " << (director.check_promises() ? "true" : "false") << endl;

            vk.set_profit(-200);
            vk.fulfill_promise();
            cout << "Promises fulfilled (true/false): " << (director.check_promises() ? "true" : "false") << endl;
            break;
        }
        default:
            cout << "Неверный номер задачи." << endl;
    }

    return 0;
}
