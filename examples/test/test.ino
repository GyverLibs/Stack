#include "Stack.h"

void test1() {
  Stack<char> st1;
  st1.push('a');
  st1.push('b');
  st1.push('c');
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
}

void test2() {
  Stack<char> st1;
  st1.push('a');
  st1.push('b');
  st1.push('c');
  st1.push('d');
  st1.push('e');

  StackT<char, 5> st2;
  st2.shift('1');
  st2.shift('2');
  st2.shift('3');
  st2.shift('4');
  st2.shift('5');

  st1 += st2;
  for (int i = 0; i < st1.length(); i++) Serial.print(st1[i]);
  Serial.println();

  st1.insert(0, '$');
  st1.insert(st1.length(), '#');

  for (int i = 0; i < st1.length(); i++) Serial.print(st1[i]);
  Serial.println();

  st1.remove(0);
  st1.remove(-1);
  st1.insert(5, '_');

  for (int i = 0; i < st1.length(); i++) Serial.print(st1[i]);
  Serial.println();

  st1.remove(5);

  for (int i = 0; i < st1.length(); i++) Serial.print(st1[i]);
}

void setup() {
  Serial.begin(115200);
  test1();
  test2();
}

void loop() {
}