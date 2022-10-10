#include <opencv2/opencv.hpp>
#include <time.h>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>
#include <experimental/filesystem>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        printf("3 arguments needed !\n");
        return 0;
    }
    int fps = atoi(argv[3]);
    string direc = argv[2];
    string vid_file = argv[1];

    struct stat info;

    if (stat(vid_file.c_str(), &info) != 0)
    {
        printf("Video doesn't exits\n");
        return 0;
    }

    if (stat(direc.c_str(), &info) != 0)
    {
        printf("creating data folder...\n");
        mkdir(direc.c_str(), 0777);
    }        
    else if (info.st_mode & S_IFDIR) 
    {
        printf("data folder already exists\n");

        int flag;
        printf("Clean up the files in data folder? [1-Yes|0-No] ");
        cin >> flag;

        if(flag)
        {
            printf("cleaning data faolder...\n");
            std::experimental::filesystem::remove_all(direc);
            mkdir(direc.c_str(), 0777);
        }
        else
        {
            printf("Re-run with new directory\n");
            return 0;
        }                    
    } 

    VideoCapture video(vid_file);

    int frames = 0;
    int saved = 0;
    Mat img;
    while(1)
    {
        video >> img;
        if(img.empty())
            break;
        else
            frames ++;

        if((frames%fps) == 1)
        {
            string name = direc + "/frame" + to_string(frames) + ".jpg";
            cout << "Saving... " << name << endl;

            imwrite(name, img);
            saved++;
        }
    }

    cout << "Total no of frames : " << frames << endl;
    cout << "Total no of frames saved : " << saved << endl;

    video.release();
    return 0;
}
