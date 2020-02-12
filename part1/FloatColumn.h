#pragma once
#include "column.h"
/*************************************************************************
 * FloatColumn::
 * Holds int values.
 */
class FloatColumn : public Column {
 public:
  FloatColumn() {

  }

  FloatColumn(float n, ...) {

  }

  int get(size_t idx) {
    return 0;
  }

  FloatColumn* as_float() {
      
  }

  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val) {

  }

  size_t size() {
      return 0;
  }

};