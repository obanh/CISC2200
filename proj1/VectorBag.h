//Oscar Banh
//September 25, 2018

#ifndef VECTORBAG_H
#define VECTORBAG_H

#include <vector>
#include "BagInterface.h"

template<class ItemType>
class VectorBag : public BagInterface <ItemType>
{
    public:
        VectorBag();
        ~VectorBag();
        int getCurrentSize() const;
        bool isEmpty() const;
        bool add(const ItemType& newEntry);
        bool remove(const ItemType& anEntry);
        void clear();
        bool contains(const ItemType& anEntry) const;
        int getFrequencyOf(const ItemType& anEntry) const;
        std::vector<ItemType> toVector() const;
        VectorBag<ItemType> operator+(VectorBag<ItemType>&anotherBag);
        VectorBag<ItemType> operator-(VectorBag<ItemType>&anotherBag);
        VectorBag<ItemType> operator*(VectorBag<ItemType>&anotherBag);

    private:
        std::vector<ItemType> bag;
};

#endif // VECTORBAG_H
