#ifndef DYNARR_H
#define DYNARR_H

#include <cstddef>
#include <new>
#include <string>
#include <iostream>

/**
 * @brief A dynamic array struct that contains the size, capacity,
 *        and data pointer used to implement this dynamic structure.
 *
 * @tparam T the type (typename) of data to store in the dynamic array
 * @field data a pointer to the data in the dynamic array on the heap
 * @field size the number of elements used in the dynamic array
 * @field capacity the number of elements the dynamic array can hold
 */
template <typename T>
struct dynamic_array
{
    T *data;
    size_t size;
    size_t capacity;
};

/**
 * @brief Create a new dynamic array with the indicated initial capacity.
 *        This will return a nullptr if the array cannot be allocated.
 *
 * @tparam T the type of data the array will store
 * @param capacity its initial capacity, with a default value of 50
 * @return dynamic_array<T>* a pointer to the new dynamic array
 */
template <typename T>
dynamic_array<T> *create_dynamic_array(size_t capacity = 50)
{
    dynamic_array<T> *arr = new (std::nothrow) dynamic_array<T>();
    if (!arr)
        return nullptr;

    arr->data = new (std::nothrow) T[capacity];
    if (!arr->data)
    {
        delete arr;
        return nullptr;
    }

    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

/**
 * @brief Free the memory allocated to the dynamic array. Once freed
 *        the data in the array will no longer be accessible.
 *
 * @tparam T the data type of the dynamic array
 * @param array a pointer to the dynamic array to free
 */
template <typename T>
void free_dynamic_array(dynamic_array<T> *array)
{
    if (array)
    {
        delete[] array->data;
        delete array;
    }
}

/**
 * @brief Resize the capacity of the dynamic array.
 *
 * If the new capacity is smaller than the current size, the size
 * will be updated to match the new capacity.
 *
 * @tparam T the type of data in the dynamic array
 * @param array the dynamic array to grow
 * @param new_capacity the new capacity of the dynamic array
 * @returns true if this succeeded, or false if it could not reallocate memory
 */
template <typename T>
bool resize_dynamic_array(dynamic_array<T> *array, size_t new_capacity)
{
    if (!array)
        return false;

    T *new_data = new (std::nothrow) T[new_capacity];
    if (!new_data)
        return false;

    size_t copy_size = (new_capacity < array->size) ? new_capacity : array->size;
    for (size_t i = 0; i < copy_size; ++i)
    {
        new_data[i] = array->data[i];
    }

    delete[] array->data;
    array->data = new_data;
    array->capacity = new_capacity;
    if (new_capacity < array->size)
    {
        array->size = new_capacity;
    }

    return true;
}

/**
 * @brief Add an element to the end of the dynamic array
 *
 * @tparam T the type of data in the dynamic array
 * @param value the value to add to the end of the dynamic array
 * @param array the dynamic array to add the value to
 * @returns true if this succeeded, false if we cannot resize to fit the new element
 */
template <typename T>
bool add_to_dynamic_array(dynamic_array<T> *array, T value)
{
    if (!array)
        return false;

    if (array->size >= array->capacity)
    {
        size_t new_capacity = (array->capacity == 0) ? 1 : array->capacity * 2;
        if (!resize_dynamic_array(array, new_capacity))
        {
            return false;
        }
    }

    array->data[array->size] = value;
    array->size++;
    return true;
}

/**
 * @brief read and return the value of the indicated element from the dynamic array.
 *
 * If the array is not allocated or the index is out of bounds, the function will throw a string exception message.
 *
 * @tparam T the type of data in the dynamic array
 * @param array the dynamic array to read the element from
 * @param index the index of the element to read
 * @throws a string message if the array is not allocated or the index is invalid
 */
template <typename T>
T get_from_dynamic_array(dynamic_array<T> *array, size_t index)
{
    if (!array)
    {
        throw std::string("Array not allocated");
    }
    if (index >= array->size)
    {
        throw std::string("Index out of bounds");
    }
    return array->data[index];
}

/**
 * @brief set the value of the indicated element from the dynamic array.
 *
 * If the index is out of bounds, the function will throw an string exception.
 *
 * @tparam T the type of data in the dynamic array
 * @param array the dynamic array to set the element in
 * @param index the index of the element to change
 * @param value the value to set the element to
 */
template <typename T>
void set_in_dynamic_array(dynamic_array<T> *array, size_t index, T value)
{
    if (!array)
    {
        throw std::string("Array not allocated");
    }
    if (index >= array->size)
    {
        throw std::string("Index out of bounds");
    }
    array->data[index] = value;
}
#endif