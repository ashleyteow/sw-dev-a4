#include "dataframe.h"

/**
 * Example
 * 
 *            | Population (int) | Tax rate (f) | Football team (s) | East Coast (b)
 * ---------- | --------------------------------------------------------------------
 * Chicago    | 2700000          | .0625        | Null              | False
 * New York   | 8600000          | .0400        | Patriots          | False
 * Boston     | 0685000          | .0625        | Giants            | True
 * San Fran   | 0884000          | .0850        | 49ers  
 * 
 */    


DataFrame* generate_city_data_frame() {
    Schema schema("IFSB");
    DataFrame* df = new DataFrame(schema);
    
    
}



