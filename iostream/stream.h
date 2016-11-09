#ifndef __STREAM_H__
#define __STREAM_H__

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

int write_file_as_hex(int argc, char* arg[]);

int read_table_into_variables(std::ifstream& f);

#endif
