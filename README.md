# Image-Homography-Image2World
Image Homography Transformation from Image to World points

OpenCV library has to be installed into C++ in order to do Homography transform. Remember to add the OpenCV library.

In Image Homography, it is best to have background tiles for reference. See "floor".

# Steps for Homography (Image2World)

1. Get 4 image coordinates and its 4 corresponding real world coordinates as input area
I will use the crossed tape markings as my input area. Using Paint software (Windows) / mtPaint (Linux), I recorded the pixel coordinates with mouse cursor and calculated the real world coordinates inside the image. See "floor_coordinates"

(Based on tape measurement, the width of each tile is 60cm while the height of every 2 tiles is 120cm)


2. Get Homography Matrix using getPerspectiveTransform
Write these 8 coordinates into the code, pixel coordinates will be imageLocs and real world coordinates will be worldLcs.

3. Choose any 3 image points inside the area to transform into world points. 
With the Homography Matrix obtained, choose any 3 to 5 points inside the input area and record their coordinates.
I specified them as imagePoints and drew them on the image. See (floor_imagepoints.jpg)
