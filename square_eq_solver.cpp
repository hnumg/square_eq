#include<math.h>
#include<stdio.h>
#include<printf.h>
#include"complex.h"
#include<malloc.h>
#include"main.h"
#include"test.h"
#include"square_eq_solver.h"


long long SolveSqEq(Coefs Cs,
                    Complex* root1, Complex* root2){
    double a=Cs.a, b=Cs.b, c=Cs.c;
    if (DoubleIsNaN(a)||DoubleIsNaN(b)||DoubleIsNaN(c)){
        double nan = a*b*c;
        root1->imaginary=root1->real=root2->imaginary=root2->real = nan;
        return 2;
    }
    if (DoubleIsZero(a)){
        if (DoubleIsZero(b)){
            if (!DoubleIsZero(c)){
                 return 0;
            }
            else{
                return INF_ROOTS;
            }
        }
        else{
            root1->real = -c/b;
            return 1;
        }
    }
    else{
        double D = b*b-(4*a*c);
        if (D>0){
            double sqrt_D_div_2a = sqrt(D)/(2*a);
            double neg_b_div_2a = -b/(2*a);
            root1->real = neg_b_div_2a+sqrt_D_div_2a;
            root2->real = neg_b_div_2a-sqrt_D_div_2a;
            root1->imaginary = root2->imaginary = 0;
            return 2;
        }
        else if (DoubleIsZero(D)){
            root1->real = -b/(2*a);
            root2->imaginary=root1->imaginary=root2->real = 0;
            return 1;
        }
        else{
            double sqrt_negD_div_2a = sqrt(-D)/(2*a);
            root1->real = root2->real = -b/(2*a);
            root2->imaginary = -(root1->imaginary = sqrt_negD_div_2a);
            return 2;
        }
    }
    Exception("ValueError", "undefined returned value!");
    abort();

}



