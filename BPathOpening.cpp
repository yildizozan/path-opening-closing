
#include <iostream>
#include "BPathOpening.h"

/**
 *
 * @param input
 */
BPathOpening::BPathOpening(const Mat &input) : input(input) {
    this->xdim = input.rows;
    this->ydim = input.cols;

    this->aux = new Mat(this->xdim, this->ydim, CV_8SC1);
    for (int row = 0; row < this->xdim; ++row) {
        for (int col = 0; col < this->ydim; ++col) {
            this->aux->at<char>(row, col, 0) = -1;
        }
    }

//    std::cout << *this->aux; // Checkpoint
}

void BPathOpening::traverse() {
    Mat img = this->input;
    for (int row = 0; row < img.rows; ++row) {
        uchar *p = img.ptr(row);
        for (int col = 0; col < img.cols; ++col) {
            std::cout << this->convertBool(*p++);
        }
        std::cout << std::endl;
    }
}

bool BPathOpening::convertBool(uchar value) {
    return value != 0;
}

uint BPathOpening::getXYBoolean(uint x, uint y) {
    return convertBool(this->input.at<uchar>(x, y));
}

/**
 * South to North
 * @param x
 * @param y
 * @return
 */
uint BPathOpening::computeUpwardSN(uint x, uint y) {
    if (!this->getXYBoolean(x, y)) {
        this->setXYCInt(*this->aux, x, y, 0, 0);
    } else {
        int l1;
        if (x - 1 >= 0 && y + 1 <= this->ydim - 1) {
            l1 = this->getXYCInt(*this->aux, x - 1, y + 1, 0);
        } else {
            l1 = 0;
        }

        int l2;
        if (y + 1 <= this->ydim - 1) {
            l2 = this->getXYCInt(*this->aux, x, y + 1, 0);
        } else {
            l2 = 0;
        }

        int l3;
        if (x + 1 <= this->xdim - 1 && y + 1 <= this->ydim - 1) {
            l3 = this->getXYCInt(*this->aux, x + 1, y + 1, 0);
        } else {
            l3 = 0;
        }

        if (l1 == -1) {
            l1 = this->computeUpwardSN(x - 1, y + 1);
        }

        if (l2 == -1) {
            l2 = this->computeUpwardSN(x, y + 1);
        }

        if (l3 == -1) {
            l3 = this->computeUpwardSN(x + 1, y + 1);
        }

        int lamda = 1 + std::max(l1, std::max(l2, l3));
        this->setXYCInt(*this->aux, x, y, 0, lamda);
        return lamda;
    }
    return 0;
}

void BPathOpening::setXYCInt(Mat &dst, uint x, uint y, uint c, uchar p) {
    dst.at<uchar>(x, y, c) = p;
}

uint BPathOpening::getXYCInt(Mat &dst, uint x, uint y, uint c) {
    return (uint) this->input.at<uchar>(x, y);
}

uint BPathOpening::computeDownwardSN(uint x, uint y) {

    if (!this->getXYBoolean(x, y)) {
        this->setXYCInt(*this->aux, x, y, 1, 0);
        return 0;
    } else {
        int l1;
        if (x - 1 >= 0 && y - 1 >= 0) {
            l1 = this->getXYCInt(*this->aux, x - 1, y - 1, 1);
        } else {
            l1 = 0;
        }

        int l2;
        if (y - 1 >= 0) {
            l2 = this->getXYCInt(*this->aux, x, y - 1, 1);
        } else {
            l2 = 0;
        }

        int l3;
        if (x + 1 <= this->xdim - 1 && y - 1 >= 0) {
            l3 = this->getXYCInt(*this->aux, x + 1, y - 1, 1);
        } else {
            l3 = 0;
        }

        if (l1 == -1) {
            l1 = this->computeDownwardSN(x - 1, y - 1);
        }

        if (l2 == -1) {
            l2 = this->computeDownwardSN(x, y - 1);
        }

        if (l3 == -1) {
            l3 = this->computeDownwardSN(x + 1, y - 1);
        }

        int lamda = 1 + std::max(l1, std::max(l2, l3));
        this->setXYCInt(*this->aux, x, y, 1, lamda);
        return lamda;
    }
}

void BPathOpening::start() {

    Mat outputSN(this->xdim, this->ydim, CV_8SC1);
    this->fillMatrix(outputSN, 0);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat temp;
    erode(this->input, temp, kernel);
    dilate(temp, this->output, kernel);
}

void BPathOpening::fillMatrix(Mat mat, schar value) {
    for (int row = 0; row < mat.rows; ++row) {
        for (int col = 0; col < mat.cols; ++col) {
            mat.at<char>(row, col) = value;
        }
    }
}

const Mat &BPathOpening::getOutput() const {
    return output;
}
