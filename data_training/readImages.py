import numpy as np
import struct
from matplotlib import pyplot as plt
import time

nbimages = 1000
nx = 28
ny = 28
imagesize = nx*ny

print "Which data set do you want mate ?? (0-9) >> ",
dataset = raw_input()
filename = "data" + dataset

images = np.zeros((nbimages,nx,ny))
with open(filename, 'r') as f:
	for i in xrange(nbimages):
		
		for x in xrange(nx):
			for y in xrange(ny):
				images[i,x,y] = struct.unpack('B', f.read(1))[0]

		plt.imshow(images[i])
		plt.title("dataset : " + str(dataset) + " image : " + str(i))
		plt.show()
