#include <iostream>
#include "./Entity.h"

Entity::Entity(EntityManager& manager): manager(manager)
{
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name): manager(manager), name(name)
{
    this->isActive = true;
}

void Entity::Initialize()
{
    // TODO: Wrap this for DEBUG setting only.
    // Log Entity and component data.
    std::cout << "Entity Name: " << name << "\n";
    for (auto const &typeComponent : componentTypeMap) {
        std::cout <<"\t Component<" << typeComponent.second->name << ">\n";
    }  
    std::cout << "\n" << std::endl;
}

void Entity::Update(float deltaTime)
{
    for (auto& component: components)
    {
        component->Update(deltaTime);
    }
}

void Entity::Render()
{
    for (auto& component: components)
    {
        component->Render();
    }
}

void Entity::Destroy() 
{
    this->isActive = false;
}

bool Entity::IsActive() const
{
    return this->isActive;
}