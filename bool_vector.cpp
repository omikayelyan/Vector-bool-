#include "bool.hpp"

Vector<bool>::reference::reference(size_t* buffer, size_t index)
    : _buffer{buffer}, _index{index}, _value{}
{
    _value = _buffer[_index / bit_count] & (1 << (_index % bit_count));
}

Vector<bool>::reference::reference(const reference& oth)
    : _buffer{oth._buffer}, _index{oth._index}, _value{oth._value}
{
}

Vector<bool>::reference::reference(reference&& oth)
    : _buffer{std::move(oth._buffer)},
    _index{oth._index},
    _value{oth._value}
{
}

Vector<bool>::reference::~reference() = default;

Vector<bool>::reference& Vector<bool>::reference::operator=(const Vector<bool>::reference& rhs)
{
    if (_value != rhs._value)
    {
        this->flip();
    }
    return *this;
}

Vector<bool>::reference& Vector<bool>::reference::operator=(Vector<bool>::reference&& rhs)
{
    if (_value != rhs._value)
    {
        this->flip();
    }
    return *this;
}

Vector<bool>::reference& Vector<bool>::reference::operator=(bool value)
{
    if (_value != value)
    {
        this->flip();
    }
    return *this;
}

Vector<bool>::reference::operator bool() const
{
    return _value;
}

void Vector<bool>::reference::flip()
{
    _buffer[_index / bit_count] ^= (1 << (_index % bit_count));
    _value = !_value;
}

Vector<bool>::Vector()
    : _cap{bit_count}, _size{}, _buffer{new size_t[1]}
{
}

Vector<bool>::Vector(size_t count)
    : _cap{(count / bit_count + 1) * bit_count}, 
    _size{count},
    _buffer{}
{
    _buffer = new size_t[_cap / bit_count];
    for (size_t i{}; i < _size; ++i)
    {
        this->operator[](i) = false;
    }
}

Vector<bool>::reference Vector<bool>::operator[](size_t pos)
{
    Vector<bool>::reference result(_buffer, pos);
    return result;
}

Vector<bool>::Vector(size_t count, bool value)
    : _cap{(count / bit_count + 1) * bit_count},
    _size{count},
    _buffer{}
{
    _buffer = new size_t[_cap / bit_count];
    for (size_t i{}; i < _size; ++i)
    {
        this->operator[](i) = value;
    }
}

Vector<bool>::Vector(const Vector<bool>& oth)
    : _cap{oth._cap}, _size{oth._size}, _buffer{}
{
    _buffer = new size_t[_cap / bit_count ];
    for (size_t i{}; i < _cap / bit_count; ++i)
    {
        _buffer[i] = oth._buffer[i];
    }
}

Vector<bool>::Vector(Vector<bool>&& oth)
    : _cap{oth._cap}, _size{oth._size}, _buffer{oth._buffer}
{
}

Vector<bool>::Vector(std::initializer_list<bool> init)
    : _cap{(init.size() / bit_count + 1) * bit_count},
    _size{init.size()},
    _buffer{}
{
    _buffer = new size_t[_cap / bit_count];
    auto it = init.begin();
    size_t i{};
    for (; it != init.end(); ++i)
    {
        (*this)[i] = *(it++);
    }
}

Vector<bool>::~Vector()
{
    delete[] _buffer;
}

Vector<bool>& Vector<bool>::operator=(const Vector<bool>& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    _cap = rhs._cap;
    _size = rhs._size;
    size_t* temp = new size_t[_cap / bit_count];
    for (size_t i{}; i < _cap / bit_count; ++i)
    {
        temp[i] = rhs._buffer[i];
    }
    delete[] _buffer;
    _buffer = temp;
    temp = nullptr;
    return *this;
}

Vector<bool>& Vector<bool>::operator=(Vector<bool>&& rhs)
{
    _cap = rhs._cap;
    _size = rhs._size;
    _buffer = std::move(rhs._buffer);
    return *this;
}

Vector<bool>::reference Vector<bool>::at(size_t pos)
{
    if (pos > 0 && pos <= _size)
    {
        return this->operator[](pos);
    }    
    throw std::out_of_range("");
}

bool Vector<bool>::empty() const
{
    return !_size;
}

size_t Vector<bool>::size() const
{
    return _size;
}

size_t Vector<bool>::capacity() const
{
    return _cap;
}

void Vector<bool>::clear()
{
    _cap = bit_count;
    _size = 0;
    delete[] _buffer;
    _buffer = new size_t[_cap / bit_count];
}

void Vector<bool>::insert(size_t pos, bool value)
{
    if (_cap == _size)
    {
        _cap += bit_count;
        size_t* temp = new size_t[_cap / bit_count];
        for (size_t i{}; i < _cap / bit_count; ++i)
        {
            temp[i] = _buffer[i];
        }
        delete[] _buffer;
        _buffer = temp;
        temp = nullptr;
    }
    for (size_t i = _size; i > pos; --i)
    {
        this->operator[](i) = this->operator[](i - 1);
    }
    this->operator[](pos) = value;
    ++_size;
}

void Vector<bool>::erase(size_t pos)
{
    if (this->empty() || pos >= _size)
        throw std:: out_of_range("");
    for (size_t i{pos}; i < _size - 1; ++i)
    {
        this->operator[](i) = this->operator[](i + 1);
    }
    --_size;
}

void Vector<bool>::push_back(bool value)
{
    if (_size == _cap)
    {
        _cap += bit_count;
        size_t* temp = new size_t[_cap / bit_count];
        for (size_t i{}; i < _cap / bit_count; ++i)
        {
            temp[i] = _buffer[i];
        }
        delete[] _buffer;
        _buffer = temp;
        temp = nullptr;
    }
    this->operator[](_size++) = value;
}

void Vector<bool>::pop_back()
{
    if (this->empty())
    {
        throw std::out_of_range("");
    }
    this->operator[](_size--) = false;
}

Vector<bool>::reference Vector<bool>::front()
{
    return this->operator[](0);
}

Vector<bool>::reference Vector<bool>::back()
{
    return this->operator[](_size - 1);
}

void Vector<bool>::resize(size_t count)
{
    _cap = (count / bit_count + 1) * bit_count;
    size_t* temp = new size_t[_cap / bit_count];
    for (size_t i{}; i < _cap / bit_count; ++i)
    {
        temp[i] = _buffer[i];
    }
    delete[] _buffer;
    _buffer = temp;
    temp = nullptr;
    if(count < _size)
    {
        _size = count;
    }
}

void Vector<bool>::print()
{
    for (int i = 0; i < _size; ++i)
    {
        std::cout << (*this)[i];
    }
}

//Examples
int main()
{
    Vector<bool> vec = {1, 0, 0, 1, 0, 1};
    vec.push_back(0);
    vec.insert(2, 1);
    vec.print();
    std::cout << std::endl << vec.size();
}