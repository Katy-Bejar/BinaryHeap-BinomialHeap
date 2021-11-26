/*

INTEGRANTES:
-Suni Quispe Yanira Angie
-Bejar Roman Edson Bryan
-Bejar Roman Katherine Nikole

*/
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class BinomialNode {
    public:
        T m_dato;   
        int grade;      
        BinomialNode<T> *m_Son;   
        BinomialNode<T> *m_pFather;    
        BinomialNode<T> *next;   

        BinomialNode(T value):m_dato(value), grade(0),
            m_Son(nullptr),m_pFather(nullptr),next(nullptr) {}
};

template <class T>
class BinomialHeap {
    private:
        BinomialNode<T> *mRoot;  

    public:
        BinomialHeap():mRoot(nullptr){}
        ~BinomialHeap(){}

        void insert(T m_dato)
        {
            BinomialNode<T>* node;
            if (contains(m_dato)){
                cout << "El dato" << m_dato << "ya bh1 sido insertado" << endl;
                return ;
            }
            node = new BinomialNode<T>(m_dato);
            if (node==nullptr)
                return ;

            mRoot = combine(mRoot, node);
        }

        void update(T oldm_dato, T newm_dato)
        {
            BinomialNode<T> *node;
            node = search(mRoot, oldm_dato);
            if (node != nullptr)
                updatem_dato(node, newm_dato);
        }
        
        void remove(T m_dato){
            mRoot = remove(mRoot, m_dato);
        }

        void extractMinimum()
        {
            mRoot = extractMinimum(mRoot);
        }

        void combine(BinomialHeap<T>* other)
        {
            if (other!=nullptr && other->mRoot!=nullptr)
                mRoot = combine(mRoot, other->mRoot);
        }

        T minimum()
        {
            BinomialNode<T> *prev_y, *y;
            minimum(mRoot, prev_y, y);
            return y->m_dato;
        }

        bool contains(T m_dato)
        {
            return search(mRoot, m_dato)!=nullptr ? true : false;
        }

        void Print(ostream& out)
        {
            BinomialNode<T> *p;
            if (mRoot == nullptr)
                return ;
            p = mRoot;
            while (p != nullptr){
                p = p->next;
            }
            int i=0;
            p = mRoot;
            while (p != nullptr){
                i++;
                out  << p->m_dato << ";" << endl;

                Print(p->m_Son, p, 1, out);
                p = p->next;
            }
            cout << endl;
        }

    private:
        void link(BinomialNode<T>* m_Son, BinomialNode<T>* root)
        {
            m_Son->m_pFather = root;
            m_Son->next   = root->m_Son;
            root->m_Son = m_Son;
            root->grade++;
        }
     
        BinomialNode<T>* merge(BinomialNode<T>* h1, BinomialNode<T>* h2)
        {
            BinomialNode<T>* root = nullptr; 
            BinomialNode<T>** pos = &root;
            while(h1 && h2){
                if(h1->grade < h2->grade){
                    *pos = h1;
                    h1 = h1->next;
                }
                else{
                    *pos = h2;
                    h2 = h2->next;
                }
                pos = &(*pos)->next;
            }
            if (h1)
                *pos = h1;
            else
                *pos = h2;
            return root;
        }

        BinomialNode<T>* combine(BinomialNode<T>* h1, BinomialNode<T>* h2)
        {
            BinomialNode<T> *root;
            BinomialNode<T> *prev_x, *x, *next_x;
            root = merge(h1, h2);
            if (root == nullptr)
                return nullptr;

            prev_x = nullptr;
            x      = root;
            next_x = x->next;

            while (next_x != nullptr){
                if ((x->grade != next_x->grade) || ((next_x->next != nullptr) && (next_x->grade == next_x->next->grade))){
                    prev_x = x;
                    x = next_x;
                }
                else if (x->m_dato <= next_x->m_dato){
                    x->next = next_x->next;
                    link(next_x, x);
                }
                else{
                    if (prev_x == nullptr){
                        root = next_x;
                    }
                    else{
                        prev_x->next = next_x;
                    }
                    link(x, next_x);
                    x = next_x;
                }
                next_x = x->next;
            }
            return root;
        }

        BinomialNode<T>* reverse(BinomialNode<T>* root)
        {
            BinomialNode<T>* next;
            BinomialNode<T>* tail = nullptr;
            if (!root)
                return root;
            root->m_pFather = nullptr;
            while (root->next){
                next          = root->next;
                root->next = tail;
                tail          = root;
                root          = next;
                root->m_pFather  = nullptr;
            }
            root->next = tail;
            return root;
        }

        BinomialNode<T>* extractMinimum(BinomialNode<T>* root)
        {
            BinomialNode<T> *y, *prev_y;    
            if (root==nullptr)
                return root;
            minimum(root, prev_y, y);
            if (prev_y == nullptr)    
                root = root->next;
            else         
                prev_y->next = y->next;
            BinomialNode<T>* m_Son = reverse(y->m_Son);
            root = combine(root, m_Son);
            delete y;
            return root;
        }

        BinomialNode<T>* remove(BinomialNode<T> *root, T m_dato)
        {
            BinomialNode<T> *node;
            BinomialNode<T> *m_pFather, *prev, *pos;

            if (root==nullptr)
                return root;

            if ((node = search(root, m_dato)) == nullptr)
                return root;

            m_pFather = node->m_pFather;
            while (m_pFather != nullptr){
                swap(node->m_dato, m_pFather->m_dato);
                node   = m_pFather;
                m_pFather = node->m_pFather;
            }
            prev = nullptr;
            pos  = root;
            while (pos != node){
                prev = pos;
                pos  = pos->next;
            }
            if (prev)
                prev->next = node->next;
            else
                root = node->next;
            root = combine(root, reverse(node->m_Son));

            delete node;
            return root;
        }
        
        BinomialNode<T>* search(BinomialNode<T>* root, T m_dato)
        {
            BinomialNode<T> *m_Son;
            BinomialNode<T> *m_pFather = root;

            m_pFather = root;
            while (m_pFather != nullptr){
                if (m_pFather->m_dato == m_dato)
                    return m_pFather;
                else{
                    if((m_Son = search(m_pFather->m_Son, m_dato)) != nullptr)
                        return m_Son;
                    m_pFather = m_pFather->next;
                }
            }
            return nullptr;
        }

        void decreasem_dato(BinomialNode<T>* node, T m_dato)
        {
            if(m_dato>=node->m_dato || contains(m_dato)){
                cout << "El dato" << m_dato <<" ya bh1 sido insertado "
                    << "o no es más pequeño que el m_dato actual (" << node->m_dato <<")" << endl;
                return ;
            }
            node->m_dato = m_dato;

            BinomialNode<T> *m_Son, *m_pFather;
            m_Son = node;
            m_pFather = node->m_pFather;
            while(m_pFather != nullptr && m_Son->m_dato < m_pFather->m_dato){
                swap(m_pFather->m_dato, m_Son->m_dato);
                m_Son = m_pFather;
                m_pFather = m_Son->m_pFather;
            }
        }

        void updatem_dato(BinomialNode<T>* node, T m_dato)
        {
            if (node == nullptr)
                return ;
            if(m_dato < node->m_dato)
                decreasem_dato(node, m_dato);
            else if(m_dato > node->m_dato)
                increasem_dato(node, m_dato);
            else
                cout <<"No necesita actualizarse!" <<endl;
        }

        void minimum(BinomialNode<T>* root, BinomialNode<T> *&prev_y, BinomialNode<T> *&y)
        {
            BinomialNode<T> *x, *prev_x; 
            if (root==nullptr)
                return ;
            prev_x = root;
            x = root->next;
            prev_y = nullptr;
            y = root;
            while (x != nullptr) {
                if (x->m_dato < y->m_dato) {
                    y = x;
                    prev_y = prev_x;
                }
                prev_x = x;
                x = x->next;
            }
        }

        void Print(BinomialNode<T>* node, BinomialNode<T>* prev, int direction, ostream& out)
        {
            while(node != nullptr){
                if(direction==1) 
                    out << prev->m_dato << "->" << node->m_dato << ";" << endl;
                else  
                    out << prev->m_pFather->m_dato << "->" << node->m_dato << ";" << endl;
                if (node->m_Son != nullptr)
                    Print(node->m_Son, node, 1, out);
                prev = node;
                node = node->next;
                direction = 2;
            }
        }
};

void testUnion()
{
    BinomialHeap<int>* bh1=new BinomialHeap<int>();
    BinomialHeap<int>* bh2=new BinomialHeap<int>();

    cout << "BH-1" << endl;
    bh1->insert(3);
    bh1->insert(45);
    bh1->insert(92);
    bh1->insert(34);
    bh1->insert(23);
    bh1->insert(26);
    bh1->insert(14);
    bh1->insert(12); 

    cout << endl;

    bh1->Print(cout);
    cout << endl;

    cout << "BH-1" << endl;
    bh2->insert(25);
    bh2->insert(65);
    bh2->insert(43);
    bh2->insert(77);
    bh2->insert(33);
    bh2->insert(87);
    bh2->insert(19); 
    bh2->insert(17); 

    cout << endl;

    bh2->Print(cout);
    cout << endl;
   
    bh1->combine(bh2);

    cout << endl;
    bh1->Print(cout);
    ofstream file("Binomial2.dot");
    bh1->Print(file);
}

void testInsert()
{
    BinomialHeap<int>* bh1 = new BinomialHeap<int>();

    bh1->insert(3);
    bh1->insert(45);
    bh1->insert(92);
    bh1->insert(34);
    bh1->insert(23);
    bh1->insert(26);
    bh1->insert(14);
    bh1->insert(12); 
    bh1->insert(5); 
    bh1->insert(7); 
    bh1->insert(39); 
    bh1->insert(22); 
    bh1->insert(99); 
    bh1->insert(48); 

    cout << endl;
    bh1->Print(cout);
    ofstream file("BinomialHeap.dot");
    bh1->Print(file);
}

int main()
{
    //testUnion();
    testInsert();
}
