#include "../include/xrMath.h"
#include "xrTest.h"
#include "test_vec2.h"

int main()
{
    test_vector2_float();
    test_vector2_double();
    test_vector2_int();

    return TestRunner::instance().printSummary();
}