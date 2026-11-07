#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    Mat img = imread("arnold_schwarzenegger.jpg");
    if(img.empty())
       return -1;
    imshow("arnold_schwarzenegger", img);
    waitKey(0);
    return 0;
}



