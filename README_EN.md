This is an automatic translation, may be incorrect in some places. See sources and examples!

# Stack
Library for convenient work with arrays of any type of data type STD :: vector or arrays in js
- Static and dynamic implementation (with reallock)
- Adding and receiving from both ends, insert and removal

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [installation] (# Install)
- [bugs and feedback] (#fedback)

<a id="init"> </a>

## initialization
`` `CPP
// External buffer
Stackext <typeename t> ();
Stackext <typeename t> (t* arr, size_t capacity, size_t length = 0);

// Dynamic buffer
Stack <Typename T> (SIZE_T SIZE = 0);

// Static buffer
Stackt <Typename T, Size_t Size> ();
`` `

<a id="usage"> </a>

## Usage
`` `CPP
// connect the buffer (only for stackext)
VOID SetBuffer (T* Arr, Size_t Capacy, Size_t Length = 0);

// reserve memory in the number of elements (only for Stack)
Bool Reserve (Size_T SIZE);

// Add to the end
Bool Push (const t & val);
Bool Operator+= (Consta T & Val);

// get from the end and delete
T Pop ();

// read from the end without deleting
T peek ();

// Add to the beginning
Bool Shift (const t & val);

// get from the beginning and delete
T Unshift ();

// read from the beginning without deleting
T unpeek ();

// Delete the element.Negative - from the end
Bool Remove (int IDX);

// insert the element to the index (the Length () index is allowed)
Bool Insert (Intx, Const T&D);

// add another array to the end
Bool Concat (Constation Stackext <t> & st);
Bool Operator+= (Const Stackext <t> & ST);

// Fill in the value (on capacity)
VOID Fill (const t & val);

// initialize, call designers (on capacity)
VOID Init ();

// Clean (set length 0)
Void Clear ();

// there is a place to add
Bool Canadd ();

// amount of elements
Size_t Length ();

// capacity, elements
Size_t Capacy ();

// Get an element under the index.Negative - from the end
T&Get (int IDX);

// Get an element under the index.Negative - from the end
T & operator [] (int IDX);

// Mastery pointer
const t* ptr ();
`` `

<a id="EXAMPLE"> </a>

## Example
The rest of the examples look at ** Examples **!
`` `CPP
Stack <Char> ST1;
ST1.push ('A');
ST1.push ('B');
ST1.push ('c');
While (st1.length ()) serial.print (st1.pop ());// CBA
Serial.println ();

Stackt <char, 10> ST2;
ST2.shift ('1');
ST2.shift ('2');
ST2.shift ('3');
ST2.shift ('4');
ST2.shift ('5');
for (int i = 0; i <st2.length (); i ++) serial.print (ST2 [i]);// 54321
Serial.println ();

Char Buf [5];
Stackext <khar> st3 (BUF, 5);
ST3.PUSH ('A');
ST3.PUSH ('B');
ST3.push ('c');
ST3.PUSH ('D');
ST3.push ('E');

ST2 += ST3;
for (int i = 0; i <st2.length (); i ++) serial.print (ST2 [i]);// 54321abcde
Serial.println ();

Stack <float> ST4 (3);
ST4.Fill (3.14);
ST4 [0] = 1234.56;
for (int i = 0; i <st4.length (); i ++) serial.println (ST4 [i]);// 1234.56/3.14/3.14
`` `

<a id="versions"> </a>

## versions
- V1.0

<a id="install"> </a>

## Installation
- The library can be found by the name ** stack ** and installed through the library manager in:
    - Arduino ide
    - aRduino ide v2
    - Platformio
- [download library] (https://github.com/gyverlibs/stack/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, but better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!

When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of thousands of lines, but the minimum code