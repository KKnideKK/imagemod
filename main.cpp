#include "guidedfilter.h"
#include<iostream>
using namespace std;
void text1(cv::Mat I)//图片平滑
{
    int r = 8; // try r=2, 4, or 8
    double eps = 0.4 * 2; // try eps=0.1^2, 0.2^2, 0.4^2

    eps *= 255 * 255;   
    cv::Mat q = guidedFilter(I, I, r, eps);

    //cv::imwrite("D:\\k.jpg", result);
    cv::namedWindow("Display Image1", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Display Image1", 800, 600);

    // 计算缩放比例
    double scale = std::min(800.0 / q.cols, 600.0 / q.rows);

    // 如果缩放比例小于1，则进行缩放
    if (scale < 1)
    {
        cv::resize(q, q, cv::Size(), scale, scale);
    }

    // 显示图片
    cv::imshow("Display Image1", q);
}
void text2(cv::Mat I,cv::Mat p)//去噪
{
    int r = 8;
    double eps = 0.02 * 0.02;

    eps *= 255 * 255;   
    cv::Mat q = guidedFilter(p, I, r, eps);
    cv::namedWindow("Display Image2", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Display Image2", 800, 600);

    // 计算缩放比例
    double scale = std::min(800.0 / q.cols, 600.0 / q.rows);

    // 如果缩放比例小于1，则进行缩放
    if (scale < 1)
    {
        cv::resize(q, q, cv::Size(), scale, scale);
    }

    // 显示图片
    cv::imshow("Display Image2", q);
}
void text3(cv::Mat I,cv::Mat p)//羽化
{
    int r = 60;
    double eps = 1e-6;

    eps *= 255 * 255;   
    cv::Mat q = guidedFilter(I, p, r, eps);

    //cv::imwrite("D:\\k.jpg", result);
    cv::namedWindow("Display Image3", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Display Image3", 800, 600);

    // 计算缩放比例
    double scale = std::min(800.0 / q.cols, 600.0 / q.rows);

    // 如果缩放比例小于1，则进行缩放
    if (scale < 1)
    {
        cv::resize(q, q, cv::Size(), scale, scale);
    }

    // 显示图片
    cv::imshow("Display Image3", q);
}
void text4(cv::Mat I)//增强
{
    I.convertTo(I, CV_32F, 1.0 / 255.0);

    cv::Mat p = I;

    int r = 16;
    double eps = 0.1 * 0.1;
    cv::Mat q = guidedFilter(I, I, r, eps);
    cv::Mat I_enhanced = (I - q) * 5 + q;
    cv::namedWindow("Display Image4", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Display Image4", 800, 600);

    // 计算缩放比例
    double scale = std::min(800.0 / q.cols, 600.0 / q.rows);

    // 如果缩放比例小于1，则进行缩放
    if (scale < 1)
    {
        cv::resize(q, q, cv::Size(), scale, scale);
    }

    // 显示图片
    cv::imshow("Display Image4", I_enhanced);
}
int main()
{
    cv::Mat I = cv::imread("D:\\2.jpg", cv::IMREAD_COLOR);
   
    if (I.empty())
    {
        std::cout << "Error: Could not open input image." << std::endl;
        return -1;
    }
    cv::Mat p;
    cv::cvtColor(I, p, cv::COLOR_BGR2GRAY);
    cv::Mat L;
    cv::threshold(p, L, 128, 255, cv::THRESH_BINARY);
    //cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    //cv::resizeWindow("Display Image", 800, 600);
    cv::Mat p1 = I;
    double scale1 = std::min(800.0 / p1.cols, 600.0 / p1.rows);
    // 如果缩放比例小于1，则进行缩放
    if (scale1 < 1)
    {
        cv::resize(I, I, cv::Size(), scale1, scale1);
        cv::resize(p, p, cv::Size(), scale1, scale1);
        cv::resize(L, L, cv::Size(), scale1, scale1);
    }

    cv::Mat flash(I.size(), I.type(), cv::Scalar(255, 255, 255));
    // 3. 在空白图像上绘制一个白色矩形，覆盖整个图像
    cv::rectangle(flash, cv::Point(0, 0), cv::Point(I.cols, I.rows), cv::Scalar(255, 255, 255), -1);

    // 4. 将原图与空白图像进行混合
    cv::Mat result;
    double alpha = 0.2; // 设置透明度，范围为0到1
    cv::addWeighted(I, alpha, flash, 1 - alpha, 0, result);

    //cv::imshow("Display Image", I);//显示原图片
    //cv::imshow("Display Image P", p);//显示灰度图片
    //cv::imshow("Display Image L", L);//显示黑白图片
    //cv::imshow("Display Image S", result);//显示闪光图片
    text1(I);//平滑
    text2(I, result);//去噪
    text3(I,L);//羽化
    text4(I);//增强
    
    // 等待按键事件
    cv::waitKey(0);
    std::cout << "Guided filter applied successfully." << std::endl;
	system("pause");
	return 0;
}