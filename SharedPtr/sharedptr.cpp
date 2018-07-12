#include <memory>
#include<iostream>


    class Foo {

public:

    int* valFoo;
    float f;

    Foo(): valFoo(nullptr) {};
    Foo(float val): valFoo(nullptr), f(val)  {};

    ~Foo()
    {
        if (valFoo != nullptr)
        {
                std::cout<<"Obj successfully destroyed: deleting valFoo"<<std::endl;
                delete valFoo;
        }
        else
        {
                std::cout<<"Obj successfully destroyed: no members are deinit"<<std::endl;
        }
    }

};


int main()
{
    std::shared_ptr<int> integral;

    std::cout<<"\nUC0 - Init and reset pointers:"<<std::endl;

    std::shared_ptr<int> test(new int(4));

    std::cout<<"Is default value of shared_ptr just a nullptr? "<<(integral==nullptr? "true":"false")<<std::endl;
    std::cout<<"Init value of test is: "<<*test<<" reference number is "<<test.use_count()<<std::endl;
    test= std::make_shared<int>(8);
    std::cout<<"Changed value of test with make_shared is: "<<*test<<" reference number is "<<test.use_count()<<std::endl;
    test.reset(new int(12));
    std::cout<<"Changed value of test with reset is: "<<*test<<" reference number is "<<test.use_count()<<std::endl;

    std::shared_ptr<Foo> test1;
    test1=std::make_shared<Foo>(Foo(.9f));
    std::cout<<"Float value of test1->f is: "<<test1->f<<std::endl;
    test1.reset();



    std::cout<<"\nUC1 - alias constructor out of scope:"<<std::endl;
    std::shared_ptr<int> integral2;
    {

      std::shared_ptr<Foo> foo;
      std::cout<<"Reference to Foo before object creation are: "<<foo.use_count()<<std::endl;
      foo = std::shared_ptr<Foo>(new Foo());
      std::cout<<"Reference to Foo before aliasing are: "<<foo.use_count()<<std::endl;

      //Trying an unrelated naked pointer
      integral = std::shared_ptr<int>(foo, new int(4));
      std::cout<<"Reference to Foo after aliasing are: "<<foo.use_count()<<std::endl;

      std::shared_ptr<Foo> foo2;
      foo2 = std::shared_ptr<Foo>(new Foo());
      foo2->valFoo = new int(8);
      //Trying to keep the member value alive, we can use any value to keep alive, it hasn't to be compatible with the obj we wish to keep alive
      integral2 = std::shared_ptr<int>(foo2, foo2->valFoo);
      std::cout<<"Value of foo2 in scope and because of the alias constructor can be called using integral2, it is: "<<*integral2<<", num references is: "<< integral2.use_count()<<std::endl;

      std::cout<<"Value of foo2 used with alias constructor in scope and before reset has num references: "<< foo2.use_count()<<std::endl;

      foo2.reset();

      std::cout<<"Value of foo2 used with alias constructor in scope and after reset has num references: "<< foo2.use_count()<<std::endl;

    }

    std::cout<<"Value of Foo2 out of scope but because of the alias constructor is still preserved in integral2 and is: "<<*integral2<<", num references is: "<< integral2.use_count()<<std::endl;
    std::cout << "Value of integral is still valid because is not out of scope and is: " << *integral<<", num references is: "<< integral.use_count()<<std::endl;

    std::cout<<"\nUC2 - fetching naked/raw pointer:"<<std::endl;

    /*In this case the variable must be deallocated because data is not stored inside the integral object but just referred, obviously it can't be referred anymore */
    std::cout<<"Address of integral pointer before deleting it is: "<<integral.get()<< " from here on avoid to refer to it to avoid undefined behaviour"<<std::endl;
    delete integral.get();

    //Undefined behaviour, it doesn't cause SEG_FAULT, we have a dandling pointer here
    //std::cout<<"Value of integral after deletion is: "<<*integral<<std::endl;

    std::cout << "Num references of integral after removing naked pointer and before calling reset still is: "<< integral.use_count()<<std::endl;

    integral.reset();

    std::cout << "Num references of integral after removing naked pointer and after calling reset is: "<< integral.use_count()<<std::endl;

    return 0;
}
