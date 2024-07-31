#include <stdio.h>
#include "cli_options.h"

int main(int argc, char *argv[]) {
    CLIOption options[] = {
        {"help", false},
        {"version", false},
        {"file", true}
    };

    cli_options_init(options, sizeof(options) / sizeof(options[0]));

    if (!cli_options_parse(argc, argv)) {
        return 1;
    }

    if (cli_option_provided("help")) {
        printf("Usage: program [options]\n");
        printf("  --help      Show this help message\n");
        printf("  --version   Show the version\n");
        printf("  --file      Specify the file\n");
    }

    if (cli_option_provided("version")) {
        printf("Version 1.0\n");
    }

    if (cli_option_provided("file")) {
        const char *file_arg = cli_option_arg("file");
        if (file_arg) {
            printf("File specified: %s\n", file_arg);
        }
    }

    cli_options_cleanup();
    return 0;
}
