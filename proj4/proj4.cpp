//Oscar Banh
//November 26, 2018
#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Event {
    int time;
    int length;
    Event(int t, int l);
};

Event::Event(int t, int l)
{
    time = t;
    length = l;
}
struct EventList {
   // other stuff here
   priority_queue<Event>eventListPQueue;
   int counter;
   bool tellerAvailable;
   void fill(istream& is);
   void simulate();
};

bool operator<(const Event& first, const Event& second)
{
    return second.time < first.time;
}
/**
 * The usual main function
 */
int main(int argc, char** argv)
{
   EventList eventList;

   // command-line parameter munging
   // also fills the event list with the input data
   char* progname = argv[0];            // simplify msgs a bit
   switch (argc) {
   case 1:
      eventList.fill(cin);
      break;
   case 2: {
      ifstream ifs(argv[1]);
      if (!ifs) {
         cerr << progname << ": couldn't open " << argv[1] << endl;
         return 1;
      }
      eventList.fill(ifs);
      break;
   }
   default:
      cerr << "Usage: " << progname << " [datafile]\n";
      return 2;
   }

   eventList.simulate();
}

void EventList::fill(istream& is)
{
    int arrivalTime, processTime;
    int mostRecentTime = 0;
    counter = 0;
    while (is >> arrivalTime >> processTime)
    {
        counter++;
        Event occurrence(arrivalTime, processTime);
        if (mostRecentTime > occurrence.time)
        {
            cerr << "customer #" << counter << " out of order (time = "
                 << occurrence.time << ", previous time = " << mostRecentTime << ")" << endl;
            throw 3;
        }
        mostRecentTime = occurrence.time;
        eventListPQueue.push(occurrence);
    }

}

void EventList::simulate()
{
    queue<Event>bankQueue;
    int currentTime = 0;
    int departureTime = 0;
    int sumDepart = 0;
    int sumArrival = 0;
    int sumLength = 0;

    tellerAvailable = true;
    while (!eventListPQueue.empty())
    {
        Event action = eventListPQueue.top();
        currentTime = action.time;
        //arrival
        if (action.length >= 0)
        {
            eventListPQueue.pop();
            Event customer = action;
            //process arrival
            if (bankQueue.empty() && tellerAvailable)
            {
                departureTime = currentTime + customer.length;
                Event depart(departureTime, -1);
                eventListPQueue.push(depart);
                tellerAvailable = false;
            }
            else
                bankQueue.push(customer);
            cout << "Processing an arrival event at time:  " << customer.time << endl;
            sumArrival += customer.time;
            sumLength += customer.length;

        }
        //departure
        else
        {
            eventListPQueue.pop();
            //process departure
            if (!bankQueue.empty())
            {
                Event customer = bankQueue.front();
                bankQueue.pop();
                departureTime = currentTime + customer.length;
                Event depart(departureTime, -1);
                eventListPQueue.push(depart);
            }
            else
                tellerAvailable = true;
            cout << "Processing a departure event at time: " << currentTime << endl;
            sumDepart += currentTime;
        }

    }

    cout << "Final Statistics: " << endl;
    cout << "     Total Number of People Processed: " << counter << endl;
    double waitTime = (double)(sumDepart - sumLength - sumArrival)/counter;
    cout << "     Average amount of time spent waiting: " << waitTime << endl;

}
