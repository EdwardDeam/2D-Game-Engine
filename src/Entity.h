#pragma once
#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "./EntityManager.h"
#include "./Component.h"

class EntityManager;
class Component;

class Entity 
{
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;
    public:
        Entity(EntityManager &manager);
        Entity(EntityManager &manager, std::string name);
        std::string name;
        void Initialize();
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;

        void LogAllComponents() const;

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args)
        {
            T* newComponent(new T(std::forward<TArgs>(args)...));
            newComponent->name = typeid(T).name();
            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentTypeMap[&typeid(*newComponent)] = newComponent;
            newComponent->Initialize();
            return *newComponent;
        }
        template <typename T>
        T* GetComponent()
        {
            return static_cast<T*>(componentTypeMap[&typeid(T)]);
        }

        template <typename T>
        bool HasComponent() const
        {
            return componentTypeMap.count(&typeid(T)) > 0;
        }
};