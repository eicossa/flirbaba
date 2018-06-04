CC = g++-6
CFLAGS = -g -Wall
INC = -I inc
SRCS = main.cpp src/ExifTool.cpp src/ExifToolPipe.cpp src/TagInfo.cpp
PROG = main

#OBJ = src/ExifTool.o src/ExifToolPipe.o src/TagInfo.o main.o
HDR = inc/ExifTool.h inc/ExifToolPipe.h inc/TagInfo.h inc/thermalMetadata.h

OPENCV = `pkg-config opencv --cflags --libs`
#EXIFTOOL = -I/inc/ExifTool.h -I/inc/ExifToolPipe.h -I/inc/TagInfo.h -L/src/ExifTool.o -L/src/ExifToolPipe.o -L/src/ExifTaginfo.o
#LIBS = $(OPENCV) $(EXIFTOOL)

$(PROG):main.o $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(INC) $(OPENCV)
