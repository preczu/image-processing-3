#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "RegionGrow.h"

using namespace cimg_library;
using namespace std;

CImg<int> rgrow(CImg<int> &image, int x, int y, int t) {
    CImg<int> result(image.width(), image.height());

    bool** presence = new bool*[image.height()];    //generating the two-dimensional table


    for (int i = 0; i < image.height(); i++) {
        presence[i] = new bool[image.width()];      //defining the table
    }

    for (int i = 0; i < image.height(); i++) {
        for (int j = 0; j < image.width(); j++) {
            presence[i][j] = false;                 //setting all values in the table to be false
        }
    }

    int seed = image(x,y);

    rgrowRecursion(image, x-1, y, t);
    rgrowRecursion(image, x+1, y, t);
    rgrowRecursion(image, x, y+1, t);
    rgrowRecursion(image, x, y-1, t);



    return result;
}

CImg<int> rgrowRecursion(CImg<int> &image, int x, int y, int t) {
    CImg<int> result(image.width(), image.height());


    return result;
}