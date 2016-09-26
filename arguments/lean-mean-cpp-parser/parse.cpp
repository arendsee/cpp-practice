// This is my own attempt at implementing subcommands

#include <iostream>
using std::cout;
using std::cerr;

#include <string>
using std::string;

#include "optionparser.h"

void subcommand_foo(int argc, char* argv[])
{
    enum  optionIndex { UNKNOWN, HELP, VERSION };
    const option::Descriptor usage[] = {
        {
            UNKNOWN, 0, "", "", option::Arg::None,
            "USAGE: dofoobar foo [options]"
        },
        {
            HELP, 0, "h", "help", option::Arg::None,
            "  -h, --help \tPrint usage and exit."
        },
        {
            UNKNOWN, 0, "", "", option::Arg::None,
            "\nExamples:\n"
            "  dofoobar foo -h\n"
            "  dofoobar foo --super-fast\n"
        },
        {0,0,0,0,0,0}
    };

    // If no arguments given, print help
    if (argc == 0) {
        option::printUsage(cout, usage);
        exit(EXIT_FAILURE);
    }

    // Prepare parsing of base (help, version, or subcommand)
    // This considers only the first argument
    option::Stats  stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);

    if (parse.error())
        exit(EXIT_FAILURE);

    if (options[HELP]) {
        option::printUsage(cout, usage);
        exit(EXIT_SUCCESS);
    }

    cout << "Doing foo\n";
}

void subcommand_bar(int argc, char* argv[])
{
    enum  optionIndex { UNKNOWN, HELP, VERSION, SCREAM };
    const option::Descriptor usage[] = {
        {
            UNKNOWN, 0, "", "", option::Arg::None,
            "USAGE: dofoobar bar [options]"
        },
        {
            HELP, 0, "h", "help", option::Arg::None,
            "  -h, --help \tPrint usage and exit."
        },
        {
            SCREAM, 0, "s", "scream", option::Arg::None,
            "  -s, --scream \tScream and exit."
        },
        {
            UNKNOWN, 0, "", "", option::Arg::None,
            "\nExamples:\n"
            "  dofoobar bar -h\n"
        },
        {0,0,0,0,0,0}
    };

    // If no arguments given, print help
    if (argc == 0) {
        option::printUsage(cout, usage);
        exit(EXIT_FAILURE);
    }

    // Prepare parsing of base (help, version, or subcommand)
    // This considers only the first argument
    option::Stats  stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);

    if (parse.error())
        exit(EXIT_FAILURE);

    if (options[HELP]) {
        option::printUsage(cout, usage);
        exit(EXIT_SUCCESS);
    }

    if(options[SCREAM]){
        cout << "Ahhhhahhahhh\n";
    } else {
        cout << "Doing bar\n";
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv)
{

    enum  optionIndex { UNKNOWN, HELP, VERSION };
    const option::Descriptor usage[] = {
        {
            UNKNOWN, 0, "", "", option::Arg::None,
            "USAGE: dofoobar [-hv] subcommand [options]"
        },
        {
            HELP, 0, "h", "help", option::Arg::None,
            "  -h, --help \tPrint usage and exit."
        },
        {
            VERSION, 0, "v", "version", option::Arg::None,
            "  -v, --version \tPrint version and exit."
        },
        {
            UNKNOWN, 0, "", "", option::Arg::None,
            "Subcommands:\n"
            "  foo - do foo\n"
            "  bar - do bar"
        },
        {
            UNKNOWN, 0, "", "", option::Arg::None,
            "\nExamples:\n"
            "  dofoobar -h\n"
            "  dofoobar -v\n"
            "  dofoobar foo -h\n"
        },
        {0,0,0,0,0,0}
    };

    // If no arguments given, print help
    if (argc == 1) {
        option::printUsage(cout, usage);
        exit(EXIT_FAILURE);
    }

    // Prepare parsing of base (help, version, or subcommand)
    // This considers only the first argument
    option::Stats  stats(usage, 1, argv+1);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, 1, argv+1, options, buffer);

    if (parse.error())
        exit(EXIT_FAILURE);

    if (options[HELP]) {
        option::printUsage(cout, usage);
        exit(EXIT_SUCCESS);
    }

    if (options[VERSION]) {
        cout << "Version 0\n";
        exit(EXIT_SUCCESS);
    }

    string subcommand(parse.nonOption(0));


    if(subcommand == "foo"){
        subcommand_foo(argc - 2, argv + 2);
    }

    else if(subcommand == "bar"){
        subcommand_bar(argc - 2, argv + 2);
    }

    else{
        cerr << "Failed to parse arguments\n\n";
        option::printUsage(cout, usage);
    }
}
