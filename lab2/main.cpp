#include <iostream>
#include <limits>
#include "polynomial.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

static void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static bool read_int(const char* prompt, int& val) {
    while (true) {
        if (prompt && prompt[0] != '\0') {
            std::cout << prompt;
        }
        if (std::cin >> val) {
            return true;
        }
        if (std::cin.eof()) {
            return false;
        }
        std::cout << "Ошибка: введите целое число.\n";
        clear_input();
    }
}

static bool read_double(const char* prompt, double& val) {
    while (true) {
        if (prompt && prompt[0] != '\0') {
            std::cout << prompt;
        }
        if (std::cin >> val) {
            return true;
        }
        if (std::cin.eof()) {
            return false;
        }
        std::cout << "Ошибка: введите вещественное число.\n";
        clear_input();
    }
}

static Polynomial input_polynomial(const char* name) {
    std::cout << "\nВвод многочлена " << name << ":\n";
    int deg = -1;
    while (true) {
        if (!read_int("Введите степень многочлена (или -1 для нулевого): ", deg)) {
            return Polynomial();
        }
        if (deg >= -1) {
            break;
        }
        std::cout << "Ошибка: степень не может быть меньше -1.\n";
    }

    if (deg == -1) {
        return Polynomial();
    }

    double* c = new double[deg + 1];
    std::cout << "Введите " << (deg + 1) << " коэффициентов от c_0 (x^0) до c_" << deg << " (x^" << deg << "):\n";
    for (int i = 0; i <= deg; ++i) {
        std::cout << "Коэффициент при x^" << i << ": ";
        read_double("", c[i]);
    }

    Polynomial result(c, deg);
    delete[] c;
    return result;
}

static void print_menu() {
    std::cout << "\n=== Меню (Семейство B: Polynomial, Вариант 8) ===\n"
              << "1. Задать многочлен A\n"
              << "2. Задать многочлен B\n"
              << "3. Напечатать многочлены A и B\n"
              << "4. Сложить A += B\n"
              << "5. Умножить A *= B\n"
              << "6. Вычислить значение A(x)\n"
              << "7. Производная A'(x) (вариант 8)\n"
              << "8. Неопределенный интеграл ∫A(x)dx (вариант 8)\n"
              << "0. Выход\n"
              << "Выберите пункт: ";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Polynomial a;
    Polynomial b;

    int choice = -1;
    while (true) {
        print_menu();
        if (!read_int("", choice)) {
            break;
        }

        if (choice == 0) {
            std::cout << "Завершение работы.\n";
            break;
        }

        switch (choice) {
            case 1: {
                a = input_polynomial("A");
                std::cout << "A(x) = ";
                a.print(std::cout);
                std::cout << " (степень: " << a.degree() << ")\n";
                break;
            }
            case 2: {
                b = input_polynomial("B");
                std::cout << "B(x) = ";
                b.print(std::cout);
                std::cout << " (степень: " << b.degree() << ")\n";
                break;
            }
            case 3: {
                std::cout << "A(x) = ";
                a.print(std::cout);
                std::cout << " (степень: " << a.degree() << ")\n";
                std::cout << "B(x) = ";
                b.print(std::cout);
                std::cout << " (степень: " << b.degree() << ")\n";
                break;
            }
            case 4: {
                std::cout << "(";
                a.print(std::cout);
                std::cout << ") + (";
                b.print(std::cout);
                std::cout << ") = ";
                a.add(b);
                a.print(std::cout);
                std::cout << " (степень: " << a.degree() << ")\n";
                break;
            }
            case 5: {
                std::cout << "(";
                a.print(std::cout);
                std::cout << ") * (";
                b.print(std::cout);
                std::cout << ") = ";
                a.mul(b);
                a.print(std::cout);
                std::cout << " (степень: " << a.degree() << ")\n";
                break;
            }
            case 6: {
                double x = 0.0;
                if (read_double("Введите точку x: ", x)) {
                    std::cout << "A(" << x << ") = " << a.evaluate(x) << "\n";
                }
                break;
            }
            case 7: {
                std::cout << "Исходный A(x) = ";
                a.print(std::cout);
                std::cout << "\nПроизводная A'(x) = ";
                Polynomial d = a.derivative();
                d.print(std::cout);
                std::cout << " (степень: " << d.degree() << ")\n";
                break;
            }
            case 8: {
                std::cout << "Исходный A(x) = ";
                a.print(std::cout);
                std::cout << "\nИнтеграл ∫A(x)dx = ";
                Polynomial integ = a.integral();
                integ.print(std::cout);
                std::cout << " (свободный член 0, степень: " << integ.degree() << ")\n";
                break;
            }
            default:
                std::cout << "Неверный пункт меню. Повторите ввод.\n";
                break;
        }
    }

    return 0;
}
