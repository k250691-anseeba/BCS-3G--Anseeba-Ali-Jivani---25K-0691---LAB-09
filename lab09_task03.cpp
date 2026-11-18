
#include <iostream>

using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value){
        data=value;
        left=NULL;
        right=NULL;
        height=1;
    }
};

int getHeight(Node* root){
    if(root==NULL) return 0;
    return root->height;
}

int getBalance(Node* root){
    if(root==NULL) return 0;
    return getHeight(root->left)-getHeight(root->right);
}

void updateHeight(Node* root){
    int leftHeight=getHeight(root->left);
    int rightHeight=getHeight(root->right);

    root->height=1+(leftHeight>rightHeight?leftHeight:rightHeight);
}

Node* rightRotate(Node* y){
    Node* x=y->left;
    Node* temp=x->right;

    x->right=y;
    y->left=temp;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node* x){
    Node* y=x->right;
    Node* temp=y->left;

    y->left=x;
    x->right=temp;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node* root,int value){
    if(root==NULL) return new Node(value);

    if(value<root->data) root->left=insert(root->left,value);
    else if(value>root->data) root->right=insert(root->right,value);
    else return root;

    updateHeight(root);

    int balance=getBalance(root);

    if(balance>1 && value>root->left->data){
        cout<<"Left-Right imbalance at "<<root->data<<endl;
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance<-1 && value<root->right->data){
        cout<<"Right-Left imbalance at "<<root->data<<endl;
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preorder(Node* root){
    if(root==NULL) return;

    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void freeTree(Node* root){
    if(root==NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main(){
    Node* root=NULL;

    int values[]={13,10,11};

    for(int i=0;i<3;i++){
        root=insert(root,values[i]);
    }

    cout<<"Final root: "<<root->data<<endl;
    cout<<"Preorder: ";
    preorder(root);
    cout<<endl;
    cout<<"Height: "<<root->height-1<<endl;

    freeTree(root);

    return 0;
}
