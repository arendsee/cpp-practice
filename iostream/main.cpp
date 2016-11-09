#include "stream.h"

int main(int argc, char * argv[]){

    int exit_status = 0;
    if(argc > 1){
        exit_status += write_file_as_hex(argc, argv);

        std::ifstream f(argv[1]);
        if(f){
            exit_status += read_table_into_variables(f);
        } else {
            std::cerr << "Failed to open file\n";
        }
    }

    return exit_status;
}
