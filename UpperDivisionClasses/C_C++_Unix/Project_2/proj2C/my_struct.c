/* This file should contain the 9 functions defined in prototypes.h */

#include <prototypes.h>

void InitializeCircle(struct Shape *S, double radius, double origin, double originY){
    S->su.C.radius = radius;
    S->su.C.x = origin;
    S->su.C.y = originY;
    S->ft.GetArea = GetCircleArea;
    S->ft.GetBoundingBox = GetCircleBoundingBox;
};

void InitializeRectangle(struct Shape *S, double minX, double maxX, double minY, double maxY){
    S->su.R.minX = minX;
    S->su.R.minY = minY;
    S->su.R.maxX = maxX;
    S->su.R.maxY = maxY;
    S->ft.GetArea = GetRectangleArea;
    S->ft.GetBoundingBox = GetRectangleBoundingBox;
};
void InitializeTriangle(struct Shape *S, double pt1X, double pt2X, double minY, double maxY){
    S->su.T.pt1X = pt1X;
    S->su.T.pt2X = pt2X;
    S->su.T.minY = minY;
    S->su.T.maxY = maxY;
    S->ft.GetArea = GetTriangleArea;
    S->ft.GetBoundingBox = GetTriangleBoundingBox;
};

double GetCircleArea(struct Shape *S){
    double area = 3.14159*S->su.C.radius * S->su.C.radius;
    return area;
};
double GetRectangleArea(struct Shape *S){
    double area = (S->su.R.maxX - S->su.R.minX)*(S->su.R.maxY - S->su.R.minY);
    return area;
};
double GetTriangleArea(struct Shape *S){
    double area = (S->su.T.pt2X - S->su.T.pt1X)*(S->su.T.maxY - S->su.T.minY)/2;
    return area;
};

void GetCircleBoundingBox(struct Shape *S, double *bbox){
    bbox[0] = S->su.C.x - S->su.C.radius;
    bbox[1] = S->su.C.x + S->su.C.radius;
    bbox[2] = S->su.C.y - S->su.C.radius;
    bbox[3] = S->su.C.y + S->su.C.radius;
};
void GetRectangleBoundingBox(struct Shape *S, double *bbox){
    bbox[0] = S->su.R.minX;
    bbox[1] = S->su.R.maxX;
    bbox[2] = S->su.R.minY;
    bbox[3] = S->su.R.maxY;
};
void GetTriangleBoundingBox(struct Shape *S, double *bbox){
    bbox[0] = S->su.T.pt1X;
    bbox[1] = S->su.T.pt2X;
    bbox[2] = S->su.T.minY;
    bbox[3] = S->su.T.maxY;
};
