CC        =  g++-6
CFLAGS    = -g -Wall -std=c++11
EXIFFLAGS = -c
INC       = -I inc/
OPENCVLIB = `pkg-config opencv --cflags --libs`

all       : flirbaba exif
exif      : ExifTool.o ExifToolPipe.o TagInfo.o
clean     : cleanup

ALLSRCS   = ${MAINSRCS} ${OTHRSRCS}
MAINSRCS  = main.cpp
OTHRSRCS  = src/*.cpp

EXIFSRCS  = src/exiftool/*.cpp
EXIFOBJS  = obj/ExifTool.o obj/ExifToolPipe.o obj/TagInfo.o

ExifTool.o : src/exiftool/ExifTool.cpp
	$(CC) $(EXIFFLAGS) -o obj/ExifTool.o ${INC} src/exiftool/ExifTool.cpp
ExifToolPipe.o : src/exiftool/ExifToolPipe.cpp
	$(CC) $(EXIFFLAGS) -o obj/ExifToolPipe.o ${INC} src/exiftool/ExifToolPipe.cpp
TagInfo.o : src/exiftool/TagInfo.cpp
	$(CC) $(EXIFFLAGS) -o obj/TagInfo.o ${INC} src/exiftool/TagInfo.cpp
flirbaba   : ${ALLSRCS} ${EXIFOBJS}
	$(CC) ${INC} -o flirbaba ${EXIFOBJS} ${ALLSRCS} ${OPENCVLIB}
cleanup    : ${ALLSRCS}
	rm -f ~/Dropbox/nabtd-images/FLIR1097/FLIR1097.jpg.thermout.png
