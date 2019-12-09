#include <iostream>
#include "unistd.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "BPathOpening.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv) {

    if (argc != 2) {
        perror("Arg wrong! ./path_opening <file path>");
    }

    Mat src = imread(argv[1], IMREAD_UNCHANGED);

    // Check for invalid input
    if (!src.data) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    auto *opening = new BPathOpening(src);
    opening->traverse();
    std::cout << "Traverse complete" << std::endl;
    std::cout << std::endl;
    opening->start();


    FileStorage file("result.png", FileStorage::WRITE);
    file << "result" << opening->getOutput();

    return 0;
}
