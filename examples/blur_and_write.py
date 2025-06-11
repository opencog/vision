#!/usr/bin/env python3
"""
Python version of blur_and_write.scm

An example of loading an image, applying a blur filter on it,
and storing the result in a file.
"""

from opencog.atomspace import *
from opencog.type_constructors import *
from opencog.vision import *

# Create an AtomSpace and set it as default
asp = AtomSpace()
set_default_atomspace(asp)

# Load an example image
img_node = Image("example_image.png")

# Define a node where we can attach values
img_collection = Concept("Image Collection")
key_1 = Concept("image#1")

# Setup an ImageBlurLink and store the result of its execution
# under img_collection key_1
img_blur = ImageBlur(img_node, NumberNode("10"))
result = img_blur.execute()
img_collection.set_value(key_1, result)

# Setup an ImageWriteLink with the image to be loaded from
# img_collection key_1 and stored in example_output_py.png
img_write = ImageWriteLink(
	ValueOfLink(img_collection, key_1),
	ConceptNode("example_output_py.png"))
img_write.execute()

print("Image processed successfully. Output saved to example_output_py.png")
