#include <cstdlib>
#ifdef STD
#define VAR std
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#else
#define VAR ft
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#ifdef BONUS
#include "set.hpp"
#endif
#endif

int main(int ac, char **av)
{
	int seed = 42;
	if (ac == 2)
		seed = atoi(av[1]);
	std::srand(seed);

	{
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Vector insertion tests --------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		VAR::vector<int>           myFirstVector;
		VAR::vector<int>::iterator it = myFirstVector.begin();
		for (it = myFirstVector.begin(); it != myFirstVector.end(); it++)
			std::cout << *it;
		std::cout << std::endl;
		for (int i = 0; i < 10; i++)
			myFirstVector.push_back(std::rand() % 2000 - 1000);

		VAR::vector<int> mySecondVector(myFirstVector.begin() + 4,
										myFirstVector.end() - 3);
		mySecondVector.insert(mySecondVector.begin(), 3, 1);
		mySecondVector.insert(mySecondVector.begin() + 3,
							  myFirstVector.end() - 1, myFirstVector.end());
		std::cout << "First vector ";
		std::cout << std::endl;
		for (it = myFirstVector.begin(); it != myFirstVector.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Second vector with 3 '1', the last element and the 3";
		std::cout << std::endl;
		std::cout << "mid elements  of the first vector";
		std::cout << std::endl;
		for (it = mySecondVector.begin(); it != mySecondVector.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Vector iterator tests----------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		for (it = myFirstVector.begin(); it != myFirstVector.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		it = myFirstVector.end();
		while (it != myFirstVector.begin())
			std::cout << *(--it) << " ";
		std::cout << std::endl;
		VAR::vector<int>::const_iterator cit = myFirstVector.begin();
		VAR::vector<int>::iterator       ite = myFirstVector.end();
		while (cit != ite)
			std::cout << *(cit++) << " ";
		std::cout << std::endl;
		VAR::vector<int>::reverse_iterator rcit = myFirstVector.rbegin();
		VAR::vector<int>::reverse_iterator rcite = myFirstVector.rend();
		while (rcit != rcite)
			std::cout << *(rcit++) << " ";
		std::cout << std::endl;
		VAR::vector<int>::iterator cite = myFirstVector.end();
		it = myFirstVector.begin();
		while (it != cite)
			std::cout << *it++ << " ";
		std::cout << std::endl;
		int i = myFirstVector.size();
		while (i)
			std::cout << myFirstVector[--i] << " ";

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Vector removal test -----------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Remove the second element";
		std::cout << std::endl;
		myFirstVector.erase(myFirstVector.begin() + 1);
		for (it = myFirstVector.begin(); it != myFirstVector.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << " Remove all the elements from the third to the 7th and";
		std::cout << std::endl;
		std::cout << "iterate from the last deleted one";
		std::cout << std::endl;
		cit = myFirstVector.erase(myFirstVector.begin() + 2,
								  myFirstVector.begin() + 7);
		while (cit != myFirstVector.end())
			std::cout << *cit++ << " ";
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Show all the remaining elements";
		std::cout << std::endl;
		for (it = myFirstVector.begin(); it != myFirstVector.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Delete everything";
		std::cout << std::endl;
		std::cout << "Size of the vector : " << myFirstVector.size()
				  << std::endl;
		myFirstVector.clear();
		std::cout << "Size of the vector : " << myFirstVector.size()
				  << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Various methods test ----------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "Size: " << mySecondVector.size() << std::endl;
		std::cout << "Max size: " << mySecondVector.max_size() << std::endl;
		std::cout << "Last element: " << mySecondVector.back() << std::endl;
		mySecondVector.pop_back();
		std::cout << "Last element after pop back: " << mySecondVector.back()
				  << std::endl;
		std::cout << "Capacity: " << mySecondVector.capacity() << std::endl;
		mySecondVector.reserve(seed);
		std::cout << "Capacity after reserve: " << mySecondVector.capacity()
				  << std::endl;
		std::cout << "Swaps: ";
		myFirstVector.swap(mySecondVector);
		for (it = myFirstVector.begin(); it != myFirstVector.end(); it++)
			std::cout << *it << " ";

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Vector time tests -------------------------";
		std::cout << std::endl;
		std::cout << "------------ 1 000 000 insertions, consultations, ------";
		std::cout << std::endl;
		std::cout << "------------ iterations, and deletions -----------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::vector<int> myTimedVector;
		std::cout << "Vector size: " << myTimedVector.size() << std::endl;
		for (int i = 0; i < 1000000; i++)
			myTimedVector.push_back(i);
		for (int i = 0; i < 1000; i++) {
			myTimedVector.insert(myTimedVector.begin() + (std::rand()
				% 1000000), std::rand() % 1000, std::rand() % 100);
		}
		std::cout << "Vector size: " << myTimedVector.size() << std::endl;
		for (int i = 0; i < 1001000; i++)
			myTimedVector[i];
		for (VAR::vector<int>::iterator iter = myTimedVector.begin();
			 iter != myTimedVector.end(); iter++)
		{
		}
		int s = myTimedVector.size();
		for (int i = 0; i < s; i++)
			myTimedVector.pop_back();
		std::cout << "Vector size: " << myTimedVector.size() << std::endl;
	}

	{
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Map insertion tests -----------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::map<int, std::string> myFirstMap = VAR::map<int, std::string>();
		VAR::map<int, std::string>::iterator it = myFirstMap.begin();
		for (it = myFirstMap.begin(); it != myFirstMap.end(); it++)
			std::cout << it->second;
		std::string alphabet =
				"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::cout << "Insertions in order" << std::endl;
		for (int i = 0; i < 52; i++)
			myFirstMap[i] = alphabet.substr(i, 1);
#ifdef DEBUG
		std::cout << std::endl;
		myFirstMap.print_tree();
#endif
		myFirstMap.clear();
		std::cout << std::endl;
		std::cout << "Random insertions";
		std::cout << std::endl;
		for (int i = 0; i < 10000; i++)
		{
			int idx = std::rand() % 52;
			myFirstMap[idx] = alphabet.substr(idx, 1);
		}
#ifdef DEBUG
		std::cout << std::endl;
		myFirstMap.print_tree();
#endif

		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Map iterator tests-------------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		it = myFirstMap.end();
		while (it != myFirstMap.begin())
			std::cout << (--it)->second;
		std::cout << std::endl;
		for (it = myFirstMap.begin(); it != myFirstMap.end(); it++)
			std::cout << it->second;
		std::cout << std::endl;
		VAR::map<int, std::string>::const_iterator cit = myFirstMap.begin();
		VAR::map<int, std::string>::iterator       ite = myFirstMap.end();
		while (cit != ite)
			std::cout << (cit++)->second;
		std::cout << std::endl;
		VAR::map<int, std::string>::reverse_iterator rcit = myFirstMap.rbegin();
		VAR::map<int, std::string>::reverse_iterator rcite = myFirstMap.rend();
		while (rcit != rcite)
			std::cout << (rcit++)->second;
		std::cout << std::endl;
		VAR::map<int, std::string>::iterator cite = myFirstMap.end();
		it = myFirstMap.find(26);
		while (it != cite)
			std::cout << (it++)->second;
		std::cout << std::endl;

		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Map removal test --------------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::map<int, std::string> mySecondMap(myFirstMap.begin(),
											   myFirstMap.end());
		for (int i = 0; i < 100; i++)
		{
			myFirstMap.erase(i);
			int j = 0;
			for (it = myFirstMap.begin(); it != myFirstMap.end(); it++)
			{
				std::cout << it->second;
				j = 1;
			}
			if (j)
				std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "New insertions";
		std::cout << std::endl;
		myFirstMap[42] = "L";
		myFirstMap[-432434] = "H";
		myFirstMap[0] = "E";
		myFirstMap[345464536] = "O";
		myFirstMap[17] = "L";
#ifdef DEBUG
		std::cout << std::endl;
		myFirstMap.print_tree();
#endif
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Map with strings as keys ------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::map<std::string, bool> myStringMap;
		myStringMap["efficiency"];
		myStringMap["speech"];
		myStringMap["sister"];
		myStringMap["library"];
		myStringMap["activity"];
		myStringMap["quality"];
		myStringMap["hospital"];
		myStringMap["tongue"];
		myStringMap["coffee"];
		myStringMap["agency"];
		myStringMap["technology"];
		myStringMap["music"];
		myStringMap["environment"];
		myStringMap["dirt"];
		myStringMap["charity"];
		myStringMap["road"];
		myStringMap["administration"];
		myStringMap["attitude"];
		myStringMap["perception"];
		myStringMap["farmer"];
		myStringMap["language"];
		myStringMap["security"];
		myStringMap["reality"];
		myStringMap["affair"];
		myStringMap["instruction"];
		myStringMap["customer"];
		myStringMap["wealth"];
		myStringMap["meaning"];
		myStringMap["cabinet"];
		myStringMap["death"];
		myStringMap["appointment"];
		myStringMap["entry"];
		myStringMap["revenue"];
		myStringMap["pie"];
		myStringMap["effort"];
		myStringMap["village"];
		myStringMap["girlfriend"];
		myStringMap["emotion"];
		myStringMap["resource"];
		myStringMap["growth"];
		myStringMap["anxiety"];
		myStringMap["theory"];
		myStringMap["communication"];
		myStringMap["teacher"];
		myStringMap["cancer"];
		myStringMap["bonus"];
		myStringMap["marriage"];
		myStringMap["surgery"];
		myStringMap["assumption"];
		myStringMap["advertising"];
		myStringMap["tank"];
#ifdef DEBUG
		std::cout << std::endl;
		myStringMap.print_tree();
#endif

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Various methods test ----------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Size: " << myStringMap.size() << std::endl;
		std::cout << "Max size: " << myStringMap.max_size() << std::endl;
		std::cout << "Count: " << myStringMap.count("count") << std::endl;
		std::cout << "Count: " << myStringMap.count("anxiety") << std::endl;
		std::cout << "Lower bound: ";
		VAR::map<std::string, bool>::iterator lower =
				myStringMap.lower_bound("music");
		std::cout << lower->first << " ";
		lower++;
		std::cout << lower->first << std::endl;
		std::cout << "Upper bound: ";
		VAR::map<std::string, bool>::iterator upper =
				myStringMap.upper_bound("music");
		std::cout << upper->first << " ";
		upper--;
		std::cout << upper->first << std::endl;
		std::cout << "Swaps: ";
		myStringMap.swap(myStringMap);
		myFirstMap.swap(mySecondMap);
		for (VAR::map<int, std::string>::const_iterator it2 =
					 mySecondMap.begin();
			 it2 != mySecondMap.end(); it2++)
		{
			std::cout << it2->second;
		}

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Map time tests ----------------------------";
		std::cout << std::endl;
		std::cout << "------------ 1 000 000 insertions, consultations, ------";
		std::cout << std::endl;
		std::cout << "------------ iterations, and deletions -----------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::map<int, bool> myTimedMap;
		std::cout << "Map size: " << myTimedMap.size() << std::endl;
		for (int i = 0; i < 1000000; i++)
			myTimedMap[i];
		std::cout << "Map size: " << myTimedMap.size() << std::endl;
		for (int i = 0; i < 1000000; i++)
			myTimedMap[i];
		for (VAR::map<int, bool>::iterator iter = myTimedMap.begin();
			 iter != myTimedMap.end(); iter++)
		{
		}
		for (int i = 0; i < 1000000; i++)
			myTimedMap.erase(i);
		std::cout << "Map size: " << myTimedMap.size() << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Stack tests -------------------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::stack<int> myFirstStack;
		for (int i = 0; i < 10; i++)
			myFirstStack.push(std::rand() % 2000 - 1000);
		std::cout << "Size: " << myFirstStack.size() << std::endl;
		std::cout << "Empty: " << myFirstStack.empty() << std::endl;
		std::cout << "Content: ";
		for (int i = 0; i < 10; i++){
			std::cout << myFirstStack.top() << " ";
			myFirstStack.pop();
		}
		std::cout << std::endl;
		std::cout << "Size :" << myFirstStack.size() << std::endl;
		std::cout << "Empty :" << myFirstStack.empty() << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Stack time tests --------------------------";
		std::cout << std::endl;
		std::cout << "------------ 1 000 000 insertions and deletions --------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::stack<int> myTimedStack;
		std::cout << "Stack size: " << myTimedStack.size() << std::endl;
		for (int i = 0; i < 1000000; i++)
			myTimedStack.push(i);
		std::cout << "Stack size: " << myTimedStack.size() << std::endl;
		for (int i = 0; i < 1000000; i++)
			myTimedStack.pop();
		std::cout << "Stack size: " << myTimedStack.size() << std::endl;
		std::cout << std::endl;
	}

#ifdef BONUS
	{
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout
				<< "------------ Set insertion tests -------------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::set<int>           myFirstSet = VAR::set<int>();
		VAR::set<int>::iterator it = myFirstSet.begin();
		for (it = myFirstSet.begin(); it != myFirstSet.end(); it++)
			std::cout << *it;
		std::cout << "Insertions in order";
		std::cout << std::endl;
		for (int i = 0; i < 100; i++)
			myFirstSet.insert(i);
#ifdef DEBUG
		std::cout << std::endl;
		myFirstSet.print_tree();
#endif
		std::cout << std::endl;
		std::cout << "Random insertions";
		std::cout << std::endl;
		VAR::set<int> mySecondSet = VAR::set<int>();
		for (int i = 0; i < 15; i++)
			mySecondSet.insert((std::rand() % 200) - 100);
#ifdef DEBUG
		std::cout << std::endl;
		mySecondSet.print_tree();
		mySecondSet.print_tree();
#endif

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Set iterator tests-------------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		for (it = mySecondSet.begin(); it != mySecondSet.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		it = mySecondSet.end();
		while (it != mySecondSet.begin())
			std::cout << *--it << " ";
		std::cout << std::endl;
		VAR::set<int>::const_iterator cit = mySecondSet.begin();
		VAR::set<int>::iterator       ite = mySecondSet.end();
		while (cit != ite)
			std::cout << *cit++ << " ";
		std::cout << std::endl;
		VAR::set<int>::reverse_iterator rcit = mySecondSet.rbegin();
		VAR::set<int>::reverse_iterator rcite = mySecondSet.rend();
		while (rcit != rcite)
			std::cout << *rcit++ << " ";
		std::cout << std::endl;
		VAR::set<int>::iterator cite = mySecondSet.end();
		VAR::pair<VAR::set<int>::iterator, bool> pos = mySecondSet.insert(42);
		while (pos.first != cite)
			std::cout << *pos.first++ << " ";
		std::cout << std::endl;
		it = mySecondSet.find(42);
		while (it != cite)
			std::cout << *it++ << " ";

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Set removal test --------------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "First set size: " << myFirstSet.size() << std::endl;
		myFirstSet.clear();
		std::cout << "First set size: " << myFirstSet.size() << std::endl;
		std::cout << "Second set size: " << mySecondSet.size() << std::endl;
		for (int i = -1000; i < 1000; i++)
			mySecondSet.erase(i);
		std::cout << "Second set size: " << mySecondSet.size() << std::endl;
		std::cout << std::endl;
		std::cout << "New insertions";
		std::cout << std::endl;
		std::cout << std::endl;
		myFirstSet.insert(1);
		myFirstSet.insert(2);
		myFirstSet.insert(3);
		myFirstSet.insert(4);
#ifdef DEBUG
		std::cout << std::endl;
		myFirstSet.print_tree();
#endif
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Set with strings as keys ------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		VAR::set<std::string> myStringSet;
		myStringSet.insert("efficiency");
		myStringSet.insert("speech");
		myStringSet.insert("sister");
		myStringSet.insert("library");
		myStringSet.insert("activity");
		myStringSet.insert("quality");
		myStringSet.insert("hospital");
		myStringSet.insert("tongue");
		myStringSet.insert("coffee");
		myStringSet.insert("agency");
		myStringSet.insert("technology");
		myStringSet.insert("music");
		myStringSet.insert("environment");
		myStringSet.insert("dirt");
		myStringSet.insert("charity");
		myStringSet.insert("road");
		myStringSet.insert("administration");
		myStringSet.insert("attitude");
		myStringSet.insert("perception");
		myStringSet.insert("farmer");
		myStringSet.insert("language");
		myStringSet.insert("security");
		myStringSet.insert("reality");
		myStringSet.insert("affair");
		myStringSet.insert("instruction");
		myStringSet.insert("customer");
		myStringSet.insert("wealth");
		myStringSet.insert("meaning");
		myStringSet.insert("cabinet");
		myStringSet.insert("death");
		myStringSet.insert("appointment");
		myStringSet.insert("entry");
		myStringSet.insert("revenue");
		myStringSet.insert("pie");
		myStringSet.insert("effort");
		myStringSet.insert("village");
		myStringSet.insert("girlfriend");
		myStringSet.insert("emotion");
		myStringSet.insert("resource");
		myStringSet.insert("growth");
		myStringSet.insert("anxiety");
		myStringSet.insert("theory");
		myStringSet.insert("communication");
		myStringSet.insert("teacher");
		myStringSet.insert("cancer");
		myStringSet.insert("bonus");
		myStringSet.insert("marriage");
		myStringSet.insert("surgery");
		myStringSet.insert("assumption");
		myStringSet.insert("advertising");
		myStringSet.insert("tank");
#ifdef DEBUG
		std::cout << std::endl;
		myStringSet.print_tree();
#endif

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Various methods test ----------------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << "Size: " << myStringSet.size() << std::endl;
		std::cout << "Max size: " << myStringSet.max_size() << std::endl;
		std::cout << "Count: " << myStringSet.count("count") << std::endl;
		std::cout << "Count: " << myStringSet.count("anxiety") << std::endl;
		std::cout << "Lower bound: ";
		VAR::set<std::string>::iterator lower =
				myStringSet.lower_bound("music");
		std::cout << *lower << " ";
		lower++;
		std::cout << *lower << std::endl;
		std::cout << "Upper bound: ";
		VAR::set<std::string>::iterator upper =
				myStringSet.upper_bound("music");
		std::cout << *upper << " ";
		upper--;
		std::cout << *upper << std::endl;
		std::cout << "Swaps: ";
		mySecondSet.swap(myFirstSet);
		for (VAR::set<int>::const_iterator it = mySecondSet.begin();
			 it != mySecondSet.end(); it++)
			std::cout << *it << " ";

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << "------------ Set time tests ----------------------------";
		std::cout << std::endl;
		std::cout << "------------ 1 000 000 insertions, consultations, ------";
		std::cout << std::endl;
		std::cout << "------------ iterations, and deletions -----------------";
		std::cout << std::endl;
		std::cout << "--------------------------------------------------------";
		std::cout << std::endl;
		std::cout << std::endl;
		VAR::set<int> myTimedSet;
		std::cout << "Set size: " << myTimedSet.size() << std::endl;
		for (int i = 0; i < 1000000; i++)
			myTimedSet.insert(i);
		std::cout << "Set size: " << myTimedSet.size() << std::endl;
		for (int i = 0; i < 1000000; i++)
			myTimedSet.find(i);
		for (VAR::set<int>::iterator iter = myTimedSet.begin();
			 iter != myTimedSet.end(); iter++)
		{
		}
		for (int i = 0; i < 1000000; i++)
			myTimedSet.erase(i);
		std::cout << "Set size: " << myTimedSet.size() << std::endl;
		std::cout << std::endl;
	}
#endif
	return 0;
}
