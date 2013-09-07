//: C13:PlacementOperatorNew.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Placement with operator new()
#include <cstddef> // size_t
#include <iostream>
using namespace std;
 
class X
{
    int i;
public:
    X(int ii = 0) : i(ii) {
        cout << "this = " << this << endl;
    }
    ~X() {
        cout << "X::~X(): by delete " << this << endl;
    }
    void* operator new(size_t, void* loc) {
        return loc;
    }
    void operator delete (void*) {} // 因为分配在本地栈中这里不要做任何内存释放
};
 
int main()
{
    int l[10];
    cout << "l = " << l << endl;
    X* xp = new(l) X(47); // X at location l
// xp->X::~X(); // Explicit destructor call
    delete xp;
// ONLY use with placement!
} ///:~
/*
$ a.exe
l = 0x28ff04
this = 0x28ff04
X::~X(): by delete 0x28ff04
 
代码中的这行可以注释掉，不影响结果：void operator delete (void*) {} // 因为分配在本地栈中这里不要做任何内存释放
 
* */
