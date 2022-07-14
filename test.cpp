#include "map.hpp"
#include "vector.hpp"
#include <cstdio>
#include <map>
#include <sys/time.h>
#include <vector>

#ifdef STD
#define VAR std
#else
#define VAR ft
#endif

int main(void)
{
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	std::cout
			<< "------------ Map insertion tests ----------------------------";
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	VAR::map<int, std::string> myFirstMap = VAR::map<int, std::string>();
	VAR::map<int, std::string>::iterator it = myFirstMap.begin();
	for (it = myFirstMap.begin(); it != myFirstMap.end(); it++)
		std::cout << it->second;
	std::string alphabet =
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::cout << "------------ Insertions in order ---------------------------";
	std::cout << std::endl;
	for (int i = 0; i < 52; i++)
		myFirstMap[i] = alphabet.substr(i, 1);
#ifdef DEBUG
	myFirstMap.print_tree();
#endif
	myFirstMap.clear();
	std::cout << "------------ Random insertions -----------------------------";
	std::cout << std::endl;
	std::srand((int)std::time(0));
	for (int i = 0; i < 10000; i++)
	{
		size_t idx = std::rand() % 52;
		myFirstMap[idx] = alphabet.substr(idx, 1);
	}
#ifdef DEBUG
	myFirstMap.print_tree();
#endif

	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	std::cout << "------------ Map iterator tests----------------------------";
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	it = myFirstMap.end();
	while (it != myFirstMap.begin())
	{
		it--;
		std::cout << it->second;
	}
	std::cout << std::endl;

	for (it = myFirstMap.begin(); it != myFirstMap.end(); it++)
	{
		std::cout << it->second;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	std::cout << "------------ Map removal test ------------------------------";
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
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
	std::cout << "------------ New insertions --------------------------------";
	std::cout << std::endl;
	myFirstMap[42] = "L";
	myFirstMap[-432434] = "H";
	myFirstMap[0] = "E";
	myFirstMap[345464536] = "O";
	myFirstMap[17] = "L";
#ifdef DEBUG
	myFirstMap.print_tree();
#endif

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	std::cout << "------------ Map with string as keys -----------------------";
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
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
	myStringMap.print_tree();
#endif

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	std::cout << "------------ Various methods test --------------------------";
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;

	std::cout << "Size: " << myStringMap.size() << std::endl;
	std::cout << "Max size: " << myStringMap.max_size() << std::endl;
	std::cout << "Count: " << myStringMap.count("count") << std::endl;
	std::cout << "Count: " << myStringMap.count("anxiety") << std::endl;
	std::cout << "Swaps: " << std::endl;
	myStringMap.swap(myStringMap);
	VAR::map<std::string, bool>::iterator lower =
			myStringMap.upper_bound("definition");
	std::cout << lower->first << " ";
	lower--;
	std::cout << lower->first << std::endl;
	myFirstMap.swap(mySecondMap);
	for (VAR::map<int, std::string>::const_iterator it = mySecondMap.begin();
		 it != mySecondMap.end(); it++)
	{
		std::cout << it->second;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	std::cout << "------------ Map time tests --------------------------------";
	std::cout << std::endl;
	std::cout << "------------ 1 000 000 insertions, consultations, ----------";
	std::cout << std::endl;
	std::cout << "------------ iterations, and deletions ---------------------";
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
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

	return 0;
}
