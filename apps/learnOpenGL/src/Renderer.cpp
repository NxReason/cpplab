#include "Renderer.h"

#include <glad/glad.h>

Renderer::Renderer(Color clearColor)
  : m_clearColor(clearColor) {}

void Renderer::clear() const {
  glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::depthTest(bool isOn) const {
  if (isOn) {
    glEnable(GL_DEPTH_TEST);
  }
  else {
    glDisable(GL_DEPTH_TEST);
  }
}