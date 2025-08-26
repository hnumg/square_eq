#include<math.h>
#include<stdio.h>
#include<printf.h>
#include"complex.h"
#include"test.h"
#include"square_eq_solver.h"
#include"exception.h"
#include<unistd.h>


//#define void unsigned long long
//bug!!!




long long CoefsInit(Coefs* self){
    self->a = .0;
    self->b = .0;
    self->c = .0;
    return 0;
}



void RootsInit(Roots* self){
    self->roots_count = 0;
    ComplexInit(&self->Root1);
    ComplexInit(&self->Root2);
}

u64 RootsObjectsIsEqual(Roots self, Roots other){
    return self.roots_count == other.roots_count &&
           ComplexIsEqual(self.Root1, other.Root1) && ComplexIsEqual(self.Root2, other.Root2);
}

void RootsPrint(Roots r){
    printf("\nВедутся раскопки корней квадратного уравнения...");
    fflush(stdout);
    for (char i = 0; i < 16; i++){
        usleep(500000);
        printf(".");
        fflush(stdout);
    }
    printf("\n");
    switch (r.roots_count){
        case 0:         printf("Копал, копал, а корней не выкопал... :((\n");
                        break;

        case 1:         printf("Выкопал всего лишь один корень: %lg\nБольше корней найти не могу :(\n", r.Root1.real);
                        break;

                        #pragma GCC diagnostic push
                        #pragma GCC diagnostic ignored "-Wformat"

        case 2:         printf("Выкопал два корня: ");
                        PrintComplex(r.Root1);
                        printf(" и ");
                        PrintComplex(r.Root2);
                        printf("\nБольше корней у невырожденных квадратных уравнений не растёт :(\n");
                        //printf("\n1:%lg", ((double*)&Root1)[1]);
                        break;

        case INF_ROOTS: printf("Не смогу выкопать все корни. У этого уравнения отрастают всё новые и новые корни :(\n");
                        break;

        default:        Exception("NotImplementedError", "default case is not defined");

    }
}


u64 CoefsInput(Coefs *Cs){

    printf("Решатель квадратных уравнений вида ax^2+bx+c=0\nВведите a:");
    if (scanf("%lg", &Cs->a)<=0){
        return 1;
    }
    printf("Введите b:");
    if (scanf("%lg", &Cs->b)<=0){
        return 1;
    }
    printf("Введите c:");
    if (scanf("%lg", &Cs->c) <= 0){
        return 1;
    }
    return 0;
}

void SolveSqEq(Coefs Cs, Roots* r){
    double a = Cs.a, b = Cs.b, c = Cs.c;

    if (DoubleIsNaN(a) || DoubleIsNaN(b) || DoubleIsNaN(c)){
        double nan = a * b * c;
        ComplexInit(&r->Root1, nan, nan);
        ComplexInit(&r->Root2, nan, nan);
        //root1->imaginary = root1->real = root2->imaginary = root2->real = nan;
        r->roots_count=2;
        return;
    }
    if (DoubleIsZero(a)){
        if (DoubleIsZero(b)){
            if (!DoubleIsZero(c)){
                 r->roots_count = 0;
                 return;
            }
            else{
                r->roots_count = INF_ROOTS;
                return;
            }
        }
        else{
            ComplexInit(&r->Root1, -c / b, .0);
            //root1->real = -c / b;
            r->roots_count = 1;
            return;
        }
    }
    else{
        double D = b*b - (4*a*c);
        if (D > 0){
            double sqrt_D_div_2a = sqrt(D) / (2*a);
            double neg_b_div_2a = -b / (2*a);
            ComplexInit(&r->Root1, neg_b_div_2a + sqrt_D_div_2a, .0);
            ComplexInit(&r->Root2, neg_b_div_2a - sqrt_D_div_2a, .0);

            /*root1->real = neg_b_div_2a + sqrt_D_div_2a;
            root2->real = neg_b_div_2a - sqrt_D_div_2a;

            root1->imaginary = root2->imaginary = 0;*/
            r->roots_count = 2;
            return;
        }
        else if (DoubleIsZero(D)){
            ComplexInit(&r->Root1, -b / (2*a), .0);
            ComplexInit(&r->Root2, .0, .0);
            /*root1->real = -b / (2*a);
            root2->imaginary = root1->imaginary = root2->real = 0.0;*/
            r->roots_count = 1;
            return;
        }
        else{
            fp64 sqrt_negD_div_2a = sqrt(-D) / (2*a);
            fp64 negb_div_2a = -b / (2*a);
            ComplexInit(&r->Root1, negb_div_2a, sqrt_negD_div_2a);
            ComplexInit(&r->Root2, negb_div_2a, -sqrt_negD_div_2a);
            /*root1->real = root2->real = -b / (2*a);
            root2->imaginary = -(root1->imaginary = sqrt_negD_div_2a);*/
            r->roots_count = 2;
            return;
        }
    }
    Exception("ValueError", "undefined returned value!");
    abort();

}
