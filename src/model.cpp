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
        //string::compare(size_t pos, size_t len, const string& str)
        //return 0 if equal
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v);

        }else if (!line.compare(0, 3, "vt ")) {
            
            iss >> trash >> trash;
            Vec2f v;
            for (int i=0;i<2;i++) iss >> v.raw[i];
            iss >> ftrash;
            verts_t_.push_back(v);

        }else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f, ft;
            int itrash, idx, idx1;
            iss >> trash;
            while (iss >> idx) {
                idx--; // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
                if(iss.peek() == '/' ){
                    iss >> trash >> idx1;
                    ft.push_back(idx1);
                }
                while(iss.peek() == '/' && iss >> trash >> itrash);
            }
            faces_.push_back(f);
            faces_t_.push_back(ft);
        }
    }
    std::cerr << "[#] vertices# " << verts_.size() << ", faces# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

Vec3f Model::vert(int i) {
    return verts_[i];
}

