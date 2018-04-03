# Scientific Visualization (C++)
I only included the final project for this since it was the largest and most complex. 

The code I created reads in a vtk data file, finds a Ray for each pixel by normalizing the camera, calculates Samples along the ray by doing linear interpolation, applies a transfer function to each sample, then calculates a Color and assigns it to the pixel.

The general outline of this ray-casting/volume rendering project was covered in class. If you care to look the slides are here:

https://classes.cs.uoregon.edu/18W/cis410visualization/lectures/CIS410W18_Lec21.pdf

### Disclaimer
The image given in this repo is slightly different than the image that will be produced by running this code. Due to githubs file size limits, the full 512mb data file could not be uploaded so I used the 64mb file. With this change I had to change the code to use the smaller data set, I also halved the image height and width and the # of samples taken from 1024 to 512. The image given is 1024x1024 with 1024 samples taken and is the result of using the more accurate data set. The image produced by the smaller data set will still look similar but will be less accurate due to the smaller data size and the smaller # of samples I take
