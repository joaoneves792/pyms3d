all:
	swig -c++ -python ms3d.i
	g++ -O3 -fPIC -c ms3d.cpp ms3d_wrap.cxx -I /usr/include/python3.4m -lms3d -lGL -lGLU -lglut -ljpeg -lpng
	ld -shared ms3d.o ms3d_wrap.o -o _ms3d.so -lms3d -lGL -lGLU -lglut -ljpeg -lpng

clean:
	rm *.o                  
	rm ms3d_wrap.cxx        
	rm ms3d.py                 
	rm _ms3d.so
