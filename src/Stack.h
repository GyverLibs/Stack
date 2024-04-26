/*
    Stack - удобный статический или динамический массив для любого типа данных
    Документация:
    GitHub: https://github.com/GyverLibs/Stack

    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
*/

#pragma once
#include <Arduino.h>

// External Static Stack
template <typename T>
class StackExt {
   public:
    StackExt() {}
    StackExt(T* arr, size_t capacity, size_t length = 0) : _arr(arr), _cap(capacity), _len(min(length, capacity)) {}

    // подключить буфер
    void setBuffer(T* arr, size_t capacity, size_t length = 0) {
        _arr = arr;
        _cap = capacity;
        _len = min(length, capacity);
    }

    // добавить в конец
    bool push(const T& val) {
        if (!_fit(_len + 1)) return 0;
        _arr[_len++] = val;
        return 1;
    }

    // добавить в конец
    bool operator+=(const T& val) {
        return push(val);
    }

    // получить с конца и удалить
    T pop() {
        return length() ? _arr[(_len--) - 1] : T();
    }

    // прочитать с конца не удаляя
    T peek() const {
        return length() ? _arr[_len - 1] : T();
    }

    // добавить в начало
    bool shift(const T& val) {
        if (!_fit(_len + 1)) return 0;
        memmove((void*)(_arr + 1), (void*)(_arr), _len * sizeof(T));
        _arr[0] = val;
        _len++;
        return 1;
    }

    // получить с начала и удалить
    T unshift() {
        if (!length()) return T();
        T t = _arr[0];
        _len--;
        memmove((void*)(_arr), (void*)(_arr + 1), _len * sizeof(T));
        return t;
    }

    // прочитать с начала не удаляя
    T unpeek() const {
        return length() ? _arr[0] : T();
    }

    // удалить элемент. Отрицательный - с конца
    bool remove(int idx) {
        if (!length() || idx >= (int)_len || idx < -(int)_len) return 0;

        if (idx < 0) idx += _len;
        memcpy((void*)(_arr + idx), (void*)(_arr + idx + 1), (_len - idx - 1) * sizeof(T));
        _len--;
        return 1;
    }

    // вставить элемент на индекс (допускается индекс length())
    bool insert(int idx, const T& val) {
        if (idx > (int)_len || idx < -(int)_len || !_fit(_len + 1)) return 0;

        if (idx < 0) idx += _len;
        if (idx == 0) return shift(val);
        else if (idx == (int)_len) return push(val);

        memmove((void*)(_arr + idx + 1), (void*)(_arr + idx), (_len - idx) * sizeof(T));
        _arr[idx] = val;
        _len++;
        return 1;
    }

    // прибавить другой массив в конец
    bool concat(const StackExt<T>& st) {
        if (!st.length()) return 1;
        if (!_fit(_len + st._len)) return 0;

        memcpy((void*)(_arr + _len), (void*)(st._arr), st._len * sizeof(T));
        _len += st._len;
        return 1;
    }

    // прибавить другой массив в конец
    bool operator+=(const StackExt<T>& st) {
        return concat(st);
    }

    // заполнить значением (на capacity)
    void fill(const T& val) {
        for (size_t i = 0; i < capacity(); i++) _arr[i] = val;
        _len = _cap;
    }

    // инициализировать, вызвать конструкторы (на capacity)
    void init() {
        fill(T());
    }

    // очистить (установить длину 0)
    void clear() {
        _len = 0;
    }

    // есть место для добавления
    bool canAdd() const {
        return _arr ? (_len < _cap) : 0;
    }

    // количество элементов
    size_t length() const {
        return _arr ? _len : 0;
    }

    // вместимость, элементов
    size_t capacity() const {
        return _arr ? _cap : 0;
    }

    // получить элемент под индексом. Отрицательный - с конца
    T& get(int idx) const {
        if (!length()) return _arr[0];  // !_arr критично
        if (idx >= (int)_len) idx = _len - 1;
        else if (idx < 0) idx = (idx + _len >= 0) ? (idx + _len) : 0;
        return _arr[idx];
    }

    // получить элемент под индексом. Отрицательный - с конца
    T& operator[](int idx) const {
        return get(idx);
    }

    // указатель на масств
    const T* ptr() const {
        return _arr;
    }

   protected:
    T* _arr = nullptr;
    size_t _cap = 0;
    size_t _len = 0;

    bool _fit(size_t size) {
        return (size <= _cap || reserve(size)) && _arr;
    }

    virtual bool reserve(size_t size) {
        return 0;
    }
};

// Dynamic Stack
template <typename T>
class Stack : public StackExt<T> {
   public:
    // зарезервировать память в кол-ве элементов
    Stack(size_t size = 0) {
        if (size) reserve(size);
    }
    Stack(const StackExt<T>& st) {
        _copyFrom(st);
    }
    Stack(const Stack<T>& st) {
        _copyFrom(st);
    }
    ~Stack() {
        if (_arr) free(_arr);
    }

    // зарезервировать память в кол-ве элементов
    bool reserve(size_t cap) {
        if (_cap >= cap) return 1;
        T* arr = (T*)realloc(_arr, cap * sizeof(T));
        if (!arr) return 0;
        _arr = arr;
        _cap = cap;
        return 1;
    }

    void operator=(const StackExt<T>& st) {
        _copyFrom(st);
    }
    void operator=(const Stack<T>& st) {
        _copyFrom(st);
    }

    // есть место для добавления (всегда true)
    bool canWrite() {
        return 1;
    }

   protected:
    using StackExt<T>::_arr;
    using StackExt<T>::_cap;
    using StackExt<T>::_len;

    // копировать из другого массива
    bool _copyFrom(const StackExt<T>& st) {
        if (!st.length() || !reserve(st.length())) {
            _len = 0;
            return 0;
        }
        _len = st.length();
        memcpy((void*)_arr, (void*)st.ptr(), _len);
        return 1;
    }

   private:
    using StackExt<T>::setBuffer;
};

// Static Stack
template <typename T, size_t size>
class StackT : public StackExt<T> {
   public:
    StackT() : StackExt<T>(arr, size) {}

   protected:
    T arr[size];

   private:
    using StackExt<T>::setBuffer;
};