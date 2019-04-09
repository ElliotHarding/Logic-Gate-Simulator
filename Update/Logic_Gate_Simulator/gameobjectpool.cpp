#include "gameobjectpool.h"


GameObjectPool::GameObjectPool()
{

}

GameObjectPool::~GameObjectPool()
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        delete m_allGates[index];
    }
}

void GameObjectPool::addGameObject(Gate* go)
{
    //Todo positions when added to page
    go->posX = SPAWN_X;
    go->posY = SPAWN_Y;

    m_allGates.push_back(go);
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
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        m_allGates[index]->UpdateOutput();
    }
}

void GameObjectPool::draw()
{
    //Draw lines between the nodes

    //Draw gates
}

void GameObjectPool::linkNodesClick(int clickX, int clickY)
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        //Check if iterated gate has any clicked nodes
        Node* node = (m_allGates[index])->GetClickedNode(clickX,clickY);
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

void GameObjectPool::dragClick(int clickX, int clickY)
{
    //Loop through all dragable gameobjects
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        //If found an object to drag, exit out of for loop
        //so we don't drag multiple objects
        if(m_allGates[index]->UpdateDrag(clickX, clickY))
        {
            return;
        }
    }
}


void GameObjectPool::deleteClick(int clickX, int clickY)
{
    for (size_t index = 0; index < m_allGates.size(); index++)
    {
        if(m_allGates[index]->UpdateClicked(clickX,clickY))
        {
            Gate* gObject = m_allGates[index];
            m_allGates.erase(m_allGates.begin() + index);
            delete gObject;

            //Exit out of for so we dont delete more than one gameobject
            return;
        }
    }
}
void GameObjectPool::defaultClick(int clickX, int clickY)
{

}
