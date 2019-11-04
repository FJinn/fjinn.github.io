# Place for FUN

Here will not allow full project folder, but just one or two files(.h/.cpp) from project ~~or something else~~ :thinking:

**Begin with article/book reading -> Google/Youtube for further learning/understanding -> Implementation -> HERE :smiley:**

## [Bezier Curve](/FunProjects/BezierCurve.h)
Put it in a simple way, it is a (curve) line from Point A to Point B, in 0-1 time, with a control point.

A point's position in a Bezier Curve line is based on the position of a point in three lines at the time(t).

Three lines: Point A to Control Point (Line 1), Control Point to Point B (Line 2), Line 1 to Line 2 (Line 3) based on time(t) at Line 1 and Line 2.

Bezier Curve is formed based on the point at time(t) in Line 3. 

Example of how the curve is formed: 
1. When t = 0, Line 3 = Point A at Line 1 -> Control Point at Line 2, Bezier Curve point will be at the start of Line 3 (Point A) as well.
2. When t = 0.5, Line 3 = Line 1 middle point -> Line 2 middle point, Bezier Curve point will be at the middle of Line 3.
2. When t = 1, Line 3 = Control Point at Line 1 -> Point B at Line 2, Bezier Curve point will be at the end of Line 3 (Point B).

_


## [GJK Algorithm](/FunProjects/GJKAlgorithm.cpp)

[Casey Muratori](https://youtu.be/Qupqu1xe7Io) and [Igor Kroitor](https://github.com/kroitor/gjk.c) are **must-see-reference**.

GJK algorithm is an algorithm for collision detection for convex polygon.
Only 2D is implemented/tested/coded here.

The basic idea: 
1. Get Minkowski difference between two polygons.
2. If the result shape contains origin (0,0,0), there are intersection between the polyons. No intersection if origin is not within the result shape.

The 'detail' process (to know the **WHY and Real Details**, refer to the reference link above):
1. Support function
   1. Get the furthest point using Minkowski difference from two polygons with the direction vector provided and put it in a container (for simplexes).
2. Loop
   1. First, get another simplex point using Support function with opposite direction vector.   
  **Note: if the dot product of new point and the search direction vector is lesser than 0, means the new point does not pass through origin, so it is impossible for the result shape to contain origin. Thus, not collision.**
   2. Second, get third point using Support function with direction vector pointing toward origin from the line formed by the previous 2 points in simplex container. **3D will be a tetrahedron/3-simplex (0-simplex is a point, 1-simplex is a line, 2-simplex is a triangle etc.)**
   3. For 2D, if there are 3 points to form a triangle, check if the triangle contains origin.
   4. If origin is found, there is collision.
   5. If not, there isn't. Continue to Support function by providing a direction vector toward origin then Loop again.
