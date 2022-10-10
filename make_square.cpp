#include <opencv2/opencv.hpp>
#include <time.h>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>
#include <experimental/filesystem>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("2 arguments needed !\n");
        return 0;
    }
    string data_direc = argv[1];
    string square_direc = argv[2];

    struct stat info;

    if (stat(data_direc.c_str(), &info) != 0)
    {
        printf("Data directory doesn't exits\n");
        return 0;
    }

    if (stat(square_direc.c_str(), &info) != 0)
    {
        printf("creating square data folder...\n");
        mkdir(square_direc.c_str(), 0777);
    }
    else if (info.st_mode & S_IFDIR)
    {
        printf("data folder already exists\n");

        int flag;
        printf("Clean up the files in data folder? [1-Yes|0-No] ");
        cin >> flag;

        if (flag)
        {
            printf("cleaning data faolder...\n");
            std::experimental::filesystem::remove_all(square_direc);
            mkdir(square_direc.c_str(), 0777);
        }
        else
        {
            printf("Re-run with new directory\n");
            return 0;
        }
    }

    for (const auto & entry : fs::directory_iterator(data_direc))
    {
        cv::Mat image1 = cv::imread(entry.path());

        // create the square container
        int dstWidth = max(image1.cols, image1.rows);
        int dstHeight = max(image1.cols, image1.rows);
        cv::Mat dst = cv::Mat(dstHeight, dstWidth, CV_8UC3, cv::Scalar(0, 0, 0));

        // Put the image into the container, roi is the new position
        cv::Rect roi(cv::Rect((dstWidth - image1.cols) / 2, (dstHeight - image1.rows) / 2, image1.cols, image1.rows));
        cv::Mat targetROI = dst(roi);
        image1.copyTo(targetROI);

        // View the result
        // cv::namedWindow("OpenCV Window");
        // cv::imshow("OpenCV Window", dst);

        // wait key for 5000 ms
        // cv::waitKey(25);

        int file_pos = string(entry.path()).find("/");

        cout << square_direc + "/" + string(entry.path()).substr(file_pos + 1) << endl;
        cv::imwrite(square_direc + "/" + string(entry.path()).substr(file_pos + 1), dst);
    }    
    return 0;
}
