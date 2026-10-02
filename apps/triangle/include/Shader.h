#pragma once

#include <glad/glad.h>

GLuint createShader(GLenum type, const char* source);
GLuint createShaderProgram();