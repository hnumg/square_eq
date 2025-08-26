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



inline static int DoubleIsZero(double n){
    union {double d; u64 i;} var = {.d = n};
    var.d = n;
    var.i &= 0x7FFFFFFFFFFFFFFF;
    return var.d < 1e-10;
}


inline static fp64 DoubleAbs(fp64 n){
    union {fp64 f; u64 i;} var = {.f = n};
    var.f = n;
    var.i &= 0x7FFFFFFFFFFFFFFF;
    return var.f;
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
inline static int DoubleIsNaN(double n){
    return n != n;
}
#pragma GCC diagnostic pop


inline static int DoubleIsInf(double n){
    union {double d; u64 i;} var = {.d = n};

    return (var.i | 0x8000000000000000) == 0xFFF0000000000000;
}



long long ComplexInit(Complex* obj);

void MulComplexToReal(Complex c, fp64 n, Complex *res);

void MulComplexToComplex(Complex c, Complex n, Complex *res);

void AddComplexToComplex(Complex c, Complex n, Complex *res);

void AddComplexToReal(Complex c, fp64 n, Complex *res);

int ComplexIsNaN(Complex n);

int ComplexIsZero(Complex n);

int ComplexIsInf(Complex n);
/*
int print_arginfo(const printf_info* _, size_t __, int* ___);

int Complex_handler(FILE *stream, const struct printf_info *info, const void *const *args);
*/
int fPrintComplex(FILE *stream, Complex arg);

int PrintComplex(Complex arg);

#endif
