This was my first attempt at following the Ray Tracing in One Weekend books, I only completed the first book.
See here for the series https://raytracing.github.io/

I plan to revisit this and use shaders instead of the CPU

### Building
This project was designed using cmake in CLion so you will need to have cmake installed to build this project
run cmake with `cmake --build`
run the executable that is created

### Running
It will prompt you for the image width in pixels
then the samples (rays to shoot per pixel)
then the bounces each pixel takes

The higher these numbers the better the image but the longer it will take to render
This is currently CPU bound so it will take a while to render, an image
of 1000 pixels wide and 50 samples and 20 bounces will take about an hour to render
