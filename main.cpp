#include <string>
#include <iomanip>
#include <iostream>

#include <opencv2/opencv.hpp>

std::string getDatetime()
{
    time_t t = time(nullptr);
    const tm* localTime = localtime(&t);
    std::stringstream s;

    s << "20" << localTime->tm_year - 100;
    s << std::setw(2) << std::setfill('0') << localTime->tm_mon + 1;
    s << std::setw(2) << std::setfill('0') << localTime->tm_mday;
    s << std::setw(2) << std::setfill('0') << localTime->tm_hour;
    s << std::setw(2) << std::setfill('0') << localTime->tm_min;
    s << std::setw(2) << std::setfill('0') << localTime->tm_sec;

    return s.str();
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " " << "/path/to/video" << std::endl;
        std::cout << "Exit." << std::endl;
        return -1;
    }

    cv::VideoCapture cap(argv[1]);

    if (!cap.isOpened())
    {
        std::cerr << "capture failed: " << argv[1] << std::endl;
        std::cout << "Exit." << std::endl;
        return -1;
    }
    cv::Mat frame;
    while (cap.read(frame))
    {
        cv::imshow("frame", frame);

        const int key = cv::waitKey(1) & 0xFF;
        if (key == 'q' || key == 27)
        {
            std::cout << "Exit." << std::endl;
            break;
        }
        else if (key == 's')
        {
            std::string filepath = "./" + getDatetime() + ".jpg";
            cv::imwrite(filepath.c_str(), frame);
            std::cout << "save image: " << filepath << std::endl;
        }
    }

    cv::destroyAllWindows();
    return 0;
}
