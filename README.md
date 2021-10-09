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
- There is `ImageBlurLink` to apply `cv::blur` to images, it takes an `ImageNode` / `ImageValue` and a `NumberNode` (for kernel size).
  - It returns an `ImageValue`.

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

Then `cmake --build build` and `cmake --install build`

If you have VCPkg and / or you want to use something like clangd that requires `compile_commands.json`, there is the `configure.sh` script that runs a slightly extended version of the above command (export `VCPKG_ROOT` with the path to your VCPkg).

## Library Usage
### CMake
- `find_package` library name: `AtomSpaceVision`.
- Target to link with: `AtomSpace::Vision`.

### Types Usage
For Scheme users:
- `(Image "<file-path>")` opens an image from a given file.
- `(ImageBlur <image node/value> (Number <kernel size>))` to setup a `cv::blur` operation.

## More plans and ideas
Other required and optional `ImageFilterLink`s. These are described at https://docs.opencv.org/4.5.3/d4/d86/group__imgproc__filter.html

  + write image to file. (Better yet: display to screen). Needed for debugging.
So, `ImageWriteLink` and/ir `ImageDisplayLink`.

  + thresholding, convert to greyscale, convert to binary b/w.

  + `filter2D()` to be wrapped in a `ImageFilter2DLink`.  The primary
need for this is just to build up some simple Haar wavelets so
that the learning algo can explore features.

  + `ImageRectangleLink` - this needs to be a white rectangle on a black
background, with a given width, height, postion. To be used with the
above to select regions.

  + `HaarWaveletLink` - we want to search for features in a
position-independent, scale-independent way. We need a good API for
that. Not at all clear what a good API for that might be ... Really,
we want something affine... Maybe this: http://wavelet2d.sourceforge.net/

  + `pyrDown()` to be wrapped in `ImageHalfSizeLink` - just downscale the
image to half its size.

  + `erode()` ... maybe useful later??

  + Extract hue, saturation, value, extract red, green blue channels. How
to do this in opencv ??

  + Maybe a circle or ellipse? to answer yes/no to circular feature
    questions.
