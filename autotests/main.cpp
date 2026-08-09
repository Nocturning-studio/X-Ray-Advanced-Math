#include "../include/xrMath.h"

#include "xrTest.h"
#include "test_vec2.h"
#include "test_vec3.h"

int main()
{
    test_vector2_float();
    test_vector2_int();

    test_vector3_float();
    test_vector3_int();

    return TestRunner::instance().printSummary();
}