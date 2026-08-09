# X-Ray Advanced Math Coding Standard
## This document defines the coding style, conventions, and architectural rules for the X-Ray Advanced Math library.
## The primary inspirations and constraints are:

### 1. X-Ray Engine Legacy (Compatibility, familiar naming for original engine developers, specific optimization macros).
### 2. Modern C++23 Standard (Transitioning legacy hacks to modern standard library features where performance allows).
### 3. Extreme Performance (SIMD readiness, bitwise math, forced inlining).

---
# All new code and refactored legacy code must conform to these guidelines.

## 1. Naming Conventions

### 1.1. Templates and Base Math Structures
Base math structures must be defined as templates and prefixed with `template_` (snake_case).
**Good:** `template_vector2`, `template_matrix4x4`, `template_quaternion`.

### 1.2. Concrete Types and Aliases
Use short, lowercase names for concrete types, following the established engine patterns (`f` for float, `d` for double, `i` for int, `u` for unsigned).
**Good:** `fvec2`, `dvec2`, `ivec2`, `fmat4x4`, `Fquaternion`.

Always define common internal aliases inside structural templates to simplify refactoring:
```cpp
typedef T TYPE;
typedef template_vector2<T> Self;
typedef Self& SelfRef;
typedef const Self& SelfCRef;
```

### 1.3. Methods and Functions
Use `snake_case` or plain lowercase for math operations and general methods.
**Good:** `add`, `sub`, `mul`, `build_projection`, `transform_tiny`, `normalize_safe`.

*Exception:* Legacy X-Ray specific rotation/coordinate methods may use `camelCase` or `PascalCase` if deeply integrated, but new methods should prefer `snake_case`.
**Allowed legacy:** `setHPB`, `rotationYawPitchRoll`.

### 1.4. Variables and Parameters
Use lowercase or `camelCase`. Avoid using Hungarian notation (like `fSinYaw`, `vView`) in new code; prefer semantic names.
**Bad:** `fDotProduct`, `vWorldUp`
**Good:** `dotProduct`, `worldUp`, `axis`, `angle`

### 1.5. Macros and Compile-Time Constants
Macros and constant values must be `UPPER_SNAKE_CASE`.
**Good:** `UNIT_TOLERANCE`, `PI_DIV_2`.

Bitwise float masks should retain the `fd` prefix followed by uppercase.
**Good:** `fdSGN`, `fdNAN`, `fdEXPO`.

## 2. Formatting

### 2.1. Braces
Opening braces must ALWAYS be placed on a new line (**Allman style**).

```cpp
IC SelfRef invert(const Self& a)
{
    x = -a.x;
    y = -a.y;
    return *this;
}
```

### 2.2. Indentation
Use **Tabs** or **4 spaces** consistently (ensure your `.editorconfig` is set up).
**Important X-Ray specific rule:** Access modifiers (`public:`, `private:`) are indented by one level, and class members are indented by one additional level.

```cpp
template <class T> struct template_quaternion
{
  public:
    typedef T TYPE;
    // ...
  private:
    IC T _asin_(T _x)
    {
        // ...
    }
};
```

### 2.3. Structs over Classes
For mathematical primitives, prefer `struct` over `class`, even if access modifiers (`private:`) are used. This maintains consistency with the original X-Ray codebase.

## 3. Macros and Preprocessor Directives

### 3.1. Include Guards
Always use `#pragma once` at the very top of header files.

### 3.2. Warning Suppression
If `#pragma warning` is necessary, wrap it tightly around the affected code using `push` and `pop`.
```cpp
#pragma warning(push)
#pragma warning(disable : 4201)
// Code with nameless structs/unions
#pragma warning(pop)
```

### 3.3. Inlining Macros
Do not use standard `inline` for math primitives. Use the engine-specific optimization macros (usually defined in core headers):
*   `IC` — Standard inline request.
*   `ICF` — Force inline (`__forceinline` or `__attribute__((always_inline))`).
*   `ICN` — No inline / specific linkage.

```cpp
ICF SelfRef set(float _u, float _v)
{
    x = T(_u);
    y = T(_v);
    return *this;
}
```

## 4. Performance & Math Specifics

### 4.1. Fast Math and Approximations
When providing approximate functions (e.g., Taylor series for trig, bitwise inverse square root), prefix them with `apx_`.
**Good:** `apx_InvSqrt`, `apx_asin`.

### 4.2. Return `*this` by Reference
Math operations that modify the object itself must return a reference to self (`SelfRef`) to allow method chaining.
```cpp
IC SelfRef translate_add(const Tvector& Loc)
{
    c.add(Loc);
    return *this;
}

// Allows: mat.identity().scale(2.f).translate_add(pos);
```

### 4.3. Unions for Memory Layout
Use anonymous structs inside unions to allow multiple ways to access mathematical data (e.g., as individual scalars, basis vectors, or 2D arrays).
```cpp
union {
    struct { T _11, _12, _13, _14; };
    struct { Tvector i; T _14_; };
    T m[4][4];
};
```

## 5. Modern C++23 Transition (Refactoring Guidelines)

Since the project targets **C++23**, legacy X-Ray constructs should be gradually modernized without sacrificing performance:

### 5.1. Bitwise Type Punning
**Legacy:** Pointer casting for bitwise math (`*(int*)&f`). This is Undefined Behavior (UB) in modern C++.
**Modern (C++20/23):** Use `std::bit_cast<u32>(f)` from `<bit>`.
```cpp
// BAD (Legacy UB):
IC bool fis_denormal(const float& f) { return !(*(int*)&f & 0x7f800000); }

// GOOD (C++20+):
#include <bit>
IC bool fis_denormal(const float& f) { return !(std::bit_cast<u32>(f) & 0x7f800000); }
```

### 5.2. Standard Math Libraries
Where legacy code implements custom versions of standard algorithms simply because the old MSVC compiler was slow, benchmark and replace them with standard C++ features if performance is equal or better.
(e.g., `std::abs`, `std::min`, `std::max` instead of macros).

### 5.3. Compile-Time Math
Leverage `constexpr` for mathematical constants and simple functions. Future iterations of templates should attempt to make methods `constexpr IC` or `constexpr ICF` where applicable.

## 6. Code Example

```cpp
#pragma once

#include "xrMath_utils.h"

template <class T> struct template_vector2
{
  public:
    typedef T TYPE;
    typedef template_vector2<T> Self;
    typedef Self& SelfRef;
    typedef const Self& SelfCRef;

  public:
    T x, y;

    ICF SelfRef set(T _x, T _y)
    {
        x = _x;
        y = _y;
        return *this;
    }

    IC SelfRef add(SelfCRef p)
    {
        x += p.x;
        y += p.y;
        return *this;
    }

    IC T dotproduct(SelfCRef p) const
    {
        return x * p.x + y * p.y;
    }

    // Modern C++ standard compatibility
    IC bool similar(SelfCRef p, T epsilon = EPS_L) const
    {
        return std::abs(x - p.x) <= epsilon && std::abs(y - p.y) <= epsilon;
    }
};

typedef template_vector2<float> fvec2;
typedef template_vector2<double> dvec2;
typedef template_vector2<int> ivec2;
```
