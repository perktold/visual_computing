#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main() {
    Mat image = imread("ex01.jpg");
    Mat image2;

    Point2f src[4] = {
        {647, 571},
        {2515, 565},
        {3019, 3401},
        {132, 3396}
    };

    Point2f dst[4] = {
        {0, 0},
        {3000, 0},
        {3000, 4000},
        {0, 4000}
    };
    
    warpPerspective(image, image, getPerspectiveTransform(src, dst), image.size());
}