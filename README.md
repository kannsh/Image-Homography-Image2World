# Image-Homography-Image2World Project
Image Homography Transformation from Image to World points

# Project Wiki
This project was the initial development of the Social Distancing Alert System based on Homography.

# ** MUST READ **
OpenCV library has to be installed into C++ in order to do Homography transform. 

In Image Homography, it is best to have background tiles for reference. See "floor".

# Steps for Homography (Image2World)

1. Get 4 image coordinates and its 4 corresponding real world coordinates as input area
I will use the crossed tape markings as my input area. Using Paint software (Windows) / mtPaint (Linux), I recorded the pixel coordinates with mouse cursor and calculated the real world coordinates inside the image. See "floor_img+world_coords"

(Based on tape measurement, the width of each tile is 60cm while the height of every 2 tiles is 120cm)


2. Get Homography Matrix using getPerspectiveTransform
Write these 8 coordinates into the code, pixel coordinates will be imageLocs and real world coordinates will be worldLcs.

3. Choose any 3 to 5 image points inside the area to transform into world points. 
With the Homography Matrix obtained, choose any 3 to 5 points inside the input area and record their coordinates.
I specified them as imagePoints and drew them on the image. See (floor_top_origin.jpg)

4. Create & read real world image
Simply download a white 2000 x 2000 pixel image, and resize according to the real world coordinate size
This will be your "worldmap" for the real world points which are transformed and drawn here.

5. Now the imagePoints will be transformed into worldPoints 
Creating a new variable called worldPoint, using the transform function, I will put the imagePoint into the Homography matrix 

6. Draw worldPoints on map. See (floor_mapview.bmp - Pink dots are worldPoints)

7. Print worldPoint value to see transformed coordinate value from pixel

8. Checking accuracy of worldPoints
To check how accurate these transformed imagePoints are, I will create a variable called idealPoints
These idealPoints are the actual real world location coordinates to verify if the worldPoint is accurate
Draw these idealPoints on the map and compare both. 
See (floor_mapview.bmp - Blue circles are idealPoints)

# (Credits)
Homography Code (Courtesy of Mika) https://stackoverflow.com/questions/25769707/camera-pixels-to-planar-world-points-given-4-known-points

getPerspectiveTransform Source Code (Courtesy of OpenCV Dev) https://github.com/opencv/opencv/blob/master/modules/imgproc/src/imgwarp.cpp
