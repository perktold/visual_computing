#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/geometry.hpp>
using namespace cv;

int main() {
    Mat image = imread("ex_01.jpg");
    Mat image2;
    namedWindow("Transformed", WINDOW_NORMAL);
    
    //perspective transform
    Point2f persp_src[4] = {
        {647, 571},
        {2515, 565},
        {3019, 3401},
        {132, 3396}
    };

    Point2f persp_dst[4] = {
        {0, 0},
        {(float)image.cols, 0},
        {(float)image.cols, (float)image.rows},
        {0, (float)image.rows}
    };
    
    warpPerspective(image, image2, getPerspectiveTransform(persp_src, persp_dst), image.size());

    imwrite("ex_01_perspective.jpg", image2);
    imshow("Transformed", image2);
    setWindowProperty(
        "Transformed",
        WND_PROP_FULLSCREEN,
        WINDOW_FULLSCREEN
    );
    waitKey(0);

    //affine transform

    Point2f affine_src[3] = {
        {647, 571},
        {2515, 565},
        {132, 3396}
    };

    Point2f affine_dst[3] = {
        {0,0},
        {(float)image.cols, 0},
        {0, (float)image.rows}
    };

    Mat affine_matrix = getAffineTransform(affine_src, affine_dst);
    warpAffine(image, image2, affine_matrix, image.size());

    //manual application of affine transformation matrix to point
    Point2f original_point(3019, 3401);

    Point2f transformed_point;

    transformed_point.x =
        affine_matrix.at<double>(0, 0) * original_point.x +
        affine_matrix.at<double>(0, 1) * original_point.y +
        affine_matrix.at<double>(0, 2);

    transformed_point.y =
        affine_matrix.at<double>(1, 0) * original_point.x +
        affine_matrix.at<double>(1, 1) * original_point.y +
        affine_matrix.at<double>(1, 2);
    
    std::cout << "x: " << transformed_point.x << ", y: " << transformed_point.y;
    imwrite("ex_01_affine.jpg", image2);
    imshow("Transformed", image2);

    waitKey(0);
    destroyAllWindows();
}
