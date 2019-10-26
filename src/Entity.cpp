#include "./Entity.h"

Entity::Entity(EntityManager& manager): manager(manager)
{
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name, LayerType layer): manager(manager), name(name), layer(layer)
{
    this->isActive = true;
}

void Entity::Initialize()
{

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

void Entity::SetComponentDebugFlags()
{
    for (auto &component : components)
    {
        component->ToggleDebugMode();
    }
    
}

void Entity::LogAllComponents() const
{
    for (auto const &mapElement : componentTypeMap) {
        std::cout <<"    Component<" << mapElement.first->name() << ">\n";
    }
    std::cout << std::endl;
}