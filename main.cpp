#include<stdio.h>
#include"square_eq_solver.h"
#include"test.h"



int main(){
    /*#pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    register_printf_function('C', Complex_handler, &print_arginfo);
    #pragma GCC diagnostic pop*/
    if (TestSolveSqEq() != 0){
        return 2;
    }

    Coefs Cs;
    CoefsInit(&Cs);
    if (CoefsInput(&Cs)!=0){
        printf("Неверный ввод\n");
        return 1;
    }

    Roots r;
    RootsInit(&r);
    SolveSqEq(Cs, &r);
    RootsPrint(r);

    return 0;
}
