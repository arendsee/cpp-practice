// This is my own attempt at implementing subcommands

#include <iostream>
using std::cout;
using std::cerr;

#include <string>
using std::string;

#include "optionparser.h"

#define SHIFT argc -= 1; argv += 1;

#define BOILERPLATE                                                      \
    if (argc == 0) {                                                     \
        option::printUsage(cout, usage);                                 \
        exit(EXIT_FAILURE);                                              \
    }                                                                    \
                                                                         \
    option::Stats  stats(usage, argc, argv);                             \
    option::Option options[stats.options_max], buffer[stats.buffer_max]; \
    option::Parser parse(usage, argc, argv, options, buffer);            \
                                                                         \
    if (parse.error())                                                   \
        exit(EXIT_FAILURE);                                              \
                                                                         \
    if (options[HELP]) {                                                 \
        option::printUsage(cout, usage);                                 \
        exit(EXIT_SUCCESS);                                              \
    }                                                                    \

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

    BOILERPLATE

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

    BOILERPLATE

    if(options[SCREAM]){
        cout << "Ahhhhahhahhh\n";
    } else {
        cout << "Doing bar\n";
    }

    cout << "Doing bar\n";
}

int main(int argc, char** argv)
{
    SHIFT

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

    BOILERPLATE

    if (options[VERSION]) {
        cout << "Version 0\n";
        exit(EXIT_SUCCESS);
    }

    SHIFT 

    string subcommand(parse.nonOption(0));

    if(subcommand == "foo"){
        subcommand_foo(argc, argv);
    }
    else if(subcommand == "bar"){
        subcommand_bar(argc, argv);
    }
    else {
        cerr << "Failed to parse arguments, subcommand '" << parse.nonOption(0) << "' is not defined\n\n";
        option::printUsage(cout, usage);
    }

}

#undef BOILERPLATE
