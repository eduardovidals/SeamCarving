//
// Created by baldder on 7/28/21.
//

#include <iostream>
#include <QImage>
#include <QImageReader>
#include "SeamCarver.h"
#include <chrono>
#include <QApplication>
#include <QPixmap>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app = {argc, argv};
    QImage inputImg;
    inputImg.load("/Users/baldder/CLionProjects/Algorithms/week7.seamcarving/Images/beach.jpg");

    int removeColumns = 200;
    int removeRows = 0;

    std::cout << "image size is " << inputImg.width() << " columns by " << inputImg.height() << " rows" << std::endl;
    std::cout << "image format is: " << inputImg.format() << std::endl;
    SeamCarver sc = {inputImg};
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < removeRows; i++) {
        int *horizontalSeam = sc.findHorizontalSeam();
        sc.removeHorizontalSeam(horizontalSeam);
    }

    for (int i = 0; i < removeColumns; i++) {
        int *verticalSeam = sc.findVerticalSeam();
        sc.removeVerticalSeam(verticalSeam);
    }

    std::cout << "new image size is " << sc.getWidth() << " columns by " << sc.getHeight() << " rows"
    << std::endl;
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Resizing time: " << elapsed.count() << " seconds." << std::endl;


    QPixmap outputImg = QPixmap::fromImage(sc.getPicture());
    QLabel labelImg;
    labelImg.setPixmap(outputImg);
    labelImg.show();
    return QApplication::exec();

    // print energy
    /*
    QImage inputImg;
    inputImg.load("/home/baldder/CLionProjects/CLionProjects/Algorithms/week7.seamcarving/Images/6x5.png");
    std::cout << "image size is " << inputImg.width() << " columns by " << inputImg.height() << " rows" << std::endl;

    SeamCarver sc = {inputImg};

    std::cout << "Printing energy calculated for each pixel." << std::endl;

    for (int row = 0; row < sc.getHeight(); row++) {
        for (int col = 0; col < sc.getWidth(); col++) {
            std::cout << "            " << std::fixed << std::setprecision(2) << sc.getEnergy(col, row);
        }
        std::cout << std::endl;
    }
     */

    // print energy
    /*
     std::cout << "            " << std::fixed << std::setprecision(2) << sc.getEnergy(col, row);
     */

    // print rgb (custom)
    /*
   QRgb colorLeft = inputImg.pixel(1, 1);
   std::cout << "            " << std::fixed << std::setprecision(2) << "(" << qRed(colorLeft) << ", "
             << qGreen(colorLeft) << ", " << qBlue(colorLeft) << ")"; */

    // print rgb
    /*
    QRgb color = inputImg.pixel(col, row);
    std::cout << "            " << std::fixed << std::setprecision(2) << "(" << qRed(color) << ", "
    << qGreen(color) << ", " << qBlue(color) << ")";
    */


    return 0;

    /* QApplication app = {argc, argv};
     QImage inputImg;
     inputImg.load("/home/baldder/CLionProjects/CLionProjects/Algorithms/week7.seamcarving/Images/6x5.png");

     int removeColumns = 1;
     int removeRows = 0;

     std::cout << "image size is " << inputImg.width() << " columns by " << inputImg.height() << " rows" << std::endl;
     SeamCarver sc = {inputImg};
     auto start = std::chrono::high_resolution_clock::now();

     for (int i = 0; i < removeRows; i++) {
         int *horizontalSeam = sc.findHorizontalSeam();
         sc.removeHorizontalSeam(horizontalSeam);
     }

     for (int i = 0; i < removeColumns; i++) {
         int *verticalSeam = sc.findVerticalSeam();
         sc.removeHorizontalSeam(verticalSeam);
     }

     std::cout << "new image size is " << inputImg.width() << " columns by " << inputImg.height() << " rows"
               << std::endl;
     auto finish = std::chrono::high_resolution_clock::now();

     std::chrono::duration<double> elapsed = finish - start;
     QPixmap outputImg = QPixmap::fromImage(sc.getPicture());
     QLabel labelImg;
     labelImg.setPixmap(outputImg);
     labelImg.show();
     return QApplication::exec(); */
}