#pragma once
#include "column.h"
#include "primitive_types_cwc.h"
/*************************************************************************
 * FloatColumn::
 * Holds int values.
 */
class FloatColumn : public Column {
 public:
  FloatColumn() {
    this->type = 'F';
    this->col_data = new Array();
  }

  FloatColumn(int n, ...) {
    col_data = new Array();
    this->type = 'F';
    va_list vl;
    va_start(vl,n);

    for (int i=0;i<n;i++)
    {
      float g = va_arg(vl, float);
      debug_printf("pushing %f \n", g);

      col_data->push(new FloatCWC(g));
      debug_printf("pushing %f \n", dynamic_cast<FloatCWC*>(this->col_data->get(i))->f);
    }
    va_end(vl);
  }

  float get(size_t idx) {
    return dynamic_cast<FloatCWC*>(this->col_data->get(idx))->f;
  }

  FloatColumn* as_float() {
    return this;
  }

  /** Set value at idx. An out of bound idx is undefined.  */
  void set(size_t idx, int val) {
    dynamic_cast<FloatCWC*>(this->col_data->get(idx))->f = val;
  }

  size_t size() {
      return this->col_data->length();
  }

  virtual void push_back(float val) {
    this->col_data->push(new FloatCWC(val));
  }

};