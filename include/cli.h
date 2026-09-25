#ifndef SYNCFORGE_CLI_H
#define SYNCFORGE_CLI_H


/*
 * Parses argv and dispatches to the appropriate command handler.
 * Returns a process exit code (0 = success).
 *
 * Current commands (Phase 2 scope):
 *   syncforge copy <src> <dest>   - copy a single file
 *   syncforge --help / -h        - usage
 *   syncforge --version          - version string
 *
 * scan/compare/sync/verify are added in later phases (see docs/ROADMAP.md).
 */

int cli_run(int argc, char **argv);

#endif /* SYNCFORGE_CLI_H */