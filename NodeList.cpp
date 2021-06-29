#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{
    length = 0;
}

NodeList::~NodeList()
{
    for (int i = 0; i < length; ++i)
    {
        delete nodes[i];
    }

    delete[] copyOfNodes;
}

NodeList::NodeList(NodeList &other)
{
    length = 0;
    for (int i = 0; i < other.length; ++i)
    {
        Node* node = other.getNode(i);
        addElement(node);
    }
}

int NodeList::getLength()
{
    return length;
}

void NodeList::addElement(Node* newPos)
{
    copyOfNodes = nullptr;
    if (length == 0)
    {
        nodes = new Node*[length + 1];
    }
    else
    {
        copyOfNodes = new Node*[length + 1];
        for (int i = 0; i < length; ++i)
        {
            copyOfNodes[i] = nodes[i];
        }

        delete[] nodes;
        nodes = nullptr;

        nodes = copyOfNodes;
    }

    Node* copy = new Node(*newPos);
    nodes[length] = copy;
    length++;
}

Node* NodeList::getNode(int i)
{
    return nodes[i];
}

bool NodeList::containsNode(int row, int col)
{
    bool outcome = false;
    for (int i = 0; i < this->getLength(); ++i)
    {
        int listColVal = this->getNode(i)->getCol();
        int listRowVal = this->getNode(i)->getRow();

        if (listColVal == col && listRowVal == row)
        {
            outcome = true;
        }
    }

    return outcome;
}

int NodeList::getNodeIndex(int row, int col)
{
    int index = -1;
    
    for (int i = 0; i < this->getLength(); ++i)
    {
        int listColVal = this->getNode(i)->getCol();
        int listRowVal = this->getNode(i)->getRow();

        if (listColVal == col && listRowVal == row)
        {
            index = i;
        }
    }

    return index;
}