#include <iostream>
using namespace std;

struct Node{
    int data;
    Node *left;
    Node *right;

    Node(int value){
        data = value;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node* node, int value){
    if(node == NULL)
        return new Node(value);
    if(value < node->data)
        node->left = insert(node->left, value);
    else if(value > node->data)
        node->right = insert(node->right, value);
    return node;
}

void inorder(Node* node){
    if(node == NULL)
        return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

int findMinValue(Node* node){
    while(node->left != NULL)
        node = node->left;
    return node->data;
}

int findMaxValue(Node* node){
    while(node->right != NULL)
        node = node->right;
    return node->data;
}

void printGreaterThan(Node* node, float threshold){
    if(node == NULL)
        return;
    printGreaterThan(node->left, threshold);
    if(node->data > threshold)
        cout << node->data << " ";
    printGreaterThan(node->right, threshold);
}

int countTwoChildren(Node* node){
    if(node == NULL)
        return 0;
    int count = 0;
    if(node->left != NULL && node->right != NULL)
        count = 1;
    return count + countTwoChildren(node->left) + countTwoChildren(node->right);
}

int height(Node* node){
    if(node == NULL)
        return -1;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    if(leftHeight > rightHeight)
        return leftHeight + 1;
    return rightHeight + 1;
}

void printLongestPath(Node* node){
    if(node == NULL)
        return;
    cout << node->data;
    if(node->left == NULL && node->right == NULL)
        return;
    cout << " -> ";
    if(height(node->left) >= height(node->right))
        printLongestPath(node->left);
    else
        printLongestPath(node->right);
}

bool isSkewed(Node* node){
    if(node == NULL)
        return true;
    if(node->left != NULL && node->right != NULL)
        return false;
    return isSkewed(node->left) && isSkewed(node->right);
}

Node* deleteOneChildNodes(Node* node, int& deletedCount){
    if(node == NULL)
        return NULL;
    bool hadOneChild = (node->left == NULL) != (node->right == NULL);
    node->left = deleteOneChildNodes(node->left, deletedCount);
    node->right = deleteOneChildNodes(node->right, deletedCount);

    if(hadOneChild){
        Node* child = node->left;
        if(child == NULL)
            child = node->right;
        delete node;
        deletedCount++;
        return child;
    }
    return node;
}

bool isValidBST(Node* node, Node* minNode, Node* maxNode){
    if(node == NULL)
        return true;
    if(minNode != NULL && node->data <= minNode->data)
        return false;
    if(maxNode != NULL && node->data >= maxNode->data)
        return false;
    return isValidBST(node->left, minNode, node) && isValidBST(node->right, node, maxNode);
}

int kthSmallest(Node* node, int& k){
    if(node == NULL)
        return -1;

    int result = kthSmallest(node->left, k);
    if(result != -1)
        return result;
    k--;
    if(k == 0)
        return node->data;
    return kthSmallest(node->right, k);
}

int main(){
    Node* root = NULL;
    int marks[] = {45, 25, 65, 15, 35, 55, 75, 10, 30, 40, 60, 80, 32, 33};
    for(int i = 0; i < 14; i++)
        root = insert(root, marks[i]);

    int k;
    cout << "Enter k: ";
    cin >> k;

    cout << "Original inorder: ";
    inorder(root);
    cout << endl;

    int minimum = findMinValue(root);
    int maximum = findMaxValue(root);
    double threshold = (minimum + maximum) / 2.0;

    cout << "Minimum mark: " << minimum << endl;
    cout << "Maximum mark: " << maximum << endl;
    cout << "Threshold: " << threshold << endl;

    cout << "Marks greater than threshold: ";
    printGreaterThan(root, threshold);
    cout << endl;

    cout << "Nodes with two children: " << countTwoChildren(root) << endl;

    cout << "Longest root-to-leaf path: ";
    printLongestPath(root);
    cout << " (" << height(root) << " edges)" << endl;

    cout << "Is tree skewed? ";
    if(isSkewed(root))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    int deletedCount = 0;
    root = deleteOneChildNodes(root, deletedCount);

    cout << "Nodes deleted: " << deletedCount << endl;
    cout << "Final inorder: ";
    inorder(root);
    cout << endl;

    if(!isValidBST(root, NULL, NULL))
        cout << "[BST INVALID!]" << endl;

    int remaining = k;
    int answer = kthSmallest(root, remaining);
    if(answer == -1)
        cout << k << "th smallest remaining mark: not available" << endl;
    else
        cout << k << "th smallest remaining mark: " << answer << endl;

    return 0;
}