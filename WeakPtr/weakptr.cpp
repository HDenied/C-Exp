#include<iostream>
#include<memory>

using namespace std;

class Nodo {

public:
        Nodo(uint32_t val): m_val(val)
        {
            cout<<"Created node"<<node_ctr<<" with value "<<m_val<<endl;
            m_ctr=node_ctr++;
        }

        ~Nodo()
        {
            cout<<"Destroyed node"<<m_ctr<<" with value "<<m_val<<endl;

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
        static void init() {Nodo::node_ctr=0;}
        static uint32_t getGlobCtr() {return Nodo::node_ctr;}

};

uint32_t Nodo::node_ctr;

int main()
{
        uint32_t uc_count = 0;
        {
                cout<<"Static variable default value is: "<<Nodo::getGlobCtr()<<endl;
                Nodo testNode=Nodo(12);
                cout<<"Default value of shared pointer is nullptr: "<<(testNode.shared_prv==nullptr? "true":"false")<<endl;
        }

        cout<<"\nUC"<<uc_count<<":"<<" basic usage"<<endl;
        Nodo::init();

        // Weakptr just < relational operator
        //cout<<"Default value of weak pointer is nullptr: "<<(testNode.weak_prv==nullptr? "true":"false")<<endl;




        return 0;
}
