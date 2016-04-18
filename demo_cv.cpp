#include <iostream>
#include <thread>
#include "include/Defs/defs.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "3rdParty/tinyXML/tinyxml2.h"
#include <cmath>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;

int main()
{
    try {
        using namespace tutorial;

        cv::Mat image;
        image = cv::imread("rgb_00000.png", CV_LOAD_IMAGE_COLOR);   // Read the file

        if(! image.data ) {                              // Check for invalid input
            cout <<  "Could not open or find the image" << std::endl ;
            return -1;
        }

        cv::namedWindow( "Srcimg", cv::WINDOW_AUTOSIZE );// Create a window for display.
        cv::imshow( "Srcimg", image );                   // Show our image inside it.


        cv::GaussianBlur( image, image, cv::Size( 21, 21 ), 5, 5 );
        cv::namedWindow( "Gaussian Blur", cv::WINDOW_AUTOSIZE );// Create a window for display.
        cv::imshow( "Gaussian Blur", image );

        cv::Mat gray;
        /// Convert the image to grayscale
        cv::cvtColor( image, gray, CV_BGR2GRAY );

        cv::namedWindow( "Gray", cv::WINDOW_AUTOSIZE );// Create a window for display.
        cv::imshow( "Gray", gray );


        cv::Mat detectedEdges;

        int lowThreshold=10;
        int ratio = 3;
        int kernel_size = 3;

        cv::Canny( gray, detectedEdges, lowThreshold, lowThreshold*ratio, kernel_size );
        cv::namedWindow( "edges", cv::WINDOW_AUTOSIZE );// Create a window for display.
        cv::imshow( "edges", detectedEdges );                   // Show our image inside it.

        cv::Mat depth;
        depth = cv::imread("depth_00000.png", CV_LOAD_IMAGE_ANYDEPTH);   // Read the file
        cv::namedWindow( "depth", cv::WINDOW_AUTOSIZE );// Create a window for display.
        cv::imshow( "depth", depth );

        cv::waitKey(0);                                          // Wait for a keystroke in the window
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
