#include "map.hpp"
#include "vector.hpp"
#include <cstdio>
#include <map>
#include <sys/time.h>
#include <vector>

template <class MAP>
void cmp(const MAP &lhs, const MAP &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############" << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs)
			  << std::endl;
	std::cout << "lt: " << (lhs < rhs) << " | le: " << (lhs <= rhs)
			  << std::endl;
	std::cout << "gt: " << (lhs > rhs) << " | ge: " << (lhs >= rhs)
			  << std::endl;
}

int main(void)
{
	//	std::vector<int> v_std;
	//	v_std.reserve(10);
	//	for (int i = 0; i < 10; i++)
	//		v_std.push_back(i);
	//
	//	std::vector<int> *leak = new std::vector<int>;
	//	(void)leak;
	//	delete leak;
	//
	//	//  printf("%i", v_std[v_std[1]]);
	//
	//
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	std::cout << "------------ Map insertion tests";
	std::cout << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl;
	ft::map<int, std::string>           myFirstMap;
	ft::map<int, std::string>::iterator it = myFirstMap.begin();
	for (it = myFirstMap.begin(); it != myFirstMap.end(); it++)
		std::cout << it->second;
	std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < 52; i++)
		myFirstMap[i] = alphabet.substr(i, 1);
	myFirstMap.print_tree();
	myFirstMap.clear();
	std::srand((int)std::time(0));
	for (int i = 0; i < 10000; i++)
	{
		size_t idx = std::rand() % 52;
		myFirstMap[idx] = alphabet.substr(idx, 1);
	}
	myFirstMap.print_tree();

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
	//
	//	std::cout << std::endl;
	//	std::cout <<
	//"------------------------------------------------------------"; std::cout
	//<< std::endl; 	std::cout << "------------ Map removal test
	//------------------------------"; 	std::cout << std::endl; 	std::cout <<
	//"------------------------------------------------------------"; std::cout
	//<< std::endl; 	for (int i = 0; i < 100; i++)
	//	{
	//		myFirstMap.erase(i);
	//		int j = 0;
	//		for (it = myFirstMap.begin(); it != myFirstMap.end(); it++)
	//		{
	//			std::cout << it->second;
	//			j = 1;
	//		}
	//		if (j)
	//			std::cout << std::endl;
	//	}
	//	myFirstMap[0] = "A";
	//	myFirstMap[1] = "B";
	//	myFirstMap.print_tree();
	//
	//	std::cout << std::endl;
	//	std::cout <<
	//"------------------------------------------------------------"; std::cout
	//<< std::endl; 	std::cout << "------------ Map with string as keys tests
	//-----------------"; 	std::cout << std::endl; 	std::cout <<
	//"------------------------------------------------------------"; std::cout
	//<< std::endl; 	ft::map<std::string, bool> myStringMap;
	//	myStringMap["efficiency"];
	//	myStringMap["speech"];
	//	myStringMap["sister"];
	//	myStringMap["library"];
	//	myStringMap["activity"];
	//	myStringMap["quality"];
	//	myStringMap["hospital"];
	//	myStringMap["tongue"];
	//	myStringMap["coffee"];
	//	myStringMap["agency"];
	//	myStringMap["technology"];
	//	myStringMap["music"];
	//	myStringMap["environment"];
	//	myStringMap["dirt"];
	//	myStringMap["charity"];
	//	myStringMap["road"];
	//	myStringMap["administration"];
	//	myStringMap["attitude"];
	//	myStringMap["perception"];
	//	myStringMap["farmer"];
	//	myStringMap["language"];
	//	myStringMap["security"];
	//	myStringMap["reality"];
	//	myStringMap["affair"];
	//	myStringMap["instruction"];
	//	myStringMap["customer"];
	//	myStringMap["wealth"];
	//	myStringMap["meaning"];
	//	myStringMap["cabinet"];
	//	myStringMap["death"];
	//	myStringMap["appointment"];
	//	myStringMap["entry"];
	//	myStringMap["revenue"];
	//	myStringMap["pie"];
	//	myStringMap["effort"];
	//	myStringMap["village"];
	//	myStringMap["girlfriend"];
	//	myStringMap["emotion"];
	//	myStringMap["resource"];
	//	myStringMap["growth"];
	//	myStringMap["anxiety"];
	//	myStringMap["theory"];
	//	myStringMap["communication"];
	//	myStringMap["teacher"];
	//	myStringMap["cancer"];
	//	myStringMap["bonus"];
	//	myStringMap["marriage"];
	//	myStringMap["surgery"];
	//	myStringMap["assumption"];
	//	myStringMap["advertising"];
	//	myStringMap["tank"];
	//	myStringMap.print_tree();
	//
	//	std::cout << std::endl;
	//	std::cout <<
	//"------------------------------------------------------------"; std::cout
	//<< std::endl; 	std::cout << "------------ Map time tests
	//--------------------------------"; 	std::cout << std::endl; 	std::cout
	//<<
	//"------------------------------------------------------------"; std::cout
	//<< std::endl; 	timeval begin; 	timeval end; 	long    seconds; 	long
	// microseconds; 	long    elapsed; 	std::cout << "Time for 10 000 000
	// insertions, consultations, iterations and " 				 "deletions with ft:
	// "; 	gettimeofday(&begin, 0); 	ft::map<int, bool> myTimedMap_ft; 	for (int i
	//= 0; i < 1000000; i++) 		myTimedMap_ft[i]; 	for (int i = 0; i < 1000000; i++)
	//		myTimedMap_ft[i];
	//	for (ft::map<int, bool>::iterator iter = myTimedMap_ft.begin();
	//		 iter != myTimedMap_ft.end(); iter++)
	//	{
	//	}
	//	for (int i = 0; i < 1000000; i++)
	//		myTimedMap_ft.erase(i);
	//	gettimeofday(&end, 0);
	//	seconds = end.tv_sec - begin.tv_sec;
	//	microseconds = end.tv_usec - begin.tv_usec;
	//	elapsed = seconds/1e-6 + microseconds;
	//	std::cout << elapsed << "ms" << std::endl;
	//
	//	std::cout << "Time for 10 000 000 insertions, consultations, iterations
	//" 				 "and deletions with std: "; 	gettimeofday(&begin, 0);
	//std::map<int, bool> myTimedMap_std; 	for (int i = 0; i < 1000000; i++)
	// myTimedMap_std[i]; 	for (int i = 0; i < 1000000; i++)
	//myTimedMap_std[i]; 	for (std::map<int, bool>::iterator iter =
	// myTimedMap_std.begin(); 		 iter != myTimedMap_std.end(); iter++)
	//	{
	//	}
	//	for (int i = 0; i < 1000000; i++)
	//		myTimedMap_std.erase(i);
	//	gettimeofday(&end, 0);
	//	seconds = end.tv_sec - begin.tv_sec;
	//	microseconds = end.tv_usec - begin.tv_usec;
	//	elapsed = seconds/1e-6 + microseconds;
	//	std::cout << elapsed << "ms" << std::endl;

	//	ft::map<char, int> mp1;
	//	ft::map<char, int> mp2;
	//
	//	mp1['a'] = 2;
	//	mp1['b'] = 3;
	//	mp1['c'] = 4;
	//	mp1['d'] = 5;
	//	mp2['e'] = 6;
	//	mp2['f'] = 7;
	//	mp2['h'] = 8;
	//	mp2['h'] = 9;
	//
	//	ft::map<char, int>::iterator it;
	//	ft::map<char, int>::iterator it1 = mp1.begin();
	//	ft::map<char, int>::iterator it2 = mp2.begin();
	//	for (it = mp1.begin(); it != mp1.end(); it++)
	//		std::cout << it->second;
	//	std::cout << std::endl;
	//	for (it = mp2.begin(); it != mp2.end(); it++)
	//		std::cout << it->second;
	//	std::cout << std::endl;
	//	mp1.swap(mp2);
	//	ft::map<char, int>::iterator it1_ = mp1.begin();
	//	ft::map<char, int>::iterator it2_ = mp2.begin();
	//	for (it = mp1.begin(); it != mp1.end(); it++)
	//		std::cout << it->second;
	//	std::cout << std::endl;
	//	for (it = mp2.begin(); it != mp2.end(); it++)
	//		std::cout << it->second;
	//	std::cout << std::endl;
	//	mp1.swap(mp2);
	//
	//	ft::map<char, int>::reverse_iterator rit = mp1.rbegin();
	//	ft::map<char, int>::reverse_iterator rite = mp1.rend();
	//	while (rit != rite)
	//	{
	//		std::cout << "[rev] " << rit->second << std::endl;
	//		rit++;
	//	}
	//	std::cout << std::endl;
	//	(void)it1;
	//	(void)it2;
	//	(void)it1_;
	//	(void)it2_;
	//	return 0;
}