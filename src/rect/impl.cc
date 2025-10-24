#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
    cv::Mat gray, bin;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::threshold(gray, bin, 128, 255, cv::THRESH_BINARY_INV);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(bin, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    double max_area = 0.0;
    int max_idx = 0;
    for(size_t i = 0; i < contours.size() ; i++)
    {
        double a = std::abs(cv::contourArea(contours[i]));
        if(a > max_area)
        {
            max_area = a;
            max_idx = i;
        }
        
    }
    
    res.first = cv::boundingRect(contours[max_idx]);
    res.second = cv::minAreaRect(contours[max_idx]);
    
    return res;
}