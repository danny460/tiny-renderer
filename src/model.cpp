#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        float ftrash;
        //string::compare(size_t pos, size_t len, const string& str), return 0 if equal;
        if (!line.compare(0, 2, "v ")) {

            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v[i];
            verts_.push_back(v);

        }else if (!line.compare(0, 3, "vt ")) {
            
            iss >> trash >> trash;
            Vec2f v;
            for (int i=0;i<2;i++) iss >> v[i];
            iss >> ftrash;
            tcoords_.push_back(v);

        }else if (!line.compare(0, 3, "vn ")) {
            
            iss >> trash >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v[i];
            iss >> ftrash;
            norms_.push_back(v);

        }else if (!line.compare(0, 2, "f ")) {
            std::vector<Vec3i> f;
            Vec3i tmp;
            iss >> trash;
            while (iss >> tmp[0]) {
                for(int i = 1 ; i < 3 ; i++){
                    if(iss.peek() == '/'){
                        iss >> trash >> tmp[i];
                    }
                }
                for(int i = 0 ; i < 3 ; tmp[i]--, i++);
                f.push_back(tmp);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "[#] vertices# " << verts_.size() << ", faces# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nnorms() {
    return (int)norms_.size();
}

int Model::ntcoords() {
    return (int)tcoords_.size();
}


int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<Vec3i> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

Vec3f Model::norm(int i) {
    return norms_[i];
}

Vec2f Model::tcoord(int i) {
    return tcoords_[i];
}
