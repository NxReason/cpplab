#pragma once

#include <glad/glad.h>
#include "graphics/GL.h"
#include "Vector.h"
#include <vector>

using nxmath::Vector3;

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
    : Rectangle { center, side_length, side_length } {}

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
