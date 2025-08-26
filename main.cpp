#include<math.h>
#include<stdio.h>
#include<printf.h>
//#include"complex.h"
#include<malloc.h>
#include"main.h"
#include"test.h"
#include"square_eq_solver.h"
#include<unistd.h>


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
    if (TestSolveSqEq() != 0) { printf("errs"); }
    Coefs Cs;
    CoefsInit(&Cs);


    Complex Root1, Root2;
    ComplexInit(&Root1); ComplexInit(&Root2);

    printf("Решатель квадратных уравнений вида ax^2+bx+c=0\nВведите a:");
    scanf("%lg", &Cs.a);
    printf("Введите b:");
    scanf("%lg", &Cs.b);
    printf("Введите c:");
    scanf("%lg", &Cs.c);
    long long num_of_solutions = SolveSqEq(Cs, &Root1, &Root2);
    printf("\nВедутся раскопки корней квадратного уравнения...");
    fflush(stdout);
    for (char i = 0; i < 16; i++){
        usleep(500000);
        printf(".");
        fflush(stdout);
    }
    printf("\n");


    switch (num_of_solutions){
        case 0:         printf("Копал, копал, а корней не выкопал... :((\n");
                        break;

        case 1:         printf("Выкопал всего лишь один корень: %lg\nБольше корней найти не могу :(\n", Root1.real);
                        break;

                        #pragma GCC diagnostic push
                        #pragma GCC diagnostic ignored "-Wformat"

        case 2:         printf("Выкопал два корня: ");
                        PrintComplex(Root1);
                        printf(" и ");
                        PrintComplex(Root2);
                        printf("\nБольше корней у невырожденных квадратных уравнений не растёт :(\n");
                        //printf("\n1:%lg", ((double*)&Root1)[1]);
                        break;

        case INF_ROOTS: printf("Не смогу выкопать все корни. У этого уравнения отрастают всё новые и новые корни :(\n");
                        break;

        default:        Exception("NotImplementedError", "default case is not defined");

    }

    return 0;

}
