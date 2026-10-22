#include "array_ops.h"
#include <iostream>

int* array_create(std::size_t size) {
    if (size == 0) {
        return nullptr;
    }
    return new int[size]();
}

void array_delete(int*& arr) {
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size) {
    if (new_size == size) {
        return arr;
    }
    if (new_size == 0) {
        array_delete(arr);
        return nullptr;
    }

    int* new_arr = new int[new_size]();
    if (arr != nullptr) {
        std::size_t copy_count = (size < new_size) ? size : new_size;
        for (std::size_t i = 0; i < copy_count; ++i) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
    }
    return new_arr;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value) {
    if (pos > size) {
        return arr;
    }

    int* new_arr = new int[size + 1];
    for (std::size_t i = 0; i < pos; ++i) {
        new_arr[i] = arr[i];
    }
    new_arr[pos] = value;
    for (std::size_t i = pos; i < size; ++i) {
        new_arr[i + 1] = arr[i];
    }

    delete[] arr;
    ++size;
    return new_arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos) {
    if (arr == nullptr || size == 0 || pos >= size) {
        return arr;
    }

    if (size == 1) {
        delete[] arr;
        size = 0;
        return nullptr;
    }

    int* new_arr = new int[size - 1];
    for (std::size_t i = 0; i < pos; ++i) {
        new_arr[i] = arr[i];
    }
    for (std::size_t i = pos + 1; i < size; ++i) {
        new_arr[i - 1] = arr[i];
    }

    delete[] arr;
    --size;
    return new_arr;
}

void array_print(const int* arr, std::size_t size) {
    if (arr == nullptr || size == 0) {
        std::cout << "[] (размер: 0)\n";
        return;
    }

    std::cout << "[";
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i + 1 < size) {
            std::cout << ", ";
        }
    }
    std::cout << "] (размер: " << size << ")\n";
}

bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t& out_index) {
    if (arr == nullptr || size == 0) {
        return false;
    }

    std::size_t left = 0;
    std::size_t right = size;
    while (left < right) {
        std::size_t mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            out_index = mid;
            return true;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return false;
}

int* array_merge(const int* a, std::size_t na, const int* b, std::size_t nb, std::size_t& out_size) {
    if (a == nullptr) {
        na = 0;
    }
    if (b == nullptr) {
        nb = 0;
    }

    out_size = na + nb;
    if (out_size == 0) {
        return nullptr;
    }

    int* result = new int[out_size];
    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t k = 0;

    while (i < na && j < nb) {
        if (a[i] <= b[j]) {
            result[k++] = a[i++];
        } else {
            result[k++] = b[j++];
        }
    }

    while (i < na) {
        result[k++] = a[i++];
    }
    while (j < nb) {
        result[k++] = b[j++];
    }

    return result;
}

bool array_is_sorted(const int* arr, std::size_t size) {
    if (arr == nullptr || size <= 1) {
        return true;
    }
    for (std::size_t i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

