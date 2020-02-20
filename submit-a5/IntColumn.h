#pragma once
#include "column.h"
#include "primitive_types_cwc.h"
/*************************************************************************
 * IntColumn::
 * Holds int values.
 */
class IntColumn : public Column {
 public:
  IntColumn() {
    this->type = 'I';
    col_data = new Array();
  }

  IntColumn(int n, ...) {
    col_data = new Array();
    this->type = 'I';
    va_list vl;
    va_start(vl,n);

    for (int i=0;i<n;i++)
    {
      int val = va_arg(vl, int);
      debug_printf("%d\n", val);
      debug_printf("col_length = %d\n", col_data->length());
      col_data->push(new IntCWC(val));
      debug_printf("col_data[i] = %d\n", dynamic_cast<IntCWC*>(col_data->get(i))->i);

    }
    va_end(vl);

  }

  int get(size_t idx) {
    return dynamic_cast<IntCWC*>(this->col_data->get(idx))->i;
  }

  IntColumn* as_int() {
    return this;
  }

  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val) {
    dynamic_cast<IntCWC*>(this->col_data->get(idx))->i = val;
  }

  size_t size() {
      return this->col_data->length();
  }

  virtual void push_back(int val) {
    this->col_data->push(new IntCWC(val));
  }

};