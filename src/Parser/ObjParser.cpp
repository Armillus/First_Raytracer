#include "ObjParser.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

rt::ObjParser::ObjParser(rt::Scene &scene) : _scene(scene)
{
    _vertices.reserve(3);
}

void rt::ObjParser::parse(const std::string &fileName)
{
    tinyobj::attrib_t attribut;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;

    bool ret = tinyobj::LoadObj(&attribut, &shapes, &materials, &err, fileName.c_str());

    if (!err.empty() || !ret)
    {
        std::cerr << "err" << std::endl;
        return;
    }

    initTriangles(attribut, shapes);
}

void rt::ObjParser::initTriangles(tinyobj::attrib_t &attrib, std::vector<tinyobj::shape_t> &shapes)
{
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];

                _vertices.push_back({vx, vy, vz});

                if ((v + 1) % 3 == 0)
                    initTriangle();
            }
            index_offset += fv;
        }
    }
}

void rt::ObjParser::initTriangle()
{
    std::size_t id = _scene.createObject(tTriangle);

    maths::Vector3f p1 = _vertices.at(0);
    maths::Vector3f p2 = _vertices.at(1);
    maths::Vector3f p3 = _vertices.at(2);
    _vertices.clear();

    std::cout << p1 << " " << p2 << " " << p3 << std::endl;

    _scene.ochangePoints(id, p1, p2, p3);
    std::cout << _scene.objects().size() << std::endl;
    //_scene.ochangeMaterial();
}
