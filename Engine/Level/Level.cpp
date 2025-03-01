#include "Level.hpp"

void Level::OnLevelInit()
{
    //
}

GameObject& Level::InstantiateObject()
{
    if (instantiatedObjs.size() - 1 >= instantiatedObjs.capacity())
    {
        instantiatedObjs.reserve(30);
    }

    instantiatedObjs.emplace_back();

    return instantiatedObjs.back();
}

void Level::DestroyObject(GameObject& obj)
{
    for (int i = 0; i < GetObjectCount(); i++)
    {
        if (instantiatedObjs.at(i) != obj)
            continue;

        instantiatedObjs.erase(instantiatedObjs.begin() + i);
    }
}

void Level::UpdateLevel()
{
    // Call level's custom update function before behaviour update
    CustomUpdate();

    // Update instantiated objects behaviour
    for (int i = 0; i < instantiatedObjs.size(); i++)
        instantiatedObjs.at(i).UpdateBehaviour();
}

void Level::CustomUpdate()
{
    //
}