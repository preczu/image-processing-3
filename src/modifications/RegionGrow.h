#include <iostream>
#include <vector>
#include <algorithm>
#include "../../lib/CImg.templ"

using namespace std;
using namespace cimg_library;

//t stands for threshold

CImg<int> rgrow(CImg<int> &image, int x, int y, int t);
CImg<int> rgrowRecursion(CImg<int> &image, int x, int y, int t);
