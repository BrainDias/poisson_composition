#include <iostream>
#include "opencv2/opencv.hpp"
#include <string>
#include <algorithm>

cv::Mat hfitted_output(std::vector<cv::Mat> &images){
        const std::vector<cv::Mat>::iterator min_img = 
        std::min_element(images.begin(), images.end(),
            [](const cv::Mat& im1, const cv::Mat& im2){return im1.size[0] < im2.size[0];}
        );

        const auto resize = [](cv::Mat& im){
            cv::resize(im, im, cv::Size(150,150));
        };

        std::for_each(images.begin(), images.end(), resize);

        cv::Mat result = *images.begin();

        for(auto it = images.begin(); it != images.end(); ++it){
            cv::hconcat(result, *it, result);
        }
        return result;
}

int main(int argc, const char** argv) {
    cv::Mat fg_img = cv::imread("foreground_im.jpg", cv::IMREAD_ANYCOLOR);
    cv::Mat bg_img = cv::imread("background_im.jpg", cv::IMREAD_ANYCOLOR);
    cv::Mat temp;
    if (bg_img.empty() || fg_img.empty()) {
        std::cout << "Error: Image cannot be loaded." << std::endl;
        system("pause");
        return -1;
    }
    temp = fg_img.clone();
    const std::string winName = "Image Window";
    cv::namedWindow(winName);

    while(true){
        if(drawing_box) draw_box(temp,box);
        std::vector<cv::Mat> images{temp, bg_img};
        cv::imshow(winName,hfitted_output(images));
        if (cv::waitKey(15) == 27) break;
    }

    return 0;
}


