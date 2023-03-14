#include "gen_cube.h"

/**
 * @brief Generate random color.
 *
 * @return glm::vec4 color in glm::vec4.
 */
glm::vec4 genRandomColor() {
  return glm::vec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX,
                   (float)rand() / RAND_MAX, 1.0f);
}

void generateCubeBuffer(std::unique_ptr<std::vector<Vertex>> &vertexBuffer) {
  // Generate all the vertices.
  vertexBuffer->resize(8);
  (*vertexBuffer)[0] = {{-1, -1, -1}, genRandomColor()};
  (*vertexBuffer)[1] = {{1, -1, -1}, genRandomColor()};
  (*vertexBuffer)[2] = {{1, 1, -1}, genRandomColor()};
  (*vertexBuffer)[3] = {{-1, 1, -1}, genRandomColor()};
  (*vertexBuffer)[4] = {{-1, -1, 1}, genRandomColor()};
  (*vertexBuffer)[5] = {{1, -1, 1}, genRandomColor()};
  (*vertexBuffer)[6] = {{1, 1, 1}, genRandomColor()};
  (*vertexBuffer)[7] = {{-1, 1, 1}, genRandomColor()};
}

void generateCubeIndices(
    std::unique_ptr<std::vector<unsigned int>> &vertexIndices) {
  // The cube contains 6 surfaces.
  // Each serface contains 2 triangles.
  // Each triangle contains 3 vertices.
  vertexIndices->resize(6 * 2 * 3);
  int indxArr[] = {
      0, 1, 4, 4, 1, 5,  // Front.
      1, 5, 2, 5, 2, 6,  // Right.
      2, 3, 6, 6, 3, 7,  // Back.
      3, 0, 4, 4, 3, 7,  // Left.
      0, 1, 3, 3, 1, 2,  // Bottom.
      4, 5, 7, 7, 5, 6   // Top.
  };

  for (int i = 0; i < vertexIndices->size(); i++) {
    (*vertexIndices)[i] = indxArr[i];
  }
}