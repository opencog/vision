;
; Opencog vision atom-types module
;
(define-module (opencog vision))

(use-modules (opencog))
(use-modules (opencog sp-config))

; Load the C library that calls the nameserver to load the types.
(load-extension (string-append opencog-ext-path-vision-types "libvision") "vision_types_init")

(load "vision/vision_types.scm")
