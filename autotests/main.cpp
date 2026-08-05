#include "../include/xrMath.h"
#include "xrTest.h"

int main()
{
    Fsphere sphere;
    sphere.identity();
    CHECK(sphere.R == 1.0f);

    template_vector3<float> point = {0.5f, 0.5f, 0.5f};
    CHECK(sphere.contains(point));

    return TestRunner::instance().printSummary();
}