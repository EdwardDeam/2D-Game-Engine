#pragma once
#include <string>

class Entity;

class Component
{
  public:
    Entity* owner;
    std::string name;
    virtual~Component() {};
    virtual void Initialize() {};
    virtual void Update(float deltaTime) {};
    virtual void Render() {};
    virtual void ToggleDebugMode() {};

  private:
};
