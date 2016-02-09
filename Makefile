OBJS= ms3d.o Tex.o shader.o GLM.o Lights.o Shadows.o Text.o ms3d_wrap.o 

CC=g++
CXXFLAGS=-O3 -Wall -fPIC -c 
LIBS=-I /usr/include/python3.5m -lms3d -lGL -lGLEW -ljpeg -lpng
LDFLAGS= -shared

#Really dumb rule, but swig generates a .cxx and make doesnt know what to do with it!
%.o : %.cxx
	$(CC) $(CXXFLAGS) $< -o $@ $(LIBS)

all: swig $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o _ms3d.so $(LIBS)
	cat constants.py >> ms3d.py

swig:
	swig -c++ -python ms3d.i

clean:
	rm $(OBJS)                  
	rm ms3d_wrap.cxx        
	rm ms3d.py                 
	rm _ms3d.so
