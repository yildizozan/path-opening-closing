//
// Created by yildizozan on 12/5/19.
//

#ifndef PATH_OPENING_BPATHOPENING_H
#define PATH_OPENING_BPATHOPENING_H

#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

class BPathOpening {
public:
    BPathOpening(const Mat &input);

    void start();

    uint getXYBoolean(uint x, uint y);

    void traverse(); // For checkpoint
    const Mat &getOutput() const;

private:
    Mat input, output, *aux;
    uint xdim, ydim;

    bool convertBool(uchar value);

    void setXYCInt(Mat &dst, uint x, uint y, uint c, uchar p);

    uint getXYCInt(Mat &dst, uint x, uint y, uint c);

    uint computeUpwardSN(uint x, uint y);

    uint computeDownwardSN(uint x, uint y);

    uint computeUpwardWE(uint x, uint y);

    uint computeDownwardWE(uint x, uint y);

    uint computeUpwardSWNE(uint x, uint y);

    uint computeDownwardSWNE(uint x, uint y);

    uint computeUpwardNWSE(uint x, uint y);

    uint computeDownwardNWSE(uint x, uint y);

    void fillMatrix(Mat mat, schar i);
};


#endif //PATH_OPENING_BPATHOPENING_H
