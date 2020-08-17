#include "opencv2/core.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgcodecs.hpp" 
#include "opencv2/imgproc.hpp" 

#include <iostream>

// g++ -o floorhomography floorhomography.cpp -I/usr/include/opencv2/ -L/usr/lib/opencv/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs  -lopencv_imgproc 
// /.floorhomography

cv::Point2f transformPoint(cv::Point2f current, cv::Mat transformation)
{
    cv::Point2f transformedPoint;
    transformedPoint.x = current.x * transformation.at<double>(0,0) + current.y * transformation.at<double>(0,1) + transformation.at<double>(0,2);
    transformedPoint.y = current.x * transformation.at<double>(1,0) + current.y * transformation.at<double>(1,1) + transformation.at<double>(1,2);
    float z = current.x * transformation.at<double>(2,0) + current.y * transformation.at<double>(2,1) + transformation.at<double>(2,2);
    transformedPoint.x /= z;
    transformedPoint.y /= z;

    return transformedPoint;
}

int main()
{

    cv::Mat chessboard = cv::imread("//home//student//Desktop//floor//floor.jpg");

    std::vector<cv::Point2f> imageLocs;

    // 4 input image points (area used on image)
    imageLocs.push_back(cv::Point2f(664, 469));   //Upper left
    imageLocs.push_back(cv::Point2f(961, 472));   //Upper right
    imageLocs.push_back(cv::Point2f(1283, 1122)); //Lower right
    imageLocs.push_back(cv::Point2f(378, 1115));  //Lower left


    for(unsigned int i=0; i<imageLocs.size(); ++i)
    {
        cv::circle(chessboard, imageLocs[i], 8, cv::Scalar(0,0,255), -1);
    }
    cv::imwrite("//home//student//Desktop//floor//floor(4points).jpg", chessboard);


    // 4 world points (corresponding to the image points)
    std::vector<cv::Point2f> worldLocs;
    worldLocs.push_back(cv::Point2f(0,0));      //Upper left
    worldLocs.push_back(cv::Point2f(240,0));    //Upper right
    worldLocs.push_back(cv::Point2f(240,720));  //Lower right
    worldLocs.push_back(cv::Point2f(0,720));    //Lower left


    // for exactly 4 correspondences. for more you can use cv::findHomography
    // this is the transformation from image coordinates to world coordinates:
    cv::Mat image2World = cv::getPerspectiveTransform(imageLocs, worldLocs);

    // We do not need World2Image
    // the inverse is the transformation from world to image.
    //cv::Mat world2Image = image2World.inv();

   
    // Select 5 imagePoints as human coordinates
    cv::Point2f imagePoint = cv::Point2f(897, 511);    
    cv::Point2f imagePoint2 = cv::Point2f(813, 511);    
    cv::Point2f imagePoint3 = cv::Point2f(590,631 );    
    cv::Point2f imagePoint4 = cv::Point2f(1020,980 );   
    cv::Point2f imagePoint5 = cv::Point2f(820,792);    
    cv::Point2f imagePoint6 = cv::Point2f(550, 726);     

    // draw these 5 imagePoints in white 
    cv::circle(chessboard, imagePoint, 10, cv::Scalar(255,255,255), -1);
    cv::circle(chessboard, imagePoint2, 10, cv::Scalar(255,255,255), -1);
    cv::circle(chessboard, imagePoint3, 10, cv::Scalar(255,255,255), -1);
    cv::circle(chessboard, imagePoint4, 10, cv::Scalar(255,255,255), -1);
    cv::circle(chessboard, imagePoint5, 10, cv::Scalar(255,255,255), -1);
    cv::circle(chessboard, imagePoint6, 10, cv::Scalar(255,255,255), -1);

    cv::imshow("chessboard", chessboard);
    cv::imwrite("//home//student//Desktop//floor//floor(top origin) filled.jpg", chessboard);
    cv::waitKey(-1);





    //Read worldmap
    cv::Mat worldmap = cv::imread("//home//student//Desktop//map.bmp"); 
    
    // Transform imagepoints to get world points (mappoints)
    cv::Point2f worldPoint = transformPoint(imagePoint, image2World); 
    cv::Point2f worldPoint2 = transformPoint(imagePoint2, image2World);
    cv::Point2f worldPoint3 = transformPoint(imagePoint3, image2World); 
    cv::Point2f worldPoint4 = transformPoint(imagePoint4, image2World); 
    cv::Point2f worldPoint5 = transformPoint(imagePoint5, image2World); 
    cv::Point2f worldPoint6 = transformPoint(imagePoint6, image2World); 



    // Draw the worldpoints on the map
    cv::circle(worldmap, worldPoint, 10, cv::Scalar(255,0,255), -1);
    cv::circle(worldmap, worldPoint2, 10, cv::Scalar(255,0,255), -1);
    cv::circle(worldmap, worldPoint3, 10, cv::Scalar(255,0,255), -1);
    cv::circle(worldmap, worldPoint4, 10, cv::Scalar(255,0,255), -1);
    cv::circle(worldmap, worldPoint5, 10, cv::Scalar(255,0,255), -1);
    cv::circle(worldmap, worldPoint6, 10, cv::Scalar(255,0,255), -1);
    
    // Show worldpoint value
    std::cout << "\n\n\nWorld points (World Map)" << std::endl;
    std::cout << worldPoint << std::endl;
    std::cout << worldPoint2 << std::endl;
    std::cout << worldPoint3 << std::endl;
    std::cout << worldPoint4 << std::endl;
    std::cout << worldPoint5 << std::endl;
    std::cout << worldPoint6 << std::endl;




    // Ideal world points (based on world locs)  corresponding to img points *
    cv::Point2f idealPoint = cv::Point2f(180,120);    
    cv::Point2f idealPoint2 = cv::Point2f(120,120);   
    cv::Point2f idealPoint3 = cv::Point2f(0,360);    
    cv::Point2f idealPoint4 = cv::Point2f(180,660);   
    cv::Point2f idealPoint5 = cv::Point2f(120,540);    
    cv::Point2f idealPoint6 = cv::Point2f(0,480);

    cv::circle(worldmap, idealPoint, 10, cv::Scalar(255,0,0), 2);
    cv::circle(worldmap, idealPoint2, 10, cv::Scalar(255,0,0), 2);
    cv::circle(worldmap, idealPoint3, 10, cv::Scalar(255, 0,0), 2);
    cv::circle(worldmap, idealPoint4, 10, cv::Scalar(255, 0,0), 2);
    cv::circle(worldmap, idealPoint5, 10, cv::Scalar(255, 0,0), 2);
    cv::circle(worldmap, idealPoint6, 10, cv::Scalar(255, 0,0), 2);
    
    cv::imshow("worldmap with points: ", worldmap);
    cv::imwrite("//home//student//Desktop//floor//floor(map view).jpg", worldmap);
    cv::waitKey(-1);

    
}


