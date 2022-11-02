//
// Created by baldder on 7/28/21.
//

#include <iostream>
#include <QImage>
#include <complex>
#include "SeamCarver.h"

SeamCarver::SeamCarver(QImage picture) {
    this->picture = {picture};
}

QImage SeamCarver::getPicture() {
    return picture;
}

int SeamCarver::getWidth() {
    return picture.width();
}

int SeamCarver::getHeight() {
    return picture.height();
}

void SeamCarver::updateEnergy() {
    energy = new double *[getWidth()];

    for (int i = 0; i < getWidth(); i++) {
        energy[i] = new double[getHeight()];
    }

    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            energy[i][j] = getEnergy(i, j);
        }
    }
}

double SeamCarver::getEnergy(int x, int y) {
    if (x < 0 || x >= getWidth() || y < 0 || y >= getHeight()) {
        throw std::invalid_argument("Invalid pixel.");
    }

    if (x == 0 || x == getWidth() - 1 || y == 0 || y == getHeight() - 1) {
        return 1000;
    }

    double gradientXY = gradientX(x, y) + gradientY(x, y);

    return std::sqrt(gradientXY);
}

int *SeamCarver::findHorizontalSeam() {
    transpose();
    seam = findVerticalSeam();
    transpose();
    return seam;
}

int *SeamCarver::findVerticalSeam() {
    updateEnergy();
    auto **distTo = new double *[getWidth()];
    int **edgeTo = new int *[getWidth()];
    for (int i = 0; i < getWidth(); i++) {
        distTo[i] = new double[getHeight()];
        edgeTo[i] = new int[getHeight()];
    }

    for (int x = 0; x < getWidth(); x++) {
        for (int y = 0; y < getHeight(); y++) {
            distTo[x][y] = std::numeric_limits<double>::infinity();
        }
    }

    for (int x = 0; x < getWidth(); x++) {
        distTo[x][0] = this->energy[x][0];
    }

    for (int y = 0; y < getHeight(); y++) {
        for (int x = 0; x < getWidth(); x++) {

            if (y < getHeight() - 1 && x > 0) {
                if (distTo[x - 1][y + 1] > distTo[x][y] + this->energy[x - 1][y + 1]) {
                    distTo[x - 1][y + 1] = distTo[x][y] + this->energy[x - 1][y + 1];
                    edgeTo[x - 1][y + 1] = x;
                }
            }

            if (y < getWidth() - 1) {
                if (distTo[x][y + 1] > distTo[x][y] + this->energy[x][y + 1]) {
                    distTo[x][y + 1] = distTo[x][y] + this->energy[x][y + 1];
                    edgeTo[x][y + 1] = x;
                }
            }

            if (y < getHeight() - 1 && x < getWidth() - 1) {
                if (distTo[x + 1][y + 1] > distTo[x][y] + this->energy[x + 1][y + 1]) {
                    distTo[x + 1][y + 1] = distTo[x][y] + this->energy[x + 1][y + 1];
                    edgeTo[x + 1][y + 1] = x;
                }
            }

        }
    }

    int edgeSP = -1; // can be treated as index
    double energySP = std::numeric_limits<double>::infinity(); // can be treated as curr minimum

    for (int x = 0; x < getWidth(); x++) {
        if (energySP > distTo[x][getHeight() - 1]) {
            energySP = distTo[x][getHeight() - 1];
            edgeSP = x;
        }
    }

    seam = new int[getHeight()];

    int x = edgeSP;
    int y = getHeight() - 1;

    while (y >= 0) {
        seam[y] = x;
        x = edgeTo[x][y];
        y--;
    }

    return seam;
}

void SeamCarver::removeVerticalSeam(int seam[]) {
    QImage temp = {getWidth() - 1, getHeight(), QImage::Format_RGB32};
    int current = 0;
    for (int y = 0; y < getHeight(); y++) {
        for (int x = 0; x < getWidth(); x++) {
            if (x != seam[y]) {
                temp.setPixel(current, y, picture.pixel(x, y));
                current++;
            }
        }
        current = 0;
    }
    picture = temp;
}

void SeamCarver::removeHorizontalSeam(int seam[]) {
    QImage temp = {getWidth(), getHeight() - 1, QImage::Format_RGB32};
    int current = 0;
    for (int y = 0; y < getWidth(); y++) {
        for (int x = 0; x < getHeight(); x++) {
            if (x != seam[y]) {
                temp.setPixel(y, current, picture.pixel(y, x));
                current++;
            }
        }
        // refresh after each row
        current = 0;
    }
    picture = temp;
}

void SeamCarver::transpose() {
    QImage temp = {getHeight(), getWidth(), QImage::Format_RGB32};

    for (int i = 0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++) {
            temp.setPixel(i, j, picture.pixel(j, i));
        }
    }
    picture = temp;
}

// gradient x energy difference
int SeamCarver::gradientX(int x, int y) {
    QRgb left = picture.pixel(x - 1, y);
    QRgb right = picture.pixel(x + 1, y);

    int rright = qRed(right);
    int gright = qGreen(right);
    int bright = qBlue(right);

    int rleft = qRed(left);
    int gleft = qGreen(left);
    int bleft = qBlue(left);

    int rx = rright - rleft;
    int gx = gright - gleft;
    int bx = bright - bleft;

    return (rx * rx) + (gx * gx) + (bx * bx);
}

int SeamCarver::gradientY(int x, int y) {
    QRgb left = picture.pixel(x, y - 1);
    QRgb right = picture.pixel(x, y + 1);

    int rtop = qRed(right);
    int gtop = qGreen(right);
    int btop = qBlue(right);

    int rbottom = qRed(left);
    int gbottom = qGreen(left);
    int bbottom = qBlue(left);

    int ry = rtop - rbottom;
    int gy = gtop - gbottom;
    int by = btop - bbottom;

    return (ry * ry) + (gy * gy) + (by * by);
}