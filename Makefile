CC        = g++-6
CFLAGS    = -g -Wall -std=c++11
EXIFFLAGS = -c
INC       = -I inc/
EXEC      = flirbaba
OBJ       = src/ExifTool.o src/ExifToolPipe.o src/TagInfo.o main.o
OPENCVLIB = `pkg-config opencv --cflags --libs`

all       : everything
flirbaba  : flirbaba.o 
exif      : ExifTool.o ExifToolPipe.o TagInfo.o

ALLSRCS   = ${MAINSRCS} ${EXIFSRCS} ${OTHRSRCS}
MAINSRCS  = main.cpp
OTHRSRCS  = src/*.cpp

EXIFSRCS  = src/exiftool/*.cpp
EXIFOBJS  = ExifTool.o ExifToolPipe.o TagInfo.o

ExifTool.o : src/exiftool/ExifTool.cpp
	$(CC) $(EXIFFLAGS) -o obj/ExifTool.o ${INC} src/exiftool/ExifTool.cpp
ExifToolPipe.o : src/exiftool/ExifToolPipe.cpp
	$(CC) $(EXIFFLAGS) -o obj/ExifToolPipe.o ${INC} src/exiftool/ExifToolPipe.cpp
TagInfo.o : src/exiftool/TagInfo.cpp
	$(CC) $(EXIFFLAGS) -o obj/TagInfo.o ${INC} src/exiftool/TagInfo.cpp

flirbaba.o : ${MAINSRCS} ${OTHRSRCS} ${EXIFSRCS}
	$(CC) -o obj/flirbaba ${INC} ${MAINSRCS} ${OTHRSRCS} ${EXIFSRCS} ${OPENCVLIB}

everything : flirbaba ${EXIFOBJS}
	${CC} ${CFLAGS} -o ${EXEC} ${ALLSRCS} ${INC} ${OPENCVLIB}
