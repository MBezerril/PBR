import glm

#Select the numbers of images
imgNumbers = 6

finalBuffer = []
header = "P3\n512 512\n255\n"

for counter in range(imgNumbers):
	arq = open("output_image" + str(counter) + ".ppm","r")
	print("output_image" + str(counter) + ".ppm")
	print("Final Buffer: "+ str(len(finalBuffer)))
	body = arq.read()
	pixels = body[15::]
	pixels = pixels.split(' ')
	if len(finalBuffer) > 0:
		for i in range(0,len(finalBuffer)):
			pos = i*3
			finalBuffer[i][0] = finalBuffer[i][0] + int(pixels[pos])
			finalBuffer[i][1] = finalBuffer[i][1] + int(pixels[pos+1])
			finalBuffer[i][2] = finalBuffer[i][2] + int(pixels[pos+2])
	else:
		for i in range(0,len(pixels)-1,3):
			finalBuffer.append(glm.vec3(int(pixels[i]), int(pixels[i+1]), int(pixels[i+2])))

for i in range(0,len(finalBuffer)):
	finalBuffer[i][0] = finalBuffer[i][0] / imgNumbers
	finalBuffer[i][1] = finalBuffer[i][1] / imgNumbers
	finalBuffer[i][2] = finalBuffer[i][2] / imgNumbers
	
welded = open("outputFinal.ppm", "w")
welded.write(header)
for i in finalBuffer:
	welded.write(str(int(i[0])) + ' ' + str(int(i[1])) + ' ' + str(int(i[2])) + ' ')