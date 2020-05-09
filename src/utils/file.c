#include "file.h"

byte* read_bin_file(const unsigned char *path) {
    struct stat st;
    int fd = -1;
    int file_size = 0;
    byte *result = null;

    if (path == NULL) {
        loge("elf path is null.");
        goto out;
    }

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        loge("open %s: %s", path, strerror(errno));
        goto out;
    }

    fstat(fd, &st);
    file_size = st.st_size;

    byte *content = (byte*)malloc(file_size);
    if (content == NULL) {
        loge("malloc elf buf failed: %s\n", strerror(errno));
        goto out;
    }

    int ret = read(fd, content, file_size);
    if (ret < 0) {
        loge("read %s : %s\n", path, strerror(errno));
        goto out;
    }

    result = content;

out:
    if (fd > 0) {
        close(fp);
    }
    if (result == NULL && content != NULL) {
        free(content);
    }
    return result;
}