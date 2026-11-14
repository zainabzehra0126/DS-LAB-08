#include <iostream>
using namespace std;

class Node{
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
    if(node == NULL)
        return new Node(value);
    if(value < node->data)
        node->left = insert(node->left, value);
    else if(value > node->data)
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

Node* findMin(Node* node){
    while(node != NULL && node->left != NULL)
        node = node->left;
    return node;
}

Node* deleteNode(Node* node, int key){
    if(node == NULL)
        return node;
    if(key < node->data)
        node->left = deleteNode(node->left, key);
    else if(key > node->data)
        node->right = deleteNode(node->right, key);
    else{
        if(node->left == NULL){
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if(node->right == NULL){
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data);
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

int main(){
    Node* root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80, 35, 45};
    int deleteValues[] = {20, 30, 50};

    for(int i = 0; i < 9; i++)
        root = insert(root, values[i]);

    for(int i = 0; i < 3; i++){
        root = deleteNode(root, deleteValues[i]);

        cout << "After deleting " << deleteValues[i] << ": ";
        inorder(root);
        if(!isValidBST(root, NULL, NULL))
            cout << " [BST INVALID!]";
        cout << endl;
    }
    return 0;
}