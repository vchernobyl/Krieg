#include "SpriteBatch.h"
#include <iostream>
#include <algorithm>

SpriteBatchItem::SpriteBatchItem(const Vector4& destRect, const Vector4& uvRect,
                                 GLuint texture, int depth, const Vector4& color) :
    texture(texture), depth(depth) {
    topLeft.color = color;
    topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
    topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

    bottomLeft.color = color;
    bottomLeft.SetPosition(destRect.x, destRect.y);
    bottomLeft.SetUV(uvRect.x, uvRect.y);

    bottomRight.color = color;
    bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
    bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

    topRight.color = color;
    topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
    topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

SpriteBatchItem::SpriteBatchItem(const Vector4& destRect, const Vector4& uvRect,
                                 GLuint texture, int depth, const Vector4& color, float angle) :
    texture(texture), depth(depth) {

    Vector2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

    Vector2 tl(-halfDims.x, halfDims.y);
    Vector2 bl(-halfDims.x, -halfDims.y);
    Vector2 br(halfDims.x, -halfDims.y);
    Vector2 tr(halfDims.x, halfDims.y);

    tl = Vector2::RotatePoint(tl, angle) + halfDims;
    bl = Vector2::RotatePoint(bl, angle) + halfDims;
    br = Vector2::RotatePoint(br, angle) + halfDims;
    tr = Vector2::RotatePoint(tr, angle) + halfDims;
    
    topLeft.color = color;
    topLeft.SetPosition(destRect.x + tl.x, destRect.y + tl.y);
    topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

    bottomLeft.color = color;
    bottomLeft.SetPosition(destRect.x + bl.x, destRect.y + bl.y);
    bottomLeft.SetUV(uvRect.x, uvRect.y);

    bottomRight.color = color;
    bottomRight.SetPosition(destRect.x + br.x, destRect.y + br.y);
    bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

    topRight.color = color;
    topRight.SetPosition(destRect.x + tr.x, destRect.y + tr.y);
    topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

SpriteBatch::SpriteBatch() {
}

void SpriteBatch::Initialize() {
    CreateVertexArray();
}

void SpriteBatch::Begin(SortType sortType) {
    this->sortType = sortType;
    spriteBatchItems.clear();
    renderBatches.clear();
}

void SpriteBatch::End() {
    spriteBatchItemPtrs.resize(spriteBatchItems.size());
    for (int i = 0; i < spriteBatchItems.size(); i++) {
        spriteBatchItemPtrs[i] = &spriteBatchItems[i];
    }
    
    SortSpriteBatchItems();
    CreateRenderBatches();
}

void SpriteBatch::Draw(const Vector4& destRect, const Vector4& uvRect,
                       GLuint texture, int depth, const Vector4& color) {
    spriteBatchItems.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::Draw(const Vector4& destRect, const Vector4& uvRect,
                       GLuint texture, int depth, const Vector4& color, float angle) {
    spriteBatchItems.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void SpriteBatch::Draw(const Vector4& destRect, const Vector4& uvRect,
                       GLuint texture, int depth, const Vector4& color, const Vector2& direction) {
    Vector2 right(1.0f, 0.0f);
    float angle = acos(Vector2::Dot(right, direction));

    if (direction.y < 0.0f) {
        angle = -angle;
    }

    spriteBatchItems.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void SpriteBatch::DrawBatch() {
    glBindVertexArray(vao);

    drawCalls = renderBatches.size();

    for (int i = 0; i < renderBatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
        glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
    }

    glBindVertexArray(0);
}

void SpriteBatch::CreateRenderBatches() {
    if (spriteBatchItemPtrs.empty()) {
        return;
    }

    std::vector<Vertex> vertices;
    vertices.resize(spriteBatchItemPtrs.size() * 6);

    renderBatches.emplace_back(0, 6, spriteBatchItemPtrs[0]->texture);

    int currentVertex = 0;
    vertices[currentVertex++] = spriteBatchItemPtrs[0]->topLeft;
    vertices[currentVertex++] = spriteBatchItemPtrs[0]->bottomLeft;
    vertices[currentVertex++] = spriteBatchItemPtrs[0]->bottomRight;

    vertices[currentVertex++] = spriteBatchItemPtrs[0]->bottomRight;
    vertices[currentVertex++] = spriteBatchItemPtrs[0]->topRight;
    vertices[currentVertex++] = spriteBatchItemPtrs[0]->topLeft;

    for (int i = 1; i < spriteBatchItemPtrs.size(); i++) {
        if (spriteBatchItemPtrs[i]->texture != spriteBatchItemPtrs[i - 1]->texture) {
            renderBatches.emplace_back(currentVertex, 6, spriteBatchItemPtrs[i]->texture);
        } else {
            renderBatches.back().numVertices += 6;
        }
        
        vertices[currentVertex++] = spriteBatchItemPtrs[i]->topLeft;
        vertices[currentVertex++] = spriteBatchItemPtrs[i]->bottomLeft;
        vertices[currentVertex++] = spriteBatchItemPtrs[i]->bottomRight;

        vertices[currentVertex++] = spriteBatchItemPtrs[i]->bottomRight;
        vertices[currentVertex++] = spriteBatchItemPtrs[i]->topRight;
        vertices[currentVertex++] = spriteBatchItemPtrs[i]->topLeft;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::CreateVertexArray() {
    if (vao == 0) glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    if (vbo == 0) glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    
    glBindVertexArray(0);
}

void SpriteBatch::SortSpriteBatchItems() {
    switch (sortType) {
    case SortType::BackToFront:
        std::stable_sort(spriteBatchItemPtrs.begin(), spriteBatchItemPtrs.end(),
                         [](SpriteBatchItem* a, SpriteBatchItem* b) { return a->depth > b->depth; });
        break;
    case SortType::FrontToBack:
        std::stable_sort(spriteBatchItemPtrs.begin(), spriteBatchItemPtrs.end(),
                         [](SpriteBatchItem* a, SpriteBatchItem* b) { return a->depth < b->depth; });
        break;
    case SortType::Texture:
        std::stable_sort(spriteBatchItemPtrs.begin(), spriteBatchItemPtrs.end(),
                         [](SpriteBatchItem* a, SpriteBatchItem* b) { return a->texture < b->texture; });
        break;
    }
}
