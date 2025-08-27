#ifndef SQUARE_EQ_SOLVER
#define SQUARE_EQ_SOLVER

#include"complex.h"

typedef unsigned long long u64;
typedef double fp64;
typedef void def;


const u64 INF_ROOTS = 0xFFFFFFFFFFFFFFFF;


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


void RootsInit(Roots* self, u64 roots_count=0,
               fp64 root1real=.0, fp64 root1imaginary=.0,
               fp64 root2real=.0, fp64 root2imaginary=.0);

u64 RootsObjectsIsEqual(Roots self, Roots other);

void RootsUnsigningNulls(Roots* r);

void RootsPrint(Roots r);


long long CoefsInit(Coefs* self);

u64 CoefsInput(Coefs *Cs);

void _SolveSqEq(Coefs Cs, Roots* r);

void SolveSqEq(Coefs Cs, Roots* r);

#endif
