#include "solution.h"
#include <iostream>
using namespace std;
int main() {
    // Read image
    std::string image_path = "test_Multi.bmp";
    std::string output_path = "smooth_image.bmp";
    AntiAliasing::CBMPMakerSingle MySolution(image_path);
    MySolution.solve(output_path);
    // cout << "Hello?" << endl;
    return 0;
}
