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

template <typename T>
class Stack;

// External Static Stack
template <typename T>
class StackExt {
    friend class Stack<T>;

   public:
    StackExt() {}
    StackExt(T* arr, size_t capacity, size_t length = 0) {
        setBuffer(arr, capacity, length);
    }

    // подключить буфер
    void setBuffer(T* arr, size_t capacity, size_t length = 0) {
        _buf = arr;
        _cap = capacity;
        _len = min(length, capacity);
    }

    // добавить в конец
    bool push(const T& val) {
        if (!canAdd(val)) return 0;
        if (!_fit(_len + 1)) return 0;
        _buf[_len++] = val;
        return 1;
    }

    // добавить в конец
    bool operator+=(const T& val) {
        return push(val);
    }

    // получить с конца и удалить
    T pop() {
        return length() ? _buf[(_len--) - 1] : T();
    }

    // прочитать с конца не удаляя
    T peek() const {
        return length() ? _buf[_len - 1] : T();
    }

    // добавить в начало
    bool shift(const T& val) {
        if (!canAdd(val)) return 0;
        if (!_fit(_len + 1)) return 0;
        memmove((void*)(_buf + 1), (void*)(_buf), _len * sizeof(T));
        _buf[0] = val;
        _len++;
        return 1;
    }

    // получить с начала и удалить
    T unshift() {
        if (!length()) return T();
        T t = _buf[0];
        _len--;
        memmove((void*)(_buf), (void*)(_buf + 1), _len * sizeof(T));
        return t;
    }

    // прочитать с начала не удаляя
    T unpeek() const {
        return length() ? _buf[0] : T();
    }

    // удалить элемент. Отрицательный - с конца
    bool remove(int idx) {
        if (!length() || idx >= (int)_len || idx < -(int)_len) return 0;

        if (idx < 0) idx += _len;
        memcpy((void*)(_buf + idx), (void*)(_buf + idx + 1), (_len - idx - 1) * sizeof(T));
        _len--;
        return 1;
    }

    // вставить элемент на индекс (допускается индекс length())
    bool insert(int idx, const T& val) {
        if (!canAdd(val)) return 0;
        if (idx > (int)_len || idx < -(int)_len || !_fit(_len + 1)) return 0;

        if (idx < 0) idx += _len;
        if (idx == 0) return shift(val);
        else if (idx == (int)_len) return push(val);

        memmove((void*)(_buf + idx + 1), (void*)(_buf + idx), (_len - idx) * sizeof(T));
        _buf[idx] = val;
        _len++;
        return 1;
    }

    // прибавить другой массив в конец
    bool concat(const StackExt<T>& st) {
        if (!st.length()) return 1;
        if (!_fit(_len + st._len)) return 0;

        memcpy((void*)(_buf + _len), (void*)(st._buf), st._len * sizeof(T));
        _len += st._len;
        return 1;
    }

    // прибавить другой массив в конец
    bool operator+=(const StackExt<T>& st) {
        return concat(st);
    }

    // заполнить значением (на capacity)
    void fill(const T& val) {
        for (size_t i = 0; i < capacity(); i++) _buf[i] = val;
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
        return _buf ? (_len < _cap) : 0;
    }

    // количество элементов
    size_t length() const {
        return _buf ? _len : 0;
    }

    // вместимость, элементов
    size_t capacity() const {
        return _buf ? _cap : 0;
    }

    // получить элемент под индексом. Отрицательный - с конца
    T& get(int idx) const {
        if (!length()) return _buf[0];  // !_buf критично
        if (idx >= (int)_len) idx = _len - 1;
        else if (idx < 0) idx = (idx + _len >= 0) ? (idx + _len) : 0;
        return _buf[idx];
    }

    // получить элемент под индексом. Отрицательный - с конца
    T& operator[](int idx) const {
        return get(idx);
    }

    operator bool() const {
        return _buf;
    }

    T* _buf = nullptr;
    size_t _len = 0;

   protected:
    size_t _cap = 0;

    bool _fit(size_t size) {
        return (size <= _cap || reserve(size)) && _buf;
    }
    virtual bool reserve(size_t size) {
        return 0;
    }
    virtual bool canAdd(const T& val) {
        return 1;
    }
};

// Static Stack
template <typename T, size_t size>
class StackT : public StackExt<T> {
   public:
    StackT() : StackExt<T>(buffer, size) {}

    T buffer[size];

   private:
    using StackExt<T>::setBuffer;
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
        _copy(st);
    }
    Stack(const Stack<T>& st) {
        _copy(st);
    }
#if __cplusplus >= 201103L
    Stack(StackExt<T>&& st) {
        _copy(st);
    }
    Stack(Stack<T>&& st) {
        _move(st);
    }
#endif
    ~Stack() {
        if (_buf) free(_buf);
    }

    // зарезервировать память в кол-ве элементов
    bool reserve(size_t cap) {
        if (_cap >= cap) return 1;
        T* arr = (T*)realloc(_buf, cap * sizeof(T));
        if (!arr) return 0;
        _buf = arr;
        _cap = cap;
        return 1;
    }

    void operator=(const StackExt<T>& st) {
        _copy(st);
    }
    void operator=(const Stack<T>& st) {
        _copy(st);
    }

#if __cplusplus >= 201103L
    void operator=(StackExt<T>&& st) {
        _copy(st);
    }
    void operator=(Stack<T>&& st) {
        _move(st);
    }
#endif

    // есть место для добавления (всегда true)
    bool canWrite() {
        return 1;
    }

   protected:
    using StackExt<T>::_buf;
    using StackExt<T>::_cap;
    using StackExt<T>::_len;

    void _init() {
        _buf = nullptr;
        _cap = 0;
        _len = 0;
    }
    void _invalidate() {
        if (_buf) free(_buf);
        _init();
    }
    void _copy(const StackExt<T>& st) {
        if (this == &st) return;
        if (!st._buf || !reserve(st._len)) {
            _invalidate();
            return;
        }

        memcpy((void*)_buf, (void*)st._buf, st._len);
        _len = st._len;
    }

#if __cplusplus >= 201103L
    void _move(Stack<T>& st) {
        if (_buf) free(_buf);
        _buf = st._buf;
        _cap = st._cap;
        _len = st._len;
        st._buf = nullptr;
    }
#endif

   private:
    using StackExt<T>::setBuffer;
};

// External Static Stack Uniq
template <typename T>
class StackUniqExt : public StackExt<T> {
   public:
    using StackExt<T>::StackExt;

    // позиция элемента (-1 если не найден)
    int indexOf(const T& val) {
        for (size_t i = 0; i < _len; i++) {
            if (_buf[i] == val) return i;
        }
        return -1;
    }

    // содержит элемент
    bool includes(const T& val) {
        return indexOf(val) != -1;
    }

    // удалить по значению (true если элемента нет)
    bool removeByVal(const T& val) {
        int i = indexOf(val);
        return (i >= 0) ? StackExt<T>::remove(i) : true;
    }

    using StackExt<T>::_len;
    using StackExt<T>::_buf;

   private:
    using StackExt<T>::concat;
    using StackExt<T>::fill;
    using StackExt<T>::init;

   protected:
    bool canAdd(const T& val) {
        return !includes(val);
    }
};

// Static Stack Uniq
template <typename T, size_t size>
class StackUniqT : public StackT<T, size> {
   public:
    using StackT<T, size>::StackT;

    // позиция элемента (-1 если не найден)
    int indexOf(const T& val) {
        for (size_t i = 0; i < _len; i++) {
            if (_buf[i] == val) return i;
        }
        return -1;
    }

    // содержит элемент
    bool includes(const T& val) {
        return indexOf(val) != -1;
    }

    // удалить по значению (true если элемента нет)
    bool removeByVal(const T& val) {
        int i = indexOf(val);
        return (i >= 0) ? StackExt<T>::remove(i) : true;
    }

    using StackExt<T>::_len;
    using StackExt<T>::_buf;

   private:
    using StackExt<T>::concat;
    using StackExt<T>::fill;
    using StackExt<T>::init;

   protected:
    bool canAdd(const T& val) {
        return !includes(val);
    }
};

// Dynamic Stack Uniq
template <typename T>
class StackUniq : public Stack<T> {
   public:
    using Stack<T>::Stack;

    // позиция элемента (-1 если не найден)
    int indexOf(const T& val) {
        for (size_t i = 0; i < _len; i++) {
            if (_buf[i] == val) return i;
        }
        return -1;
    }

    // содержит элемент
    bool includes(const T& val) {
        return indexOf(val) != -1;
    }

    // удалить по значению (true если элемента нет)
    bool removeByVal(const T& val) {
        int i = indexOf(val);
        return (i >= 0) ? StackExt<T>::remove(i) : true;
    }

    using StackExt<T>::_len;
    using StackExt<T>::_buf;

   private:
    using StackExt<T>::concat;
    using StackExt<T>::fill;
    using StackExt<T>::init;

   protected:
    bool canAdd(const T& val) {
        return !includes(val);
    }
};