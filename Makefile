OBJS= ms3d.o Tex.o shader.o GLM.o Lights.o Shadows.o Text.o Body.o ms3d_wrap.o 

CC=g++
CXXFLAGS = -O3 -Wall -fPIC -c $(shell pkg-config --cflags python3) 
LDFLAGS  = -shared $(shell pkg-config --libs python3) -lms3d -lGL -lGLEW -ljpeg -lpng


all: swig $(OBJS)
	$(LD) $(OBJS) -o _ms3d.so $(LDFLAGS) 
	cat constants.py >> ms3d.py

#Really dumb rule, but swig generates a .cxx and make doesnt know what to do with it!
ms3d_wrap.o : ms3d_wrap.cxx
	$(CC) $(CXXFLAGS) ms3d_wrap.cxx -o ms3d_wrap.o $(LDFLAGS)

swig:
	swig -c++ -python ms3d.i

clean:
	rm $(OBJS)                  
	rm ms3d_wrap.cxx        
	rm ms3d.py                 
	rm _ms3d.so
