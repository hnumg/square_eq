#include"complex.h"
#include"main.h"


void _rdrand_q(void *ptr);

u64 CheckSpecialComplexZero(Complex res, Coefs c);

u64 RootIsIncorrect(Coefs c, Complex root);

u64 rootsAreIncorrect(Coefs c, Complex root1, Complex root2);


u64 OneAutotestSolveSqEq();

u64 TestSolveSqEq();
