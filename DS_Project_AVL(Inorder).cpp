#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct node
{
    int data;
    int height;
    struct node* leftChild;
    struct node* rightChild;
};

//Operations that can be performed on the tree nodes:
struct node* createTree(int value);
struct node* insertNode(struct node* root, int value, bool &avl);
struct node* deleteNode(struct node* root, int value, string side, bool &avl);
struct node* searchNode(struct node* root, int value);
struct node* parentFinder(struct node* root, struct node *child, struct node *parent);
int depthFinder(struct node *root, int value, int depth);
int heightFinder(struct node *node);

//Functions required in other functions:
struct node* findMin(struct node* root);
struct node* findMax(struct node* root);
struct node* balance(struct node* root, bool &avl);
struct node* avlInsert(struct node *h, vector<int> values, bool &avl);
void inorder(struct node* root, vector<int>& vec);
int balanceFactorFinder(struct node *root);

//Output format handlers:
void printHandlerInProgress(struct node* root, struct node* node, int value);
string printHandlerAfterProgress(struct node *root, struct node* node, int value, string output);

int main()
{
    string output = "";
    struct node* root = NULL;
    bool avl = true;
    int programNum;
    cin >> programNum;
    int value;
    string program;
    string side = "";
    for (int i = 0; i < programNum; i++)
    {
        cin >> value;
        cin >> program;
        if (program == "I")
        {
            root = insertNode(root, value, avl);
            if (avl == false)
                root = balance(root, avl);
            
        }
        else if (program == "D")
        {
            cin >> side;
            root = deleteNode(root, value, side, avl);
            if (avl == false)
                root = balance(root, avl);
        }
        else
        {
            struct node* searchedNode = searchNode(root, value);
            printHandlerInProgress(root, searchedNode, value);
            //output = printHandlerAfterProgress(root, searchedNode, value, output);
        }
    }
    //cout << output;
}

struct node* createTree(int value)
{
    struct node* n;
    n = new(struct node);
    n->data = value;
    n->height = 1;
    n->leftChild = NULL;
    n->rightChild = NULL;
    return n;
}

struct node* insertNode(struct node* root, int value, bool &avl)
{
    if (root == NULL)
        return(createTree(value));

    if (value < root->data)
        root->leftChild = insertNode(root->leftChild, value, avl);  

    else if (value > root->data)
        root->rightChild = insertNode(root->rightChild, value, avl);

    root->height = 1 + max(heightFinder(root->leftChild), heightFinder(root->rightChild));

    int balanceFacor = balanceFactorFinder(root);
    if (balanceFacor >= 2 || balanceFacor <= -2)
        avl = false;
    return root;
}

struct node* deleteNode(struct node* root, int value, string side, bool &avl)
{
    struct node* temp;
    if (root == NULL)
        return root;

    if (value < root->data)
        root->leftChild = deleteNode(root->leftChild, value, side, avl);

    else if (value > root->data)
        root->rightChild = deleteNode(root->rightChild, value, side, avl);

    else
    {
        if (root->leftChild == NULL)
        {
            temp = root->rightChild;
            free(root);
            return temp;
        }
        else if (root->rightChild == NULL)
        {
            temp = root->leftChild;
            free(root);
            return temp;
        }

        if (side == "R") {
            temp = findMin(root->rightChild);
            root->data = temp->data;
            root->rightChild = deleteNode(root->rightChild, temp->data, side, avl);
        }
        else if (side == "L")
        {
            temp = findMax(root->leftChild);
            root->data = temp->data;
            root->leftChild = deleteNode(root->leftChild, temp->data, side, avl);
        }
    }

    root->height = 1 + max(heightFinder(root->leftChild), heightFinder(root->rightChild));

    int balanceFacor = balanceFactorFinder(root);
    if (balanceFacor >= 2 || balanceFacor <= -2)
        avl = false;
    return root;
}

struct node* searchNode(struct node* root, int value)
{
    if (root == NULL || root->data == value)
        return root;

    if (root->data < value)
        return searchNode(root->rightChild, value);

    return searchNode(root->leftChild, value);
}

struct node *parentFinder(struct node* root, struct node *child, struct node *parent)
{
    if (root == NULL || root == child)
        return parent;
    if (root->data > child->data)
        return parentFinder(root->leftChild, child, root);
    else
        return parentFinder(root->rightChild, child, root);
}

int depthFinder(struct node *root, int value, int depth)
{
    if (root == NULL)
        return 0;
 
    if (root->data == value)
        return depth;
 
    int d = depthFinder(root->leftChild, value, depth+1);
    
    if (d != 0)
      return d;
 
    d = depthFinder(root->rightChild, value, depth+1);
    
    return d;
}

int heightFinder(struct node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

struct node* findMin(struct node* root)
{
    struct node* temp;

    temp = root;
    while (temp->leftChild != NULL)
        temp = temp->leftChild;

    return temp;
}

struct node* findMax(struct node* root)
{
    struct node* temp;

    temp = root;
    while (temp->rightChild != NULL)
        temp = temp->rightChild;

    return temp;
}

struct node* balance(struct node* root, bool &avl)
{
    struct node* temp = NULL;
    vector<int> nodeValues;
    inorder(root, nodeValues);
    temp = avlInsert(temp, nodeValues, avl);
    return temp;

}

struct node* avlInsert(struct node *h, vector<int> values, bool &avl)
{
    avl = true;
    int mid = values.size() / 2;
    if (!values.empty())
    {
        h = insertNode(h, values[mid], avl);
        vector<int> left(&values[0], &values[mid]);
        vector<int> right(&values[mid + 1], &values[values.size()]);
        avlInsert(h, left, avl);
        avlInsert(h, right, avl);
    }
    return h;
    
}

void inorder(struct node* root, vector<int>& vec)
{
    if (root != NULL)
    {
        inorder(root->leftChild, vec);
        vec.push_back(root->data);
        inorder(root->rightChild, vec);
    }
}

int balanceFactorFinder(struct node* root)
{
    if (root == NULL)
        return 0;
    return heightFinder(root->leftChild) - heightFinder(root->rightChild);
}

void printHandlerInProgress(struct node* root, struct node* node, int value)
{
    if (node != NULL) {
        cout << node->data << " " << depthFinder(root, value, 1) << " ";
        if (parentFinder(root, node, NULL) != NULL)
            cout << parentFinder(root, node, NULL)->data << " ";
        else
            cout << "N" << " ";
        if (node->leftChild != NULL)
            cout << node->leftChild->data << " ";
        else
            cout << "N" << " ";
        if (node->rightChild != NULL)
            cout << node->rightChild->data << " ";
        else
            cout << "N" << " ";
    }
    else
    {
        cout << value << " " << "N";
    }
    cout << endl;
}

string printHandlerAfterProgress(struct node *root, struct node* node, int value, string output)
{
    if (node != NULL) {
        output += to_string(node->data) + " " + to_string(depthFinder(root, value, 1)) + " ";
        if (parentFinder(root, node, NULL) != NULL)
            output += to_string(parentFinder(root, node, NULL)->data) + " ";
        else
            output += "N ";
        if (node->leftChild != NULL)
            output += to_string(node->leftChild->data) + " ";
        else
            output += "N ";
        if (node->rightChild != NULL)
            output += to_string(node->rightChild->data) + " ";
        else
            output += "N ";
    }
    else
        output += to_string(value) + " " + "N";

    output += "\n";
    return output;
}
 