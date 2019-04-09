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
    //Todo positions when added to page
    go->posX = 5;
    go->posY = 5;

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
        if(dynamic_cast<Gate*>(allGameObjects[index]))
        {
            //Check if iterated gate has any clicked nodes
            Node* node = dynamic_cast<Gate*>(allGameObjects[index])->GetClickedNode(clickX,clickY);
            if(node != nullptr)
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

                return; //so that we dont acidentally get more than one clicked node
            }
        }
    }
}

void GameObjectPool::dragClick(int clickX, int clickY)
{
    //Loop through all dragable gameobjects
    for (size_t index = 0; index < allGameObjects.size(); index++)
    {
        if(dynamic_cast<DragableGameObject*>(allGameObjects[index]))
        {
            //If found an object to drag, exit out of for loop
            //so we don't drag multiple objects
            if(dynamic_cast<DragableGameObject*>(allGameObjects[index])->
                    UpdateDrag(clickX, clickY))
            {
                return;
            }
        }
    }
}


void GameObjectPool::deleteClick(int clickX, int clickY)
{
    for (size_t index = 0; index < allGameObjects.size(); index++)
    {
        if(allGameObjects[index]->UpdateClicked(clickX,clickY))
        {
            GameObject* gObject = allGameObjects[index];
            allGameObjects.erase(allGameObjects.begin() + index);
            delete gObject;

            //Exit out of for so we dont delete more than one gameobject
            return;
        }
    }
}
void GameObjectPool::defaultClick(int clickX, int clickY)
{

}
