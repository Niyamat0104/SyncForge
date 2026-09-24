#include "file_ops.h"
#include "logger.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define COPY_BUFFER_SIZE 65536
const char *file_op_result_str(FileOpResult result) {
    switch(result) {
        case FOP_OK:  return"OK";
        case FOP_ERR_OPEN_SOURCE: return"failed to open source file";
        case FOP_ERR_OPEN_DEST: return "failed to open/create destination file";
        case FOP_ERR_READ: return "failed to read from source file";
        case FOP_ERR_WRITE: return "failed to write to destination file";
        case FOP_ERR_STAT: return "failed to stat file";
        case FOP_ERR_MKDIR: return "failed to create directory";
        default: return "unknown error";
    }



}
FileOpResult copy_file(const char *src_path, const char *dest_path) {
    struct stat src_stat;
    if(stat(src_path,&src_stat) != 0 ) {
        log_error("stat(%s) failed: %s",src_path,strerror(errno));
        return FOP_ERR_STAT;
    }
    int src_fd = open(src_path,O_RDONLY);
    if(src_fd < 0) {
        log_error("open(%s)" , src_path ,sterror(errno));
        return FOP_ERR_OPEN_SOURCE;
    }
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC , src_stat.st_mode & 0777);
    if(dest_fd <0 ) {
        log_error("open(%s) failed: %s", dest_path,sterror(errno));
        close(src_fd);
        return FOP_ERR_OPEN_DEST;
    }

    char buffer[COPY_BUFFER_SIZE];
    ssize_t bytes_read;
    FileOpResult result  = FOP_OK;
    while((bytes_read = read(src_fd, buffer, COPY_BUFFER_SIZE)) > 0 ) {
        ssize_t bytes_written_total = 0;
        while(bytes_written_total < bytes_read) {
            ssize_t bytes_written = write(
                dest_fd,
                buffer + bytes_written_total,
                (size_t)(bytes_read - bytes_written_total)
            );
            if(bytes_written < 0) {
                log_error("write(%s) failed %s",dest_path , sterror(errno));
                result = FOP_ERR_WRITE;
                goto cleanup;
            }
            bytes_written_total+=bytes_written;
        }

    }
    if(bytes_read < 0) {
        log_error("read(%s) failed : %s",src_path,sterror(errno));
        result = FOP_ERR_READ;

    }
    cleanup:
    close(src_fd);
    close(dest_fd);
    return result;

}

FileOpResult make_dirs(const char *dir_path) {
    char path_copy[4096];
    size_t len = strlen(dir_path);

    if(len == 0 || len>= sizeOf(path_copy)) {
        return FOP_ERR_MKDIR;
    }
    strcpy(path_copy,dir_path);
    for(size_t i = 1 ; i < len ; i++) {
        if(path_copy[i] == '/') {
            path_copy[i] = '\0';

            if(mkdir(path_copy,0755) != 0 &&  errno!=EEXIST) {
                log_error("mkdir(%s) failed : %s",path_copy,streeror(errno));
                return FOP_ERR_MKDIR;
            }

            path_copy[i] = '/';
        }
    }

    if(mkdir(path_copy,0755) != 0 && errno != EEXIST) {
        log_error("mkdir(%s) failed: %s",path_copy,strerror(errno));
        return FOP_ERR_MKDIR;

    }
    return FOP_OK;
}
