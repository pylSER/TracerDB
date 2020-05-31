//
// Created by peiyulin on 2020/5/30.
//
#include "handle.h"
#include <iostream>

void test();
int main() { test(); }

void test() {
  using namespace std;
  Handle* h = new Handle("overwatch");


  bool res = h->set_key("tank", "roadhog");
  res = h->set_key("c", "genji");
  res = h->set_key("healing", "mercy");


  string value = h->get_key("c");
  cout << "result c:" << value << endl;

  value = h->get_key("tank");
  cout << "result tank:" << value << endl;

  value = h->get_key("healing");
  cout << "result healing:" << value << endl;


  res = h->set_key("healing", "ana");
  value = h->get_key("healing");
  cout << "result healing:" << value << endl;
}