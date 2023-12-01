EXEMAIN = app
OBJS  = main.o PNG.o HSLAPixel.o lodepng.o chain.o block.o RGBA_PNG.o RGBAPixel.o lab_intro.o

CXX = g++
CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++14

all : app

$(EXEMAIN) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXEMAIN)

main.o : main.cpp chain.h cs221util/PNG.h cs221util/HSLAPixel.h block.h lab_intro.h cs221util/RGBA_PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) main.cpp

chain.o : chain.cpp chain.h block.h
	$(CXX) $(CXXFLAGS) chain.cpp

block.o : block.cpp block.h cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) block.cpp

lab_intro.o : lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) lab_intro.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

RGBA_PNG.o : cs221util/RGBA_PNG.cpp cs221util/RGBA_PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/RGBA_PNG.cpp  

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp	

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXEMAIN)
