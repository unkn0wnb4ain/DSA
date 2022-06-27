#include <bits/stdc++.h>

using namespace std;

class node
{
public:
    int data;
    vector <node*> children;
};

node* newnode(int key)
{
    node* t = new node;
    t->data = key;
    return t;
}

node* construct(vector <int> a, int n)
{
    stack <node*> s;
    node* root = NULL;

    for (int i = 0; i < n; ++i)
    {   
        if(a[i] == -1)
            s.pop();

        else
        {
            node* t = newnode(a[i]);

            if(s.empty())
                root = t;

            else
                s.top()->children.push_back(t);

            s.push(t);
        }
    }

    return root;
}

int size(node* root)
{
    int ct = 1;

    for(auto Node : root -> children)
    {
        ct += size(Node);
    }

    return ct;
}

int max(node* root)
{
    int mx = root->data;

    for(auto child : root->children)
    {
        mx = max(mx, max(child));
    }

    return mx;
}

void traversal(node* root)
{
    //DFS traversals
    cout << "Node Pre " << root->data << endl;
    
    for(auto child : root->children)
    {
        cout << "Edge Pre " << root->data << "--" << child->data << endl;
        traversal(child);
        cout << "Edge Post " << root->data << "--" << child->data << endl;
    }   

    cout << "Node Post " << root->data << endl;
}

int height(node* root)
{
    int h = 0;

    for(auto child : root->children)
    {
        h = max(h, 1 + height(child));
    }

    return h;
}

void bfs(node* root)
{
    //stack needed for zig-zag pattern
    //for simple bfs declare both q and qq as queue
    stack <node*> q;
    queue <node*> qq;
    q.push(root);

    int ct = 1;

    while(!q.empty())
    {
        node* temp = q.top();
        q.pop();
        cout << temp->data << " ";

        //use ct when zig zag line wise pattern is needed 
        //else use simple range based for loop

        if(ct & 1)
        {
            for(int i = 0; i < temp->children.size(); ++i)
                qq.push(temp->children[i]);
        }
        else
        {
            for(int i = temp->children.size() - 1; i >= 0 ; --i)
                qq.push(temp->children[i]);
        }

        if(q.size() == 0)
        {
            while(qq.size())
            {
                q.push(qq.front());
                qq.pop();
            }
            ct++;
            cout << endl;
        }
    }
}

vector <int> nodetoroot(node* root, int val)
{
    if(root->data == val)
    {
        vector <int> v = {root->data};
        return v;
    }

    vector <int> v;

    for(auto child : root->children)
    {
        v = nodetoroot(child, val);

        if(v.size())
        {
            v.push_back(root->data);
            return v;
        }
    }

    return v;
}

int lca(node* root, int val1, int val2)
{
    //for LCA - find the path of both nodes from root, reverse it and find the last common element 
    //for find the number of edges between two nodes --> use concept of lca 
    vector <int> a = nodetoroot(root, val1);
    vector <int> b = nodetoroot(root, val2);

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int lca = 0, i = 0, j = 0;

    while(i < a.size() && j < b.size())
    {
        if(a[i] == b[j])
            lca = a[i];

        else
            break;

        i++; j++;
    }

    return lca;
}

bool similar(node* root1, node* root2)
{
    //for findning whether trees have similar shape or not
    //similar function cal also be used for checking mirror trees with some minor changes 
    if(root1->children.size() != root2->children.size())
        return false;

    for(int i = 0; i < root1->children.size(); ++i)
    {
        node* a = root1->children[i];
        node* b = root2->children[i];

        if(!similar(a, b))
            return false;
    }

    return true;
}

void multisolver(node* root)
{
    //single function for calculating max, min, height, sum, etc
    //pass the parameters in the function which needs to be calculated

    //sz++;
    //mx = max(mx, root->data);
    //height = max(height, depth);

    for(auto child : root->children)
    {
        multisolver(child);
    }
}

node* prede = NULL;
node* succe = NULL;
int state = 0;

void prede_and_succe(node* root, int data)
{
    //function for finding predecessor and succesor of a node using modeified multisolver function
    if(state == 0)
    {
        if(root->data == data)
            state = 1;
        else
            prede = root;
    }
    else if(state == 1)
    {
        succe = root;
        state = 2;
    }

    for(auto child : root->children)
        prede_and_succe(child, data);
}

void ceil_and_floor(node* root, int val, int &ceil, int &floor)
{
    //function for ceil and floor of a node data
    if(root->data > val)
        ceil = min(ceil, root->data);

    if(root->data < val)
        floor = max(floor, root->data);

    for(auto child : root->children)
        ceil_and_floor(child, val, ceil, floor);
}

int max_subsum = 0;

int max_subtree_sum(node* root)
{
    //function for calculating maximum subtree sum
    int sum = root->data;

    for(auto child : root->children)
    {
        sum += max_subtree_sum(child);
    }

    max_subsum = max(max_subsum, sum);

    return sum;
}


int32_t main()
{

    int n;
    cin >> n;

    vector <int> v(n);

    for(int i = 0; i < n; ++i)
        cin >> v[i];

    node* root = construct(v, n);

}

