#include <solution.h>

int main() {
    // Read image
    std::string image_path = "test_Multi.bmp";
    std::string output_path = "smooth_image.bmp";
    AntiAliasing::CBMPMakerSingle MySolution(image_path);
    MySolution.solve(output_path);
    return 0;
}
