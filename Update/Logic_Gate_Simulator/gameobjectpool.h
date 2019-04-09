#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H

#include "gate.h"
#include "clickmode.h"

class GameObjectPool
{
public:
    GameObjectPool();
    ~GameObjectPool();

    void addGameObject(Gate* go);

    void handleInput(int clickX, int clickY, ClickMode clickMode);

    void runGates();

    void draw();

private:
    std::vector<Gate*> m_allGates;

    void linkNodesClick(int clickX, int clickY);
    void dragClick(int clickX, int clickY);
    void deleteClick(int clickX, int clickY);
    void defaultClick(int clickX, int clickY);

    Node* m_linkNodeA = nullptr;

    //Coords of newly spawned gate
    const int SPAWN_X = 50;
    const int SPAWN_Y = 50;
};

#endif // GAMEOBJECTPOOL_H
