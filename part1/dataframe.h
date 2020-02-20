#pragma once
#include "column.h"
#include "Schema.h"
#include "Rower.h"
#include "array.h"
#include "object.h"


/****************************************************************************
 * DataFrame::
 *
 * A DataFrame is table composed of columns of equal length. Each column
 * holds values of the same type (I, S, B, F). A dataframe has a schema that
 * describes it.
 */
class DataFrame : public Object {
 public:
  Schema* schema;
  Array* arr_col;
 
  /** Create a data frame with the same columns as the given df but with no rows or rownmaes */
  DataFrame(DataFrame& df) {
    schema = new Schema(df.get_schema());
    arr_col = new Array();
    for(int i = 0; i < df.nrows(); i++) {

      Row* temp_row = new Row(*this->schema);
      // Build temp_row based on our arr_col
      for(int row_i = 0; row_i < temp_row->width(); row_i++) {
        char t = temp_row->col_type(row_i);
        if (t == 'B') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(df.arr_col->get(i))->as_bool()->get(row_i));
        } else if (t == 'I') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(df.arr_col->get(i))->as_int()->get(row_i));
        } else if (t == 'F') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(df.arr_col->get(i))->as_float()->get(row_i));
        } else if (t == 'S') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(df.arr_col->get(i))->as_string()->get(row_i));
        }
      }
      this->add_row(*temp_row);
    }
  }
 
  /** Create a data frame from a schema and columns. All columns are created
    * empty. */
  DataFrame(Schema& schema) {
    this->schema = new Schema(schema);
    this->arr_col = new Array();
    for (int i = 0; i < schema.width(); i++) {
      char t = schema.col_type(i);
        if (t == 'B') {
          this->arr_col->push(new BoolColumn());
        } else if (t == 'I') {
          this->arr_col->push(new IntColumn());
        } else if (t == 'F') {
          this->arr_col->push(new FloatColumn());
        } else if (t == 'S') {
          this->arr_col->push(new StringColumn());
        }

    }
  }
 
  /** Returns the dataframe's schema. Modifying the schema after a dataframe
    * has been created in undefined. */
  Schema& get_schema() {
    return *this->schema;
  }
 
  /** Adds a column this dataframe, updates the schema, the new column
    * is external, and appears as the last column of the dataframe, the
    * name is optional and external. A nullptr colum is undefined. */
  void add_column(Column* col, String* name) {
    this->schema->add_column(col->get_type(), name);
    arr_col->push(col);
  }
 
  /** Return the value at the given column and row. Accessing rows or
   *  columns out of bounds, or request the wrong type is undefined.*/
  int get_int(size_t col, size_t row) {
    Column* c = dynamic_cast<Column*>(arr_col->get(col));
    IntColumn* i = c->as_int();
    int ret = i->get(row);
    return ret;
  }

  bool get_bool(size_t col, size_t row) {
    return dynamic_cast<Column*>(arr_col->get(col))->as_bool()->get(row);
  }

  float get_float(size_t col, size_t row) {
    return dynamic_cast<Column*>(arr_col->get(col))->as_float()->get(row);
  }

  String* get_string(size_t col, size_t row) {
    return dynamic_cast<Column*>(arr_col->get(col))->as_string()->get(row);
  }
 
  /** Return the offset of the given column name or -1 if no such col. */
  int get_col(String& col) {
    return schema->col_idx(col.c_str());
  }
 
  /** Return the offset of the given row name or -1 if no such row. */
  int get_row(String& col) {
      return schema->row_idx(col.c_str());
  }
 
  /** Set the value at the given column and row to the given value.
    * If the column is not  of the right type or the indices are out of
    * bound, the result is undefined. */
  void set(size_t col, size_t row, int val) {
    dynamic_cast<Column*>(arr_col->get(col))->as_int()->set(row, val);
  }

  void set(size_t col, size_t row, bool val) {
    dynamic_cast<Column*>(arr_col->get(col))->as_bool()->set(row, val);
  }

  void set(size_t col, size_t row, float val) {
    dynamic_cast<Column*>(arr_col->get(col))->as_float()->set(row, val);
  }

  void set(size_t col, size_t row, String* val) {
   dynamic_cast<Column*>(arr_col->get(col))->as_string()->set(row, val);
  }
 
  /** Set the fields of the given row object with values from the columns at
    * the given offset.  If the row is not form the same schema as the
    * dataframe, results are undefined.
    */
  void fill_row(size_t idx, Row& row) {
    for(int i = 0; i < this->schema->width(); i++) {
      char t = row.col_type(i);
      if (t == 'B') {
        dynamic_cast<Column*>(arr_col->get(i))->as_bool()->set(idx, row.get_bool(i));
      } else if (t == 'I') {
        dynamic_cast<Column*>(arr_col->get(i))->as_int()->set(idx, row.get_int(i));
      } else if (t == 'F') {
        dynamic_cast<Column*>(arr_col->get(i))->as_float()->set(idx, row.get_float(i));
      } else if (t == 'S') {
        dynamic_cast<Column*>(arr_col->get(i))->as_string()->set(idx, row.get_string(i));
      }
    }
  }
 
  /** Add a row at the end of this dataframe. The row is expected to have
   *  the right schema and be filled with values, otherwise undedined.  */
  void add_row(Row& row) {
    for(int i = 0; i < arr_col->length(); i++) {
      char t = row.col_type(i);
      if (t == 'B') {
        dynamic_cast<Column*>(arr_col->get(i))->push_back(row.get_bool(i));
      } else if (t == 'I') {
        dynamic_cast<Column*>(arr_col->get(i))->push_back(row.get_int(i));
      } else if (t == 'F') {
        dynamic_cast<Column*>(arr_col->get(i))->push_back(row.get_float(i));
      } else if (t == 'S') {
        dynamic_cast<Column*>(arr_col->get(i))->push_back(row.get_string(i));
      }
    }
    this->schema->add_row(new String(""));
    
  }
 
  /** The number of rows in the dataframe. */
  size_t nrows() {
    return this->schema->length();
  }
 
  /** The number of columns in the dataframe.*/
  size_t ncols() {
    return this->schema->width();
  }
 
  /** Visit rows in order */
  void map(Rower& r) {
    for (int row = 0; row < this->nrows(); row++) {
      Row* temp_row = new Row(*this->schema);

      // Build temp_row based on our arr_col
      for(int col_i = 0; col_i < temp_row->width(); col_i++) {
        char t = temp_row->col_type(col_i);
        if (t == 'B') {
          temp_row->set(col_i, 
            dynamic_cast<Column*>(arr_col->get(col_i))->as_bool()->get(row));
        } else if (t == 'I') {
          IntColumn* i = dynamic_cast<Column*>(arr_col->get(col_i))->as_int();
          int set_val = i->get(row);

          temp_row->set(col_i, set_val);
            // dynamic_cast<Column*>(arr_col->get(row_i))->as_int()->get(row));
        } else if (t == 'F') {
          temp_row->set(col_i, 
            dynamic_cast<Column*>(arr_col->get(col_i))->as_float()->get(row));
        } else if (t == 'S') {
          temp_row->set(col_i, 
            dynamic_cast<Column*>(arr_col->get(col_i))->as_string()->get(row));
        }
      }
      r.accept(*temp_row);
      // Since temp_row does not actually update our dataframe
      // we have to load back in the items that were just updated via 
      // our r.accept call
      this->fill_row(row, *temp_row);
      delete temp_row;
    }
  }
<<<<<<< HEAD

  void pmap_range(int start, int end, Rower& r) { 

    unsigned int start_clock = clock();

    std::cout << "Start pmap_range start from " << start << ": " << clock()-start_clock << std::endl;

    for (int row = start; row < end; row++) {
      Row* temp_row = new Row(*this->schema);
      // temp_rows[row] = temp_row;

      // Build temp_row based on our arr_col
      for(int col_i = 0; col_i < temp_row->width(); col_i++) {
        char t = temp_row->col_type(col_i);
        if (t == 'B') {
          temp_row->set(col_i, 
            dynamic_cast<Column*>(arr_col->get(col_i))->as_bool()->get(row));
        } else if (t == 'I') {
          IntColumn* i = dynamic_cast<Column*>(arr_col->get(col_i))->as_int();
          int set_val = i->get(row);

          temp_row->set(col_i, set_val);
            // dynamic_cast<Column*>(arr_col->get(row_i))->as_int()->get(row));
        } else if (t == 'F') {
          temp_row->set(col_i, 
            dynamic_cast<Column*>(arr_col->get(col_i))->as_float()->get(row));
        } else if (t == 'S') {
          temp_row->set(col_i, 
            dynamic_cast<Column*>(arr_col->get(col_i))->as_string()->get(row));
        }
      }
      // if(row % 100 == 0)
      //   printf("At row = %d\n", row);
      r.accept(*temp_row);
      this->fill_row(row, *temp_row);
      delete temp_row;

    }
    std::cout << "End pmap_range start from " << start << ": " << clock()-start_clock << std::endl;

  }

  /** Visit rows in order */
  void pmap(Rower& r) {
    //End: 8235513
    //End: 21113917
    const int TC = 8;
    std::thread* threads[TC];
    Row* temp_rows[this->nrows()];

    unsigned int start = clock();

    // df->print();
    std::cout << "Start: " << clock()-start << std::endl;

    for (int i = 0; i < TC; i ++) {
      int s_i = (i * this->nrows())/TC;
      int e_i = ((i + 1) * this->nrows())/TC;
      debug_printf("Starting thread: %d at t = %d : Start = %d, End = %d\n", i, clock()-start, s_i, e_i);
      threads[i] = new std::thread([&r, s_i, e_i, this] { 
        this->pmap_range ( s_i, e_i, r );
      });
    }
    

    for(int i = 0; i < TC; i++) {
      threads[i]->join();
      debug_printf("Closing thread: %d at t = %d\n", i, clock()-start);
      // this->fill_row(i, *temp_rows[i]);
    }
  }
=======
 
>>>>>>> 184d1d7f1d6f90d19323c3776cc51d9fba83660a
  /** Create a new dataframe, constructed from rows for which the given Rower
    * returned true from its accept method. */
  DataFrame* filter(Rower& r) {
    DataFrame* copy = new DataFrame(*this->schema);
    for (int row = 0; row < this->nrows(); row++) {
      Row* temp_row = new Row(*this->schema);
      // Build temp_row based on our arr_col
      for(int row_i = 0; row_i < temp_row->width(); row_i++) {
        char t = temp_row->col_type(row_i);
        if (t == 'B') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_bool()->get(row_i));
        } else if (t == 'I') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_int()->get(row_i));
        } else if (t == 'F') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_float()->get(row_i));
        } else if (t == 'S') {
          temp_row->set(row_i, 
            dynamic_cast<Column*>(arr_col->get(row))->as_string()->get(row_i));
        }
      }
      if(r.accept(*temp_row)) {
        copy->add_row(*temp_row);
      }
    }
    return copy;
  }
 
  /** Print the dataframe in SoR format to standard output. */
  void print() {

    //HEaders
    for(int i = 0; i < this->schema->width(); i++) {
      printf("<%s>", this->schema->header_strings->get(i)->c_str());
    }
    std::cout << std::endl;

    //Body
    for(int j = 0; j < this->schema->length(); j++) {
      for(int i = 0; i < this->schema->width(); i++) {
        char t = this->schema->col_type(i);
        std::cout << '<';
        if (t == 'B') {
          std::cout << dynamic_cast<Column*>(arr_col->get(i))->as_bool()->get(j);
        } else if (t == 'I') {
          std::cout << dynamic_cast<Column*>(arr_col->get(i))->as_int()->get(j);
        } else if (t == 'F') {
          std::cout << dynamic_cast<Column*>(arr_col->get(i))->as_float()->get(j);
        } else if (t == 'S') {
          std::cout << '"' << dynamic_cast<Column*>(arr_col->get(i))->as_string()->get(j)->c_str() << '"';
        }
        std::cout << '>';
      }
      std::cout << std::endl;
    }
  }
};