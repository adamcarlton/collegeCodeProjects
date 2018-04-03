/* This file should contain your struct definitions for Circle, Triangle, and 
   Rectangle */
struct Circle
{
    double x;
    double y;
    double radius;
};

struct Rectangle
{
    double minX;
    double minY;
    double maxX;
    double maxY;
};

struct Triangle
{
    double pt1X;
    double pt2X;
    double maxY;
    double minY;
};

struct Shape;

typedef struct FunctionTable
{
    double (*GetArea)(struct Shape *);
    void (*GetBoundingBox)(struct Shape *, double *);
} FunctionTable;

typedef enum ShapeType
{
    Circle,
    Rectangle,
    Triangle
} ShapeType;

typedef union ShapeUnion
{
    struct Circle C;
    struct Rectangle R;
    struct Triangle T;
} ShapeUnion;

struct Shape
{
    ShapeUnion su;
    ShapeType st;
    FunctionTable ft;
};
