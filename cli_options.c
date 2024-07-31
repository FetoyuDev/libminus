#include "cli_options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>  // For size_t

static const CLIOption *cli_options = NULL;
static size_t cli_options_count = 0;
static char **cli_argv = NULL;
static int cli_argc = 0;

void cli_options_init(const CLIOption *options, size_t count) {
    cli_options = options;
    cli_options_count = count;
    cli_argv = NULL;
    cli_argc = 0;
}

bool cli_options_parse(int argc, char *argv[]) {
    cli_argc = argc;
    cli_argv = argv;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            bool is_long_option = (argv[i][1] == '-');
            const char *option_name = is_long_option ? argv[i] + 2 : argv[i] + 1;

            for (size_t j = 0; j < cli_options_count; j++) {
                if (strcmp(cli_options[j].name, option_name) == 0) {
                    if (cli_options[j].has_arg) {
                        if (i + 1 < argc) {
                            // Argument storage can be added here
                        } else {
                            fprintf(stderr, "Option '%s' requires an argument.\n", argv[i]);
                            return false;
                        }
                    }
                    break;
                }
            }
        }
    }
    return true;
}

bool cli_option_provided(const char *option_name) {
    for (int i = 1; i < cli_argc; i++) {
        if (cli_argv[i][0] == '-') {
            bool is_long_option = (cli_argv[i][1] == '-');
            const char *name = is_long_option ? cli_argv[i] + 2 : cli_argv[i] + 1;
            if (strcmp(option_name, name) == 0) {
                return true;
            }
        }
    }
    return false;
}

const char* cli_option_arg(const char *option_name) {
    for (int i = 1; i < cli_argc; i++) {
        if (cli_argv[i][0] == '-') {
            bool is_long_option = (cli_argv[i][1] == '-');
            const char *name = is_long_option ? cli_argv[i] + 2 : cli_argv[i] + 1;
            if (strcmp(option_name, name) == 0 && cli_options) {
                if (cli_options[i].has_arg && i + 1 < cli_argc) {
                    return cli_argv[i + 1];
                }
            }
        }
    }
    return NULL;
}

void cli_options_cleanup() {
    // Cleanup if necessary
}
