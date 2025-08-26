#ifndef NDEBUG
#define Exception(Exception_name, Message ) do {        \
    fprintf(stderr, "\033[31m    File <\"%s\">, line %d\n\n%s: %s \033[0m\n",  \
           __FILE__, __LINE__, Exception_name, Message);\
    abort();                                             \
} while (0)
#else
#define Exception(Exception_name, Message) do{}while(0)
#endif
