#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{
    length = 0;
    nodes = nullptr;
}

NodeList::~NodeList()
{
    for (int i = 0; i < length-1; i++)
    {
        delete nodes[i];
    }
    delete[] nodes;
}

NodeList::NodeList(NodeList& other) :
    nodes(new Node*[other.getLength()]),
    length(other.length)
{
    for (int i = 0; i < other.getLength(); ++i)
    {
        nodes[i] = new Node(other.getNode(i)->getRow(), 
                            other.getNode(i)->getCol(), 
                            other.getNode(i)->getDistanceTraveled());
    }
}

int NodeList::getLength()
{
    return length;
}

void NodeList::addElement(Node* newNode)
{
    if(nodes == nullptr)
    {
        nodes = new Node*[1];
        nodes[length] = newNode;
        length++;
    }
    else
    {   //Create new array with one extra space
        Node** largerArray = new Node*[length+1];

        //Copy array over and disconnect the contents of smaller array
        for (int i = 0; i < length; i++) 
        {
            largerArray[i] = nodes[i];
            nodes[i] = nullptr;
        }
        //Put new element in at the end
        largerArray[length] = newNode;

        //Switch array reference and disconnect the newly created one
        nodes = largerArray;
        largerArray = nullptr;
        length++;
    }
}

Node* NodeList::getNode(int i)
{
    return nodes[i];
}