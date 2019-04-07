#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H

#include "gameobject.h"
#include "node.h"
#include "clickmode.h"

class GameObjectPool
{
public:
    GameObjectPool();
    ~GameObjectPool();

    void addGameObject(GameObject* go);

    void handleInput(int clickX, int clickY, ClickMode clickMode);

    void runGates();

    void draw();

private:
    std::vector<GameObject*> allGameObjects;

    void linkNodesClick(int clickX, int clickY);
    void dragClick(int clickX, int clickY);
    void deleteClick(int clickX, int clickY);
    void defaultClick(int clickX, int clickY);


    Node* m_linkNodeA = nullptr;
};

#endif // GAMEOBJECTPOOL_H
