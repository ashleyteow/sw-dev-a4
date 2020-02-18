#pragma once

#include "object.h"


/**
 * Creating our own primitive data type so that we can
 * use our array class to push our bools too.
 */ 
class BoolCWC : public Object {
public:
  bool b;
  BoolCWC(bool b) {
    this->b = b;
  }

  bool equals(Object* that) {
    return this->b == dynamic_cast<BoolCWC*>(that)->b;
  }
};

/**
 * Creating our own primitive data type so that we can
 * use our array class to push our bools too.
 */ 
class IntCWC : public Object {
public:
  int i;
  IntCWC(int i) {
    this->i = i;
  }

  bool equals(Object* that) {
    return this->i == dynamic_cast<IntCWC*>(that)->i;
  }
};

/**
 * Creating our own primitive data type so that we can
 * use our array class to push our bools too.
 */ 
class FloatCWC : public Object {
public:
  float f;
  FloatCWC(float f) {
    this->f = f;
  }

  bool equals(Object* that) {
    return this->f == dynamic_cast<FloatCWC*>(that)->f;
  }
};
