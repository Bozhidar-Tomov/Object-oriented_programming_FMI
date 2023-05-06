#pragma once
#include <istream>
#include <ostream>

const size_t DEFAULT_CAPACITY = 8;

class MyString
{
    char *_data = nullptr;
    size_t _size = 0;
    size_t _capacity = DEFAULT_CAPACITY;

public:
    // Big 4
    MyString();
    MyString(const char *);
    MyString(const MyString &);
    MyString &operator=(const MyString &);
    ~MyString();

    char *operator*() const;

public:
    // Capacity:
    size_t size() const;
    size_t length() const;
    void resize(size_t, char = '\0');
    size_t capacity() const;
    void reserve(size_t);
    void clear();
    bool empty() const;
    void shrink_to_fit();

    // Element access:
    char &operator[](size_t);
    const char &operator[](size_t) const;

    char &at(size_t);
    const char &at(size_t) const;

    char &front();
    const char &front() const;

    char &back();
    const char &back() const;

    // Modifiers:
    MyString &operator+=(const MyString &);
    MyString &operator+=(const char *);

    MyString &append(const MyString &);
    MyString &append(const char *);

    void push_back(char);

    MyString &replace(size_t, size_t, const MyString &);
    MyString &replace(size_t, size_t, size_t, char);

    void swap(MyString &);
    void pop_back();

    // String operations:
    const char *c_str() const;
    size_t find_first_of(char, size_t = 0) const;
    size_t find_last_of(char, size_t = SIZE_MAX) const;
    MyString substr(size_t, size_t) const;

    size_t compare(const MyString &) const;
    size_t compare(const char *) const;

private:
    // Big 4 helper functions
    void manageCapacity(size_t, bool, bool = true);

    void free();
    void copyFrom(const MyString &);
    void copyData(const char *);

private:
    friend std::ostream &operator<<(std::ostream &, const MyString &);
};

MyString operator+(const MyString &, const MyString &);

bool operator==(const MyString &, const MyString &);
bool operator!=(const MyString &, const MyString &);

bool operator<(const MyString &, const MyString &);
bool operator>(const MyString &, const MyString &);

bool operator<=(const MyString &, const MyString &);
bool operator>=(const MyString &, const MyString &);
