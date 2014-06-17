from PIL import Image
import os
imSize = 200
n = 40000
def fillSampleToImage(sFile, im):
	fin = open(sFile)
	for i in fin:
		xy = i.split()
		x = float(xy[0])
		y = float(xy[1])
		xx = int(imSize*x)
		yy = int(imSize*y)
		im.putpixel((xx,yy), (255,255,255))
	fin.close()

def samplesToBMP(sFile, bmpFile):
	im = Image.new("RGB", (imSize,imSize), "black")
	for i in xrange(1):
		#os.system("main.exe")
		fillSampleToImage(sFile,im)
	im.show()
	im.save(bmpFile)

samplesToBMP('c.samples','o.bmp')