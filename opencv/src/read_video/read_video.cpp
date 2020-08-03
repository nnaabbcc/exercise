#include <opencv2/opencv.hpp>
#include <iostream>

int read_file(std::string filename)
{
    cv::Mat frame;
    cv::VideoCapture cap(filename);

    if (!cap.isOpened())
    {
        std::cerr << "Error! Unable to open video file "
            << filename;
        return -1;
    }

    auto width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    auto height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::cout << "Video Resolution is " << width << "x" << height << std::endl;

    auto fps = cap.get(cv::CAP_PROP_FPS);
    std::cout << "Video framerate is " << fps << std::endl;

    auto framecount = cap.get(cv::CAP_PROP_FRAME_COUNT);
    std::cout << "Video framecount is " << framecount << std::endl;

    for (int i = 0; i < 1000000; i++)
    {
        std::cout << "Frame " << i << std::endl;
        auto posFrames = cap.get(cv::CAP_PROP_POS_FRAMES);
        std::cout << "Pos Frames: " << posFrames << std::endl;

        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "End of file" << std::endl;
            break;
        }

        auto text = std::to_string(static_cast<int>(posFrames)) + "/"
            + std::to_string(static_cast<int>(framecount));
        cv::putText(frame, text,
            {20, 50}, cv::FONT_HERSHEY_SIMPLEX, 2, {255, 255, 0});

        cv::imshow(filename, frame);
        int ms = 25;
        if (fps < 1000)
        {
            ms = static_cast<int>(1000 / fps);
        }
        if (cv::waitKey(ms) >= 0)
        {
            break;
        }
    }

    return 0;
}

int read_camera()
{
    cv::Mat frame;
    cv::VideoCapture cap(0); // default camera

    if (!cap.isOpened())
    {
        std::cerr << "Error! Unable to open camera" << std::endl;
        return -1;
    }

    auto width = 1920;
    auto height = 1080;
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);

    auto windowName = "Camera 0";
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::resizeWindow(windowName, width, height);

    for (;;)
    {
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "End of file" << std::endl;
            break;
        }

        cv::imshow(windowName, frame);
        if (cv::waitKey(5) >= 0)
        {
            break;
        }
    }

    return 0;
}

int main(int, char**)
{
    auto readCamera = true;
    if (readCamera)
    {
        return read_camera();
    }
    else
    {
        auto fileName = "01.mp4";
        return read_file(fileName);
    }
}
