#include "VertexArray.h"
#include "Assert.h"
#include <GL/glew.h>

VertexArray::VertexArray() {}

VertexArray::VertexArray(const float* vertices, unsigned int vertexCount,
			 const unsigned int* indices, unsigned int indexCount)
    : vertexCount(vertexCount),
      indexCount(indexCount) {
    // Create the vertex array object (VAO).
    GL_CALL(glGenVertexArrays(1, &vertexArray));
    GL_CALL(glBindVertexArray(vertexArray));

    // Create the vertex buffer.
    GL_CALL(glGenBuffers(1, &vertexBuffer));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertexCount * 5 * sizeof(float), vertices, GL_STATIC_DRAW));

    // Create the index buffer.
    GL_CALL(glGenBuffers(1, &indexBuffer));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    // Specify the vertex attributes.
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3)));
}

VertexArray::~VertexArray() {
    GL_CALL(glDeleteBuffers(1, &vertexBuffer));
    GL_CALL(glDeleteBuffers(1, &indexBuffer));
    GL_CALL(glDeleteVertexArrays(1, &vertexArray));
}

void VertexArray::SetActive() {
    GL_CALL(glBindVertexArray(vertexArray));
}
