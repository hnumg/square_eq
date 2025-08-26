#ifndef MAIN_H
#define MAIN_H


#ifndef NDEBUG
#define Exception(Exception_name, Message ) do {        \
    fprintf(stderr, "\033[31m    File <\"%s\">, line %d\n\n%s: %s \033[0m\n",  \
           __FILE__, __LINE__, Exception_name, Message);\
    abort();                                             \
} while (1)
#else
#define Exception(Exception_name, Message) do{void *ptr = (void*)malloc(8); *ptr = (void)8; free(ptr);}while(0)
#endif


typedef unsigned long long u64;
typedef double fp64;



enum {
    INF_ROOTS = 0x80000000
};


typedef struct {
    double a;
    double b;
    double c;
} Coefs;


long long CoefsInit(Coefs* obj);

#endif

