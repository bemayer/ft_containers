#include <iostream>

using namespace std;

struct Test {
    char * c;
    std::allocator<char> alloc;
    Test() {
        c = alloc.allocate(1);
        std::cout << "c address = " << static_cast<void*>(c) << std::endl;
    }
    
    void newAdr(){
        char * d = alloc.allocate(1);
        std::cout << "d address = " << static_cast<void*>(d) << std::endl;
    }
};

int main()
{
    std::allocator<Test> alloc;
    Test *test;
    
    test = alloc.allocate(1);
    alloc.construct(test);
    test->newAdr();
}
