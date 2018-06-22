CC        =  g++-6
CFLAGS    = -g -Wall -std=c++11
EXIFFLAGS = -c
INC       = -I inc/
OPENCVLIB = `pkg-config opencv --cflags --libs`

flirbaba  : flirbaba.o 
#exif      : ExifTool.o ExifToolPipe.o TagInfo.o

ALLSRCS   = ${MAINSRCS} ${EXIFSRCS} ${OTHRSRCS}
MAINSRCS  = main.cpp
OTHRSRCS  = src/*.cpp
EXIFSRCS  = src/exiftool/*.cpp

#ExifTool.o : src/exiftool/ExifTool.cpp
#	$(CC) $(EXIFFLAGS) -o obj/ExifTool.o ${INC} src/exiftool/ExifTool.cpp
#ExifToolPipe.o : src/exiftool/ExifToolPipe.cpp
#	$(CC) $(EXIFFLAGS) -o obj/ExifToolPipe.o ${INC} src/exiftool/ExifToolPipe.cpp
#TagInfo.o : src/exiftool/TagInfo.cpp
#	$(CC) $(EXIFFLAGS) -o obj/TagInfo.o ${INC} src/exiftool/TagInfo.cpp
flirbaba.o : ${ALLSRCS}
	$(CC) ${INC} -o flirbaba.o ${ALLSRCS} ${OPENCVLIB}
