#ifndef VECTOR_BOOL_H
#define VECTOR_BOOL_H

#include <iostream>
#include <initializer_list>

template <typename T>
class Vector
{
public:
    Vector();
    Vector(const Vector<T> &);
    Vector(Vector<T> &&);
    Vector(size_t);
    Vector(size_t, T);
    Vector(std::initializer_list<T>);
    Vector& operator=(const Vector<T> &);
    Vector& operator=(Vector<T> &&);
    ~Vector();
public:
    void push_back(const T&);
    void push_back(T&&);
    void pop_back();
    void insert(size_t pos, const T&);
    size_t size() const;
    size_t capacity() const;
    void clear();
    void resize(size_t);
    void erase(size_t);
    bool empty() const;
    void shrink_to_fit();
    T& at(size_t);
    const T& at(size_t) const;
    T& operator[](size_t);
    const T& operator[](size_t) const;
    void print() const;
private:
    size_t m_size;
    size_t m_cap;
    T *m_buf;
};


template <>
class Vector<bool>
{
public:
    Vector<bool>();
    Vector<bool>(const Vector<bool>&);
    Vector<bool>(Vector<bool>&&);
    Vector<bool>(size_t);
    Vector<bool>(size_t, bool);
    Vector<bool>(std::initializer_list<bool>);
    ~Vector<bool>();
public:
    class reference
    {
    public:
        reference(size_t*, size_t);
        reference(const reference&);
        reference(reference&&);
        ~reference();
        reference& operator=(const reference&);
        reference& operator=(reference&&);
        reference& operator=(bool);
        operator bool() const;
        void flip();
    private:
        size_t* _buffer;
        size_t _index;
        bool _value;
    };

public:
    Vector<bool>& operator=(const Vector<bool>&);
    Vector<bool>& operator=(Vector<bool>&&);
public:    
    reference at(size_t);
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void clear();
    void insert(size_t, bool);
    void erase(size_t);
    void push_back(bool);
    void pop_back();
    reference operator[](size_t);
    reference front();
    reference back();
    void resize(size_t);
    void print();
private:
    static const size_t bit_count = sizeof(size_t) * 8;
private:
    size_t _cap;
    size_t _size;
    size_t* _buffer;
};

#endif // VECTOR_BOOL_H