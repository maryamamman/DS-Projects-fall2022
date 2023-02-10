#include<iostream>
#include<string>
using namespace std;

struct node
{
    int data;
    struct node* leftChild;
    struct node* rightChild;
};

//Operations that can be performed on the tree nodes:
struct node* createTree(int value);
struct node* insertNode(struct node* root, int value);
struct node* deleteNode(struct node* root, int value, string side);
struct node* searchNode(struct node* root, int value);
struct node* parentFinder(struct node* root, struct node *child, struct node *parent);
int depthFinder(struct node *root, int value, int depth);

//Functions required in other functions:
struct node* findMin(struct node* root);
struct node* findMax(struct node* root);

//Output format handlers:
void printHandlerInProgress(struct node* root, struct node* node, int value);
string printHandlerAfterProgress(struct node *root, struct node* node, int value, string output);

int main()
{
    string output = "";
    struct node* root = NULL;
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
            root = insertNode(root, value);
        else if (program == "D")
        {
            cin >> side;
            root = deleteNode(root, value, side);
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
    struct node* node;
    node = new(struct node);
    node->data = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

struct node* insertNode(struct node* root, int value)
{
    if (root == NULL)
        return createTree(value);
    if (value < root->data)
    {
        root->leftChild = insertNode(root->leftChild, value);
    }

    else if (value > root->data)
    {
        root->rightChild = insertNode(root->rightChild, value);
    }
    return root;
}

struct node* deleteNode(struct node* root, int value, string side)
{
    struct node* temp;
    if (root == NULL) return root;

    if (value < root->data)
        root->leftChild = deleteNode(root->leftChild, value, side);

    else if (value > root->data)
        root->rightChild = deleteNode(root->rightChild, value, side);

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

        if (side == "R")
        {
            temp = findMin(root->rightChild);

            root->data = temp->data;

            root->rightChild = deleteNode(root->rightChild, temp->data, side);
        }
        else if (side == "L")
        {
            temp = findMax(root->leftChild);

            root->data = temp->data;

            root->leftChild = deleteNode(root->leftChild, temp->data, side);
        }

    }
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

