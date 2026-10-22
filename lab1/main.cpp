#include <iostream>
#include <limits>
#include "array_ops.h"

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

static bool read_size(const char* prompt, std::size_t& val) {
    while (true) {
        if (prompt && prompt[0] != '\0') {
            std::cout << prompt;
        }
        long long temp = 0;
        if (std::cin >> temp) {
            if (temp >= 0) {
                val = static_cast<std::size_t>(temp);
                return true;
            }
            std::cout << "Ошибка: размер не может быть отрицательным.\n";
        } else {
            if (std::cin.eof()) {
                return false;
            }
            std::cout << "Ошибка: введите неотрицательное целое число.\n";
            clear_input();
        }
    }
}

static void print_menu() {
    std::cout << "\n=== Меню (Семейство A, Вариант 8) ===\n"
              << "1. Создать массив\n"
              << "2. Напечатать массив\n"
              << "3. Вставить элемент\n"
              << "4. Удалить элемент\n"
              << "5. Изменить размер\n"
              << "6. Бинарный поиск\n"
              << "7. Алгоритм варианта (слияние отсортированных массивов)\n"
              << "0. Выход\n"
              << "Выберите пункт: ";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    int* arr = nullptr;
    std::size_t size = 0;

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
                array_delete(arr);
                size = 0;

                if (!read_size("Введите размер массива: ", size)) {
                    break;
                }

                arr = array_create(size);
                if (size > 0) {
                    std::cout << "Введите " << size << " целых чисел:\n";
                    for (std::size_t i = 0; i < size; ++i) {
                        read_int("", arr[i]);
                    }
                }
                std::cout << "Массив создан: ";
                array_print(arr, size);
                break;
            }
            case 2: {
                std::cout << "Текущий массив: ";
                array_print(arr, size);
                break;
            }
            case 3: {
                std::cout << "Введите позицию для вставки (0.." << size << "): ";
                std::size_t pos = 0;
                if (!read_size("", pos)) {
                    break;
                }
                if (pos > size) {
                    std::cout << "Ошибка: позиция выходит за границы.\n";
                    break;
                }
                int value = 0;
                if (!read_int("Введите значение: ", value)) {
                    break;
                }
                arr = array_insert(arr, size, pos, value);
                std::cout << "Результат: ";
                array_print(arr, size);
                break;
            }
            case 4: {
                if (size == 0) {
                    std::cout << "Массив пуст, удаление невозможно.\n";
                    break;
                }
                std::cout << "Введите индекс для удаления (0.." << (size - 1) << "): ";
                std::size_t pos = 0;
                if (!read_size("", pos)) {
                    break;
                }
                if (pos >= size) {
                    std::cout << "Ошибка: индекс выходит за границы.\n";
                    break;
                }
                arr = array_remove(arr, size, pos);
                std::cout << "Результат: ";
                array_print(arr, size);
                break;
            }
            case 5: {
                std::size_t new_size = 0;
                if (!read_size("Введите новый размер массива: ", new_size)) {
                    break;
                }
                arr = array_resize(arr, size, new_size);
                size = new_size;
                std::cout << "Результат: ";
                array_print(arr, size);
                break;
            }
            case 6: {
                if (size == 0) {
                    std::cout << "Массив пуст.\n";
                    break;
                }
                if (!array_is_sorted(arr, size)) {
                    std::cout << "Предупреждение: массив не отсортирован по возрастанию. "
                              << "Бинарный поиск может дать некорректный результат.\n";
                }
                int target = 0;
                if (!read_int("Введите искомое число: ", target)) {
                    break;
                }
                std::size_t found_idx = 0;
                if (array_binary_search(arr, size, target, found_idx)) {
                    std::cout << "Элемент " << target << " найден на позиции " << found_idx << ".\n";
                } else {
                    std::cout << "Элемент " << target << " не найден в массиве.\n";
                }
                break;
            }
            case 7: {
                std::cout << "--- Слияние двух отсортированных массивов ---\n";
                std::size_t na = 0;
                if (!read_size("Размер первого массива (a): ", na)) {
                    break;
                }
                int* a = array_create(na);
                if (na > 0) {
                    std::cout << "Введите " << na << " отсортированных элементов массива a:\n";
                    for (std::size_t i = 0; i < na; ++i) {
                        read_int("", a[i]);
                    }
                }

                std::size_t nb = 0;
                if (!read_size("Размер второго массива (b): ", nb)) {
                    array_delete(a);
                    break;
                }
                int* b = array_create(nb);
                if (nb > 0) {
                    std::cout << "Введите " << nb << " отсортированных элементов массива b:\n";
                    for (std::size_t i = 0; i < nb; ++i) {
                        read_int("", b[i]);
                    }
                }

                if (!array_is_sorted(a, na) || !array_is_sorted(b, nb)) {
                    std::cout << "Предупреждение: один из массивов не отсортирован по возрастанию.\n";
                }

                std::size_t out_size = 0;
                int* merged = array_merge(a, na, b, nb, out_size);

                std::cout << "Результат слияния: ";
                array_print(merged, out_size);

                array_delete(a);
                array_delete(b);
                array_delete(merged);
                break;
            }
            default:
                std::cout << "Неверный пункт меню. Повторите ввод.\n";
                break;
        }
    }

    array_delete(arr);
    return 0;
}
