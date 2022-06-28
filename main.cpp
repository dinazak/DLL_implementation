#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

template<class T>
struct Node
{
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node()
    {
        prev = next = NULL;
    }
};

int done = 0;
template<class T>
class myList
{
    Node<T>* first;
    Node<T>* last;
    int initial_size;
public:

    myList()
    {
        first = new Node<T>();
        last = new Node<T>();
        first = last;
        initial_size = 0;
    }

    myList(T value, int size)
    {
        first = new Node<T>();
        last = new Node<T>();
        first = last;
        initial_size = size;
        while (size-- > 0)
        {
            insert(value, myList<T>::begin());
        }

    }

    ~myList()
    {
        if (done != 0)
        {
            done--;
        }
        else
        {
            Node<T>* curNode = first;
            Node<T>* tmp=curNode;
            int s = size();
            while (s--)
            {
                tmp = curNode->next;
                delete curNode;
                curNode = tmp;
            }
            delete curNode;
            delete tmp;
        }
    }

    int size()
    {
        return initial_size;
    }


    class iterator
    {
        Node<T>* point;

        friend class myList;

    public:

        iterator()
        {
            point = NULL;
        }

        iterator(Node<T>* ptr)
        {
            point = ptr;
        }

        void operator++()
        {
            point = point->next;
        }

        void operator--()
        {
            point = point->prev;
        }

        T& operator*()
        {
            return point->data;
        }


        bool operator==(const iterator& obj)
        {
            return point == obj.point;
        }

        bool operator!=(const iterator& obj)
        {
            return point != obj.point;
        }
    };

    void insert(T value, iterator position)
    {

        Node<T>* newNode = new Node<T>();
        newNode->data = value;
        if (position.point == first)
        {
            newNode->next = first;
            first->prev = newNode;
            first = newNode;
            first->prev = NULL;
        }
        else
        {
            newNode->next = position.point;
            newNode->prev = position.point->prev;
            position.point->prev->next = newNode;
            position.point->prev = newNode;
        }
        ++initial_size;
        newNode = first;
        for (int i = 0; i < initial_size - 1; i++)
        {
            newNode = newNode->next;
        }
        newNode->next = NULL;
        last = newNode;
    }


    myList<T>& operator=(myList<T> another_list)
    {
        Node<T>* curNode = first;
        while (curNode != 0)
        {
            Node<T>* tmp = curNode->next;
            delete curNode;
            curNode = tmp;
        }
        iterator it = another_list.begin();
        while (it != another_list.end())
        {
            insert(*it, End());
            ++it;
        }
        return *this;
    }

    iterator begin()
    {
        return iterator(first);
    }

    iterator End()
    {
        return iterator(last);
    }

    iterator erase(iterator position)
    {

        if (position.point == last) {
            cout<<"this element is undefined"<<endl;
            return 0;
        }
        if (position.point == first)
        {
            Node<T> *tmp = first;
            first = tmp->next;
             delete tmp;
            initial_size--;
            return first;
        }
        else
        {
            position.point->next->prev = position.point->prev;
            Node<T> *tmp = position.point->next;;
            position.point->prev->next = tmp;

            delete position.point;
            initial_size--;
            return tmp;
        }
    }
    Node<T>* gethead()
    {
        return first;
    }
    Node<T>* getlast()
    {
        return last;
    }

};

template<class T>
void print(myList<T>& l)
{
    typename myList<T>::iterator it = l.begin();

    while (it != l.End())
    {

        cout << *it << ' ';
        ++it;
    }
    cout << *it;
    cout << endl;
}
template<class T>
T& firstNode(myList<T>& l)
{
    typename myList<T>::iterator it = l.begin();
    return *it;
}

template<class T>
Node<T>* complete(Node<T>* h)
{
    if (h->next == NULL)
        return h;
    h->next = complete(h->next);
    return h;
}

template<class T>
Node<T>* mergelist(myList <T>& l1, myList <T>& l2)
{
    done = 2;
    Node <T>* n1 = l1.gethead();
    Node <T>* n2 = l2.gethead();
    Node <T>* n3 = l2.gethead();
    Node <T>* n4 = l2.gethead();
    Node <T>* head=NULL;
    int sl1, sl2;
    sl1 = l1.size();
    sl2 = l2.size();
    int counterl1 = 0;
    int counterl2 = 0;

    while (counterl1 < sl1 && counterl2 < sl2)
    {
        n2 = n3;
        if (n1->data > n2->data&& counterl1 == 0 && counterl2 == 0)
        {
            n3 = n2->next;
            n1->prev = n2;
            n2->next = n1;
            n2->prev = NULL;
            head = n2;
            n2->next;
            counterl2++;
        }
        else if (n1->data <= n2->data && counterl1 == 0 && counterl2 == 0)
        {
            n1->prev = NULL;
            head = n1;
            n1 = n1->next;
            counterl1++;
        }
        else if (n1->data <= n2->data && counterl1 + 1 == sl1)
        {
            break;
        }
        else if (n1->data > n2->data&& counterl2 + 1 == sl2)
        {
            n3 = n2;
            n1->prev->next = n2;
            n2->prev = n1->prev;
            n1->prev = n2;
            n2->next = n1;
            counterl2++;
        }
        else if (n1->data <= n2->data)
        {
            n1 = n1->next;
            counterl1++;
        }
        else if (n1->data > n2->data)
        {
            n3 = n2->next;
            n1->prev->next = n2;
            n2->prev = n1->prev;
            n1->prev = n2;
            n2->next = n1;
            counterl2++;
        }
    }
    if (counterl2 < sl2)
    {
        n1->next = n3;
        n3->prev = n1;
    }

    return head;
}
template<class T>
int removeDuplicates (Node <T>* mergedhead){
    int count=0;
    Node<T>* current = mergedhead;
    Node<T>* Next;
    if(current==NULL){
         // return;
    }
    while(current->next!=NULL){
        if (current->data==current->next->data){
            Next=current->next->next;
            delete(current->next);
            count++;
            current->next=Next;
        }
        else{current=current->next;}

    }
    return count;
}
template<class T>
void printbyhead(Node <T>* mergedhead, myList <T> &l1, myList <T> &l2)
{
    int d=removeDuplicates(mergedhead);
    done = 2;

    int n = l1.size() + l2.size()-d;
    while (n--)
    {
        cout << mergedhead->data << " ";
        mergedhead = mergedhead->next;
    }
}

int main()
{
    myList<int> l1;
    l1.insert(6, l1.begin());
    l1.insert(4, l1.begin());
    l1.insert(2, l1.begin());
    l1.insert(0, l1.begin());

    cout<<"The first list is: ";
    print(l1);
    myList<int> l2;
    l2.insert(7, l2.begin());
    l2.insert(5, l2.begin());
    l2.insert(3, l2.begin());
    l2.insert(0, l2.begin());//checking function removeDuplicates
    cout<<"The second list is: ";
    print(l2);
    cout<<"after merge"<<endl;
    Node<int>* mergedhead1 = mergelist(l1, l2);
    printbyhead(mergedhead1, l1, l2);
    cout << endl;



    return 0;
}