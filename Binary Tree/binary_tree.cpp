#include <bits/stdc++.h>

using namespace std;


class Node
{
public:
    int data;
    Node* left = NULL;
    Node* right = NULL;

    Node(int data)
    {
        this->data = data;
    }
};

class Pair
{
public:
    Node* node;
    int state;

    Pair(Node* node, int state)
    {
        this->node = node;
        this->state = state;
    }
};


Node* construct_(int a[], int n)
{
    //constructing tree using stack 
    Node* root = new Node(a[0]);

    stack <Pair*> s;
    Pair* root_pair = new Pair(root, 1);

    s.push(root_pair);

    int id = 0;
    while(s.size())
    {
        Pair* top = s.top();
        if(top->state == 1)
        {
            id++;
            if(a[id] != -1)
            {
                top->node->left = new Node(a[id]);
                Pair* lp = new Pair(top->node->left, 1);
                s.push(lp);
            }
            else
            {
                top->node->left = NULL;
            }
            top->state++;
        }

        else if(top->state == 2)
        {
            id++;
            if(a[id] != -1)
            {
                top->node->right = new Node(a[id]);
                Pair* rp = new Pair(top->node->right, 1);
                s.push(rp);
            }
            else
            {
                top->node->right = NULL;
            }
            top->state++;
        }

        else
            s.pop();
    }

    return root;
}


int idx = 0;
Node* construct(vector <int> arr)
{
    if (idx == arr.size() || arr[idx] == -1)
    {
        idx++;
        return nullptr;
    }
    Node* node = new Node(arr[idx++]);

    node->left = construct(arr);
    node->right = construct(arr);

    return node;
}


void display(Node* node)
{
    if (node == nullptr)
        return;

    string str = "";
    str += node->left != nullptr ? to_string(node->left->data) : ".";

    str += " <- " + to_string(node->data) + " -> ";
    str += node->right != nullptr ? to_string(node->right->data) : ".";

    cout << str << endl;

    display(node->left);
    display(node->right);
}


int size = 0, sum = 0, mx = INT_MIN, height = 0;

void dfs(Node* root, int depth)
{
    if(root == NULL)
        return;

    mx = max(mx, root->data);
    sum += root->data;
    height = max(height, depth);

    size++;

    dfs(root->left, depth + 1);
    dfs(root->right, depth + 1);
}

void preorder(Node* root)
{
    if(root == NULL)
        return;

    cout << root->data << endl;
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root)
{
    if(root == NULL)
        return;

    inorder(root->left);
    cout << root->data << endl;
    inorder(root->right);
}

void postorder(Node* root)
{
    if(root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << endl;
}

void bfs(Node* root)
{
    queue <Node*> q, child;
    q.push(root);
    
    while(q.size())
    {
        Node* top = q.front();
        q.pop();

        cout << top->data << " ";

        if(top->left != NULL)
            child.push(top->left);

        if(top->right != NULL)
            child.push(top->right);

        if(q.size() == 0)
        {
            q = child;
            child = queue <Node*> ();
            cout << endl;
        }
    }
}

vector <int> node_to_root(Node* root, int val)
{
    vector <int> v;

    if(root == NULL)
        return v;

    if(root->data == val)
    {
        v.push_back(root->data);
        return v;
    }

    if(node_to_root(root->left, val).size())
    {
        v = node_to_root(root->left, val);
        v.push_back(root->data);
        return v;
    }

    if(node_to_root(root->right, val).size())
    {
        v = node_to_root(root->right, val);
        v.push_back(root->data);
        return v;
    }

    return v;
}

void leaf_to_root_in_range(Node* root, string path, int sum, int lo, int hi)
{
    if(root == NULL)
        return;

    if(root->left == NULL && root->right == NULL)
    {
        sum += root->data;
        if(sum >= lo && sum <= hi)
        {
            path += to_string(root->data);
            cout << path << endl;
        }
        return;
    }

    path = path + to_string(root->data) + " ";

    leaf_to_root_in_range(root->left, path, sum + root->data, lo, hi);
    leaf_to_root_in_range(root->right, path, sum + root->data, lo, hi);
}

Node* left_clone_tree(Node* root)
{   
    if(root == NULL)
        return NULL;

    Node* left_clone = left_clone_tree(root->left);
    
    Node* right_clone = left_clone_tree(root->right);

    Node* new_left = new Node(root->data);
    new_left->left = left_clone;
    new_left->right = NULL;

    root->left = new_left;
    root->right = right_clone;

    return root;
}

Node* left_cloned_to_normal(Node* root)
{
    if(root == NULL)
        return NULL;

    Node* left_normal = left_cloned_to_normal(root->left->left);
    Node* right_normal = left_cloned_to_normal(root->right);

    root->left = left_normal;
    root->right = right_normal;
}

Node* remove_leaves(Node* root)
{
    if(root == NULL || root->left == NULL && root->right == NULL)
        return NULL;

    Node* new_left = remove_leaves(root->left);
    Node* new_right = remove_leaves(root->right);

    root->left = new_left;
    root->right = new_right;

    return root;
}

//class needed for calculating diameter of a tree efficiently in a single function
class Dia_pair
{
public:
    int height;
    int dia;
};

//recursive function for calculating diameter and height simultaneously in O(n)
//there are 3 cases to be considered for calculating diameter
//first -> when deepest and second deepest nodes lie on diff sides
//second -> when both lie on the left side
//third -> when both lie on the right side
Dia_pair* diameter(Node* root)
{
    if(root == NULL)
    {
        Dia_pair* base = new Dia_pair;
        base->height = -1;
        base->dia = 0;

        return base;
    }

    Dia_pair* left = diameter(root->left);
    Dia_pair* right = diameter(root->right);

    Dia_pair* parent = new Dia_pair;
    parent->height = max(left->height, right->height) + 1;

    //max diameter if one deepest node is considered from left and one from right
    int left_right_max = left->height + right->height + 2;

    parent->dia = max({left_right_max, left->dia, right->dia});

    return parent;
}


//tilt of a node is absolute of difference of left subtree sum and right subtree sum
//tilt of whole tree is represented as the sum of all the tilts of the tree
int Tilt = 0;
int tilt(Node* root)
{
    if(root == NULL)
        return 0;

    int sum = 0;

    int s1 = tilt(root->left);
    int s2 = tilt(root->right);

    sum += s1 + s2 + root->data;

    Tilt += abs(s1 - s2);
    return sum;
}

//a BST or Binary Search tree is a tree in which ---
//  -> every node is greater than or equal to than every node in its left subtree
//and -> every node is smaller than or equal to than every node in its right subtree

//class needed for determing whether a tree is BST or not
class BST
{
public:
    bool isBST;
    int mn = INT_MAX;
    int mx = INT_MIN;
    int sz = 0;
    Node* root;
};

BST* is_BST(Node* root)
{
    if(root == NULL)
    {
        BST* base = new BST;
        base->isBST = true;
        base->mn = INT_MAX;
        base->mx = INT_MIN;
        root = NULL;
        sz = 0;
        return base;
    }

    BST* left = is_BST(root->left);
    BST* right = is_BST(root->right);

    BST* parent = new BST;

    bool self = root->data >= left->mx && root->data <= right->mn;

    parent->mn = min({root->data, left->mn, right->mn});
    parent->mx = max({root->data, left->mx, right->mx});
    parent->isBST = left->isBST && right->isBST && self;

    if(parent->isBST)
    {
        parent->root = root;
        parent->sz = left->sz + right->sz + 1;
    }
    else if(left->sz > right->sz)
    {
        parent->root = left->root;
        parent->sz = left->sz;
    }
    else
    {
        parent->root = right->root;
        parent->sz = right->sz;
    }

    return parent;
}

bool is_balanced = true;
int balanced(Node* root)
{
    if(root == NULL)
        return 0;

    int h1 = balanced(root->left);
    int h2 = balanced(root->right);

    is_balanced &= (abs(h1 - h2) < 2);

    return max(h1, h2) + 1;
}

int32_t main()
{

    int n;
    cin >> n;

    vector <int> a(n);

    for(int i = 0; i < n; ++i)
    {   
        string s;
        cin >> s;

        if(s == "n")
            a[i] = -1;

        else
            a[i] = stoi(s);
    }

    Node* root = construct(a);

}
