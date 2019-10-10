#pragma once
#include "./Entity.h"
#include "./Component.h"
#include <vector>

class EntityManager
{
    private:
        std::vector<Entity*> entities;
    public:
        void ClearData();
        void Initialize();
        void Update(float deltaTime);
        void Render();
        bool HasNoEntities() const;
        Entity& AddEntity(std::string entityName);
        std::vector<Entity*> GetEntities() const;
        unsigned int GetEntityCount();
};