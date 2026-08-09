#include "../include/xrMath.h"
#include "xrTest.h"
#include <cmath>
#include <limits>

void test_vector3_float()
{
    fvec3 v1 = { 1.0f, 2.0f, 3.0f };
    fvec3 v2;
    v2.set(4.0f, 5.0f, 6.0f);
    CHECK_SIMILAR(v2, (fvec3{ 4.0f, 5.0f, 6.0f }), FLOAT_EPS);

    v2.set(v1);
    CHECK_SIMILAR(v2, (fvec3{ 1.0f, 2.0f, 3.0f }), FLOAT_EPS);

    fvec3 v3 = { -1.0f, 2.0f, -3.0f };
    v3.abs({ -4.0f, 5.0f, -6.0f });
    CHECK_SIMILAR(v3, (fvec3{ 4.0f, 5.0f, 6.0f }), FLOAT_EPS);

    fvec3 a = { 2.0f, 5.0f, -1.0f };
    fvec3 b = { 3.0f, 1.0f,  4.0f };
    a.min(b);
    CHECK_SIMILAR(a, (fvec3{ 2.0f, 1.0f, -1.0f }), FLOAT_EPS);
    a.set(2.0f, 5.0f, -1.0f);
    a.max(b);
    CHECK_SIMILAR(a, (fvec3{ 3.0f, 5.0f, 4.0f }), FLOAT_EPS);

    fvec3 c;
    c.min(a, b);
    CHECK_SIMILAR(c, (fvec3{ 3.0f, 1.0f, 4.0f }), FLOAT_EPS);
    c.max(a, b);
    CHECK_SIMILAR(c, (fvec3{ 3.0f, 5.0f, 4.0f }), FLOAT_EPS);

    fvec3 p = { 1.0f, 2.0f, 3.0f };
    fvec3 q = { 3.0f, 2.0f, 1.0f };
    p.add(q);
    CHECK_SIMILAR(p, (fvec3{ 4.0f, 4.0f, 4.0f }), FLOAT_EPS);
    p.sub(q);
    CHECK_SIMILAR(p, (fvec3{ 1.0f, 2.0f, 3.0f }), FLOAT_EPS);

    p.add(2.0f);
    CHECK_SIMILAR(p, (fvec3{ 3.0f, 4.0f, 5.0f }), FLOAT_EPS);
    p.sub(1.0f);
    CHECK_SIMILAR(p, (fvec3{ 2.0f, 3.0f, 4.0f }), FLOAT_EPS);

    fvec3 r;
    r.add(p, q);
    CHECK_SIMILAR(r, (fvec3{ 5.0f, 5.0f, 5.0f }), FLOAT_EPS);
    r.sub(p, q);
    CHECK_SIMILAR(r, (fvec3{ -1.0f, 1.0f, 3.0f }), FLOAT_EPS);

    r.add(p, 10.0f);
    CHECK_SIMILAR(r, (fvec3{ 12.0f, 13.0f, 14.0f }), FLOAT_EPS);
    r.sub(p, 2.0f);
    CHECK_SIMILAR(r, (fvec3{ 0.0f, 1.0f, 2.0f }), FLOAT_EPS);

    fvec3 m = { 2.0f, 3.0f, 4.0f };
    m.mul(q);
    CHECK_SIMILAR(m, (fvec3{ 6.0f, 6.0f, 4.0f }), FLOAT_EPS);
    m.div(q);
    CHECK_SIMILAR(m, (fvec3{ 2.0f, 3.0f, 4.0f }), FLOAT_EPS);

    m.mul(0.5f);
    CHECK_SIMILAR(m, (fvec3{ 1.0f, 1.5f, 2.0f }), FLOAT_EPS);
    m.div(2.0f);
    CHECK_SIMILAR(m, (fvec3{ 0.5f, 0.75f, 1.0f }), FLOAT_EPS);

    fvec3 n;
    n.mul(p, q);
    CHECK_SIMILAR(n, (fvec3{ 6.0f, 6.0f, 4.0f }), FLOAT_EPS);
    n.mul(p, 3.0f);
    CHECK_SIMILAR(n, (fvec3{ 6.0f, 9.0f, 12.0f }), FLOAT_EPS);
    n.div(p, q);
    CHECK_SIMILAR(n, (fvec3{ 2.0f / 3.0f, 1.5f, 4.0f }), FLOAT_EPS);
    n.div(p, 2.0f);
    CHECK_SIMILAR(n, (fvec3{ 1.0f, 1.5f, 2.0f }), FLOAT_EPS);

    fvec3 inv = { 1.0f, -2.0f, 3.0f };
    inv.invert();
    CHECK_SIMILAR(inv, (fvec3{ -1.0f, 2.0f, -3.0f }), FLOAT_EPS);
    fvec3 src = { 3.0f, -4.0f, 5.0f };
    inv.invert(src);
    CHECK_SIMILAR(inv, (fvec3{ -3.0f, 4.0f, -5.0f }), FLOAT_EPS);

    fvec3 d1 = { 1.0f, 0.0f, 0.0f };
    fvec3 d2 = { 0.0f, 1.0f, 0.0f };
    fvec3 d3 = { 0.0f, 0.0f, 1.0f };
    CHECK_CLOSE(d1.dotproduct(d2), 0.0f, FLOAT_EPS);
    CHECK_CLOSE(d1.dotproduct(d1), 1.0f, FLOAT_EPS);
    fvec3 cross_res;
    cross_res.crossproduct(d1, d2);
    CHECK_SIMILAR(cross_res, d3, FLOAT_EPS);
    cross_res.crossproduct(d2, d1);
    CHECK_SIMILAR(cross_res, (fvec3{ 0.0f, 0.0f, -1.0f }), FLOAT_EPS);
    cross_res.crossproduct(d2, d3);
    CHECK_SIMILAR(cross_res, d1, FLOAT_EPS);

    fvec3 len = { 1.0f, 2.0f, 2.0f };
    CHECK_CLOSE(len.magnitude(), 3.0f, FLOAT_EPS);
    CHECK_CLOSE(len.square_magnitude(), 9.0f, FLOAT_EPS);
    fvec3 other = { 0.0f, 0.0f, 0.0f };
    CHECK_CLOSE(len.distance_to(other), 3.0f, FLOAT_EPS);
    CHECK_CLOSE(len.distance_to_sqr(other), 9.0f, FLOAT_EPS);
    fvec3 h_point = { 1.0f, 10.0f, 2.0f };
    CHECK_CLOSE(len.distance_to_xz(h_point), 0.0f, FLOAT_EPS);
    CHECK_CLOSE(len.distance_to_xz_sqr(h_point), 0.0f, FLOAT_EPS);

    fvec3 norm_v = { 1.0f, 2.0f, 2.0f };
    norm_v.normalize();
    CHECK_CLOSE(norm_v.magnitude(), 1.0f, FLOAT_EPS);
    CHECK_SIMILAR(norm_v, (fvec3{ 1.0f / 3.0f, 2.0f / 3.0f, 2.0f / 3.0f }), FLOAT_EPS);

    norm_v.set(0.0f, 0.0f, 0.0f);
    norm_v.normalize_safe();
    CHECK_SIMILAR(norm_v, (fvec3{ 0.0f, 0.0f, 0.0f }), FLOAT_EPS);

    fvec3 target;
    target.normalize({ 0.0f, 3.0f, 4.0f });
    CHECK_SIMILAR(target, (fvec3{ 0.0f, 0.6f, 0.8f }), FLOAT_EPS);
    target.normalize_safe({ 0.0f, 0.0f, 0.0f });
    CHECK_SIMILAR(target, (fvec3{ 0.0f, 0.6f, 0.8f }), FLOAT_EPS);

    fvec3 len_v = { 3.0f, 4.0f, 0.0f };
    float mag = len_v.normalize_magn();
    CHECK_CLOSE(mag, 5.0f, FLOAT_EPS);
    CHECK_CLOSE(len_v.magnitude(), 1.0f, FLOAT_EPS);
    len_v.set(3.0f, 4.0f, 0.0f);
    len_v.set_length(10.0f);
    CHECK_CLOSE(len_v.magnitude(), 10.0f, FLOAT_EPS);
    CHECK_SIMILAR(len_v, (fvec3{ 6.0f, 8.0f, 0.0f }), FLOAT_EPS);

    fvec3 mad_res;
    mad_res = { 0.0f, 0.0f, 0.0f };
    mad_res.mad({ 1.0f, 0.0f, 0.0f }, 2.0f);
    CHECK_SIMILAR(mad_res, (fvec3{ 2.0f, 0.0f, 0.0f }), FLOAT_EPS);

    mad_res.set(1.0f, 2.0f, 3.0f);
    mad_res.mad({ 1.0f, 0.0f, 0.0f }, 3.0f);
    CHECK_SIMILAR(mad_res, (fvec3{ 4.0f, 2.0f, 3.0f }), FLOAT_EPS);

    mad_res.mad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, 5.0f);
    CHECK_SIMILAR(mad_res, (fvec3{ 5.0f, 0.0f, 0.0f }), FLOAT_EPS);

    mad_res.mad({ 1.0f, 2.0f, 3.0f }, { 2.0f, 3.0f, 4.0f }, (fvec3{ 1.0f, 1.0f, 1.0f }));
    CHECK_SIMILAR(mad_res, (fvec3{ 1.0f + 2.0f * 1.0f, 2.0f + 3.0f * 1.0f, 3.0f + 4.0f * 1.0f }), FLOAT_EPS);

    fvec3 base = { 1.0f, 2.0f, 3.0f };
    fvec3 avg;
    avg.average(base, { 3.0f, 4.0f, 5.0f });
    CHECK_SIMILAR(avg, (fvec3{ 2.0f, 3.0f, 4.0f }), FLOAT_EPS);
    avg.average({ 0.0f, 0.0f, 0.0f }, { 10.0f, 10.0f, 10.0f });
    CHECK_SIMILAR(avg, (fvec3{ 5.0f, 5.0f, 5.0f }), FLOAT_EPS);

    fvec3 lerp_res;
    lerp_res.lerp({ 0.0f, 0.0f, 0.0f }, { 10.0f, 20.0f, 30.0f }, 0.2f);
    CHECK_SIMILAR(lerp_res, (fvec3{ 2.0f, 4.0f, 6.0f }), FLOAT_EPS);

    fvec3 inert = { 10.0f, 10.0f, 10.0f };
    inert.inertion({ 0.0f, 0.0f, 0.0f }, 0.8f);
    CHECK_SIMILAR(inert, (fvec3{ 8.0f, 8.0f, 8.0f }), FLOAT_EPS);

    fvec3 clp = { 5.0f, -2.0f, 10.0f };
    clp.clamp({ 0.0f, 0.0f, 0.0f }, { 4.0f, 4.0f, 4.0f });
    CHECK_SIMILAR(clp, (fvec3{ 4.0f, 0.0f, 4.0f }), FLOAT_EPS);

    clp.set(5.0f, -2.0f, 10.0f);
    clp.clamp({ 3.0f, 3.0f, 3.0f });
    CHECK_SIMILAR(clp, (fvec3{ 3.0f, -2.0f, 3.0f }), FLOAT_EPS);

    fvec3 sq = { 0.001f, -0.002f, 0.003f };
    sq.squeeze(0.01f);
    CHECK_SIMILAR(sq, (fvec3{ 0.0f, 0.0f, 0.0f }), FLOAT_EPS);

    fvec3 al = { 3.0f, 5.0f, 4.0f };
    al.align();
    CHECK_SIMILAR(al, (fvec3{ 0.0f, 0.0f, 1.0f }), FLOAT_EPS);
    al.set(5.0f, 1.0f, 3.0f);
    al.align();
    CHECK_SIMILAR(al, (fvec3{ 1.0f, 0.0f, 0.0f }), FLOAT_EPS);

    fvec3 arr = { 10.0f, 20.0f, 30.0f };
    CHECK_CLOSE(arr[0], 10.0f, FLOAT_EPS);
    CHECK_CLOSE(arr[1], 20.0f, FLOAT_EPS);
    CHECK_CLOSE(arr[2], 30.0f, FLOAT_EPS);
    arr[0] = 100.0f; arr[1] = 200.0f; arr[2] = 300.0f;
    CHECK_CLOSE(arr.x, 100.0f, FLOAT_EPS);
    CHECK_CLOSE(arr.y, 200.0f, FLOAT_EPS);
    CHECK_CLOSE(arr.z, 300.0f, FLOAT_EPS);
    CHECK_EQUAL(&arr[0], &arr.x);
    CHECK_EQUAL(&arr[1], &arr.y);
    CHECK_EQUAL(&arr[2], &arr.z);

    fvec3 vhp;
    vhp.setHP(0.0f, 0.0f);
    CHECK_SIMILAR(vhp, (fvec3{ 0.0f, 0.0f, 1.0f }), FLOAT_EPS);
    float h, pitch;
    vhp.getHP(h, pitch);
    CHECK_CLOSE(h, 0.0f, FLOAT_EPS);
    CHECK_CLOSE(pitch, 0.0f, FLOAT_EPS);

    fvec3 east = { 1.0f, 0.0f, 0.0f };
    CHECK_CLOSE(east.getH(), -PI_DIV_2, FLOAT_EPS);
    CHECK_CLOSE(east.getP(), 0.0f, FLOAT_EPS);

    fvec3 up = { 0.0f, 1.0f, 0.0f };
    CHECK_CLOSE(up.getH(), 0.0f, FLOAT_EPS);
    CHECK_CLOSE(up.getP(), PI_DIV_2, FLOAT_EPS);

    fvec3 dir = { 1.0f, 0.0f, 0.0f };
    fvec3 norm = { 0.0f, 1.0f, 0.0f };
    fvec3 ref;
    ref.reflect(dir, norm);
    CHECK_SIMILAR(ref, (fvec3{ 1.0f, 0.0f, 0.0f }), FLOAT_EPS);

    dir = { 1.0f, 1.0f, 0.0f };
    norm = { 0.0f, 1.0f, 0.0f };
    ref.reflect(dir, norm);
    CHECK_SIMILAR(ref, (fvec3{ 1.0f, -1.0f, 0.0f }), FLOAT_EPS);

    fvec3 sld;
    sld.slide(dir, norm);
    CHECK_SIMILAR(sld, (fvec3{ 1.0f, 0.0f, 0.0f }), FLOAT_EPS);

    fvec3 axis = { 0.0f, 1.0f, 0.0f };
    fvec3 up_vec, right_vec;
    template_vector3<float>::generate_orthonormal_basis(axis, up_vec, right_vec);
    CHECK_CLOSE(up_vec.magnitude(), 1.0f, FLOAT_EPS);
    CHECK_CLOSE(right_vec.magnitude(), 1.0f, FLOAT_EPS);
    CHECK_CLOSE(up_vec.dotproduct(axis), 0.0f, FLOAT_EPS);
    CHECK_CLOSE(right_vec.dotproduct(axis), 0.0f, FLOAT_EPS);
    CHECK_CLOSE(up_vec.dotproduct(right_vec), 0.0f, FLOAT_EPS);

    fvec3 check_axis;
    check_axis.crossproduct(right_vec, up_vec);
    CHECK_SIMILAR(check_axis, axis, FLOAT_EPS);

    fvec3 vA = { 0.0f, 0.0f, 0.0f };
    fvec3 vB = { 1.0f, 0.0f, 0.0f };
    fvec3 vC = { 0.0f, 1.0f, 0.0f };
    fvec3 vD = { 0.0f, 0.0f, 1.0f };
    fvec3 bary_res;
    bary_res.from_bary(vA, vB, vC, 1.0f, 0.0f, 0.0f);
    CHECK_SIMILAR(bary_res, vA, FLOAT_EPS);
    bary_res.from_bary(vA, vB, vC, 0.0f, 0.5f, 0.5f);
    CHECK_SIMILAR(bary_res, (fvec3{ 0.5f, 0.5f, 0.0f }), FLOAT_EPS);
    bary_res.from_bary4(vA, vB, vC, vD, 0.0f, 0.0f, 0.0f, 1.0f);
    CHECK_SIMILAR(bary_res, vD, FLOAT_EPS);

    fvec3 p0 = { 0.0f, 0.0f, 0.0f };
    fvec3 p1 = { 1.0f, 0.0f, 0.0f };
    fvec3 p2 = { 0.0f, 1.0f, 0.0f };
    fvec3 nrm;
    nrm.mknormal_non_normalized(p0, p1, p2);
    CHECK_SIMILAR(nrm, (fvec3{ 0.0f, 0.0f, 1.0f }), FLOAT_EPS);
    nrm.mknormal(p0, p1, p2);
    CHECK_CLOSE(nrm.magnitude(), 1.0f, FLOAT_EPS);
    CHECK_SIMILAR(nrm, (fvec3{ 0.0f, 0.0f, 1.0f }), FLOAT_EPS);

    fvec3 op1 = { 1.0f, 2.0f, 3.0f };
    fvec3 op2 = { 3.0f, 2.0f, 1.0f };

    CHECK_SIMILAR(-op1, (fvec3{ -1.0f, -2.0f, -3.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op1 + op2, (fvec3{ 4.0f, 4.0f, 4.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op1 - op2, (fvec3{ -2.0f, 0.0f, 2.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op1 + 10.0f, (fvec3{ 11.0f, 12.0f, 13.0f }), FLOAT_EPS);
    CHECK_SIMILAR(10.0f + op1, (fvec3{ 11.0f, 12.0f, 13.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op1 - 0.5f, (fvec3{ 0.5f, 1.5f, 2.5f }), FLOAT_EPS);

    fvec3 s_minus_v = 5.0f - op1;
    CHECK_SIMILAR(s_minus_v, (fvec3{ 4.0f, 3.0f, 2.0f }), FLOAT_EPS);

    CHECK_SIMILAR(op1 * 3.0f, (fvec3{ 3.0f, 6.0f, 9.0f }), FLOAT_EPS);
    CHECK_SIMILAR(3.0f * op1, (fvec3{ 3.0f, 6.0f, 9.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op2 / 2.0f, (fvec3{ 1.5f, 1.0f, 0.5f }), FLOAT_EPS);

    fvec3 s_div_v = 10.0f / op2;
    CHECK_SIMILAR(s_div_v, (fvec3{ 10.0f / 3.0f, 5.0f, 10.0f }), FLOAT_EPS);

    CHECK_SIMILAR(op1 * op2, (fvec3{ 3.0f, 4.0f, 3.0f }), FLOAT_EPS);
    CHECK_SIMILAR(op2 / op1, (fvec3{ 3.0f, 1.0f, 1.0f / 3.0f }), FLOAT_EPS);

    CHECK_EQUAL(op1 == op1, true);
    CHECK_EQUAL(op1 != op2, true);

    fvec3 valid_v = { 1.0f, 2.0f, 3.0f };
    CHECK_EQUAL(_valid(valid_v), TRUE);
    fvec3 nan_v = { std::numeric_limits<float>::quiet_NaN(), 0.0f, 0.0f };
    CHECK_EQUAL(_valid(nan_v), FALSE);

    fvec3 en = { 0.0f, 3.0f, 4.0f };
    exact_normalize(en);
    CHECK_CLOSE(en.magnitude(), 1.0f, FLOAT_EPS);
}

void test_vector3_int()
{
    ivec3 iv1 = { 2, 3, 4 };
    ivec3 iv2 = { 5, 6, 7 };

    iv1.add(iv2);
    CHECK_EQUAL(iv1.x, 7);
    CHECK_EQUAL(iv1.y, 9);
    CHECK_EQUAL(iv1.z, 11);

    iv1.sub(iv2);
    CHECK_EQUAL(iv1.x, 2);
    CHECK_EQUAL(iv1.y, 3);
    CHECK_EQUAL(iv1.z, 4);

    iv1.mul(3);
    CHECK_EQUAL(iv1.x, 6);
    CHECK_EQUAL(iv1.y, 9);
    CHECK_EQUAL(iv1.z, 12);

    iv1.div(3);
    CHECK_EQUAL(iv1.x, 2);
    CHECK_EQUAL(iv1.y, 3);
    CHECK_EQUAL(iv1.z, 4);

    ivec3 iv3;
    iv3.sub(10, iv1);
    CHECK_EQUAL(iv3.x, 8);
    CHECK_EQUAL(iv3.y, 7);
    CHECK_EQUAL(iv3.z, 6);

    CHECK_SIMILAR(iv1, (ivec3{ 2, 3, 4 }), 0);
    CHECK(!iv1.similar(ivec3{ 2, 3, 5 }, 0));
}
