# 🧮 linalg — Lightweight Linear Algebra Library
`linalg` is a modern, header-only C++ library providing efficient and type-safe vector and matrix operations for 2D, 3D, and 4D computations. Designed for graphics, simulations, and general-purpose numerical code, it offers a minimal yet powerful API for everyday linear algebra tasks.

## ✨ Features
- `Vec2`, `Vec3`, `Vec4` and `Mat3`, `Mat4` with templated types
- Common arithmetic operations and dot products
- Element-wise operations: `cwiseMin`, `cwiseMax`, `cwiseClamp`, `cwiseProduct`
- Vector ↔ Matrix multiplication
- Utility functions like `getRotationMatrix`, `toVec3`, `toVec4`
- Compact and readable code with no external dependencies

## 📦 Installation
Simply copy the include/ folder into your project. The library is header-only — no need to build or link anything.

```cpp
#include "linalg.hpp"
```

## 🧑‍💻 Example Usage

```cpp
#include "linalg.hpp"

using namespace linalg;

int main() {
    Vec3<float> a{1.0f, 2.0f, 3.0f};
    Vec3<float> b{4.0f, 5.0f, 6.0f};

    float d = dot(a, b); // 1*4 + 2*5 + 3*6 = 32

    Vec3<float> clamped = cwiseClamp(a, Vec3<float>{0.0f}, Vec3<float>{2.0f, 2.5f, 2.8f});
    Vec3<float> scaled = 2.0f * a;

    Mat3<float> rotation = getRotationMatrix(0.0f, 0.0f, 3.1415f);
    Vec3<float> rotated = rotation * a;

    return 0;
}
```