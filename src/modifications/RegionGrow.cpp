#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"
#include "RegionGrow.h"

using namespace cimg_library;
using namespace std;

CImg<int> rgrow(CImg<int> &image, int x, int y, int t) {
    CImg<int> result(image.width(), image.height());

    bool** presence = new bool* [image.width()];    //generating the two-dimensional table


    for (int i = 0; i < image.width(); i++) {
        presence[i] = new bool[image.height()];      //defining the table
    }

    for (int i = 0; i < image.height(); i++) {
        for (int j = 0; j < image.width(); j++) {
            presence[i][j] = false;                 //setting all values in the table to be false
        }
    }

    int seed = image(x,y);

    presence[x][y] = true;

    if (x > 0) rgrowRecursion(image, x-1, y, t, presence, seed);
    if (x < image.width()) rgrowRecursion(image, x+1, y, t, presence, seed);
    if (y < image.height()) rgrowRecursion(image, x, y+1, t, presence, seed);
    if (y > 0) rgrowRecursion(image, x, y-1, t, presence, seed);

    for (int i = 0; i < image.height(); i++) {
        for (int j = 0; j < image.width(); j++) {
            if (presence[i][j] == true) {

                result(i, j) = 255;
            }
            else result(i ,j) = 0;
        }
    }
    result(x,y) = 127;

    return result;
}

bool** rgrowRecursion(CImg<int> &image, int x, int y, int t, bool** presence, int seed) {
    int threshold1 = seed - t;
    int threshold2 = seed + t;
    if (threshold2 > 255) threshold2 = 255;
    if (threshold1 < 0) threshold1 = 0;
    cout << "x = " << x << "    y = " << y << "     t = " << t << endl;

    if(image(x,y) > threshold1 && image(x,y) < threshold2) {
        presence[x][y] = true;

        if (x > 0 && presence[x-1][y] == false) rgrowRecursion(image, x-1, y, t, presence, seed);
        if (x < image.width() && presence[x+1][y] == false) rgrowRecursion(image, x+1, y, t, presence, seed);
        if (y < image.height() && presence[x][y+1] == false) rgrowRecursion(image, x, y+1, t, presence, seed);
        if (y > 0 && presence[x][y-1] == false) rgrowRecursion(image, x, y-1, t, presence, seed);

    }
    else presence[x][y] = false;

    return presence;
}