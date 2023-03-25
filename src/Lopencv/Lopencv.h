#pragma once

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void minSquare(std::string imagePathDir, std::string imageName)
{
    // Load image
    Mat image = imread(imagePathDir + imageName, IMREAD_COLOR);
    if (image.empty())
        cerr << "Could not open or find the image " << imagePathDir + imageName << endl;

    // Gray image and edge detection
    Mat gray, edges;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    Canny(gray, edges, 50, 200, 3);

    // Find contours
    vector<vector<Point>> contours;
    findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Merge contours (need only one contour for minAreaRect to work properly)
    vector<Point> all_contours;
    for (size_t i = 0; i < contours.size(); i++)
    {
        all_contours.insert(all_contours.end(), contours[i].begin(), contours[i].end());
    }

    RotatedRect minRect = minAreaRect(all_contours);
    double utilization_ratio = (minRect.size.width * minRect.size.height) / (image.cols * image.rows);

    auto enable_printRect = [=]() {
        std::cout << "\nminRect Info:\n";
        std::cout << "\tminRect.size.width:\t" << minRect.size.width << std::endl;
        std::cout << "\tminRect.size.height:\t" << minRect.size.height << std::endl;
        std::cout << "\tminRect.angle:\t\t" << minRect.angle << std::endl;
        std::cout << "\tminRect.center.x:\t" << minRect.center.x << std::endl;
        std::cout << "\tminRect.center.y:\t" << minRect.center.y << std::endl;
        std::cout << "\tUtilization ratio:\t" << utilization_ratio * 100.0 << "%" << std::endl;
    };

    // Draw contours on the original image
    auto enable_drawContoursOnOriginal = [=]() {
        // Draw contours on the original image
        Point2f rect_points[4];
        minRect.points(rect_points);
        for (int j = 0; j < 4; j++)
        {
            line(image, rect_points[j], rect_points[(j + 1) % 4], Scalar(0, 0, 255), 2);
        }

        // Show the result
        namedWindow("Original Image", WINDOW_NORMAL);
        resizeWindow("Original Image", image.cols, image.rows);
        imshow("Original Image", image);

        // Write the result to disk
        // imwrite(imagePathDir + "\\" + imageName + "_miniRect.png", image);

        waitKey();
    };

    // Draw contours on the rotated image
    auto enable_rotate = [=]() {
        // Define rotation matrix
        double angle = minRect.angle;
        double scale = 1.0 / sqrt(utilization_ratio);
        Size size(image.cols, image.rows);

        // Get the rotation matrix with the specifications above
        Point2f center(minRect.center.x, minRect.center.y);
        Mat M = getRotationMatrix2D(center, angle, scale);

        // Apply rotation to the image
        Mat rotated;
        warpAffine(image, rotated, M, size, INTER_LINEAR, BORDER_CONSTANT, Scalar());

        // Show the result
        namedWindow("Rotated Image", WINDOW_NORMAL);
        resizeWindow("Rotated Image", rotated.cols, rotated.rows);
        imshow("Rotated Image", rotated);

        // Write the rotated image to disk
        // imwrite(imagePathDir + "\\" + imageName + "_rotated_miniRect.png", rotated);

        waitKey();
    };

    enable_printRect();
    enable_drawContoursOnOriginal();
    enable_rotate();
}
