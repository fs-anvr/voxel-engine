#pragma once

#include <glad/gl.h>

#include <cstdint>

#include "VoxelModel.hpp"

namespace VoxelEngine {

// clang-format off
const std::int32_t VOXEL_VERTEX_NUM = 36;

static const GLfloat voxelVertex[] = {
  0.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 1.0f,
  1.0f, 1.0f, 1.0f,
  1.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 0.0f
};

static const GLint voxelIndex[] = {
  // front
  0, 3, 1, 2, 1, 3,
  // back
  4, 7, 5, 6, 5, 7,
  // right
  3, 7, 2, 6, 2, 7,
  // left
  0, 4, 1, 5, 1, 4,
  // top
  2, 6, 1, 5, 1, 6,
  // bottom
  3, 7, 0, 4, 0, 7
};

// clang-format on

class Renderer {
  static GLuint voxelVertexBuffer;  // костыль?
  static GLuint voxelIndexBuffer;   // костыль?
  static GLuint colorBuffer;        // костыль?
  static GLuint VBO;                // костыль?

 public:
  Renderer();
  ~Renderer();

  void Init();
  void Render(const VoxelModel&);
};

}  // namespace VoxelEngine