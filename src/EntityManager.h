#pragma once
#include "./Entity.h"
#include "./Component.h"
#include <vector>
#include <iostream>

class EntityManager
{
    private:
        std::vector<Entity*> entities;
    public:
        void ClearData();
        void LogAllEntities() const;
        void Initialize();
        void InitializeEntities();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities() const;
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> GetEntities() const;
        unsigned int GetEntityCount();
};