#include "stream.h"

int write_file_as_hex(int argc, char* argv[]){
    if(argc < 2){
        std::cerr << "Please provide a filename\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if(! file){
        std::cerr << "Failed to open file '" << argv[1] << "'\n";
        return 1;
    }

    std::cout << "file.good() == " << file.good() << "\n";
    std::cout << "file.bad()  == " << file.bad()  << "\n";
    std::cout << "file.fail() == " << file.fail() << "\n";
    std::cout << "file.eof()  == " << file.eof()  << "\n";

    char c;
    for(int i = 0; ! file.eof(); i++, file >> c){
        std::cout << std::hex << (int)c << " ";
        if(i % 16 == 0){
            std::cout << "\n";
        }
    }

    std::cout << "\n";

    return 0;
}

int read_table_into_variables(std::ifstream& f){
    std::string name;
    std::string age;
    std::string sign;

    std::string line;
    while(std::getline(f, line)){

        // convert a string to a stringstream 
        std::stringstream row(line);

        // splits on space
        // NOTE: silent failure
        row >> name >> age >> sign;

        std::cout << name << age << sign << "\n";
    }

    return 1;
}
