#include<iostream>
#include<memory>

using namespace std;


class Nodo;

void print(weak_ptr<Nodo> ptr)
{
	cout<<"\nNumber of references shared pointer inside a function are: "<<ptr.use_count()<<endl;
}

class Nodo {

public:
        Nodo(uint32_t val): m_val(val)
        {
            cout<<"\nCreated node"<<node_ctr<<" with value "<<m_val<<endl;
            m_ctr=node_ctr++;
        }

        ~Nodo()
        {
            cout<<"\nDestroyed node"<<m_ctr<<" with value "<<m_val<<endl;

        }


private:

        static uint32_t node_ctr;
        uint32_t m_val;
        uint32_t m_ctr;

        Nodo(){};

public:
        shared_ptr<Nodo> shared_prv;
        shared_ptr<Nodo> shared_nxt;

        weak_ptr<Nodo> weak_prv;
        weak_ptr<Nodo> weak_nxt;
	uint32_t getVal() {return m_val;}
        static void init() {Nodo::node_ctr=0;}
        static uint32_t getGlobCtr() {return Nodo::node_ctr;}

};

uint32_t Nodo::node_ctr;

int main()
{
	shared_ptr<Nodo> nd1Shared, nd2Shared;
	weak_ptr<Nodo> nd1Weaked, nd2Weaked;
        uint32_t uc_count = 0;
        {
                cout<<"Static variable default value is: "<<Nodo::getGlobCtr()<<endl;
                Nodo testNode=Nodo(12);
                cout<<"Default value of shared pointer is nullptr: "<<(testNode.shared_prv==nullptr? "true":"false")<<endl;
        }

        Nodo::init();

        cout<<"\n==========UC"<<uc_count<<":"<<" reset shared_ptr and keeping nd1Weaked and nd2Weaked=========="<<endl;

	nd1Shared=make_shared<Nodo>(1);
	nd1Weaked = nd1Shared;
	nd2Weaked = nd1Shared;
	cout<<"\nReference to nd1Shared before resetting it are: "<<nd1Weaked.use_count()<<endl;
	nd1Shared.reset();

	/****************************** The following command just reset a temporary instance not the referred shared ptr *******************************************/
	//nd1Weaked.lock().reset();

	cout<<"\nReference to nd1Shared via nd1Weaked after reset nd1Shared are: "<<nd1Weaked.use_count()<<" expired? "<<(nd1Weaked.expired()? "True": "False") <<endl;
	cout<<"Address of a weakptr via nd1Weaked after reset nd1Shared is null? "<<(nd1Weaked.lock().get()==nullptr?"true":"false")<<endl;

	cout<<"\nReference to nd1Shared via nd2Weaked after reset nd1Shared are: "<<nd2Weaked.use_count()<<" expired? "<<(nd2Weaked.expired()? "True": "False") <<endl;
	cout<<"Address of a weakptr via nd2Weaked after reset nd1Shared is null? "<<(nd2Weaked.lock().get()==nullptr?"true":"false")<<endl;

	uc_count++;
        cout<<"\n==========UC"<<uc_count<<":"<<" reset nd1Weaked and keeping nd2Weaked=========="<<endl;

	cout<<"Default value of a weakptr is null? "<<(nd1Weaked.lock().get()==nullptr?"true":"false")<<endl;
	nd1Shared=make_shared<Nodo>(12);
	nd1Weaked = nd1Shared;
	//nd2Weaked = nd1Shared == nd2Weaked=nd1Weaked
	nd2Weaked=nd1Weaked;
	cout<<"\nReference to nd1Shared before resetting it are: "<<nd1Weaked.use_count()<<endl;

	/****************************** The following command just reset a temporary instance not the referred shared ptr *******************************************/
	nd1Weaked.reset();

	cout<<"\nValue of nd1Share via sharedPtr after resetting nd1Weaked is: "<<nd1Shared->getVal()<<endl;

	cout<<"\nReference to nd1Shared via nd1Weaked after reset are: "<<nd1Weaked.use_count()<<" expired? "<<(nd1Weaked.expired()? "True": "False") <<endl;
	cout<<"Address of a weakptr via nd1Weaked after reset is null? "<<(nd1Weaked.lock().get()==nullptr?"true":"false")<<endl;

	//This creates a segmentation fault
	//cout<<"Value of nd1Share via nd1Weaked after reset is: "<<nd1Weaked.lock()->getVal()<<endl;

	cout<<"\nReference to nd1Shared via nd2Weaked after reset are: "<<nd2Weaked.use_count()<<" expired? "<<(nd2Weaked.expired()? "True": "False") <<endl;
	cout<<"Address of a weakptr via nd2Weaked after reset is null? "<<(nd2Weaked.lock().get()==nullptr?"true":"false")<<endl;
	cout<<"Value of nd1Share via nd2Weaked after reset is: "<<nd2Weaked.lock()->getVal()<<endl;

	uc_count++;
        cout<<"\n==========UC"<<uc_count<<":"<<" reassigning shared ptr pointed by 2 weakptr=========="<<endl;
	nd1Shared.reset(new Nodo(100));
	nd1Weaked = nd1Shared;
	nd2Weaked = nd1Weaked;
	cout<<"New nd1Shared value is "<<nd1Shared->getVal()<<" ,nd1Weaked is "<<nd1Weaked.lock()->getVal()<<" ,nd2Weaked is "<<nd2Weaked.lock()->getVal()<<endl;
	nd1Shared.reset(new Nodo(22));
	//This create a segmentation fault as the values in the weakptr are not automatically reassigned
	//cout<<"New nd1Shared value is "<<nd1Shared->getVal()<<" ,nd1Weaked is "<<nd1Weaked.lock()->getVal()<<" ,nd2Weaked is "<<nd2Weaked.lock()->getVal()<<endl;
	cout<<" After changing nd1Shared value destructor is called and nd1Weaked is nullptr? "<<(nd1Weaked.expired()? "True" : "False")<<endl;

	uc_count++;
        cout<<"\n==========UC"<<uc_count<<":"<<" passing sharedptr to a function which accepts weakptr as argument=========="<<endl;
	nd1Shared.reset(new Nodo(15));
	print(nd1Shared);










        return 0;
}
