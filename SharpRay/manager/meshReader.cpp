#include "meshReader.h"
#include <vector>
#include <string>
#include <iostream>
#include "stdcompact.h"
#include <fstream>
#include <sstream>
#include <Core/world.h>

std::vector<point3D> positions;
std::vector<point3D> texcoords;
std::vector<normal3D> normals;
struct _ObjMeshFaceIndex{
    int pos_index[3];
    int tex_index[3];
    int nor_index[3];
};

std::vector<_ObjMeshFaceIndex>  faces;

void readFace(std::stringstream& ss, _ObjMeshFaceIndex& face)
{
    char interupt;
    for(int i = 0; i < 3; ++i){
        face.nor_index[i] = 0;
        face.tex_index[i] = 0;
        face.pos_index[i] = 0;
        ss >> face.pos_index[i];
        if (ss.peek() == '/') // v//vn or v/vt/vn v/vt
        {
            ss >> interupt;
            if (ss.peek() == '/') // v//vn
            {
                ss >> interupt;
                ss >> face.nor_index[i];
            }
            else    //v/vt/vn or v/vt
            {
                ss >> face.tex_index[i];
                if (ss.peek() == '/') //v/vt/vn
                {
                    ss >> interupt;
                    ss >> face.nor_index[i];
                }
            }
        }
    }
}

bool readObjFile(const char* fName, Mesh* mesh){
    std::ifstream filestream;
    filestream.open(fName);

    std::string line_stream;
    while(std::getline(filestream, line_stream)){
        std::stringstream str_stream(line_stream);
        std::string type_str;
        str_stream >> type_str;
        if(type_str == "v"){
            point3D pos;
            str_stream >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        }else if(type_str == "vt"){
            point3D tex;
            str_stream >> tex.x >> tex.y;
            texcoords.push_back(tex);
        }else if(type_str == "vn"){
            normal3D nor;
            str_stream >> nor.x >> nor.y >> nor.z;
            normals.push_back(nor);
        }else if(type_str == "f"){
            _ObjMeshFaceIndex face_index;
            faces.push_back(face_index);
        }else if (type_str[0] == '#')
            continue;
        else{
            fprintf(stderr, "Unknown token %s\n", type_str.c_str());
            continue;
        }
    }
    filestream.close();
    mesh->triMesh = new Triangle[faces.size()];
    mesh->numTriangle = faces.size();

    for(size_t i = 0; i < faces.size(); ++i){
        Triangle& face = mesh->triMesh[i];
        for(size_t j = 0; j < 3; ++j){
            face.vertex[j] = positions[faces[i].pos_index[j] - 1];
            if (faces[i].tex_index[j]>0)
                face.texturePos[j]  = texcoords[faces[i].tex_index[j] - 1];
            face.normal[j]    = normals[faces[i].nor_index[j] - 1];
        }
    }
    return true;
}
