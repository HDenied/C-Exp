/* The order of member initializers in the list is irrelevant: the actual order of initialization is as follows:

1) If the constructor is for the most-derived class, virtual base classes are initialized in the order in which they appear in depth-first left-to-right traversal of the base class declarations (left-to-right refers to the appearance in base-specifier lists)
2) Then, direct base classes are initialized in left-to-right order as they appear in this class's base-specifier list
3) Then, non-static data members are initialized in order of declaration in the class definition.
4) Finally, the body of the constructor is executed

(Note: if initialization order was controlled by the appearance in the member initializer lists of different constructors, then the destructor wouldn't be able to ensure that the order of destruction is the reverse of the order of construction) */

#include<iostream>

using namespace std;

class D
{
public:
	D()
	{
		cout<<"Calling  D constructor"<<endl;
	}

	~D()
	{
		cout<<"Calling D destructor"<<endl;
	}


};

class C
{
public:
	C()
	{
		cout<<"Calling virtual C constructor"<<endl;
	}

	~C()
	{
		cout<<"Calling virtual C destructor"<<endl;
	}


};



class A: public D, virtual public C
{
private:
	int valC;
	int valB;
	int valA;

public:
	A(): D(), valA(valB), C(), valB(7)
	{
		valC=valA;
		cout<<"Value of valC="<<valC<<endl;
		cout<<"Value of valA="<<valA<<endl;
		cout<<"Calling A constructor"<<endl;
	}

	~A()
	{
		cout<<"Calling A destructor"<<endl;
	}


};

class B {

public:

	B()
	{
		cout<<"Calling B constructor"<<endl;
	}
	~B()
	{
		cout<<"Calling B destructor"<<endl;
	}


};



int main()
{
	B b;
	A a;

    return 0;
}
