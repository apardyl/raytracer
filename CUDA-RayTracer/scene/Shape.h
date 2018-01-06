﻿#ifndef RAY_TRACER_SHAPE_H
#define RAY_TRACER_SHAPE_H

#include "Material.h"
#include "Triangle.h"

struct Shape {
private:
    Triangle *triangles;

public:
    Material material;
    int triangleCount;

    explicit Shape(int triangleCount);

    Shape(int triangleCount, const Material &material);

    Shape(const Shape &shape);
    Shape(Shape &&shape) noexcept;

    ~Shape();

    Shape& operator=(const Shape &shape);
};

#endif // RAY_TRACER_SHAPE_H