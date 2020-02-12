#pragma once
#include "column.h"
/*************************************************************************
 * BoolColumn::
 * Holds int values.
 */
class BoolColumn : public Column {
 public:
  BoolColumn() {

  }

  BoolColumn(bool n, ...) {

  }

  int get(size_t idx) {
    return 0;
  }

  BoolColumn* as_bool() {
      
  }

  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val) {

  }

  size_t size() {
      return 0;
  }

};