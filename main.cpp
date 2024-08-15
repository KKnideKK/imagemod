#include "guidedfilter.h"
#include<iostream>
using namespace std;
void text1(cv::Mat I)//ͼƬƽ��
{
    int r = 8; // try r=2, 4, or 8
    double eps = 0.4 * 2; // try eps=0.1^2, 0.2^2, 0.4^2

    eps *= 255 * 255;   
    cv::Mat q = guidedFilter(I, I, r, eps);

    //cv::imwrite("D:\\k.jpg", result);
    cv::namedWindow("Display Image1", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Display Image1", 800, 600);

    // �������ű���
    double scale = std::min(800.0 / q.cols, 600.0 / q.rows);

    // ������ű���С��1�����������
    if (scale < 1)
    {
        cv::resize(q, q, cv::Size(), scale, scale);
    }

    // ��ʾͼƬ
    cv::imshow("Display Image1", q);
}
void text2(cv::Mat I,cv::Mat p)//ȥ��
{
    int r = 8;
    double eps = 0.02 * 0.02;

    eps *= 255 * 255;   
    cv::Mat q = guidedFilter(p, I, r, eps);
    cv::namedWindow("Display Image2", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Display Image2", 800, 600);

    // �������ű���
    double scale = std::min(800.0 / q.cols, 600.0 / q.rows);

    // ������ű���С��1�����������
    if (scale < 1)
    {
        cv::resize(q, q, cv::Size(), scale, scale);
    }

    // ��ʾͼƬ
    cv::imshow("Display Image2", q);
}
void text3(cv::Mat I,cv::Mat p)//��
{
    int r = 60;
    double eps = 1e-6;

    eps *= 255 * 255;   
    cv::Mat q = guidedFilter(I, p, r, eps);

    //cv::imwrite("D:\\k.jpg", result);
    cv::namedWindow("Display Image3", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Display Image3", 800, 600);

    // �������ű���
    double scale = std::min(800.0 / q.cols, 600.0 / q.rows);

    // ������ű���С��1�����������
    if (scale < 1)
    {
        cv::resize(q, q, cv::Size(), scale, scale);
    }

    // ��ʾͼƬ
    cv::imshow("Display Image3", q);
}
void text4(cv::Mat I)//��ǿ
{
    I.convertTo(I, CV_32F, 1.0 / 255.0);

    cv::Mat p = I;

    int r = 16;
    double eps = 0.1 * 0.1;
    cv::Mat q = guidedFilter(I, I, r, eps);
    cv::Mat I_enhanced = (I - q) * 5 + q;
    cv::namedWindow("Display Image4", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Display Image4", 800, 600);

    // �������ű���
    double scale = std::min(800.0 / q.cols, 600.0 / q.rows);

    // ������ű���С��1�����������
    if (scale < 1)
    {
        cv::resize(q, q, cv::Size(), scale, scale);
    }

    // ��ʾͼƬ
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
    // ������ű���С��1�����������
    if (scale1 < 1)
    {
        cv::resize(I, I, cv::Size(), scale1, scale1);
        cv::resize(p, p, cv::Size(), scale1, scale1);
        cv::resize(L, L, cv::Size(), scale1, scale1);
    }

    cv::Mat flash(I.size(), I.type(), cv::Scalar(255, 255, 255));
    // 3. �ڿհ�ͼ���ϻ���һ����ɫ���Σ���������ͼ��
    cv::rectangle(flash, cv::Point(0, 0), cv::Point(I.cols, I.rows), cv::Scalar(255, 255, 255), -1);

    // 4. ��ԭͼ��հ�ͼ����л��
    cv::Mat result;
    double alpha = 0.2; // ����͸���ȣ���ΧΪ0��1
    cv::addWeighted(I, alpha, flash, 1 - alpha, 0, result);

    //cv::imshow("Display Image", I);//��ʾԭͼƬ
    //cv::imshow("Display Image P", p);//��ʾ�Ҷ�ͼƬ
    //cv::imshow("Display Image L", L);//��ʾ�ڰ�ͼƬ
    //cv::imshow("Display Image S", result);//��ʾ����ͼƬ
    text1(I);//ƽ��
    text2(I, result);//ȥ��
    text3(I,L);//��
    text4(I);//��ǿ
    
    // �ȴ������¼�
    cv::waitKey(0);
    std::cout << "Guided filter applied successfully." << std::endl;
	system("pause");
	return 0;
}