#ifndef SYNCFORGE_FILE_OPS_H
#define SYNCFORGE_FILE_OPS_H

#include <sys/types.h>


typedef enum {
    FOP_OK = 0, 
    FOP_ERR_OPEN_SOURCE,
    FOP_ERR_OPEN_DEST,
    FOP_ERR_READ,
    FOP_ERR_WRITE,
    FOP_ERR_STAT,
    FOP_ERR_MKDIR
} FileOpResult;

/*
 * Copies src_path -> dest_path using a manual open/read/write/close loop
 * (no sendfile()/system() shortcuts -- the point is to implement it).
 * Preserves the source file's permission bits on the newly created file.
 * Overwrites dest_path if it already exists.
 */

FileOpResult copy_file(const char *src_path , const char *dest_path);

/*
 * Recursively creates all directory components of dir_path that don't yet
 * exist (like `mkdir -p`), using mkdir() in a loop over path segments.
 */

FileOpResult make_dirs(const char *fir_path);

/* Returns a human-readable string for a FileOpResult, for logging. */


const char *file_op_result_str(FileOpResult result);

#endif


