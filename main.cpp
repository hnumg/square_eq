#include<stdio.h>
#include"square_eq_solver.h"
#include"test.h"
//#include<math.h>



static bool strcmp(const char* s1, const char* s2){
    u64 i = 0;
    i--;
    do{
        i++;
        if (s1[i]<s2[i]){
            return -1;
        }
        else if (s1[i]>s2[i]){
            return -1;
        }
    }while (s1[i]!=0&&s2[i]!=0);
    return 0;
}


static u64 args_handler(int argc, char** argv){
    if (argc>1){
        bool flag = false;
        for (u64 i = 1; i<(u64)argc; i++){
            if (strcmp(argv[i], "-t")!=0&&strcmp(argv[i], "--test")!=0){
                fprintf(stderr, "Unknown command line argument \"");
                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wformat-security"
                fprintf(stderr, argv[i]);
                #pragma GCC diagnostic pop
                fprintf(stderr, "\"\n");
                flag = true;
            }
        }
        if (flag){
            return 3;
        }
        //здесь невозможно оказаться, если переданы хоть какие-то аргументы, кроме -t или --test
        if (TestSolveSqEq() != 0){
            return 2;
        }
    }
    return 0;
}


int main(int argc, char** argv){
    /*#pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    register_printf_function('C', Complex_handler, &print_arginfo);
    #pragma GCC diagnostic pop*/
    u64 code = 0;
    if ((code = args_handler(argc, argv))!=0){
        return (int) code;
    }


    Coefs Cs;// = {.a = NAN, .b = NAN, .c = NAN};
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
