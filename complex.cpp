//#include<math.h>
#include<printf.h>
#include<stdio.h>
#include "complex.h"

void ComplexInit(Complex* self, fp64 real/*=.0*/, fp64 imaginary/*=.0*/){
    self->real = real;
    self->imaginary = imaginary;
}


void MulComplexToReal(Complex c, fp64 n, Complex *res){
    res->real = n * c.real;
    res->imaginary = n * c.imaginary;
}

void MulComplexToComplex(Complex c, Complex n, Complex *res){
    res->real = n.real * c.real - n.imaginary * c.imaginary;
    res->imaginary = n.real * c.imaginary + n.imaginary * c.real;
}

void AddComplexToComplex(Complex c, Complex n, Complex *res){
    res->imaginary = c.imaginary + n.imaginary;
    res->real = c.real + n.real;
}

void AddComplexToReal(Complex c, fp64 n, Complex *res){
    res->real = c.real + n;
    res->imaginary = c.imaginary;
}

bool ComplexIsNaN(Complex n){
    return DoubleIsNaN(n.imaginary) || DoubleIsNaN(n.real);
}

bool ComplexIsZero(Complex n){
    return DoubleIsZero(n.imaginary) && DoubleIsZero(n.real);
}

bool ComplexIsInf(Complex n){
    return !ComplexIsNaN(n) && (DoubleIsInf(n.imaginary) || DoubleIsInf(n.real));
}

bool ComplexIsEqual(Complex n, Complex m){
    return DoubleIsEqual(n.imaginary, m.imaginary)&&DoubleIsEqual(n.real, m.real);
}

/*
int print_arginfo(const printf_info* _, size_t __, int* ___){
    (void)_;(void)__;(void)___;
    return 1;
}

int Complex_handler(FILE *stream, const struct printf_info *info, const void *const *args){
    (void)info;
    printf("\n%p, %lg\n", args[0], (*((const double*)args[0])));
    double real = (*((const double* const*)args[0]))[0];
    double imaginary = (*((const double* const*)args[0]))[1];

    if (DoubleIsZero(real)&&DoubleIsZero(imaginary)){
        fprintf(stream, "0");
    }
    else if(DoubleIsZero(imaginary)){
        fprintf(stream, "%lg", real);
    }
    else if (DoubleIsZero(real)){
            fprintf(stream, "%lgj", imaginary);
    }
    else {
        fprintf(stream, "%lg%+lgj", real, imaginary);

    }
    return 0;
}
*/

void fPrintComplex(FILE *stream, Complex arg){
    double real = arg.real;
    double imaginary = arg.imaginary;

    if (DoubleIsZero(real) && DoubleIsZero(imaginary)){
        fprintf(stream, "0");
    }
    else if(DoubleIsZero(imaginary)){
        fprintf(stream, "%lg", real);
    }
    else if (DoubleIsZero(real)){
            fprintf(stream, "%lgj", imaginary);
    }
    else {
        fprintf(stream, "%lg%+lgj", real, imaginary);
    }
}

void PrintComplex(Complex c){
    fPrintComplex(stdout, c);
}
