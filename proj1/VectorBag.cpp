//Oscar Banh
//September 25, 2018

#include "VectorBag.h"
#include <iostream>
#include <vector>
using namespace std;


template<class ItemType>
VectorBag<ItemType>::VectorBag()
{}

template<class ItemType>
VectorBag<ItemType>::~VectorBag()
{}

template<class ItemType>
int VectorBag<ItemType>::getCurrentSize() const
{
    return bag.size();
}

template<class ItemType>
bool VectorBag<ItemType>::isEmpty() const
{
    return bag.size() == 0;
}

template<class ItemType>
bool VectorBag<ItemType>::add(const ItemType& newEntry)
{
    bag.push_back(newEntry);
    return true;
}

template<class ItemType>
bool VectorBag<ItemType>::remove(const ItemType& anEntry)
{
    for (int i = 0; i < bag.size(); i++)
    {
        if (bag.at(i) == anEntry)
        {
            bag[i] = bag[bag.size() - 1];
            bag.pop_back();
            return true;
        }
    }
    return false;
}

template<class ItemType>
void VectorBag<ItemType>::clear()
{
    bag.clear();
}

template<class ItemType>
int VectorBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
    int frequency = 0;
    for (int i = 0; i < bag.size(); i++)
    {
        if (bag.at(i) == anEntry)
        {
            frequency++;
        }
    }
    return frequency;
}
template<class ItemType>
bool VectorBag<ItemType>::contains(const ItemType& anEntry) const
{
    for (int i = 0; i < bag.size(); i++)
    {
        if (bag.at(i) == anEntry)
        {
            return true;
        }
    }
    return false;
}

template<class ItemType>
vector<ItemType> VectorBag<ItemType>::toVector() const
{
    return bag;
}

template<class ItemType>
VectorBag<ItemType> VectorBag<ItemType>::operator+(VectorBag<ItemType> &anotherBag)
{
    VectorBag<ItemType> combined;
    for (int i = 0; i < bag.size(); i++)
    {
        combined.add(bag.at(i));
    }
    for (int i = 0; i < anotherBag.getCurrentSize(); i++)
    {
        combined.add(anotherBag.bag.at(i));
    }
    return combined;
}

template<class ItemType>
VectorBag<ItemType> VectorBag<ItemType>::operator-(VectorBag<ItemType> &anotherBag)
{
    VectorBag<ItemType> complement;
    for (int i = 0; i < bag.size(); i++)
    {
        complement.add(bag.at(i));
    }
    for (int i = 0; i < anotherBag.getCurrentSize(); i++)
    {
        complement.remove(anotherBag.bag.at(i));
    }
    return complement;
}

template<class ItemType>
VectorBag<ItemType> VectorBag<ItemType>::operator*(VectorBag<ItemType> & anotherBag)
{
    VectorBag<ItemType> temp;
    VectorBag<ItemType> bagCopy;
    VectorBag<ItemType> intersection;
    for (int i = 0; i < bag.size(); i++)
    {
        for (int n = 0; n < anotherBag.getCurrentSize(); n++)
        {
            if (bag.at(i) == anotherBag.bag.at(n))
            {
                if (temp.contains(bag.at(i)) == false)
                {
                    temp.add(bag.at(i));
                }
            }
        }
        bagCopy.add(bag.at(i));
    }
    for (int i = 0; i < temp.getCurrentSize(); i++)
    {
        if (anotherBag.contains(temp.bag.at(i)) && bagCopy.contains(temp.bag.at(i)))
        {
            int bag1Freq = bagCopy.getFrequencyOf(temp.bag.at(i));
            int bag2Freq = anotherBag.getFrequencyOf(temp.bag.at(i));
            int counter = 0;
            if (bag1Freq >= bag2Freq)
            {
                while (counter < bag2Freq)
                {
                    intersection.add(temp.bag.at(i));
                    counter++;
                }
            }
            else
            {
                while (counter < bag1Freq)
                {
                    intersection.add(temp.bag.at(i));
                    counter++;
                }
            }
        }
    }
    return intersection;
}
