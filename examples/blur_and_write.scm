#!/usr/bin/env guile
!#
;
; blur_and_write.scm
;
; An example of loading an image, applying a blur filter on it,
; and storing the result in a file.
;
(use-modules (opencog) (opencog exec) (opencog vision))

; Load an example image.
(define img-node (Image "example_image.png"))

; Define a node where we can attach values.
(define img-collection (Concept "Image Collection"))
(define key-1 (Concept "image#1"))

; Setup an ImageBlurLink and store the result of its execution
; under `img-collection key-1`. The blurring is expressed in pixels;
; ten pixels should be fairly noticable.
(define img-blur (ImageBlur img-node (Number "10")))
(cog-set-value! img-collection key-1 (cog-execute! img-blur))

; Setup an ImageWriteLink with the image to be loaded from
; `img-collection key-1` and stored in `example_output.png`.
(define img-write (ImageWrite (ValueOf img-collection key-1) (Concept "example_output.png")))
(cog-execute! img-write)
