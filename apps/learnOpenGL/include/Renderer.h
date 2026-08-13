#pragma once

#include "utils/Color.h"

class Renderer {
public:
  Renderer(Color clearColor = { 0.1f, 0.1f, 0.1f, 1.0f });
  void clear() const;

  void depthTest(bool isOn = true) const;
private:
  Color m_clearColor;
};