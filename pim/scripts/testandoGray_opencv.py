# Python program to explain splitting of channels

# Importing cv2
import cv2
import numpy as np
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('image_path', help='Path to image')

args = parser.parse_args()

# image = Image.open(args.image_path)
# image.show()

# Reading the image using imread() function
image = cv2.imread(args.image_path)

height, width, channels = image.shape

# Traverse the image
for y in range(height):  # Loop over rows
    for x in range(width):  # Loop over columns
        b, g, r = image[y, x]  # Access BGR pixel values
        # Example operation: Convert to grayscale manually
        gray_value = int(0.2989 * r + 0.5870 * g + 0.1140 * b)
        if g > 150:
            image[y, x] = (gray_value, gray_value, gray_value)

# Displaying the original BGR image
cv2.imshow('Image', image)
# mean = np.mean(image)

# if mean < 85:
#     print('Dark')
# elif mean < 170:
#     print('Grey')
# else:
#     print('Light')

# Waits for user to press any key
cv2.waitKey(0)
