#pragma once
#include "column.h"
#include "primitive_types_cwc.h"



/*************************************************************************
 * BoolColumn::
 * Holds int values.
 */
class BoolColumn : public Column {
 public:
  BoolColumn() {
    this->type = 'B';
    this->col_data = new Array();
  }

  BoolColumn(int n, ...) {
    col_data = new Array();
    this->type = 'B';
    va_list vl;
    va_start(vl,n);

    for (int i=0;i<n;i++)
    {
      col_data->push(new BoolCWC(va_arg(vl, bool)));
      debug_printf("col_length = %d\n", col_data->length());
    }
    va_end(vl);
  }

  bool get(size_t idx) {
    return dynamic_cast<BoolCWC*>(this->col_data->get(idx))->b;
  }

  BoolColumn* as_bool() {
    return this;
  }

  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, bool val) {
    dynamic_cast<BoolCWC*>(this->col_data->get(idx))->b = val;
  }

  size_t size() {
      return this->col_data->length();
  }

  virtual void push_back(bool val) {
    this->col_data->push(new BoolCWC(val));
  }

};