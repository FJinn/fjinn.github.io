# -> [Bezier Curve](/FunProjects/BezierCurve.h) <-

<img src="https://raw.githubusercontent.com/FJinn/fjinn.github.io/master/FunProjects/Image/BezierCurve.jpg?raw=true"/>

Put it in a simple way, it is a (curve) line from Point A (Green) to Point B (Yellow), in 0-1 time, with a control point(Point where both line are connected).

A point's position in a Bezier Curve line is based on the position of a point in three lines at the time(t).

Three lines: Point A to Control Point (Line 1), Control Point to Point B (Line 2), Line 1 to Line 2 (Line 3) based on time(t) at Line 1 and Line 2.

Bezier Curve is formed based on the point at time(t) in Line 3 (Black). 

Example of how the curve is formed: 
1. When t = 0, Line 3 = Point A at Line 1 -> Control Point at Line 2, Bezier Curve point will be at the start of Line 3 (Point A) as well.
2. When t = 0.5, Line 3 = Line 1 middle point -> Line 2 middle point, Bezier Curve point will be at the middle of Line 3.
2. When t = 1, Line 3 = Control Point at Line 1 -> Point B at Line 2, Bezier Curve point will be at the end of Line 3 (Point B).
