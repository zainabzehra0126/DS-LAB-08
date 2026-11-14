#include <iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *left;
    Node *right;

    Node(int v) : data(v), left(NULL), right(NULL){}
};

Node* insert(Node* root, int value){
    if (root == NULL)
        return new Node(value);
    if (value < root->data)
        root->left  = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}

void preorder(Node* node){
    if (!node)
        return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

void inorder(Node* node){
    if (!node)
        return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

void postorder(Node* node){
    if (!node)
        return;
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}

int countOneChild(Node* node){
    if (!node) 
        return 0;
    int self = ((node->left == NULL) != (node->right == NULL)) ? 1 : 0;
    return self + countOneChild(node->left) + countOneChild(node->right);
}

int countTwoChildren(Node* node){
    if (!node) return 0;
    int self = (node->left && node->right) ? 1 : 0;
    return self + countTwoChildren(node->left) + countTwoChildren(node->right);
}

int height(Node* node){
    if (!node)
        return -1;
    int l = height(node->left), rt = height(node->right);
    return 1 + (l > rt ? l : rt);
}

int main(){
    int scores[] ={45, 25, 65, 15, 35, 55, 75, 30};
    Node* root = NULL;
    for (int i = 0; i < 8; i++)
        root = insert(root, scores[i]);

    cout << "Preorder: ";  preorder(root);  cout << endl;
    cout << "Inorder: ";   inorder(root);   cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;
    cout << "Nodes with one child: "  << countOneChild(root)  << endl;
    cout << "Nodes with two children: " << countTwoChildren(root) << endl;
    cout << "Height: " << height(root) << endl;
    return 0;
}