#include <iostream>
using namespace std;

class Node {
    public:
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
    if (node == NULL)
        return new Node(value);
    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    return node;
}

void inorder(Node* node){
    if (node == NULL)
        return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

int countRange(Node* node, int lower, int upper){
    if (node == NULL)
        return 0;
    if (node->data < lower)
        return countRange(node->right, lower, upper);
    if (node->data > upper)
        return countRange(node->left, lower, upper);
    return 1 + countRange(node->left, lower, upper) + countRange(node->right, lower, upper);
}

Node* trim(Node* node, int lower, int upper){
    if (node == NULL)
        return NULL;
    if (node->data < lower){
        Node* rightPart = trim(node->right, lower, upper);
        Node* leftPart = node->left;

        node->left = NULL;
        node->right = NULL;

        trim(leftPart, upper + 1, upper);
        delete node;
        return rightPart;
    }

    if (node->data > upper){
        Node* leftPart = trim(node->left, lower, upper);
        Node* rightPart = node->right;

        node->left = NULL;
        node->right = NULL;
        trim(rightPart, upper + 1, upper);

        delete node;
        return leftPart;
    }
    node->left = trim(node->left, lower, upper);
    node->right = trim(node->right, lower, upper);
    return node;
}

int main(){
    Node* root = NULL;
    int values[] = {50, 25, 75, 10, 30, 60, 90, 20, 40, 70, 80};
    int lower = 25;
    int upper = 70;

    for(int i = 0; i < 11; i++)
        root = insert(root, values[i]);

    cout << "IDs in range: ";
    inorder(root);
    cout << endl;

    cout << "Count: " << countRange(root, lower, upper) << endl;

    root = trim(root, lower, upper);
    cout << "After deleting outside range: ";
    inorder(root);
    cout << endl;
    return 0;
}