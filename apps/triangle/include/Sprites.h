#pragma once

#include <cmath>
#include <vector>

#include <glad/glad.h>
#include "graphics/GL.h"
#include "Vector.h"
#include "nxmath.h"

using namespace nxmath;

struct Mesh {
  VAO vao{};
  VBO vbo{};
  EBO ebo{};
};

class Sprite {
public:
  int vertex_count { 0 };
  Mesh mesh {};
  Vector3 color { 1.0, 0.0, 1.0 };

  virtual std::vector<float> get_coords() const = 0;
  virtual std::vector<unsigned int> get_indices() const = 0;

  virtual std::vector<VertexAttribute> vao_layout() const {
    return {
      VertexAttribute { 3, GL_FLOAT, 3 * sizeof(float) }
    };
  }
};

class Triangle : public Sprite {
public:
  Triangle(Vector3 a = { -0.5, -0.5 }, Vector3 b = { 0.5, -0.5 }, Vector3 c = { 0.0, 0.5 }) 
    : a { a }, b { b }, c { c }
  {
    vertex_count = 3;

    mesh.vao.bind();

    mesh.vbo.bind();
    mesh.vbo.data(get_coords());

    mesh.ebo.bind();
    mesh.ebo.data(get_indices());

    mesh.vao.attrib_layout(vao_layout());
  }

  std::vector<float> get_coords() const override {
    return {
      a.x, a.y, a.z,
      b.x, b.y, b.z,
      c.x, c.y, c.z
    };
  }

  std::vector<unsigned int> get_indices() const override {
    return { 0, 1, 2 };
  }
private:
  Vector3 a;
  Vector3 b;
  Vector3 c;
};

class Rectangle : public Sprite {
public:
  Rectangle(Vector3 center, float width, float height) 
    : m_center { center }, m_width { width }, m_height { height } {
    vertex_count = 6;
    mesh.vao.bind();

    mesh.vbo.bind();
    mesh.vbo.data(get_coords());

    mesh.ebo.bind();
    mesh.ebo.data(get_indices());

    mesh.vao.attrib_layout(vao_layout());
  }

  Rectangle()
    : Rectangle { { 0, 0 }, .25, .25 } {}

  Rectangle(Vector3 center, float side_length) 
    : Rectangle { center, side_length / 2, side_length / 2 } {}

  Rectangle(float side_length)
    : Rectangle {
      Vector3 { 0, 0 }
      , side_length / 2
      , side_length / 2 } {} 

  Rectangle(float width, float height)
    : Rectangle {
      Vector3 { 0, 0 },
      width / 2,
      height / 2
    } {}

  std::vector<float> get_coords() const override {
    return {
      m_center.x - m_width, m_center.y - m_height, m_center.z,
      m_center.x - m_width, m_center.y + m_height, m_center.z,
      m_center.x + m_width, m_center.y + m_height, m_center.z,
      m_center.x + m_width, m_center.y - m_height, m_center.z,
    };
  }

  std::vector<unsigned int> get_indices() const override {
    return { 
      0, 1, 2,
      0, 2, 3
    };
  }

  std::vector<VertexAttribute> vao_layout() const override {
    return {
      VertexAttribute { 3, GL_FLOAT, 3 * sizeof(float) }
    };
  }
private:
  Vector3 m_center { 0.0, 0.0, 0.0 };
  float m_width { 0.1 }, m_height { 0.1 };
};

class Cube : public Sprite {
public:
  Cube(Vector3 center, float width) 
    : m_center { center }, m_width { width } {
    vertex_count = 36;
    mesh.vao.bind();

    mesh.vbo.bind();
    mesh.vbo.data(get_coords());

    mesh.ebo.bind();
    mesh.ebo.data(get_indices());

    mesh.vao.attrib_layout(vao_layout());
  }

  Cube(float width)
    : Cube {
      Vector3 { 0, 0 },
      width
    }
    {}

  std::vector<float> get_coords() const override {
    float half = m_width / 2;
    return {
      m_center.x - half, m_center.y - half, m_center.z - half,
      m_center.x - half, m_center.y - half, m_center.z + half,
      m_center.x - half, m_center.y + half, m_center.z - half,
      m_center.x - half, m_center.y + half, m_center.z + half,

      m_center.x + half, m_center.y - half, m_center.z - half,
      m_center.x + half, m_center.y - half, m_center.z + half,
      m_center.x + half, m_center.y + half, m_center.z - half,
      m_center.x + half, m_center.y + half, m_center.z + half,
    };
  }

  std::vector<unsigned int> get_indices() const override {
    return { 
      0, 1, 2,
      1, 2, 3,
      4, 5, 6,
      5, 6, 7,
      1,5, 7,
      1, 3, 7,
      0, 2, 6,
      0, 4, 6,
      3, 7, 6,
      3, 2, 6,
      1, 5, 4,
      1, 0, 4
    };
  }

  std::vector<VertexAttribute> vao_layout() const override {
    return {
      VertexAttribute { 3, GL_FLOAT, 3 * sizeof(float) }
    };
  }

private:
  Vector3 m_center { 0.0, 0.0, 0.0 };
  float m_width { 0.1 };
};


class Circle : public Sprite {
public:
  Circle(const Vector3& center, float radius)
    : center { center }, radius { radius }
  {
    vertex_count = slices * 3;

    mesh.vao.bind();

    mesh.vbo.bind();
    mesh.vbo.data(get_coords());

    mesh.ebo.bind();
    mesh.ebo.data(get_indices());

    mesh.vao.attrib_layout(vao_layout());
  }

  Circle(float radius)
    : Circle {
      Vector3 { 0, 0 },
      radius
    }
  {}

  std::vector<float> get_coords() const override {
    std::vector<float> vertices;
    vertices.reserve(3 + slices * 3);
    vertices.push_back(center.x);
    vertices.push_back(center.y);
    vertices.push_back(center.z);

    float slice_angle = deg_to_rad(360 / static_cast<float>(slices));
    for (int i = 0; i < slices; i++) {
      float angle = i * slice_angle;

      vertices.push_back(center.x + radius * std::cos(angle));
      vertices.push_back(center.y + radius * std::sin(angle));
      vertices.push_back(center.z);
    }
    return vertices;
  }

  std::vector<unsigned int> get_indices() const override {
    std::vector<unsigned int> indices;
    indices.reserve(slices * 3);
    for (int i = 0; i < slices; i++) {
      indices.push_back(0);
      indices.push_back(i + 1);
      indices.push_back(i + 2);
    }
    indices[indices.size() - 1] = 1;
    return indices;
  }
private:
  Vector3 center;
  float radius;
  
  int slices { 8 * 2 * 2 * 2 };
};