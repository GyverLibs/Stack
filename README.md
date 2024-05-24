[![latest](https://img.shields.io/github/v/release/GyverLibs/Stack.svg?color=brightgreen)](https://github.com/GyverLibs/Stack/releases/latest/download/Stack.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/Stack.svg)](https://registry.platformio.org/libraries/gyverlibs/Stack)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/Stack?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# Stack
Библиотека для удобной работы с массивами любого типа данных типа std::vector или массивов в js
- Статическая и динамическая реализация (с реаллокацией)
- Добавление и получение с обоих концов, вставка и удаление

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Установка](#install)
- [Баги и обратная связь](#feedback)

<a id="init"></a>

## Инициализация
```cpp
// внешний буфер
StackExt<typename T>();
StackExt<typename T>(T* arr, size_t capacity, size_t length = 0);
StackUniqExt<typename T>();
StackUniqExt<typename T>(T* arr, size_t capacity, size_t length = 0);

// динамический буфер
Stack<typename T>(size_t size = 0);
StackUniq<typename T>(size_t size = 0);

// статический буфер
StackT<typename T, size_t size>();
StackUniqT<typename T, size_t size>();

// Uniq - массив с уникальными данными, при добавлении проверяется наличие элемента
```

<a id="usage"></a>

## Использование
```cpp
// добавить в конец
bool push(const T& val);
bool operator+=(const T& val);

// получить с конца и удалить
T pop();

// прочитать с конца не удаляя
T peek();

// добавить в начало
bool shift(const T& val);

// получить с начала и удалить
T unshift();

// прочитать с начала не удаляя
T unpeek();

// удалить элемент. Отрицательный - с конца
bool remove(int idx);

// вставить элемент на индекс (допускается индекс length())
bool insert(int idx, const T& val);

// прибавить другой массив в конец
bool concat(const StackExt<T>& st);
bool operator+=(const StackExt<T>& st);

// заполнить значением (на capacity)
void fill(const T& val);

// инициализировать, вызвать конструкторы (на capacity)
void init();

// очистить (установить длину 0)
void clear();

// есть место для добавления
bool canAdd();

// количество элементов
size_t length();

// вместимость, элементов
size_t capacity();

// получить элемент под индексом. Отрицательный - с конца
T& get(int idx);

// получить элемент под индексом. Отрицательный - с конца
T& operator[](int idx);

// доступ для ручного взаимодействия
T* _buf;
size_t _len;
```

### Дополнительно
```cpp
// только для StackExt и StackUniqExt
// ==================================

// подключить буфер 
void setBuffer(T* arr, size_t capacity, size_t length = 0);

// только для Stack и StackUniq
// ==================================

// зарезервировать память в кол-ве элементов
bool reserve(size_t size);

// только для *Uniq
// ==================================

// позиция элемента (-1 если не найден)
int indexOf(const T& val);

// содержит элемент
bool includes(const T& val);

// удалить по значению (true если элемента нет)
bool removeByVal(const T& val);
```

<a id="example"></a>

## Пример
Остальные примеры смотри в **examples**!
```cpp
Stack<char> st1;
st1.push('a');
st1.push('b');
st1 += 'c';
while (st1.length()) Serial.print(st1.pop()); // cba
Serial.println();

StackT<char, 10> st2;
st2.shift('1');
st2.shift('2');
st2.shift('3');
st2.shift('4');
st2.shift('5');
for (int i = 0; i < st2.length(); i++) Serial.print(st2[i]);  // 54321
Serial.println();

char buf[5];
StackExt<char> st3(buf, 5);
st3.push('a');
st3.push('b');
st3.push('c');
st3.push('d');
st3.push('e');

st2 += st3;
for (int i = 0; i < st2.length(); i++) Serial.print(st2[i]);  // 54321abcde
Serial.println();

Stack<float> st4(3);
st4.fill(3.14);
st4[0] = 1234.56;
for (int i = 0; i < st4.length(); i++) Serial.println(st4[i]);  // 1234.56/3.14/3.14
```

<a id="versions"></a>

## Версии
- v1.0
- v1.0.1 - добавлен move конструктор и move операторы. Добавлен режим уникального стека

<a id="install"></a>

## Установка
- Библиотеку можно найти по названию **Stack** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/Stack/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!

При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
