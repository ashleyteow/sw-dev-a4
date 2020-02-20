#include <stdio.h>
#include "dataframe.h"
#include "string.h"
#include "Rower.h"
#include <ctime> 
#include <time.h> 


const char* DATA_FILE = "datafile.txt";

// rounds floats to the nearest whole number
// changes birthyear to age 
// adds 1 to each char for string columns
class ComplicatedTaskRower : public Rower {
  public:
  //accept method for the rower object
  virtual bool accept(Row& r) {
    for(int i = 0; i < r.width(); i++) {
      switch (r.col_type(i)) {
        case 'I': {
          for(int j = 0; j < r.get_int(i); j++) {
            for (int k = 0; k < j; k++) {
              // printf("%d", k);
            }
            // printf("%d\n", j);
          }
          // if column is birthyear, set its value to be the user's age
          if (i == 13) {
            r.set(i, 2020 - r.get_int(i));
          }
          if (i == 0) {
            r.set(i, r.get_int(i) / 60);
          }
          break;
        }
        case 'F': {
          // we round floats to the nearest whole number
          int floor = static_cast<int>(r.get_float(i));
          float rounded = static_cast<float>(r.get_float(i) - static_cast<float>(floor) >= 0.5 ? floor + 1 : floor);
          // rounded = rounded * (floor % 100);
          // for (int i = 0; i < rounded; i++) {
          //   floor += rounded;
          // }
          // rounded *= floor;

          r.set(i, static_cast<float>(rounded));
          break;
        }
        case 'S': {
          for (int col = 0; col < r.get_string(i)->size(); col++) {
            r.get_string(i)->cstr_[col] += 1;
          }
        break;
        }
        default:
          break;
      }      
    }
  }
};

// rounds the lat long's in the dataset to the nearest whole number
class SimpleTaskRower : public Rower {
  public:
  //accept method for the rower object
  virtual bool accept(Row& r) {
    for(int i = 0; i < r.width(); i++) {
      switch (r.col_type(i)) {
        case 'F': {
          // we round floats to the nearest whole number
          int floor = static_cast<int>(r.get_float(i));
          r.set(i, static_cast<float>(r.get_float(i) - static_cast<float>(floor) >= 0.5 ? floor + 1 : floor));
          break;
        }
        default:
          break;
      }      
    }
  }
};

/**
 * Generates a data frame based on a header_line in csv format and a column schema
 */ 
DataFrame* create_data_frame(char* header_line, char* col_schema) {
    Schema s("");
    DataFrame* df = new DataFrame(s);

    char *token;
    int col = 0;
    /* get the first token */
    token = strtok(header_line, ",");
    
    /* walk through other tokens */
    while( token != NULL ) {
        char curr_t = col_schema[col];
        if (curr_t == 'I') {
            df->add_column(new IntColumn(), new String(token));
        } else if (curr_t == 'B') {
            df->add_column(new BoolColumn(), new String(token));
        } else if (curr_t == 'F') {
            df->add_column(new FloatColumn(), new String(token));
        } else if (curr_t == 'S') {
            df->add_column(new StringColumn(), new String(token));
        }
        token = strtok(NULL, ",");
        col++;
        // free(token);
    }
    return df;


}

/**
 * reads in a CSV based on a column schema and generates a 
 * DataFrame object from it.
 * 
 * User will need to delete the DataFrame after it is returned.
 */ 
DataFrame* read_in_csv(const char* file, char* col_schema) {    


    FILE *fp;
    debug_printf("file = %s\n",file);
    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Wrong file");
        return NULL;
    }
    size_t len;
    char* line;
    //Header
    getline(&line, &len, fp);
    debug_printf("data = %s\n",line);
    DataFrame* df = create_data_frame(line, col_schema);

    // df->print();

    //Body
    // getline(&line, &len, fp);

    int line_count = 0;
    while (line != NULL && getline(&line, &len, fp) != EOF) {
        Row temp_row(df->get_schema());
        char* token = strtok(line, ",");
        int i= 0;
        while( token != NULL ) {
            if (col_schema[i] == 'I') {
                temp_row.set(i, atoi(token));
            } else if (col_schema[i] == 'F') {
                temp_row.set(i, static_cast<float>(atof(token)));
            } else if (col_schema[i] == 'S') {
                temp_row.set(i, new String(token));
            } else if (col_schema[i] == 'B') {
                temp_row.set(i, atoi(token) > 0);
            }
            token = strtok(NULL, ",");
            i++;
        }
        df->add_row(temp_row);
        if (++line_count % 10000 == 0) {
          printf("Reading in line #%d\n", line_count);
        }
        free(token);
    }
    fclose(fp);
    // // time_t my_time = time(NULL); 
    // auto timenow = 
    //   std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); 
  
    // std::cout << ctime(&timenow) << std::endl; 
    // printf("Start time = %s\n", ctime(&my_time)); 
    unsigned int start = clock();

    // df->print();
    ComplicatedTaskRower r;
    std::cout << "Start: " << clock()-start << std::endl;
    df->pmap(r);
    // std::cout << ctime(&timenow) << std::endl; 
    std::cout << "End: " << clock()-start  << std::endl;
    // printf("Done Mapping time = %s\n", ctime(&my_time)); 
    // df->print();
    // printf("Done Printing time = %s\n", ctime(&my_time)); 

}


int main () {
    read_in_csv(DATA_FILE, "ISSISFFISFFISII");
    return 0;
}