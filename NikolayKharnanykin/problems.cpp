#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace problem {

    // Задача 1
    unsigned problem1() {
        int n;
        std::cin >> n;
        int product = 1;
        while (n > 0) {
            product *= n % 10;
            n /= 10;
        }
        return product;
    }

    // Задача 2
    std::string problem2() {
        std::string n;
        std::cin >> n;
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
        return std::to_string(sum_even) + std::to_string(sum_odd);
    }

    // Задача 3
    double problem3() {
        int n;
        std::cin >> n;
        int sum = 0;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            std::cin >> x;
            if (x % 3 == 0) {
                sum += x;
                count++;
            }
        }
        if (count > 0) {
            return (double)sum / count;
        } else {
            return -1.0;
        }
    }

    // Задача 4
    int problem4() {
        int a;
        std::cin >> a;
        int f1 = 1, f2 = 1, n = 2;
        while (f2 < a) {
            int temp = f2;
            f2 = f1 + f2;
            f1 = temp;
            n++;
        }
        if (f2 == a) {
            return n;
        } else {
            return -1;
        }
    }

    // Задача 5
    std::string problem5() {
        int n;
        std::cin >> n;
        int p = 1;
        std::stringstream ss;
        while (p <= n) {
            ss << p << " ";
            p *= 2;
        }
        return ss.str();
    }

    // Задача 6
    int problem6() {
        int n;
        std::cin >> n;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            std::cin >> x;
            if (x > 0) {
                count++;
            }
        }
        return count;
    }

    // Задача 7
    int problem7() {
        int x;
        int max_val = -1;
        int count = 0;
        while (std::cin >> x && x != 0) {
            if (x > max_val) {
                max_val = x;
                count = 1;
            } else if (x == max_val) {
                count++;
            }
        }
        return count;
    }

    // Задача 8: Класс Laptop
    class Laptop {
    public:
        std::string brand;
        std::string model;
        double price;
        std::string laptop_name_attr;

        Laptop(std::string brand, std::string model, double price) 
            : brand(brand), model(model), price(price) {
            laptop_name_attr = brand + " " + model;
        }

        std::string laptop_name() {
            return laptop_name_attr;
        }
    };

    std::string problem8() {
        Laptop laptop("Apple", "MacBook", 1500.0);
        return laptop.laptop_name();
    }

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
        std::string first_name;
        std::string second_name;
        int id;
        Promise promise;

        Person(std::string first_name, std::string second_name, int id, double salary)
            : first_name(first_name), second_name(second_name), id(id), promise(id, salary) {}
    };

    class Director : public Person {
    public:
        Director(std::string first_name, std::string second_name, int id, double salary)
            : Person(first_name, second_name, id, salary) {}

        bool check_promises() {
            return promise.fulfilled;
        }
    };

    class Employee : public Person {
    public:
        Employee(std::string first_name, std::string second_name, int id, double salary)
            : Person(first_name, second_name, id, salary) {}
    };

    class Company {
    private:
        double balance;
        double profit;
        std::unique_ptr<Director> dir;
        std::vector<Employee> employees;

    public:
        Company(double balance) : balance(balance), profit(0), dir(nullptr) {}

        void create_director(std::string first_name, std::string second_name, int id, double salary) {
            dir = std::make_unique<Director>(first_name, second_name, id, salary);
        }

        void create_employee(std::string first_name, std::string second_name, int id, double salary) {
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

    std::string problem9() {
        Company vk(50);
        vk.create_director("Владимир", "Кириенко", 1, 15);
        vk.create_employee("Елена", "Иванова", 2, 8);
        vk.create_employee("Виктор", "Кузнецов", 3, 6);

        vk.set_profit(145.12);
        vk.fulfill_promise();

        auto& director = vk.director();
        std::string res1 = director.check_promises() ? "true" : "false";

        vk.set_profit(-200);
        vk.fulfill_promise();
        std::string res2 = director.check_promises() ? "true" : "false";
        
        return res1 + "\n" + res2;
    }

} // namespace problem

using namespace problem;

int main() {
    auto run_problem = [](this auto&& self) -> void {
        unsigned id_problem;
        if (!(std::cin >> id_problem)) return;

        switch (id_problem) {
            case 1:
                std::cout << problem1() << '\n';
                break;
            case 2:
                std::cout << problem2() << '\n';
                break;
            case 3:
                std::cout << problem3() << '\n';
                break;
            case 4:
                std::cout << problem4() << '\n';
                break;
            case 5:
                std::cout << problem5() << '\n';
                break;
            case 6:
                std::cout << problem6() << '\n';
                break;
            case 7:
                std::cout << problem7() << '\n';
                break;
            case 8:
                std::cout << problem8() << '\n';
                break;
            case 9:
                std::cout << problem9() << '\n';
                break;
            default:
                self();
                break;
        }
    };

    run_problem();
    return 0;
}
