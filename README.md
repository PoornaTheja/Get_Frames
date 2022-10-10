# Get_Frames
Get the frames from a video with user specified FPS

## Compile get_frames.cpp
``` g++ -std=c++17 get_frames.cpp -lstdc++fs -o out `pkg-config --cflags --libs opencv4` ```

(This may change according to your c++ version and opencv)

## Run get_frames.py
`./out arg1 arg2 arg3`
- arg1 - Video file name
- arg2 - Data directory name
- arg3 - FPS

Eg : `./out video.mp4 data 10`
#

# Make_square
Reshape the images into square

## Compile make_square.cpp
``` g++ -std=c++17 make_square.cpp -lstdc++fs -o out `pkg-config --cflags --libs opencv4` ```

(This may change according to your c++ version and opencv)

## Run make_square.py
`./out arg1 arg2`
- arg1 - Data directory name (Input)
- arg2 - Target directory name (Output)

Eg : `./out data square_data`
