#pragma once

class Component {
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void Update(float deltaTime);

    int GetUpdateOrder() const { return updateOrder; }

protected:
    class Actor* owner;
    int updateOrder;
};
