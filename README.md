TICPP_PlacementOperatorNew
==========================

TICPP: C13:PlacementOperatorNew.cpp

Reference:
http://zhidao.baidu.com/question/385106392.html?fr=fd
http://www.cnblogs.com/younes/archive/2010/04/26/1721528.html
 
这个实际上是new操作符重载，这个new 的实现不从堆里分配内存，而是从第2个参数得到内存地址（就是在本地栈分配了int [10]的地址
l），然后返回这个地址，其实这是new操作符重载常用的手法，就是改变new缺省的内存分配方式，但这里有个问题，它没有重载delete
操作，因此，如果用 delete xp, 程序会崩溃, 因此，程序中直接用了析构。重载delete 操作可如下写：
void operator delete (void*) { } // 因为分配在本地栈中这里不要做任何内存释放
有了这个重载，你可以用delete xp ; 取代 xp->X::~X(); ，这样更符合C++的编程习惯，也不容易出错。
 
至于placement new，只是operator new的一个重载的版本，只是我们很少用到它。如果你想在已经分配的内存中创建一个对象，
使用new时行不通的。也就是说placement new允许你在一个已经分配好的内存中（栈或者堆中）构造一个新的对象。
 
我们知道使用new操作符分配内存需要在堆中查找足够大的剩余空间，这个操作速度是很慢的，而且有可能出现无法分配内存的
异常（空间不够）。placement new就可以解决这个问题。我们构造对象都是在一个预先准备好了的内存缓冲区中进行，不需要
查找内存，内存分配的时间是常数。而且不会出现在程序运行中途出现内存不足的异常。所以，placement new非常适合那些
对时间要求比较高，长时间运行不希望被打断的应用程序。
 
1. 缓冲区提前分配，可以使用堆的空间，也可以使用栈的空间。所以分配方式有如下两种：
class MyClass {…};
char *buf=new char[N*sizeof(MyClass)+sizeof(int)];
char buf[N*sizeof(MyClass)+sizeof(int)];
 
2. 对象的构造
MyClass * pClass=new(buf) MyClass; //使用placement new
 
3. 对象的销毁
一旦这个对象使用完毕，你必须显式的调用类的析构函数进行销毁对象。但此时内存空间不会被释放，以便其他的对象的构造。
 
4. 内存的释放
如果缓冲区在堆中，那么调用delete[] buf 进行内存的释放。如果在栈中，那么在其作用域内有效，跳出作用域，内存自动释放。 
