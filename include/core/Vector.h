//
// Created by dirii on 27/04/2023.
//

#ifndef VISUALGO_CS162_VECTOR_H
#define VISUALGO_CS162_VECTOR_H

template<class T> class Vector {
private:
    T* arr;
    int capacity{};
    int _size{};

public:
    Vector();
    explicit Vector(int capacity);
    Vector(const Vector<T>& other);
    ~Vector();

    void push_back(T data);
    void pop_back();
    void insert(int index, T data);
    void erase(int index);
    void erase(T* position);
    void clear();
    void resize(int capacity);
    void assign(int capacity, T data);
//    void reserve();
//    void shrink_to_fit();

    T& operator[](int index);
    Vector<T>& operator=(const Vector<T>& other);

    [[nodiscard]] int getCapacity() const;
    [[nodiscard]] int size() const;
    [[nodiscard]] bool empty() const;
    T& at(int index) const;
    T& front() const;
    T& back() const;
    T* data() const;
    T* begin();
    T* end();
};

template<class T>
void Vector<T>::assign(int _capacity, T data) {
    this->clear();
    this->resize(_capacity);
    for (int i = 0; i < capacity; ++i) {
        this->arr[i] = data;
    }

}

template<class T>
void Vector<T>::erase(T *position) {
    for (int i = 0; i < this->_size; ++i) {
        if (this->arr + i == position) {
            this->erase(i);
            break;
        }
    }
}

template<class T>
T *Vector<T>::end() {
    return this->arr + this->_size;
}

template<class T>
T *Vector<T>::begin() {
    return this->arr;
}

template<class T>
T *Vector<T>::data() const {
    return this->arr;
}

template<class T>
T &Vector<T>::back() const {
    return this->arr[this->_size - 1];
}

template<class T>
T &Vector<T>::front() const {
    return this->arr[0];
}

template<class T>
T &Vector<T>::at(int index) const {
    return this->arr[index];
}

template<class T>
bool Vector<T>::empty() const {
    return this->_size == 0;
}

template<class T>
int Vector<T>::size() const {
    return this->_size;
}

template<class T>
int Vector<T>::getCapacity() const {
    return this->capacity;
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    if (this != &other) {
        this->capacity = other.capacity;
        this->_size = other._size;
        delete[] this->arr;
        this->arr = new T[this->capacity];
        for (int i = 0; i < this->_size; i++) {
            this->arr[i] = other.arr[i];
        }
    }
    return *this;
}

template<class T>
T &Vector<T>::operator[](int index) {
    return this->arr[index];
}

template<class T>
void Vector<T>::resize(int _capacity) {
    this->_size = _capacity;
    if (_capacity > 0) {
        this->capacity = _capacity;
        T* temp = new T[this->capacity];
        for (int i = 0; i < this->_size; i++) {
            temp[i] = this->arr[i];
        }
        delete[] this->arr;
        this->arr = temp;
    }
}

template<class T>
void Vector<T>::clear() {
    this->_size = 0;
}

template<class T>
void Vector<T>::erase(int index) {
    if (index >= 0 && index < this->_size) {
        for (int i = index; i < this->_size - 1; i++) {
            this->arr[i] = this->arr[i + 1];
        }
        this->_size--;
    }
}

template<class T>
void Vector<T>::insert(int index, T data) {
    if (index >= 0 && index <= this->_size) {
        if (this->_size >= this->capacity) {
            this->capacity *= 2;
            T* temp = new T[this->capacity];
            for (int i = 0; i < this->_size; i++) {
                temp[i] = this->arr[i];
            }
            delete[] this->arr;
            this->arr = temp;
        }
        for (int i = this->_size; i > index; i--) {
            this->arr[i] = this->arr[i - 1];
        }
        this->arr[index] = data;
        this->_size++;
    }
}

template<class T>
void Vector<T>::pop_back() {
    if (this->_size > 0) {
        this->_size--;
    }
}

template<class T>
void Vector<T>::push_back(T data) {
    if (this->_size >= this->capacity) {
        this->capacity *= 2;
        T* temp = new T[this->capacity];
        for (int i = 0; i < this->_size; i++) {
            temp[i] = this->arr[i];
        }
        delete[] this->arr;
        this->arr = temp;
    }
    this->arr[this->_size] = data;
    this->_size++;
}

template<class T>
Vector<T>::Vector(const Vector<T> &other) {
    this->capacity = other.capacity;
    this->_size = other._size;
    this->arr = new T[this->capacity];
    for (int i = 0; i < this->_size; i++) {
        this->arr[i] = other.arr[i];
    }
}

template<class T>
Vector<T>::~Vector() {
    delete[] this->arr;
}

template<class T>
Vector<T>::Vector(int capacity) {
    this->capacity = capacity;
    this->_size = capacity;
    this->arr = new T[this->capacity];
}

template<class T>
Vector<T>::Vector() {
    this->capacity = 10;
    this->_size = 0;
    this->arr = new T[this->capacity];
}

#endif //VISUALGO_CS162_VECTOR_H
