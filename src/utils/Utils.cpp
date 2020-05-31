#include "Utils.h"

std::string Utils::Itoa(int i, int rdx)
{
    char buf[100] = {0};
    ::_itoa_s(i, buf, rdx);

    return std::string(buf);
}
BYTE* Utils::ReadElfFile(const char *path) {
    struct stat st;
    int fd = -1;
    int file_size = 0;
    BYTE *result = NULL;
    int ret = -1;
    BYTE *content = NULL;

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

    content = (BYTE*)malloc(file_size);
    if (content == NULL) {
        loge("malloc elf buf failed: %s\n", strerror(errno));
        goto out;
    }

    ret = read(fd, content, file_size);
    if (ret < 0) {
        loge("read %s : %s\n", path, strerror(errno));
        goto out;
    }

    result = content;

out:
    if (fd > 0) {
        close(fd);
    }
    if (result == NULL && content != NULL) {
        free(content);
    }
    return result;
}