#include<iostream>

#include <string>

#include <list>

#include <vector>

#include <iterator>

#include <algorithm>


using namespace std;


struct LionDescription

{

   string name;

   int height;

};


struct LionSchedule

{

   string name;

   int enterTime;

   int exitTime;

};


class LionCompetition

{

   list<LionDescription> competition_lions;

   list<LionSchedule> competition_schedule;

   vector<int> showroom_lions_heights;


   public:

      //add enterTime sorting to the schedule???

      //add safety secure protection to the data input (at least time check)

      LionCompetition(list<LionDescription> lions, list<LionSchedule> schedule)

      {

         for (auto const& lion : lions)

            competition_lions.push_back(lion);


         for (auto const& lion_schedule : schedule)

            competition_schedule.push_back(lion_schedule);


         //copy(lions.rbegin(), lions.rend(), competition_lions);

         //copy(schedule.rbegin(), schedule.rend(), competition_schedule);

      }


      ~LionCompetition()

      {

         competition_lions.clear();

         competition_schedule.clear();

         showroom_lions_heights.clear();

      }


      void print_lions()

      {

         cout << "\nYour lions list below:" << endl;

         for (auto const& lion : competition_lions)

            cout << lion.name << " " << lion.height << endl;

         return;

      }


      void print_schedule()

      {

         cout << "\nYour lions schedule below:" << endl;

         for (auto const& lion : competition_schedule)

            cout << lion.name << " " << lion.enterTime << " " << lion.exitTime << endl;

         return;

      }


      void lionEntered(int currentTime, int lion_height)

      {

         showroom_lions_heights.push_back(lion_height);

         return;

      }


      void lionLeft(int currentTime, int height)

      {

         showroom_lions_heights.erase(remove(showroom_lions_heights.begin(), showroom_lions_heights.end(), height), showroom_lions_heights.end());


         return;

      }


      void print_showroom()

      {

         cout << "Lions in the showroom atm:" << endl;


         for (auto const& lion_height : showroom_lions_heights)

            cout << lion_height << endl;


         return;

      }


      list<string> getBiggestLions()

      {

         list<string> result;

         vector<int> lions_heights = showroom_lions_heights;


         int max_height = 0;

         int lion_counter = 0;

         bool flag = true;


         do

         {

            max_height = *max_element(lions_heights.begin(), lions_heights.end());


            for (auto const& our_lion : competition_lions)

            {

               if (our_lion.height == max_height)

               {

                  ++lion_counter;


                  result.push_back(our_lion.name);


                  lions_heights.erase(remove(lions_heights.begin(), lions_heights.end(), max_height), lions_heights.end());


                  break;

               }


               else

                  flag = false;

            }


         } while (flag);


         result.sort();


         cout << lion_counter << " ";


         for (auto const& lion_name : result)

            cout << lion_name << " ";


         cout << endl;


         return result;

      }

      //what about lions of the same height? need names of them in the schedule

      //or impose a constraint of all the heights being different (natural)

};


int main(void)

{

   string operation;


   list<LionDescription> descriptions;

   list<LionSchedule> schedule;


   do

   {

      cout << "\nYour operation: ";

      cin >> operation;


      if (operation == "description")

      {

         string name;

         int size;


         cin >> name >> size;

         descriptions.push_back({name, size});

      }


      if (operation == "schedule")

      {

         string name;

         int enterTime, exitTime;

         cin >> name >> enterTime >> exitTime;


         schedule.push_back({name, enterTime, exitTime});

      }


   } while (operation != "start");


   LionCompetition lion_competition(descriptions, schedule);

   //lion_competition.print_lions();

   //lion_competition.print_schedule();


   do

   {

      cout << "\nTime and operation: ";

      int currentTime;

      cin >> currentTime >> operation;


      if (operation == "enter")

      {

         int size;

         cin >> size;


         lion_competition.lionEntered(currentTime, size);

         lion_competition.print_showroom();

      }


      if (operation == "exit")

      {

         int size;

         cin >> size;


         lion_competition.lionLeft(currentTime, size);

         lion_competition.print_showroom();

      }


      if (operation == "inspect")

      {

         list<string> lions = lion_competition.getBiggestLions();

      }

   } while (operation != "end");


   return 0;

}

//----------------------------------------------------------------------------------------
/*
Sample Input:

definition marry 300
definition rob 250
schedule marry 10 15
schedule rob 13 20
start
8 enter 200
10 enter 310
10 enter 300
11 inspect    // we compare our lion (marry) with others; return empty list since there is bigger
13 enter 250
13 exit 310
13 inspect    // both marry and rob are bigger than 200cm-lion, return a list [marry, rob]
15 exit 300
16 inspect    // marry left, so there is only rob which is the biggest
16 exit 200
20 exit 250
21 end


Sample Output:

0
2 marry rob
1 rob
*/