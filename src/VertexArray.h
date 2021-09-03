#pragma once

class VertexArray {
public:
    VertexArray();
    VertexArray(const float* vertices, unsigned int vertexCount,
		const unsigned int* indices, unsigned int indexCount);
    ~VertexArray();

    void SetActive();
    unsigned int GetIndexCount() const { return indexCount; }
    unsigned int GetVertexCount() const { return vertexCount; }

private:
    unsigned int vertexCount;
    unsigned int indexCount;

    unsigned int vertexBuffer; // OpenGL id for vertex buffer.
    unsigned int indexBuffer;  // OpenGL id for index buffer.
    unsigned int vertexArray;  // OpenGL id for vertex array object.
};
