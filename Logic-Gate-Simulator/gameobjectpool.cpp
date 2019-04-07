#include "gameobjectpool.h"


GameObjectPool::GameObjectPool()
{

}

GameObjectPool::~GameObjectPool()
{
    for (size_t index = 0; index < allGameObjects.size(); index++)
    {
        delete allGameObjects[index];
    }
}

void GameObjectPool::addGameObject(GameObject* go)
{
    allGameObjects.push_back(go);
}

void GameObjectPool::handleInput(int clickX, int clickY, ClickMode clickMode)
{
    switch (clickMode)
    {
    case CLICK_DRAG:        dragClick(clickX,clickY);  break;

    case CLICK_LINK_NODES:  linkNodesClick(clickX,clickY); break;

    case CLICK_DELETE_GATE: deleteClick(clickX,clickY);  break;

    case CLICK_NONE:        defaultClick(clickX,clickY);  break;
    }
}

void GameObjectPool::runGates()
{
    for (size_t index = 0; index < allGameObjects.size(); index++)
    {
        if(dynamic_cast<Gate*>(allGameObjects[index]))
        {
            dynamic_cast<Gate*>(allGameObjects[index])->UpdateOutput();
        }
    }
}

void GameObjectPool::draw()
{
    //Draw lines between the nodes

    //Draw the icons of the gates
}

void GameObjectPool::linkNodesClick(int clickX, int clickY)
{
    for (size_t index = 0; index < allGameObjects.size(); index++)
    {
        if(dynamic_cast<Node* >(allGameObjects[index]))
        {
            Node* node = dynamic_cast<Node* >(allGameObjects[index]);

            //check if clicked
            if(node->UpdateClicked(clickX,clickY))
            {

                //If m_linkNodeA is a null pointer then its the first node to be clicked
                if(m_linkNodeA != nullptr)
                {
                    m_linkNodeA = node;
                }

                //Otherwise click on second node, so link first & second and then set m_linkNodeA to null
                else
                {
                    m_linkNodeA->LinkNode(node);
                    node->LinkNode(m_linkNodeA);
                    m_linkNodeA = nullptr;
                }
            }
        }
    }
}
void GameObjectPool::dragClick(int clickX, int clickY)
{
    for (size_t index = 0; index < allGameObjects.size(); index++)
    {
        if(dynamic_cast<DragableGameObject*>(allGameObjects[index]))
        {
            dynamic_cast<DragableGameObject*>(allGameObjects[index])->UpdateDrag(clickX, clickY);
        }
    }
}

//Option --> Delete the first gate clicked on
void GameObjectPool::deleteClick(int clickX, int clickY)
{
    for (size_t index = 0; index < allGameObjects.size(); index++)
    {
        if(allGameObjects[index]->UpdateClicked(clickX,clickY))
        {
            GameObject* gObject = allGameObjects[index];
            allGameObjects.erase(allGameObjects.begin() + index);
            delete gObject;
            return;
        }
    }
}
void GameObjectPool::defaultClick(int clickX, int clickY)
{

}
