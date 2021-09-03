#include "VertexArray.h"
#include <glew.h>

VertexArray::VertexArray() {}

VertexArray::VertexArray(const float* vertices, unsigned int vertexCount,
			 const unsigned int* indices, unsigned int indexCount) {
    // Create the vertex array object (VAO).
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // Create the vertex buffer.
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 5 * sizeof(float), vertices, GL_STATIC_DRAW);

    // Create the index buffer.
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Specify the vertex attributes.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
}

VertexArray::~VertexArray() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
}

void VertexArray::SetActive() {
    glBindVertexArray(vertexArray);
}
