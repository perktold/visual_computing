#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/geometry.hpp>
#include <string>
#include <filesystem>
using namespace cv;
using namespace std;

void transformations() {
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

    imwrite("ex01/ex_01_perspective.jpg", image2);
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
    imwrite("ex01/ex_01_affine.jpg", image2);
    imshow("Transformed", image2);

    waitKey(0);
    destroyAllWindows();
}

void gabor_filter() {
    Mat img = imread("arnold_schwarzenegger.jpg", IMREAD_GRAYSCALE);
    img.convertTo(img, CV_32F, 1.0 / 255);

    const double sigma = 3, lambda = 7.0, gamma = 0.5, psi = 0;
    const int ksize = 31;
    const int angles[4] = {0, 45, 90, 135};

    // initialize Matrix for combined kernels with smallest possible float
    Mat combined(img.size(), CV_32F, Scalar(-FLT_MAX));
    Mat first = Mat();

    for (int i = 0; i < 4; ++i) {
        double theta = angles[i] * CV_PI / 180.0;

        // compute kernel
        Mat kernel = getGaborKernel(Size(ksize, ksize), sigma, theta, lambda, gamma, psi, CV_32F);

        // filter image
        Mat resp;
        filter2D(img, resp, CV_32F, kernel);

        // combine results by taking the max value of each pixel
        max(combined, resp, combined);

        // normalize to 0-255 for saving
        Mat k8, r8;
        normalize(kernel, k8, 0, 255, NORM_MINMAX, CV_8U);
        normalize(resp, r8, 0, 255, NORM_MINMAX, CV_8U);

        std::string a = std::to_string(angles[i]);
        imwrite("gabor/kernel_" + a + ".png", k8);
        imwrite("gabor/result_" + a + ".png", r8);
    }

    Mat c8;
    normalize(combined, c8, 0, 255, NORM_MINMAX, CV_8U);
    imwrite("gabor/tmp.png", c8);
    imshow("combined", c8);
    waitKey(0);
}

void gaussian_pyramid() {

    Mat image = imread("arnold_schwarzenegger.jpg");
    Mat image2;
    Mat final_image;
    Mat kernel = (Mat_<float>(1, 5) << 1.0f, 4.0f, 6.0f, 4.0f, 1.0f) / 16.0f;
    namedWindow("Transformed", WINDOW_NORMAL);

    for(int i = 0; i <= 4; i++){
        pyrDown(image, image2);
        image = final_image.clone();
        string image_name = "ex02/ex_02_" + to_string(i + 1) + ".jpg";
        imwrite(image_name, image);
        imshow("Transformed", image);
        waitKey(0);
        setWindowProperty("Transformed", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
    }
    destroyAllWindows();
}

void laplacian_pyramid() {
    Mat image = imread("arnold_schwarzenegger.jpg");
    vector<Mat> pyramid;
    vector<Mat> laplacian;
    Mat expanded;
    Mat difference;
    namedWindow("Transformed", WINDOW_NORMAL);
    setWindowProperty("Transformed", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
    buildPyramid (image, pyramid, 4);
    
    for (int i = 0; i < 4; i++) {
        pyrUp(pyramid[i + 1], expanded, pyramid[i].size());
        subtract(pyramid[i], expanded, difference, noArray(), CV_16SC3);
        laplacian.push_back(difference.clone());
        string image_name = "laplacian/ex_03_" + to_string(i + 1) + ".jpg";
        Mat display;
        normalize(difference, display, 0, 255, NORM_MINMAX);
        display.convertTo(display, CV_8UC3);

        imwrite(image_name, display);
        imshow("Transformed", display);
        waitKey(0);
    }
    laplacian.push_back(pyramid[4]);
    destroyAllWindows();
}

void canny_edge(){
    Mat img = imread("arnold_schwarzenegger.jpg", IMREAD_GRAYSCALE);
    Mat otsuImage;
    namedWindow("Transformed", WINDOW_NORMAL);
    setWindowProperty("Transformed", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

    double otsuThreshold = threshold(img, otsuImage, 0, 255, THRESH_BINARY | THRESH_OTSU);
    double lowerThreshold = 0.5 * otsuThreshold;
    double upperThreshold = otsuThreshold;
    Mat edges;
    Canny(img, edges, lowerThreshold, upperThreshold);

    imshow("Transformed", img);
    waitKey(0);

    imwrite("ex04/canny_edge.jpg", edges);
    imshow("Transformed", edges);
    waitKey(0);
}

int main() {
   laplacian_pyramid();
}
