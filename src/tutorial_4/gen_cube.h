#pragma once

#include <vector>
#include <memory>

#include "vertex.h"

/**
 * @brief Generate the cube vertex buffer given a vertexBuffer reference.
 *
 * @param vertexBuffer the reference to the vertexBuffer vector.
 */
void generateCubeBuffer(std::unique_ptr<std::vector<Vertex>> &vertexBuffer);

/**
 * @brief Generate the cube index buffer given a vertexIndices reference.
 *
 * @param vertexIndices the reference to the vertexIndices vector.
 */
void generateCubeIndices(
    std::unique_ptr<std::vector<unsigned int>> &vertexIndices);