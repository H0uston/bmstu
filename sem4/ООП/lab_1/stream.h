#ifndef STREAM_H
#define STREAM_H

#include <iostream>

#include "config.h"

typedef struct STREAM stream_t;
struct STREAM
{
    FILE *file;
};

stream_t stream_init(void);
FILE* get_file_from_stream_t(stream_t &stream);
void close_stream(stream_t &stream);
int file_openning_save(stream_t &stream, char *filename);
int file_openning_read(stream_t &stream, char *filename);

#endif // STREAM_H
