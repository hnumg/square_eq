#ifndef SQUARE_EQ_SOLVER
#define SQUARE_EQ_SOLVER

#include"complex.h"

typedef unsigned long long u64;
typedef double fp64;
typedef void def;


enum {
    INF_ROOTS = 0x80000000
};


typedef struct {
    double a;
    double b;
    double c;
} Coefs;


typedef struct {
    Complex Root1;
    Complex Root2;
    u64 roots_count;
} Roots;


void RootsInit(Roots* self);

u64 RootsObjectsIsEqual(Roots self, Roots other);

void RootsPrint(Roots r);


long long CoefsInit(Coefs* self);

u64 CoefsInput(Coefs *Cs);

void SolveSqEq(Coefs Cs, Roots* r);

#endif
