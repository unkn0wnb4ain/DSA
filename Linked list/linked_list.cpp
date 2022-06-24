#include <bits/stdc++.h>

using namespace std;

class node 
{

public:
    int val;
    node* next;

};

class LinkedList
{

public:
    node* head = nullptr;
    node* tail = nullptr;
    int sizee = 0;

    int size()
    {
        return this -> sizee;
    }

    bool empty()
    {
        return sizee == 0;
    }

    LinkedList makeList() 
    {
        LinkedList l;
        int n1;
        cin >> n1;

        for(int i = 0; i < n1; i++) 
        {
            int val;
            cin >> val;
            l.add_at_last(val);
        }

        return l;
    }

    void add_at_start(int val) 
    {
        node* newnode = new node;
        newnode->val = val;
        newnode->next = NULL;

        if (head == NULL) 
            head = newnode;

        else 
        {
            newnode ->next = head;
            head = newnode;
        }

        sizee++;
    }

    void add_at_last(int val)
    {
        if (head == NULL) 
        {
            node* newnode = new node;
            newnode->val = val;
            newnode->next = NULL;
            head = newnode;
        }

        else 
        {
            node* newnode = new node;
            newnode->val = val;
            newnode->next = NULL;
            node* temp = head;

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
        }

        sizee++;
    }

    void print() 
    {
        node* temp = head;

        if (head == NULL) 
        {
            cout << "0" << endl;
            return;
        }

        while (temp != NULL) 
        {
            cout << temp->val << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void delete_first() 
    {
        if (head == NULL) return;

        node* temp = head;
        head = head->next;
        delete temp;

        sizee--;
    }

    void delete_last() 
    {
        if (head == NULL) return;

        node* previous = NULL;
        node* temp = head;
        while (temp->next != NULL) 
        {
            previous = temp;
            temp = temp->next;
        }

        previous->next = NULL;
        delete temp;

        sizee--;
    }


    void last() 
    {
        node* temp = head;
        while (temp->next != NULL) 
            temp = temp->next;

        cout << temp->val << endl;
    }
      
    int first() 
    {
        return head->val;
    }

    node* get_at(int p) 
    {
        int cnt = 0;
        node* temp = head;
    
        while (cnt < p) 
        {
            cnt++;
            temp = temp->next;
        }

        cout << temp->val << endl;
        return temp;
    }

    void add_at(int pos, int data) 
    {
        if (pos == 0) 
        {
            add_at_start(data);
            return;
        }
        
        node* newnode = new node;
        newnode->val = data;
        
        int cnt = 0;
        
        node* temp = head;
        while (cnt < pos - 1) 
        {
            cnt++;
            temp = temp->next;
        }

        newnode->next = temp->next;
        temp->next = newnode;

        sizee++;
    }

    void remove_at(int pos) 
    {
        if(pos == 0) 
        {
            delete_last();
            return;
        }

        int cnt = 0;
        node* temp = head;
        
        while(cnt < pos - 1) 
        {
            cnt++;
            temp = temp->next;
        }

        temp->next = temp->next->next;

        sizee--;
    }

    void reverse_di() 
    {
        //reversing the order of the data
        int left = 0;
        int right = size() - 1;

        while (left < right) 
        {
            node* templ = get_at(left);
            node* tempr = get_at(right);

            int temp = templ->val;
            templ->val = tempr->val;
            tempr->val = temp;
            left++;
            right--;
        }
    }

    void reverse_pi() 
    {
        //reversing the list using pointers
        if (size() <= 1) 
        {
            return;
        }

        node* t = head;
        while (t->next != NULL) 
            t = t->next;

        tail = t;

        node* prev = nullptr;
        node* curr = head;

        while(curr != nullptr) 
        {
            node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        node* temp = head;
        head = tail;
        tail = temp;
    }

};

    
int main() 
{

    LinkedList l;

    l.add_at_start(4);
    l.add_at_start(1);
    l.add_at_start(2);
    l.add_at_start(4);
    l.add_at_start(6);

    l.print();
    cout << l.size() << endl;


}
