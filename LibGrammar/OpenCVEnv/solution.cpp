#include "solution.h"
AntiAliasing::CBMPMakerSingle::CBMPMakerSingle( std::string _image_path ) : image_path( _image_path ) {}

/**
 * Perform the solve task.
 *
 * \param dest_path
 */
void AntiAliasing::CBMPMakerSingle::solve( std::string dest_path ) {
    // cv::Mat originalImage = cv::imread(cv::samples::findFile(image_path), 0);
    cv::Mat originalImage = cv::imread( image_path, cv::IMREAD_GRAYSCALE );

    if ( originalImage.empty() ) {
        std::cerr << "Could not read the image: " << image_path << std::endl;
        exit( -1 );
    }

    cv::Mat imageReverse;
    cv::bitwise_not( originalImage, imageReverse );
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours( imageReverse, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );
    // TODO qDebug()
    std::cout << "Found " << contours.size() << " contours" << std::endl;
    std::for_each( hierarchy.begin(), hierarchy.end(),
                   []( cv::Vec4i elem ) -> void {
                       static int index = 0;
                       std::cout << "contour " << index++ << " :" << std::endl;
                       std::cout << elem[0] << "," << elem[1] << "," << elem[2] << "," << elem[3];
                       std::cout << std::endl;
                   } );

    // Create a blank canvas
    cv::Mat smooth_image = cv::Mat::zeros( imageReverse.size(), imageReverse.type() );

    // Perform BFS traversal to fill smooth_image
    this->_bfs_traverse( contours, hierarchy, smooth_image );

    // Reverse the pre-reversed image to get the final result
    cv::bitwise_not( smooth_image, smooth_image );

    // Save the output image
    std::string output_path = "smooth_image.bmp";
    imwrite( output_path, smooth_image );

    std::cout << "Smooth image saved: " << output_path << std::endl;

    return;
}

/**
 * Implement the bfs traversal to the contours.
 *
 * \param contours
 * \param hierarchy
 * \param smooth_image
 */
void AntiAliasing::CBMPMakerSingle::_bfs_traverse( std::vector<std::vector<cv::Point>> contours, std::vector<cv::Vec4i> hierarchy, cv::Mat smooth_image ) {
    std::deque<int> queue{};
    std::set<int> visited;
    for ( int forestIterator = 0; forestIterator < hierarchy.size(); forestIterator++ ) {
        if ( visited.contains( forestIterator ) ) {
            continue;
        } else {
            // Append contour tree root index to the queue
            queue.push_back( forestIterator );
        }
        int level = 0;
        int current_level = 0;
        int fillColor = 255;  // White
        int current_fill = -1;
        while ( !queue.empty() ) {
            int queue_size = queue.size();

            for ( int i = 0; i < queue_size; ++i ) {
                int node = queue.front();
                queue.pop_front();

                if ( visited.contains( node ) ) {
                    continue;
                }
                visited.insert( node );
                // Extract contour
                const std::vector<cv::Point>& contour = contours[node];
                // Approximate contour
                double epsilon = 0.00018 * cv::arcLength( contour, true );
                std::vector<cv::Point> approx;
                cv::approxPolyDP( contour, approx, epsilon, true );

                if ( level != current_level ) {
                    current_fill = ( fillColor == 0 ) ? 255 : 0;  // Swap fill color in each level
                    cv::drawContours( smooth_image, std::vector<std::vector<cv::Point>>{ approx }, -1, cv::Scalar( current_fill ), cv::FILLED );
                    drawContours( smooth_image, std::vector<std::vector<cv::Point>>{ approx }, -1, cv::Scalar( 255 ), 1 );
                } else {
                    cv::drawContours( smooth_image, std::vector<std::vector<cv::Point>>{ approx }, -1, cv::Scalar( fillColor ), cv::FILLED );
                }
                // Enqueue child contours
                int next_child = hierarchy[node][2];
                while ( next_child != -1 ) {
                    queue.push_back( next_child );
                    next_child = hierarchy[next_child][0];
                }
            }
            // Update fill color and level
            fillColor = current_fill;
            current_level = level;
            ++level;
        }
    }
}
