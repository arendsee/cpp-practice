#include "stream.h"
#include "foo.h"

#include <vector>

int main(int argc, char * argv[]){

    int exit_status = 0;
    if(argc > 1){
        exit_status += write_file_as_hex(argc, argv);

        std::ifstream f(argv[1]);
        if(f){
            std::vector<Foo> foos;
            std::string line;

            std::cout << "\nReading z.tab into Foo objects\n";
            while(std::getline(f, line)){
                std::stringstream row(line); 
                Foo foo;
                if(row >> foo){
                    foos.push_back(foo);
                } else {
                    std::cerr << "Failed to read line:\n" << line << "\n";
                }
            }
            std::cout << "\nWriting Foo objects\n";
            for(size_t i = 0; i < foos.size(); i++){
                std::cout << foos[i];
            }

            f.seekg(0, f.beg);

            std::cout << "\nReading table into variables (but doing nothing)\n";
            exit_status += read_table_into_variables(f);
        } else {
            std::cerr << "Failed to open file\n";
        }
    }

    return exit_status;
}
