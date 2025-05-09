#include "Level.hpp"

void Level::OnLevelInit()
{
    //
}

GameObject* Level::InstantiateObject()
{
    if (instantiatedObjs.size() - 1 >= instantiatedObjs.capacity())
    {
        instantiatedObjs.reserve(30);
    }

    instantiatedObjs.push_back(std::make_unique<GameObject>());

    return instantiatedObjs.back().get();
}

bool Level::DestroyObject(GameObject* obj)
{
    for (int i = 0; i < GetObjectCount(); i++)
    {
        if (instantiatedObjs.at(i).get() != obj)
            continue;

        instantiatedObjs.erase(instantiatedObjs.begin() + i);
        return true;
    }

    return false;
}

void Level::UpdateLevel()
{
    // Call level's custom update function before behaviour update
    CustomUpdate();

    // Update instantiated objects behaviour
    for (int i = 0; i < instantiatedObjs.size(); i++)
        instantiatedObjs.at(i)->UpdateBehaviour();
}

void Level::CustomUpdate()
{
    //
}