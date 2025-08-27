#include"complex.h"
#include"square_eq_solver.h"

void _rdrand_q(void *ptr);

typedef struct{
    Coefs cs;
    Roots roots;
} TestType;

u64 CheckSpecialComplexZero(Complex res, Coefs c);

u64 RootIsIncorrect(Coefs c, Complex root);

u64 OneRootIsIncorrect(Coefs c, Complex root);

u64 rootsAreIncorrect(Coefs c, Complex root1, Complex root2);

u64 ManualTest(TestType ct);

u64 ManualTests();

u64 OneAutotestSolveSqEq();

u64 TestSolveSqEq();
