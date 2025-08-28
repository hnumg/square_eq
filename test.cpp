#include"test.h"
//#include"complex.h"
#include"square_eq_solver.h"


void _rdrand_q(void *ptr){
    asm("rdrand %%rax\n\t"
        "movq %%rax, 0(%0)\n\t"::"r"(ptr):"rax", "flags", "memory");
}

u64 CheckSpecialComplexZero(Complex res, Coefs c){
    c.a = DoubleAbs(c.a); c.b = DoubleAbs(c.b); c.c = DoubleAbs(c.c);
    //printf("a=%lg;b=%lg;c=%lg\n", c.a, c.b, c.c);
    fp64 a = c.a;
    a = c.b > a ? c.b : a;
    a = c.c > a ? c.c : a;
    fp64 b = c.c;
    b = c.b < b ? c.b : b;
    b = c.a < b ? c.a : b;
    //printf("a=%lg;b=%lg;;;;\n", a, b);
    fp64 sqa = a * a;
    fp64 sqb = b * b;
    fp64 adb = a / b;
    fp64 d = adb<1/adb?adb:1/adb;
    sqa = sqa < 1.0/sqa ? sqa : 1.0/sqa;
    sqb = sqb < 1.0/sqb ? sqb : 1.0/sqb;
    adb = adb < 1.0/adb ? adb : 1.0/adb;
    sqa = sqa < sqb ? sqa : sqb;
    sqa = sqa < adb ? sqa : adb;
    sqa /= 4;
    //printf("sqa=%lg\n", sqa);
    res.imaginary *= sqa;
    res.real *= sqa;
    //printf("res.i=%lg\n", res.imaginary);
    //printf("res.r=%lg\n", res.real);
    return ComplexIsLittle(res) || ComplexIsNaN(res) || ComplexIsInf(res) || DoubleIsZero(sqa) || DoubleIsNaN(sqa)||DoubleIsLittle(d);
}

u64 OneRootIsIncorrect(Coefs c, Complex root){
    Complex c1;
    Complex c2;
    MulComplexToReal(root, c.b, &c2);
    AddComplexToReal(c2, c.c, &c1);
    if ((!CheckSpecialComplexZero(c1, c)) && !(ComplexIsNaN(c1) || ComplexIsInf(c1))){
        printf("ptr1=%p, ptr2=%p\n", &root, &c1);
        printf("a=%lg,b=%lg,c=%lg;\nr1=", c.a, c.b, c.c);
        PrintComplex(root);
        printf(";r1ref=");
        PrintComplex(c1);
        printf("\n");
        return 1;
    }
    else{
        return 0;
    }
}


u64 RootIsIncorrect(Coefs c, Complex root){
    Complex c1;
    Complex c2;
    Complex c3;
    MulComplexToComplex(root, root, &c1);
    MulComplexToReal(c1, c.a, &c2);
    MulComplexToReal(root, c.b, &c1);
    AddComplexToComplex(c1, c2, &c3);
    AddComplexToReal(c3, c.c, &c1);
    if ((!CheckSpecialComplexZero(c1, c)) && !(ComplexIsNaN(c1) || ComplexIsInf(c1))){
        printf("2roots");
        printf("ptr1=%p, ptr2=%p\n", &root, &c1);
        printf("a=%lg,b=%lg,c=%lg;\nr1=", c.a, c.b, c.c);
        PrintComplex(root);
        printf(";r1ref=");
        PrintComplex(c1);
        printf("\n");
        return 1;
    }
    else{
        return 0;
    }
}

u64 rootsAreIncorrect(Coefs c, Complex root1, Complex root2){
    return RootIsIncorrect(c, root1) || RootIsIncorrect(c, root2);
}



u64 OneAutotestSolveSqEq(){
    Coefs c;
    _rdrand_q(&c.a);
    _rdrand_q(&c.b);
    _rdrand_q(&c.c);

    Roots roots;
    RootsInit(&roots);

    SolveSqEq(c, &roots);
    if (DoubleIsNaN(c.a) || DoubleIsNaN(c.b) || DoubleIsNaN(c.c)){
        if (!(DoubleIsNaN(roots.Root1.imaginary) && DoubleIsNaN(roots.Root1.real) &&
              DoubleIsNaN(roots.Root2.imaginary) && DoubleIsNaN(roots.Root2.real) && !roots.roots_count)){

            fprintf(stderr, "NaNs err");
            return 1;
        }
    }
    else if (DoubleIsZero(c.a) && DoubleIsZero(c.b) && !DoubleIsZero(c.c)){
        if (roots.roots_count != 0){
            fprintf(stderr, "NZER");
            return 1;
        }
    }
    /*else if (res==1&&(!(DoubleIsZero(c.a)&&!DoubleIsZero(c.b)&&!DoubleIsZero(c.c))&&!DoubleIsZero(c.b*c.b-4*c.a*c.c))){
        //printf("fake");
        //return 1;
    }*/
    else if (roots.roots_count == 1){
        return OneRootIsIncorrect(c, roots.Root1);
        /*Complex c1;//res
        Complex c2;
        MulComplexToReal(root1, c.b, &c2);
        AddComplexToReal(c2, c.c, &c1);
        //res = c.b*root1+c.c
        if ((!CheckSpecialComplexZero(c1, c))&&!(ComplexIsNaN(c1)||ComplexIsInf(c1))){
            printf("ptr1=%p, ptr2=%p\n", &root1, &c1);
            printf("a=%lg,b=%lg,c=%lg;\nr1=", c.a, c.b, c.c);
            PrintComplex(root1);
            printf(";r1ref=");
            PrintComplex(c1);
            printf("\n");
            return 1;
        }
        else{
            return 0;
        }*/
    }
    else if (roots.roots_count == 0){ fprintf(stderr, "ZER"); return 1; }
    else if (roots.roots_count>2 && !(DoubleIsZero(c.a) && DoubleIsZero(c.b) && DoubleIsZero(c.c))){ printf("MORETHAN2"); return 1; }
    else{
        return rootsAreIncorrect(c, roots.Root1, roots.Root2);
    }
    return 0;



}


u64 ManualTest(TestType ct){
    Roots roots;
    SolveSqEq(ct.cs, &roots);
    if (!RootsObjectsIsEqual(ct.roots, roots)){
        printf("Test failed: a=%lg, b=%lg, c=%lg,\nExpected roots_count=%llu, root1=",
               ct.cs.a, ct.cs.b, ct.cs.c, ct.roots.roots_count);
        PrintComplex(ct.roots.Root1);
        printf(", root2=");
        PrintComplex(ct.roots.Root2);
        printf(", but got roots_count=%llu, root1=", roots.roots_count);
        PrintComplex(roots.Root1);
        printf(", root2=");
        PrintComplex(roots.Root2);
        printf("\n");
        return 1;
    }
    return 0;
}

const u64 MANUAL_TESTS_COUNT = 8;




u64 ManualTests(){
    TestType t;
    FILE * f = fopen64("./manual_tests", "r");
    u64 manual_tests_failed = 0;

    for (u64 i=0; i<MANUAL_TESTS_COUNT;i++){
        fscanf(f, "%lg %lg %lg %llu %lg %lg %lg %lg", &t.cs.a, &t.cs.b, &t.cs.c,
               &t.roots.roots_count,
               &t.roots.Root1.real, &t.roots.Root1.imaginary,
               &t.roots.Root2.real, &t.roots.Root2.imaginary);
        manual_tests_failed+=ManualTest(t);
    }
    return manual_tests_failed;
}

//TODO: manual tests from file


const u64 TEST_COUNT = 0xFFFF;

u64 TestSolveSqEq(){
    u64 errs_cnt = 0;
    for (u64 i = 0; i < TEST_COUNT; i++){
        errs_cnt += OneAutotestSolveSqEq();
    }
    ManualTests();
    return errs_cnt;
}
