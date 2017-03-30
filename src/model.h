#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"
#include "tgaimage.h"

class Model {
private:
	TGAImage diffusemap_;
	// TGAImage normalmap_;
	// TGAImage specularmap_;
	std::vector<Vec3f> verts_;
	std::vector<Vec3f> norms_;
	std::vector<Vec2f> tcoords_;
	std::vector<std::vector<Vec3i> > faces_;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nnorms();
	int ntcoords();
	int nfaces();
	Vec3f vert(int i);
	Vec3f norm(int i);
	Vec2f tcoord(int i);
	std::vector<Vec3i> face(int idx);
	TGAColor get_diffuse(int x, int y);
	bool load_texture(const char* filename, const char* option);
	int get_texture_width(const char* option);
	int get_texture_height(const char* option);
};

#endif //__MODEL_H__
