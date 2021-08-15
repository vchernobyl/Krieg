#pragma once

class Component {
public:
    Component(class Actor* owner, int updateOrder = 100);

    virtual ~Component();
    virtual void Update(float deltaTime) {}
    virtual void ProcessInput(const struct InputState& inputState) {}
    virtual void OnUpdateWorldTransform() {}
    
    int GetUpdateOrder() const { return updateOrder; }
    class Actor* GetOwner() const { return owner; }
    
protected:
    class Actor* owner;
    int updateOrder;
};
