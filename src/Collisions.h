#pragma once

#include "Math.h"

bool RayIntersects(const Vector2& rayOrigin, const Vector2& rayDir, const Rect& target,
		   Vector2& contactPoint, Vector2& contactNormal, float& tHitNear);

bool DynamicRectsIntersect(const Rect& in, const Vector2& vel,
			   const Rect& target, Vector2& contactPoint,
			   Vector2& contactNormal, float& contactTime, float deltaTime);

bool BoxCollidersIntersect(class BoxColliderComponent* a, class BoxColliderComponent* b,
			   class Manifold& info, float deltaTime);
