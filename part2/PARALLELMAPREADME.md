# Part 2 Readme

have example use-cases of your pmap,

You can use pmap just as a normal map :)


describe your design for your parallel map,

We designed our parallel map to build temp rows and generate a thread for each row. So that each row will have a single thread to map its values too. We also keep an array of rows that will will then call fill rows with on ourdf object

describe how the examples in your parallel_map_examples.cpp file demonstrate that pmap is faster, and

N/A
describe issues that you encountered in implementing your parallel map.
