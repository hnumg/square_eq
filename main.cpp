#include<math.h>
#include<stdio.h>
#include<printf.h>
//#include"complex.h"
#include<malloc.h>
#include"main.h"
#include"test.h"
#include"square_eq_solver.h"


#define void unsigned long long





long long CoefsInit(Coefs* obj){
    obj->a = .0;
    obj->b = .0;
    obj->c = .0;
    return 0;
}



int main(){
    /*#pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    register_printf_function('C', Complex_handler, &print_arginfo);
    #pragma GCC diagnostic pop*/
    if (TestSolveSqEq()!=0){printf("errs");}
    Coefs Cs;
    CoefsInit(&Cs);


    Complex Root1, Root2;
    ComplexInit(&Root1);ComplexInit(&Root2);

    scanf("%lg %lg %lg", &Cs.a, &Cs.b, &Cs.c);
    long long num_of_solutions = SolveSqEq(Cs, &Root1, &Root2);


    switch (num_of_solutions){
        case 0:         printf("no solution\n");
                        break;

        case 1:         printf("one root: %lg\n", Root1.real);
                        break;

                        #pragma GCC diagnostic push
                        #pragma GCC diagnostic ignored "-Wformat"

        case 2:         printf("two roots: ");
                        PrintComplex(Root1);
                        printf(" and ");
                        PrintComplex(Root2);
                        printf("\n");
                        //printf("\n1:%lg", ((double*)&Root1)[1]);
                        break;

        case INF_ROOTS: printf("infinity roots\n");
                        break;

        default:        Exception("NotImplementedError", "default case is not defined");

    }

    return 0;

}
