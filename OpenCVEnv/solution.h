#include <opencv2/opencv.hpp>
namespace AntiAliasing
{
    class CBMPMakerSingle {
    public:
        CBMPMakerSingle(std::string _image_path);
        void solve(std::string dest_path);
    private:
        std::string image_path;
        void _bfs_traverse(std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy, cv::Mat smooth_image);
    };
};
