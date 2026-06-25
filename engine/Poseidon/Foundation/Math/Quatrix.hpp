#pragma once

#ifdef _MSC_VER
#include <intrin.h>
#elif defined(__x86_64__) || defined(__i386__)
#include <xmmintrin.h>
#elif defined(__aarch64__) || defined(__arm__)
#include <sse2neon/sse2neon.h>
#endif

namespace Poseidon::Foundation
{
typedef __m128 Vec4M128[4];

struct Quatrix4
{
    Vec4M128 qa[3];

    operator Vec4M128*() { return qa; }
    operator const Vec4M128*() const { return qa; }
};

typedef __m128 Vec3M128[3];

struct Quatrix3
{
    Vec3M128 qa[3];

    operator Vec3M128*() { return qa; }
    operator const Vec3M128*() const { return qa; }
};

} // namespace Poseidon::Foundation

using ::Poseidon::Foundation::Quatrix3;
using ::Poseidon::Foundation::Quatrix4;
