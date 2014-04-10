from PIL import Image
import os
def samplesToBMP(sFile, bmpFile):
	im = Image.new("RGB", (512,512), "black")
	fin = open(sFile)
	for i in fin:
		xy = i.split()
		x = int(float(xy[0]) * 512)
		y = int(float(xy[1]) * 512)
		im.putpixel((x,y), (255,255,255))
	im.show()
	im.save(bmpFile)

samplesToBMP('c.samples','o.bmp')