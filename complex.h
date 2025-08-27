#ifndef COMPLEX_H
#define COMPLEX_H

#include<printf.h>
#include<stdio.h>


typedef unsigned long long u64;
typedef double fp64;

typedef struct {
    double real;
    double imaginary;
} Complex;



inline static u64 DoubleIsZero(double n){
    union {double d; u64 i;} var = {.d = n};
    var.d = n;
    var.i &= 0x7FFFFFFFFFFFFFFF;
    return var.d < 1e-100;
}

inline static u64 DoubleIsLittle(double n){
    union {double d; u64 i;} var = {.d = n};
    var.d = n;
    var.i &= 0x7FFFFFFFFFFFFFFF;
    return var.d < 1e-10;//что тут? e-10?
}

/*
inline static u64 DoubleIsLittle2(double n){
    union {double d; u64 i;} var = {.d = n};
    var.d = n;
    var.i &= 0x7FFFFFFFFFFFFFFF;
    return var.d < 1e-20;
}*/


inline static fp64 DoubleAbs(fp64 n){
    union {fp64 f; u64 i;} var = {.f = n};
    var.f = n;
    var.i &= 0x7FFFFFFFFFFFFFFF;
    return var.f;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
inline static u64 DoubleIsNaN(double n){
    return n != n;
}
#pragma GCC diagnostic pop


inline static u64 DoubleIsInf(double n){
    union {double d; u64 i;} var = {.d = n};

    return (var.i | 0x8000000000000000) == 0xFFF0000000000000;
}


inline static u64 DoubleIsEqual(fp64 n, fp64 m){
    fp64 divisor = DoubleIsZero(n+m)?1:n+m;
    return DoubleIsZero((n-m)/divisor);
}


void ComplexInit(Complex* self, fp64 real=.0, fp64 imaginary=.0);

void MulComplexToReal(Complex c, fp64 n, Complex *res);

void MulComplexToComplex(Complex c, Complex n, Complex *res);

void AddComplexToComplex(Complex c, Complex n, Complex *res);

void AddComplexToReal(Complex c, fp64 n, Complex *res);

bool ComplexIsNaN(Complex n);

bool ComplexIsZero(Complex n);

bool ComplexIsInf(Complex n);

bool ComplexIsEqual(Complex n, Complex m);

bool ComplexIsLittle(Complex n);

/*
int print_arginfo(const printf_info* _, size_t __, int* ___);

int Complex_handler(FILE *stream, const struct printf_info *info, const void *const *args);
*/
void fPrintComplex(FILE *stream, Complex arg);

void PrintComplex(Complex arg);

#endif
