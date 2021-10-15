# AtomSpace Computer Vision Types
> Atomese wrappers around a subset of OpenCV

The general idea is that the `ImageValue`s will hold a handle to the
image being processed, and the `ImageBlurLink`, and other things of that
kind specify the kinds of transformations to be applied to the image.
The actual images are never in the AtomSpace, only the abstract
processing tree, and a way of hooking that tree to the image(s) to be
processed.

## Status
- It is possible to read an image from a file using `ImageNode`, its name corresponds to the image file location.
- There are a few OpenCV operations that you can invoke both on image Nodes and Values. They return `ImageValue`s. Look down for usage info in Scheme.
- Saving images supported with `ImageWriteLink`.

## Building
### Dependencies
- CMake (build dependency)
- OpenCV (`libopencv-dev` package on Debian-derived Linux distributions)
- AtomSpace

### Commands
The basic command is just CMake:
```
cmake -B build/ -S .
```

Then `cmake --build build` and `sudo cmake --install build`

If you have VCPkg and / or you want to use something like clangd that requires `compile_commands.json`, there is the `configure.sh` script that runs a slightly extended version of the above command (export `VCPKG_ROOT` with the path to your VCPkg).

## Library Usage
### CMake
- `find_package` library name: `AtomSpaceVision`.
- Target to link with: `AtomSpace::Vision`.

### Types Usage
For Scheme users:
- `(Image "<file-path>")` opens an image from a given file.
- `(ImageBlur <Image or ValueOf> (Number <kernel size>))` to setup a `cv::blur` operation.
- `(ImageWrite <Image or ValueOf> <Concept or ValueOf>)` writes an image to a given location.
- `(ImageHalfSize <Image or ValueOf>)` to setup a `cv::pyrDown` operation.
- `(ImageFilter2D <Image or ValueOf> (Number <ddepth>) <Image or ValueOf>:kernel)` to setup a `cv::filter2D` operation.

## More plans and ideas
Other required and optional `ImageFilterLink`s. These are described at https://docs.opencv.org/4.5.3/d4/d86/group__imgproc__filter.html

  + display to screen for debugging.
    So, `ImageDisplayLink`.

  + thresholding, convert to greyscale, convert to binary b/w.

  + `ImageRectangleLink` - this needs to be a white rectangle on a black
background, with a given width, height, postion. To be used with the
above to select regions (but `Rect` is a separate type in OpenCV that is used by other procedures for selecting ROI,
is this necessary as a Link then?).

  + `HaarWaveletLink` - we want to search for features in a
position-independent, scale-independent way. We need a good API for
that. Not at all clear what a good API for that might be ... Really,
we want something affine... Maybe this: http://wavelet2d.sourceforge.net/

  + `erode()` ... maybe useful later??

  + Extract hue, saturation, value, extract red, green blue channels. How
to do this in opencv ??

  + Maybe a circle or ellipse? to answer yes/no to circular feature
    questions.
