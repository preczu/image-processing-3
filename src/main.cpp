#include <iostream>
#include <unistd.h>
#include <string>
#include "../lib/CImg.templ"
#include "RegionGrow.h"

using namespace std;
using namespace cimg_library;

void help() {
    cout << " \n"
    "                 image-processing\n"
    " \n"
    "             program to process images\n"
    "          Anna Preczyńska and Piotr Kocik\n"
    " \n"
    "  usage: image-processing <command> <x_coordinate> <y_coordinate> <threshold> <name_of_image_to_edit>\n"
    " \n"
    "Commands:\n"
    "   --help          list avaiable commands and the usage of the program\n"
    "   --rgrow         apllying region growing formulas\n"
    " \n";
}

void displaying() {
        CImg<int> img1("../out/original.bmp");
        CImg<int> img2("../out/modified.bmp");
        img1.append(img2).display("Image");
}

float checkIntValue(char* val){
    int number = atoi(val);
    if (number == 0){
        if (strcmp(val,"0") == 0){
            cout << "You forgot to give the value! \n" << endl;
            help();
            exit(0);
        }
        else return number;
    }
    else if (number < 0) {
        cout << "Numbers cannot be smaller than zero! " << endl;
        help();
        exit(0);
    }
    else return number;
}

void input(int argc, char* argv[]) {
    int numberOfArgc = argc;

    if (string("--help").compare(argv[1]) == 0) {
        help();
    }

    else if (string("--rgrow").compare(argv[1]) == 0) {
            if( numberOfArgc < 5){
                help();
                exit(0);
            }
            
            int x = checkIntValue(argv[2]);
            int y = checkIntValue(argv[3]);
            int t = checkIntValue(argv[4]);

            if(argc == 5) {
                CImg<int> img("../src/pentagon.bmp");
                img.save("original.bmp");                   //saving an image in folder "../out"

                if (img(x,y) - t < 0 || img(x,y) + t > 255) {
                    cout << "Value of threshold is too high for this pixel!" << endl;
                    exit(0);
                }
                else if (x > img.width() || y > img.height()) {
                    cout << "Coordinates are too high!" << endl;
                    exit(0);
                }
                img = rgrow(img, x,y,t);                    //implementing the function
                img.save("modified.bmp");                   //saving the resultant image in folder "../out"
            }
            else if (argc == 6) {
                    CImg<int> img(argv[5]);                 //defining an image from input
                    img.save("original.bmp");               //saving an image in folder "../out"
                    img = rgrow(img, x,y,t);                 //implementing the function
                    img.save("modified.bmp");               //saving the resultant image in folder "../out"
            }
            displaying();                                   //displaying pictures
    }

    else {
        help();
        exit(0);
    }
}

int main(int argc, char* argv[]) {

    if (argc < 2 && argc > 6){
        help();
        return 0;
    }
    else {
        input(argc, argv);    
    } 
    return 0;
}

