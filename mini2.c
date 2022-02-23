#include <stdio.h>
#include <float.h>
#include <math.h>

struct Point {
    double x, y;
};

struct Vec2 {
    double x, y;
    double sqrMagnitude;
};

typedef struct Point Point;
typedef struct Vec2 Vec2;

Vec2 toEdge(Point from, Point to)
{
    Point vector = { to.x - from.x, to.y - from.y };
    double sqrMagnitude = vector.x * vector.x + vector.y * vector.y;

    Vec2 result = { vector.x, vector.y, sqrMagnitude };
    return result;
}

void printEdge(Vec2 edge, char* name)
{
    printf("%s: X:%lf Y:%lf sqrMagnitude:%lf\n", name, edge.x, edge.y, edge.sqrMagnitude);
}

int isRightTriangle(Point a, Point b, Point c)
{
    Vec2 edge1 = toEdge(a, b);
    Vec2 edge2 = toEdge(a, c);
    Vec2 edge3 = toEdge(b, c);

    printEdge(edge1, "edge1");
    printEdge(edge2, "edge2");
    printEdge(edge3, "edge3");

    Vec2 hypotenuse;
    Vec2 leg1;
    Vec2 leg2;

    if (edge1.sqrMagnitude > edge2.sqrMagnitude && edge1.sqrMagnitude > edge3.sqrMagnitude)
    {
        hypotenuse = edge1;
        leg1 = edge2;
        leg2 = edge3;
    }else if (edge2.sqrMagnitude > edge1.sqrMagnitude && edge2.sqrMagnitude > edge3.sqrMagnitude)
    {
        hypotenuse = edge2;
        leg1 = edge1;
        leg2 = edge3;
    }else if (edge3.sqrMagnitude > edge1.sqrMagnitude && edge3.sqrMagnitude > edge2.sqrMagnitude)
    {
        hypotenuse = edge3;
        leg1 = edge1;
        leg2 = edge2;
    }

    printEdge(hypotenuse, "hypotenuse");
    printEdge(leg1, "leg1");
    printEdge(leg2, "leg2");

    double dotProduct = leg1.x * leg2.x + leg1.y * leg2.y;
    printf("%lf\n", dotProduct);
    dotProduct = fabs(dotProduct);
    printf("%lf\n", dotProduct);

    return dotProduct <= FLT_EPSILON;
}

int main(){
    Point a = {4.1, 0.000001};
    Point b = {0, 4.0};
    Point c = {0, 0};

    printf("%d", isRightTriangle(a, b, c));
}