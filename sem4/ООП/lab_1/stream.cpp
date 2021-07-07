#include "stream.h"

// Инициализация файлового потока
stream_t stream_init(void)
{
    stream_t stream;
    stream.file = nullptr;
    return stream;
}

// Функция обертка для файла
FILE* get_file_from_stream_t(stream_t &stream)
{
    return stream.file;
}

// Функция закрытия потока
void close_stream(stream_t &stream)
{
    fclose(stream.file);
}

// Функция обертка для открытия потока (запись)
int file_openning_save(stream_t &stream, char *filename)
{
    stream.file = fopen(filename, "w");
    if (stream.file) {
        return OK;
    }
    else
    {
        return ERR_OPEN;
    }
}

// Функция обертка для открытия потока (чтение)
int file_openning_read(stream_t &stream, char *filename)
{
    stream.file = fopen(filename, "r");
    if (stream.file)
    {
        return OK;
    }
    else
    {
        return ERR_OPEN;
    }
}
