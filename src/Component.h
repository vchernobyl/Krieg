#pragma once

class Component {
public:
    Component(class Actor* owner, int updateOrder = 100);

    virtual ~Component();
    virtual void Update(float deltaTime) {}
    virtual void ProcessInput(const struct InputState& inputState) {}
    virtual void OnUpdateWorldTransform() {}
    virtual void OnBeginContact(const struct Contact& contact) {}
    
    int GetUpdateOrder() const { return updateOrder; }
    class Actor* GetOwner() const { return owner; }

    void SetEnabled(bool enabled) { this->enabled = enabled; }
    bool IsEnabled() const { return enabled; }
    
protected:
    class Actor* owner;
    int updateOrder;

private:
    bool enabled = true;
};
