#include "ms3d.h"
#include "Textures.h"

Tex::Tex(char* filename){
	_tex = LoadGLTexture(filename);
}
int Tex::getTexture(){
	return _tex;
}
