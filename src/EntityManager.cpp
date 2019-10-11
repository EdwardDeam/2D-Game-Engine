#include "./EntityManager.h"


void EntityManager::ClearData()
{
    for(auto& entity: entities)
    {
        entity->Destroy();
    }
}

void EntityManager::LogAllEntities() const
{
    unsigned int i = 0;
    for (auto& entity: entities)
    {
        std::cout << "Entity["<< i << "]: " << entity->name << "\n";
        entity->LogAllComponents();
        i++;
    }
    std::cout << std::endl;
    
}

bool EntityManager::HasNoEntities() const
{
    return entities.size() == 0;
}

void EntityManager::Initialize()
{

}

void EntityManager::InitializeEntities()
{
    for(auto& entity: entities)
    {
        entity->Initialize();
    }
}

void EntityManager::Update(float deltaTime)
{
    for(auto& entity: entities)
    {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render()
{
    for(auto& entity: entities)
    {
        entity->Render();
    }
}

Entity& EntityManager::AddEntity(std::string entityName)
{
    Entity* entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const{
    return entities;
}

unsigned int EntityManager::GetEntityCount()
{
    return entities.size();
}