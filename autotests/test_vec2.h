#include "../include/xrMath.h"
#include "xrTest.h"
#include <cmath>

void test_vector2_float()
{
    fvec2 v1 = { 1.0f, 2.0f };
    fvec2 v2;
    v2.set(3.0f, 4.0f);
    CHECK_SIMILAR(v2, (fvec2{ 3.0f, 4.0f }), FLOAT_EPS);

    v2.set(v1);
    CHECK_SIMILAR(v2, (fvec2{ 1.0f, 2.0f }), FLOAT_EPS);

    fvec2 v3 = { -3.0f, 4.0f };
    v3.abs(v3);
    CHECK_SIMILAR(v3, (fvec2{ 3.0f, 4.0f }), FLOAT_EPS);

    fvec2 a = { 2.0f, 5.0f };
    fvec2 b = { 3.0f, 1.0f };
    a.min(b);
    CHECK_SIMILAR(a, (fvec2{ 2.0f, 1.0f }), FLOAT_EPS);
    a.set(2.0f, 5.0f);
    a.max(b);
    CHECK_SIMILAR(a, (fvec2{ 3.0f, 5.0f }), FLOAT_EPS);

    a.set(2.0f, 5.0f);
    a.min(1.0f, 6.0f);
    CHECK_SIMILAR(a, (fvec2{ 1.0f, 5.0f }), FLOAT_EPS);
    a.set(2.0f, 5.0f);
    a.max(10.0f, 3.0f);
    CHECK_SIMILAR(a, (fvec2{ 10.0f, 5.0f }), FLOAT_EPS);

    fvec2 p = { 2.0f, 3.0f };
    p.add(1.0f);
    CHECK_SIMILAR(p, (fvec2{ 3.0f, 4.0f }), FLOAT_EPS);
    p.sub(1.0f);
    CHECK_SIMILAR(p, (fvec2{ 2.0f, 3.0f }), FLOAT_EPS);

    fvec2 q = { 1.0f, 2.0f };
    p.add(q);
    CHECK_SIMILAR(p, (fvec2{ 3.0f, 5.0f }), FLOAT_EPS);
    p.sub(q);
    CHECK_SIMILAR(p, (fvec2{ 2.0f, 3.0f }), FLOAT_EPS);

    fvec2 r;
    r.add(p, q);
    CHECK_SIMILAR(r, (fvec2{ 3.0f, 5.0f }), FLOAT_EPS);
    r.sub(p, q);
    CHECK_SIMILAR(r, (fvec2{ 1.0f, 1.0f }), FLOAT_EPS);

    r.sub(q, 0.5f);
    CHECK_SIMILAR(r, (fvec2{ 0.5f, 1.5f }), FLOAT_EPS);
    r.add(q, 0.5f);
    CHECK_SIMILAR(r, (fvec2{ 1.5f, 2.5f }), FLOAT_EPS);

    fvec2 m = { 2.0f, 3.0f };
    m.mul(2.0f);
    CHECK_SIMILAR(m, (fvec2{ 4.0f, 6.0f }), FLOAT_EPS);
    m.div(2.0f);
    CHECK_SIMILAR(m, (fvec2{ 2.0f, 3.0f }), FLOAT_EPS);

    fvec2 n = { 3.0f, 4.0f };
    m.mul(n);
    CHECK_SIMILAR(m, (fvec2{ 6.0f, 12.0f }), FLOAT_EPS);

    fvec2 inv = { 3.0f, -4.0f };
    inv.invert();
    CHECK_SIMILAR(inv, (fvec2{ -3.0f, 4.0f }), FLOAT_EPS);
    fvec2 src = { 1.0f, 2.0f };
    inv.invert(src);
    CHECK_SIMILAR(inv, (fvec2{ -1.0f, -2.0f }), FLOAT_EPS);

    fvec2 rot = { 1.0f, 2.0f };
    rot.rot90();
    CHECK_SIMILAR(rot, (fvec2{ 2.0f, -1.0f }), FLOAT_EPS);

    fvec2 orig_cross = { 3.0f, 4.0f };
    fvec2 cr = orig_cross;
    cr.cross(orig_cross);
    CHECK_SIMILAR(cr, (fvec2{ 4.0f, -3.0f }), FLOAT_EPS);

    fvec2 crossed = orig_cross.cross();
    CHECK_SIMILAR(crossed, (fvec2{ 4.0f, -3.0f }), FLOAT_EPS);

    fvec2 d1 = { 1.0f, 0.0f };
    fvec2 d2 = { 0.0f, 1.0f };
    CHECK_CLOSE(d1.dot(d2), 0.0f, FLOAT_EPS);
    CHECK_CLOSE(d1.dot(d1), 1.0f, FLOAT_EPS);
    CHECK_CLOSE(d1.dotproduct(d2), 0.0f, FLOAT_EPS);
    CHECK_CLOSE(d1.crossproduct(d2), 1.0f, FLOAT_EPS);
    CHECK_CLOSE(d2.crossproduct(d1), -1.0f, FLOAT_EPS);

    fvec2 len = { 3.0f, 4.0f };
    CHECK_CLOSE(len.magnitude(), 5.0f, FLOAT_EPS);
    CHECK_CLOSE(len.square_magnitude(), 25.0f, FLOAT_EPS);
    fvec2 other = { 0.0f, 0.0f };
    CHECK_CLOSE(len.distance_to(other), 5.0f, FLOAT_EPS);
    CHECK_CLOSE(other.distance_to(len), 5.0f, FLOAT_EPS);

    fvec2 norm_v = { 3.0f, 4.0f };
    norm_v.norm();
    CHECK_SIMILAR(norm_v, (fvec2{ 0.6f, 0.8f }), FLOAT_EPS);
    CHECK_CLOSE(norm_v.magnitude(), 1.0f, FLOAT_EPS);

    fvec2 zero_v = { 0.0f, 0.0f };
    zero_v.norm_safe();
    CHECK_SIMILAR(zero_v, (fvec2{ 0.0f, 0.0f }), FLOAT_EPS);

    fvec2 target;
    target.normalize({ 6.0f, 8.0f });
    CHECK_SIMILAR(target, (fvec2{ 0.6f, 0.8f }), FLOAT_EPS);
    target.normalize_safe({ 0.0f, 0.0f });
    CHECK_SIMILAR(target, (fvec2{ 0.6f, 0.8f }), FLOAT_EPS);

    fvec2 mad_res;
    mad_res.mad({ 1.0f, 2.0f }, { 0.5f, 1.0f }, 2.0f);
    CHECK_SIMILAR(mad_res, (fvec2{ 1.0f + 0.5f * 2.0f, 2.0f + 1.0f * 2.0f }), FLOAT_EPS);

    fvec2 avg;
    avg.averageA({ 2.0f, 4.0f }, { 4.0f, 6.0f });
    CHECK_SIMILAR(avg, (fvec2{ 3.0f, 5.0f }), FLOAT_EPS);
    avg.averageG({ 4.0f, 9.0f }, { 9.0f, 16.0f });
    CHECK_CLOSE(avg.x, 6.0f, FLOAT_EPS);
    CHECK_CLOSE(avg.y, 12.0f, FLOAT_EPS);

    fvec2 s1 = { 1.0f, 2.0f };
    fvec2 s2 = { 1.001f, 1.999f };
    CHECK(s1.similar(s2, 0.01f));
    CHECK(!s1.similar({ 2.0f, 2.0f }, 0.01f));

    fvec2 arr = { 10.0f, 20.0f };
    CHECK_CLOSE(arr[0], 10.0f, FLOAT_EPS);
    CHECK_CLOSE(arr[1], 20.0f, FLOAT_EPS);
    arr[0] = 100.0f;
    arr[1] = 200.0f;
    CHECK_CLOSE(arr.x, 100.0f, FLOAT_EPS);
    CHECK_CLOSE(arr.y, 200.0f, FLOAT_EPS);

    CHECK_EQUAL(&arr[0], &arr.x);
    CHECK_EQUAL(&arr[1], &arr.y);

    fvec2 east = { 1.0f, 0.0f };
    CHECK_CLOSE(east.getH(), -PI_DIV_2, FLOAT_EPS);
    fvec2 west = { -1.0f, 0.0f };
    CHECK_CLOSE(west.getH(), PI_DIV_2, FLOAT_EPS);
    fvec2 north = { 0.0f, 1.0f };
    CHECK_CLOSE(north.getH(), 0.0f, FLOAT_EPS);
    fvec2 south = { 0.0f, -1.0f };
    CHECK_CLOSE(south.getH(), PI, FLOAT_EPS);

    fvec2 op1 = { 1.0f, 2.0f };
    fvec2 op2 = { 3.0f, 4.0f };

    CHECK_SIMILAR(-op1, (fvec2{ -1.0f, -2.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op1 + op2, (fvec2{ 4.0f, 6.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op1 - op2, (fvec2{ -2.0f, -2.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op1 + 10.0f, (fvec2{ 11.0f, 12.0f }), FLOAT_EPS);
    CHECK_SIMILAR(10.0f + op1, (fvec2{ 11.0f, 12.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op1 - 0.5f, (fvec2{ 0.5f, 1.5f }), FLOAT_EPS);

    fvec2 s_minus_v = 5.0f - op1;
    CHECK_SIMILAR(s_minus_v, (fvec2{ 4.0f, 3.0f }), FLOAT_EPS);

    CHECK_SIMILAR(op1 * 3.0f, (fvec2{ 3.0f, 6.0f }), FLOAT_EPS);
    CHECK_SIMILAR(3.0f * op1, (fvec2{ 3.0f, 6.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op2 / 2.0f, (fvec2{ 1.5f, 2.0f }), FLOAT_EPS);

    fvec2 s_div_v = 10.0f / op2;
    CHECK_SIMILAR(s_div_v, (fvec2{ 10.0f / 3.0f, 2.5f }), FLOAT_EPS);

    CHECK_SIMILAR(op1 * op2, (fvec2{ 3.0f, 8.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op2 / op1, (fvec2{ 3.0f, 2.0f }), FLOAT_EPS);

    fvec2 valid_v = { 1.0f, 2.0f };
    CHECK_EQUAL(_valid(valid_v), TRUE);
    fvec2 nan_v = { std::numeric_limits<float>::quiet_NaN(), 0.0f };
    CHECK_EQUAL(_valid(nan_v), FALSE);
}

void test_vector2_int()
{
    ivec2 iv1 = { 2, 3 };
    ivec2 iv2 = { 5, 7 };

    iv1.add(iv2);
    CHECK_EQUAL(iv1.x, 7);
    CHECK_EQUAL(iv1.y, 10);

    iv1.sub(iv2);
    CHECK_EQUAL(iv1.x, 2);
    CHECK_EQUAL(iv1.y, 3);

    iv1.mul(3);
    CHECK_EQUAL(iv1.x, 6);
    CHECK_EQUAL(iv1.y, 9);

    iv1.div(3);
    CHECK_EQUAL(iv1.x, 2);
    CHECK_EQUAL(iv1.y, 3);

    ivec2 iv3;
    iv3.sub(10, iv1);
    CHECK_EQUAL(iv3.x, 8);
    CHECK_EQUAL(iv3.y, 7);

    CHECK_SIMILAR(iv1, (ivec2{ 2, 3 }), 0);
    CHECK(!iv1.similar(ivec2{ 2, 4 }, 0));
}
