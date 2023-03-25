#include "LprojectionPlane.h"
#include <iostream>
#include <string>

// Method 1: using OpenCV
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    // Given point, plane normal and plane point
    // Point3d point(1, 2, 1);
    // Point3d point(1, 1, 1);
    Point3d point(2, 3, 4);
    Vec3d normal(1, 1, 1);
    Point3d plane_point(1, 0, 0);

    // Compute the projection
    Mat point_mat(point, CV_64FC1);
    Mat normal_mat(normal, CV_64FC1);
    Mat plane_point_mat(plane_point, CV_64FC1);
    double distance = abs(normal_mat.dot(point_mat - plane_point_mat)) / norm(normal_mat);
    Mat projection_mat =
        point_mat - (point_mat - plane_point_mat).dot(normal_mat) / (normal_mat.dot(normal_mat)) * normal_mat;
    Point3d projection(projection_mat);

    // Result
    cout << "Point: " << point << endl;
    cout << "Normal: " << normal << endl;
    cout << "Plane Point: " << plane_point << endl;
    cout << "Projection: " << projection << endl;
    return 0;
}

// Method 2: using simple c++
/*
int main()
{
    // Plane normal vector, coordinate of plane point
    double a = 1, b = 1, c = 1;
    double x0 = 1, y0 = 0, z0 = 0;

    // Coordinate of point to be projected
    double x = 1, y = 2, z = 1;

    // Compute vector from plane point to point
    double v1 = x - x0;
    double v2 = y - y0;
    double v3 = z - z0;

    // Compute projection
    double d = (a * v1 + b * v2 + c * v3) / (a * a + b * b + c * c);
    double x_p = x - d * a;
    double y_p = y - d * b;
    double z_p = z - d * c;

    cout << "point(" << x << "," << y << "," << z << ") to plane (" << x_p << "," << y_p << "," << z_p << ")" << endl;

    return 0;
}
*/