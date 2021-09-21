# vision
Atomese wrappers around a subset of OpenCV

The general idea is that the `ImageValue`s will hold a handle to the
image being processed, and the `ImageBlurLink`, and other things of that
kind specify the kinds of transformations to be applied to the image.
The actual images are never in the AtomSpace, only the abstract
processing tree, and a way of hooking that tree to the image(s) to be
processed.

### Status
Nothing yet. Version 0.0.0

### Plan
Cut-n-paste of email:

* Set up the conventional opencog repo boilerplate. A cut-n-paste of
the makefiles in opencog/atomspace-rocks might be easiest.

* Create an atom types file & etc. a cut-n-paste of the types in
opencog/spacetime might be easiest. Its mostly boilerplate ... except
for the types themselves.

* For starters, we need to get still images into the system. I'm
thinking that this could be an `ImageNode` (or `IMAGE_NODE <- NODE` in the
types file).  Corresponding to this type is a C++ class that
implements a wrapper to the suitable OpenCV analog.

The ImageNode is a type of Node, the string would be the name of the
file (or URL) containing the image. The c++ constructor can either do
nothing, or maybe it can try to open that file. The C++ class would
have as private/protected members whatever is needed from
https://docs.opencv.org/4.5.3/d4/da8/group__imgcodecs.html  which
seems to be how opencv reads images. So I guess a `Mat` which seems to
be the opencv handle to an image.

* Next, we need to do something with that image. So, I'm looking at
https://docs.opencv.org/4.5.3/d4/d86/group__imgproc__filter.html  and
`cv:blur()` looks like a good place to start. So, we need an
`ImageBlurLink` which expects .. well, for now one parameter: a
`NumberNode` for the size, and the image to apply it to. So a typical
use would be `(ImageBlurLink (ImageNode "/tmp/foo.jpg") (NumberNode
20))`

Calling the C++ method `ImageBlurLink::execute()` would apply the
filter to the image, and return a ... well, that's a good question.
It could return another ImageNode holding a handle to the mutated
image. But I don't want to place these "temporary results" into Atoms
.. they really need to be Values ... so it should return an
ImageValue, which is almost exactly the same thing as an ImageNode,
except that ... its a Value, not an Atom.

So .. how do Values work? They're just like Atoms, except you can't
store them in the AtomSpace. If you don't know Values well, please
review the demo.
https://github.com/opencog/atomspace/blob/master/examples/atomspace/values.scm

The `StreamValue` was invented to hold things like audio, video, and I
guess its OK to use it for static images, too. See
https://github.com/opencog/atomspace/blob/master/examples/atomspace/stream.scm

Just to confuse things, I should mention three more demos::
https://github.com/opencog/atomspace/blob/master/examples/atomspace/formulas.scm
 and https://github.com/opencog/atomspace/blob/master/examples/atomspace/flows.scm
and https://github.com/opencog/atomspace/blob/master/examples/atomspace/flow-formulas.scm
... Those examples all use `TruthValue`s to do their stuff; the general
idea that something similar would be used to route around video and
sound.  But maybe we can ignore these for now.
Values were invented for this kind of stuff, but using
them for audio, video would be new.


#### More plans and ideas
Other required and optional `ImageFilterLink`s. These are described at https://docs.opencv.org/4.5.3/d4/d86/group__imgproc__filter.html

  + write image to file. (Better yet: display to screen). Needed for debugging.
So, `ImageWriteLink` and/ir `ImageDisplayLink`.

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
