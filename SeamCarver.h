//
// Created by baldder on 7/28/21.
//

#ifndef CLIONPROJECTS_SEAMCARVER_H
#define CLIONPROJECTS_SEAMCARVER_H

#include <iostream>
#include <QImage>

class SeamCarver {
private:
    QImage picture;
    double **energy;
    int *seam;

    void updateEnergy();

    void transpose();

    int gradientX(int x, int y);

    int gradientY(int x, int y);

public:
    SeamCarver(QImage picture);

    QImage getPicture();

    int getWidth();

    int getHeight();

    double getEnergy(int x, int y);

    int* findHorizontalSeam();

    int* findVerticalSeam();

    void removeVerticalSeam(int seam[]);

    void removeHorizontalSeam(int seam[]);

};


#endif //CLIONPROJECTS_SEAMCARVER_H
