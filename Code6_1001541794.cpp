//Samuel Adegoke
//ID 1001541794
#include "TrickOrTreater.h"
#include "House.h"
#include "CandyHouse.h"
#include "ToothbrushHouse.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <map>
#include <chrono>
#include <thread>
#include <vector>
#include <iomanip>
#include <sstream>
#include <new>
#include <mutex>
using namespace std;


void get_command_line_params (int argc, char *argv[], string &File1, string &File2, string &File3)
{
    if (argc == 4)
    {
       File1 = argv[1];
       File2 = argv[2];
       File3 = argv[3];
    }
    else 
    {
        throw "invalid_argument";
    }
}

int main (int argc, char *argv[])
{
	string file1; //TOT.txt
    string file2; //HOUSE.txt
    string file3; //CANDY.txt
    string CandyFromFile; //grabbing the candy from the file
    vector <string> Candies;
    vector <int> Ranks;
    srand((int)time(0)); //Randomizing the speed every time the program is ran
    ostringstream houseNames;
    try
    {
        get_command_line_params (argc, argv, file1, file2, file3);
    }
    catch (const char *message)
    {
        cout<< "Missing command line parameters–-Usage : input^filename output^filename" << message << endl;
        exit(0);
    }
    map<int, string> sortingCandy; //storing the names of the candy and the rank in a map
    ifstream CandyFile{file3};
    ifstream HouseFile{file2};
    ifstream TOTFile{file1};
    if(CandyFile.is_open()) //opening the candy file
    {
    	while(getline(CandyFile, CandyFromFile))
    	{
    		string FinalCandy = strtok(&CandyFromFile[0], "|"); //reading in the candy from the file
    		int CandyRanking = atoi(strtok(NULL, "|")); //Turning the candy ranks into integers
    		// Candies.push_back(FinalCandy);
    		// Ranks.push_back(CandyRanking);
    		sortingCandy.insert(make_pair(CandyRanking, FinalCandy)); //passing everything into a map
    	}
        CandyFile.close();
    }
    else
    {
        cout << "File could not open" << endl;
        exit(0);
    }


    for (auto printingMap : sortingCandy) // printing out the contents of the map
    {
    	cout << printingMap.first << " " << printingMap.second << endl;
    }

    vector <House*> vecOfHouses; //Vector of pointers to put new house objects in the vector
    if(HouseFile.is_open())
    {
    	string HousesFromFile;
        houseNames << "          ";
    	while(getline(HouseFile, HousesFromFile))
    	{
            int RANDOMNUMBER = (rand() % 2 + 1);
            if (RANDOMNUMBER == 1)
            {
                vecOfHouses.push_back(new ToothbrushHouse(HousesFromFile, sortingCandy));
            }
            else
            {
                vecOfHouses.push_back(new CandyHouse(HousesFromFile, sortingCandy));  //declaring new objects for the house
            }
            houseNames << left << setw(11) << HousesFromFile; //putting each house into an ostringstream to output at the end
    	}
        HouseFile.close();
    }
    else 
    {
        cout << "File could not open" << endl;
        exit(0);
    }

    cout << "\n\n\n\n" << endl;

    vector<TrickOrTreater> vecOfNames;
    string namesOfTOTs;
    if(TOTFile.is_open())
    {
    	while(getline(TOTFile, namesOfTOTs))
    	{
    		vecOfNames.push_back(TrickOrTreater{namesOfTOTs, vecOfHouses}); //pushing all the trick or treater names into a file
    	}
    	TOTFile.close();
    }
    else
    {
        cout << "File could not open" << endl;
        exit(0);
    }

    for(auto &it: vecOfNames) 
    {
    	it.startThread();  //starting the thread
    }

    while (TrickOrTreater::ImDone != vecOfNames.size())
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        cout << houseNames.str() << endl;  //printing put the houses to know which kids are at which house

        for(auto &names: vecOfNames)
        {
           cout << names.getPath() << names.getName() << endl; //accessing the path and TOT names from the TrickOrTreater.cpp
        }
        this_thread::sleep_for(chrono::milliseconds(5)); // sleeping the thread for 5 milliseconds before refreshing the screen
        
    }


    for(auto &it: vecOfNames)
    {
        it.joinThread(); //Links the threads together
    }


    for (auto& it : vecOfNames)
    {
        cout << it.getName() << "'s" << " " << it << " " << endl; //overloaded operator to print out the kid's buckets
    }

    for (auto& it : vecOfHouses)
    {
        delete it;
    }

}
