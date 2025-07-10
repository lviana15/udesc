import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
from math import atan2, pi, sqrt

prewitt_x = np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]])

prewitt_y = np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]])

img = cv.imread("img02.jpg")
gray_scale = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
filtered = cv.glaussianBlur(gray_scale, (5, 5), 0)

gx = cv.filter2D(filtered, -1, prewitt_x)
gy = cv.filter2D(filtered, -1, prewitt_y)

epsilon = 1e-8
M = np.sqrt(gx**2 + gy**2)
D = np.arctan2(gy, gx + epsilon) * (180 / np.pi)
D[D < 0] += 180  