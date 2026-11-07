#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/geometry.hpp>
using namespace cv;

int main() {
    Mat image = imread("ex_01.jpg");
    Mat image2;

    Point2f src[4] = {
        {647, 571},
        {2515, 565},
        {3019, 3401},
        {132, 3396}
    };

    Point2f dst[4] = {
        {0, 0},
        {(float)image.cols, 0},
        {(float)image.cols, (float)image.rows},
        {0, (float)image.cols}
    };
    
    warpPerspective(image, image2, getPerspectiveTransform(src, dst), image.size());

    imshow("gangang", image2);
    waitKey(0);
    destroyAllWindows();
}
