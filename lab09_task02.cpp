
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

    if(balance<-1 && value>root->right->data){
        cout<<"Right-Right imbalance at "<<root->data<<endl;
        return leftRotate(root);
    }

    if(balance>1 && value<root->left->data){
        cout<<"Left-Left imbalance at "<<root->data<<endl;
        return rightRotate(root);
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
    Node* root1=NULL;
    Node* root2=NULL;

    int sequence1[]={30,35,45};
    int sequence2[]={13,10,5};

    cout<<"Sequence 1:"<<endl;

    for(int i=0;i<3;i++){
        root1=insert(root1,sequence1[i]);
    }

    cout<<"Balanced root: "<<root1->data<<endl;
    cout<<"Preorder: ";
    preorder(root1);
    cout<<endl;

    cout<<endl<<"Sequence 2:"<<endl;

    for(int i=0;i<3;i++){
        root2=insert(root2,sequence2[i]);
    }

    cout<<"Balanced root: "<<root2->data<<endl;
    cout<<"Preorder: ";
    preorder(root2);
    cout<<endl;

    freeTree(root1);
    freeTree(root2);

    return 0;
}
