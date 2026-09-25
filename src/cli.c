#include "cli.h"
#include "file_ops.h"
#include "logger.h"

#include <stdio.h>
#include <string.h>

#define SYNCFORGE_VERSION "0.1.0 (Phase 2 - file copier)"

static void print_usage(const char *prog_name) {
    printf("SyncForge - Linux file synchronization utility\n\n");
    printf("Usage:\n");
    printf("  %s copy <source-file> <destination-file>\n", prog_name);
    printf("  %s --help\n", prog_name);
    printf("  %s --version\n", prog_name);
    printf("\n");
    printf("Note: scan/compare/sync/verify commands arrive in later phases.\n");
    printf("See docs/ROADMAP.md for the full build plan.\n");
}

static int cmd_copy(const char *src, const char *dest) {
    log_info("Copying %s -> %s", src, dest);

    FileOpResult result = copy_file(src, dest);

    if (result != FOP_OK) {
        log_error("Copy failed: %s", file_op_result_str(result));
        return 1;
    }

    log_info("Copy completed successfully.");
    return 0;
}

int cli_run(int argc, char **argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "--help") == 0 || strcmp(command, "-h") == 0) {
        print_usage(argv[0]);
        return 0;
    }

    if (strcmp(command, "--version") == 0) {
        printf("syncforge %s\n", SYNCFORGE_VERSION);
        return 0;
    }

    if (strcmp(command, "copy") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s copy <source-file> <destination-file>\n", argv[0]);
            return 1;
        }
        return cmd_copy(argv[2], argv[3]);
    }

    fprintf(stderr, "Unknown command: %s\n\n", command);
    print_usage(argv[0]);
    return 1;
}