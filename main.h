#ifndef MAIN_H
#define MAIN_H


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

