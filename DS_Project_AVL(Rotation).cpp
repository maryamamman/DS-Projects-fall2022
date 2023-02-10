#include<iostream>
#include<string>
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
struct node* insertNode(struct node* root, int value);
struct node* deleteNode(struct node* root, int value, string side);
struct node* searchNode(struct node* root, int value);
struct node* parentFinder(struct node* root, struct node *child, struct node *parent);
int depthFinder(struct node *root, int value, int depth);
int heightFinder(struct node *node);

//Functions required in other functions:
struct node* rightRotation(struct node *root);
struct node* leftRotation(struct node *root);
struct node* findMin(struct node* root);
struct node* findMax(struct node* root);
int balanceFactorFinder(struct node *root);

//Output format handlers:
void printHandlerInProgress(struct node* root, struct node* node, int value);
string printHandlerAfterProgress(struct node *root, struct node* node, int value, string output);

int main()
{
    string output = "";
    struct node* root = NULL;
    int programNum;
    cin >> programNum;
    for (int i = 0; i < programNum; i++)
    {
        int value;
        string program;
        string side = "";
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
            //printHandlerInProgress(searchedNode, value);
            output = printHandlerAfterProgress(root, searchedNode, value, output);
        }
    }
    cout << output;
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

struct node* insertNode(struct node* root, int value)
{
    if (root == NULL)
        return(createTree(value));
    if (value < root->data)
    {
        root->leftChild  = insertNode(root->leftChild, value);
    }
    else if (value > root->data)
    {
        root->rightChild = insertNode(root->rightChild, value);
    }
    else 
        return root;
 
    root->height = 1 + max(heightFinder(root->leftChild), heightFinder(root->rightChild));
 
    int balanceFacor = balanceFactorFinder(root);
 
    //LL
    if (balanceFacor >=2 && value < root->leftChild->data)
        return rightRotation(root);
 
    //RR
    if (balanceFacor <=-2 && value > root->rightChild->data)
        return leftRotation(root);
 
    //LR
    if (balanceFacor >=2 && value > root->leftChild->data)
    {
        root->leftChild =  leftRotation(root->leftChild);
        return rightRotation(root);
    }
 
    //RL
    if (balanceFacor <=-2 && value < root->rightChild->data)
    {
        root->rightChild = rightRotation(root->rightChild);
        return leftRotation(root);
    }
 
    return root;
}

struct node* deleteNode(struct node* root, int value, string side)
{
    struct node* temp;
	if (root == NULL)
        return root;
    if ( value < root->data )
        root->leftChild = deleteNode(root->leftChild, value, side);
    else if( value > root->data )
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
        
        if (side == "R"){
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

    if (root == NULL)
      return root;
    
    root->height = 1 + max(heightFinder(root->leftChild), heightFinder(root->rightChild));
 
    int balanceFactor = balanceFactorFinder(root);
 
    if (balanceFactor > 1 && balanceFactorFinder(root->leftChild) >= 0)
        return rightRotation(root);
 
    if (balanceFactor > 1 && balanceFactorFinder(root->leftChild) < 0)
    {
        root->leftChild =  leftRotation(root->leftChild);
        return rightRotation(root);
    }
 
    if (balanceFactor < -1 && balanceFactorFinder(root->rightChild) <= 0)
        return leftRotation(root);
 
    if (balanceFactor < -1 && balanceFactorFinder(root->rightChild) > 0)
    {
        root->rightChild = rightRotation(root->rightChild);
        return leftRotation(root);
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

int heightFinder(struct node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

struct node *rightRotation(struct node *root)
{
    struct node *newRoot,*temp;
	
	newRoot = root->leftChild;
    temp = newRoot->rightChild;
 
    newRoot->rightChild = root;
    root->leftChild = temp;
 
    root->height = max(heightFinder(root->leftChild), heightFinder(root->rightChild)) + 1;
    newRoot->height = max(heightFinder(newRoot->leftChild), heightFinder(newRoot->rightChild)) + 1;
    return newRoot;
}

struct node *leftRotation(struct node *root)
{
    struct node *newRoot,*temp;
	
	newRoot = root->rightChild;
    temp = newRoot->leftChild;
 
    newRoot->leftChild = root;
    root->rightChild = temp;
 
    root->height = 1 + max(heightFinder(root->leftChild), heightFinder(root->rightChild)) ;
    newRoot->height = 1 + max(heightFinder(newRoot->leftChild), heightFinder(newRoot->rightChild)) ;
    return newRoot;
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

int balanceFactorFinder(struct node *root)
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

