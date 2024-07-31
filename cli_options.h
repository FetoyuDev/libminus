#ifndef CLI_OPTIONS_H
#define CLI_OPTIONS_H

#include <stdbool.h>
#include <stddef.h>  // For size_t

typedef struct {
    const char *name;
    bool has_arg;
} CLIOption;

void cli_options_init(const CLIOption *options, size_t count);
bool cli_options_parse(int argc, char *argv[]);
bool cli_option_provided(const char *option_name);
const char* cli_option_arg(const char *option_name);
void cli_options_cleanup();

#endif // CLI_OPTIONS_H
