#include <gtest/gtest.h>
#include "array_ops.h"

TEST(ArrayOpsTest, CreateAndDeleteNormal) {
    std::size_t size = 5;
    int* arr = array_create(size);
    ASSERT_NE(arr, nullptr);

    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], 0);
        arr[i] = static_cast<int>(i * 10);
    }

    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], static_cast<int>(i * 10));
    }

    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayOpsTest, CreateZero) {
    int* arr = array_create(0);
    EXPECT_EQ(arr, nullptr);
    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayOpsTest, ResizeEnlarge) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr = array_resize(arr, size, 5);
    size = 5;
    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 0);
    EXPECT_EQ(arr[4], 0);

    array_delete(arr);
}

TEST(ArrayOpsTest, ResizeShrink) {
    std::size_t size = 4;
    int* arr = array_create(size);
    arr[0] = 5;
    arr[1] = 6;
    arr[2] = 7;
    arr[3] = 8;

    arr = array_resize(arr, size, 2);
    size = 2;
    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 6);

    array_delete(arr);
}

TEST(ArrayOpsTest, ResizeToZero) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr = array_resize(arr, size, 0);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayOpsTest, InsertBeginning) {
    std::size_t size = 2;
    int* arr = array_create(size);
    arr[0] = 20;
    arr[1] = 30;

    arr = array_insert(arr, size, 0, 10);
    EXPECT_EQ(size, 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    array_delete(arr);
}

TEST(ArrayOpsTest, InsertMiddle) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 1;
    arr[1] = 3;
    arr[2] = 4;

    arr = array_insert(arr, size, 1, 2);
    EXPECT_EQ(size, 4u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);

    array_delete(arr);
}

TEST(ArrayOpsTest, InsertEnd) {
    std::size_t size = 2;
    int* arr = array_create(size);
    arr[0] = 100;
    arr[1] = 200;

    arr = array_insert(arr, size, 2, 300);
    EXPECT_EQ(size, 3u);
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);

    array_delete(arr);
}

TEST(ArrayOpsTest, InsertOutOfBounds) {
    std::size_t size = 2;
    int* arr = array_create(size);
    arr[0] = 1;
    arr[1] = 2;

    int* unchanged = array_insert(arr, size, 5, 999);
    EXPECT_EQ(unchanged, arr);
    EXPECT_EQ(size, 2u);

    array_delete(arr);
}

TEST(ArrayOpsTest, InsertIntoEmpty) {
    std::size_t size = 0;
    int* arr = nullptr;

    arr = array_insert(arr, size, 0, 42);
    EXPECT_EQ(size, 1u);
    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(arr[0], 42);

    array_delete(arr);
}

TEST(ArrayOpsTest, RemoveBeginning) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr = array_remove(arr, size, 0);
    EXPECT_EQ(size, 2u);
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 30);

    array_delete(arr);
}

TEST(ArrayOpsTest, RemoveMiddle) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr = array_remove(arr, size, 1);
    EXPECT_EQ(size, 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);

    array_delete(arr);
}

TEST(ArrayOpsTest, RemoveEnd) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr = array_remove(arr, size, 2);
    EXPECT_EQ(size, 2u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    array_delete(arr);
}

TEST(ArrayOpsTest, RemoveSingleElement) {
    std::size_t size = 1;
    int* arr = array_create(size);
    arr[0] = 77;

    arr = array_remove(arr, size, 0);
    EXPECT_EQ(size, 0u);
    EXPECT_EQ(arr, nullptr);
}

TEST(ArrayOpsTest, RemoveOutOfBounds) {
    std::size_t size = 2;
    int* arr = array_create(size);
    arr[0] = 1;
    arr[1] = 2;

    int* unchanged = array_remove(arr, size, 5);
    EXPECT_EQ(unchanged, arr);
    EXPECT_EQ(size, 2u);

    array_delete(arr);
}

TEST(ArrayOpsTest, BinarySearchFound) {
    std::size_t size = 5;
    int* arr = array_create(size);
    arr[0] = 2;
    arr[1] = 4;
    arr[2] = 6;
    arr[3] = 8;
    arr[4] = 10;

    std::size_t idx = 0;
    EXPECT_TRUE(array_binary_search(arr, size, 2, idx));
    EXPECT_EQ(idx, 0u);

    EXPECT_TRUE(array_binary_search(arr, size, 6, idx));
    EXPECT_EQ(idx, 2u);

    EXPECT_TRUE(array_binary_search(arr, size, 10, idx));
    EXPECT_EQ(idx, 4u);

    array_delete(arr);
}

TEST(ArrayOpsTest, BinarySearchNotFound) {
    std::size_t size = 4;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;

    std::size_t idx = 0;
    EXPECT_FALSE(array_binary_search(arr, size, 5, idx));
    EXPECT_FALSE(array_binary_search(arr, size, 25, idx));
    EXPECT_FALSE(array_binary_search(arr, size, 50, idx));

    array_delete(arr);
}

TEST(ArrayOpsTest, BinarySearchEmpty) {
    std::size_t idx = 0;
    EXPECT_FALSE(array_binary_search(nullptr, 0, 10, idx));
}

TEST(ArrayOpsTest, MergeExampleFromTask) {
    // Контрольный пример из задания:
    // a={1, 3, 5}, b={2, 4, 6} -> {1, 2, 3, 4, 5, 6}, out_size=6
    int a[] = {1, 3, 5};
    int b[] = {2, 4, 6};
    std::size_t out_size = 0;

    int* res = array_merge(a, 3, b, 3, out_size);
    ASSERT_EQ(out_size, 6u);
    ASSERT_NE(res, nullptr);

    int expected[] = {1, 2, 3, 4, 5, 6};
    for (std::size_t i = 0; i < out_size; ++i) {
        EXPECT_EQ(res[i], expected[i]);
    }

    array_delete(res);
}

TEST(ArrayOpsTest, MergeOneEmpty) {
    int a[] = {1, 5, 9};
    std::size_t out_size = 0;

    int* res = array_merge(a, 3, nullptr, 0, out_size);
    ASSERT_EQ(out_size, 3u);
    ASSERT_NE(res, nullptr);
    EXPECT_EQ(res[0], 1);
    EXPECT_EQ(res[1], 5);
    EXPECT_EQ(res[2], 9);
    array_delete(res);

    res = array_merge(nullptr, 0, a, 3, out_size);
    ASSERT_EQ(out_size, 3u);
    ASSERT_NE(res, nullptr);
    EXPECT_EQ(res[0], 1);
    EXPECT_EQ(res[1], 5);
    EXPECT_EQ(res[2], 9);
    array_delete(res);
}

TEST(ArrayOpsTest, MergeBothEmpty) {
    std::size_t out_size = 999;
    int* res = array_merge(nullptr, 0, nullptr, 0, out_size);
    EXPECT_EQ(out_size, 0u);
    EXPECT_EQ(res, nullptr);
}

TEST(ArrayOpsTest, MergeDuplicatesAndDifferentLengths) {
    int a[] = {1, 2, 2, 5, 8, 9};
    int b[] = {2, 3, 7};
    std::size_t out_size = 0;

    int* res = array_merge(a, 6, b, 3, out_size);
    ASSERT_EQ(out_size, 9u);

    int expected[] = {1, 2, 2, 2, 3, 5, 7, 8, 9};
    for (std::size_t i = 0; i < out_size; ++i) {
        EXPECT_EQ(res[i], expected[i]);
    }

    array_delete(res);
}

TEST(ArrayOpsTest, MergeNegativeNumbers) {
    int a[] = {-10, -5, 0, 7};
    int b[] = {-8, -2, 3, 10};
    std::size_t out_size = 0;

    int* res = array_merge(a, 4, b, 4, out_size);
    ASSERT_EQ(out_size, 8u);

    int expected[] = {-10, -8, -5, -2, 0, 3, 7, 10};
    for (std::size_t i = 0; i < out_size; ++i) {
        EXPECT_EQ(res[i], expected[i]);
    }

    array_delete(res);
}

