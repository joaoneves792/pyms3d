all:
	swig -c++ -python ms3d.i
	g++ -O3 -Wall -fPIC -c ms3d.cpp shader.cpp Tex.cpp GLM.cpp Lights.cpp ms3d_wrap.cxx -I /usr/include/python3.5m -lms3d -lGL -lGLU -lglut -ljpeg -lpng
	ld -shared ms3d.o Tex.o shader.o GLM.o Lights.o ms3d_wrap.o -o _ms3d.so -lms3d -lGL -lGLU -lglut -ljpeg -lpng
	cat constants.py >> ms3d.py

clean:
	rm *.o                  
	rm ms3d_wrap.cxx        
	rm ms3d.py                 
	rm _ms3d.so
