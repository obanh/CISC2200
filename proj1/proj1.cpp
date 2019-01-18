/** @mainpage
 *
 * CISC 5220: Data Structures<br/>
 * Project 1: Extending the Bag ADT<br/>
 *
 * <p>This program tests the <code>VectorBag</code> class.  It is a
 * modification of the program given in Section&nbsp;3.2 of the text,
 * which tests the <code>ArrayBag</code> class.</p>
 *
 * <p>In addition to testing the operations that VectorBag implements
 * from the abstract BagInterface class, it tests the set-like
 * operations of union, intersection, and difference.</p>
 *
 * <p>(Based on Exercises&nbsp;1.6-1.8, along with Programming
 * Problem&nbsp;3.5.)</p>
 *
 * @author Oscar Banh
 * @date September 25, 2018
 * @file proj1.cpp
 *
 **********************************************************************/

// usual front matter (includes, declarations)

#include <algorithm>
#include <iostream>
#include <string>
#include "VectorBag.cpp"

using namespace std;

template<class ItemType> void displayBag(VectorBag<ItemType>& bag);
template<class ItemType> void bagTester(VectorBag<ItemType>& bag);
void newOpsTester();

/**
 * The usual <code>main()</code> function.
 */
int main()
{
   VectorBag<string> bag;
   cout << "Testing the Vector-Based Bag:" << endl;
   cout << "The initial bag is empty." << endl;
   bagTester(bag);
   newOpsTester();
   cout << "All done!" << endl;

   return 0;
}

/**
 * Display the contents of a <code>VectorBag</code>, which can hold
 * any kind of element.  The elements are displayed in sorted order.
 * (This means that the <code>ItemType</code> must be one for which
 * the&nbsp;"&lt;" operation is defined.)
 * @param bag The bag to be displayed.
 */
template<class ItemType>
void displayBag(VectorBag<ItemType>& bag)
{
   cout << "The bag contains " << bag.getCurrentSize()
        << " items:" << endl;
   vector<ItemType> bagItems = bag.toVector();

   int numberOfEntries = static_cast<int>(bagItems.size());
   sort(bagItems.begin(), bagItems.end());

   for (int i = 0; i < numberOfEntries; i++)
      cout << bagItems[i] << " ";
   cout << endl << endl;
}  // end displayBag

/**
 * This is an adaption of the <code>bagTester</code> function in
 * Carrano-Henry <code>main.cpp</code>, which tests the
 * <code>ArrayBag</class>.  The changes are as follows:
 * <ol>
 * <li> Whereas the original version assumed that
 * the <code>ArrayBag</code> contained <code>string</code>, our
 * version allows the <code>VectorBag</code> to contain any kind of
 * item.</li>
 * <li> In addition to testing the original operations that are
 * implemented from <code>BagInterface</code>, we test the operations
 * of union, intersection, and difference.</li>
 * </ol>
 * @param bag The bag to be tested.
 */
template<class ItemType> void bagTester(VectorBag<ItemType>& bag)
{
   cout << "isEmpty: returns " << bag.isEmpty()
        << "; should be 1 (true)" << endl;
   displayBag(bag);

   string items[] = {"one", "two", "three", "four", "five", "one"};
   unsigned int itemsSize = sizeof(items)/sizeof(items[0]);
   cout << "Adding " << itemsSize << " items to the bag: " << endl;
   for (unsigned int i = 0; i < itemsSize; i++)
      bag.add(items[i]);

   displayBag(bag);

   cout << "isEmpty: returns " << bag.isEmpty()
        << "; should be 0 (false)" << endl;

   cout << "getCurrentSize: returns " << bag.getCurrentSize()
        << "; should be " << itemsSize << endl;

   cout << "Try to add another entry: add(\"extra\") returns "
        << bag.add("extra") << endl;

   cout << "contains(\"three\"): returns " << bag.contains("three")
        << "; should be 1 (true)" << endl;
   cout << "contains(\"ten\"): returns " << bag.contains("ten")
        << "; should be 0 (false)" << endl;
   cout << "getFrequencyOf(\"one\"): returns "
        << bag.getFrequencyOf("one") << " should be 2" << endl;
   cout << "remove(\"one\"): returns " << bag.remove("one")
        << "; should be 1 (true)" << endl;
   cout << "getFrequencyOf(\"one\"): returns "
        << bag.getFrequencyOf("one") << " should be 1" << endl;
   cout << "remove(\"one\"): returns " << bag.remove("one")
        << "; should be 1 (true)" << endl;
   cout << "remove(\"one\"): returns " << bag.remove("one")
        << "; should be 0 (false)" << endl;
   cout << endl;

   displayBag(bag);

   cout << "After clearing the bag, ";
   bag.clear();

   cout << "isEmpty: returns " << bag.isEmpty()
        << "; should be 1 (true)" << endl;
}  // end bagTester

/**
 * Test the new VectorBag operations (union, intersection, difference)
 */
void newOpsTester()
{
   cout << "\nLet's test the new bag operations.\n\n";
   int firstItems[] = {2, 4, 6, 6, 8, 10, 12, 15, 15};
   VectorBag<int> firstBag;
   int firstSize = sizeof(firstItems)/sizeof(int);
   cout << "Adding " << firstSize << " items to first bag: " << endl;
   for (int i = 0; i < firstSize; i++)
      firstBag.add(firstItems[i]);
   cout << "First bag: ";
   displayBag(firstBag);

   int secondItems[] = {3, 6, 9, 12, 12, 15, 15, 18};
   VectorBag<int> secondBag;
   int secondSize = sizeof(secondItems)/sizeof(int);
   cout << "Adding " << secondSize << " items to second bag: " << endl;
   for (int i = 0; i < secondSize; i++)
      secondBag.add(secondItems[i]);
   cout << "Second bag: ";
   displayBag(secondBag);

   VectorBag<int> unionBag = firstBag + secondBag;
   cout << "firstBag union secondBag: \n";
   displayBag(unionBag);


   VectorBag<int> intersectBag = firstBag * secondBag;
   cout << "firstBag intersect secondBag: \n";
   displayBag(intersectBag);

   VectorBag<int> diffBag = firstBag - secondBag;
   cout << "firstBag minus secondBag: \n";
   displayBag(diffBag);

   diffBag = secondBag - firstBag;
   cout << "secondBag minus firstBag: \n";
   displayBag(diffBag);

}
