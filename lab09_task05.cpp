
#include<iostream>
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
    if(root==NULL){
        return 0;
    }
    return root->height;
}

int getBalance(Node* root){
    if(root==NULL){
        return 0;
    }
    return getHeight(root->left)-getHeight(root->right);
}

void updateHeight(Node* root){
    int leftHeight=getHeight(root->left);
    int rightHeight=getHeight(root->right);

    if(leftHeight>rightHeight){
        root->height=leftHeight+1;
    }
    else{
        root->height=rightHeight+1;
    }
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
    if(root==NULL){
        return new Node(value);
    }

    if(value<root->data){
        root->left=insert(root->left,value);
    }
    else if(value>root->data){
        root->right=insert(root->right,value);
    }
    else{
        return root;
    }

    updateHeight(root);

    int balance=getBalance(root);

    if(balance>1 && value<root->left->data){
        return rightRotate(root);
    }

    if(balance<-1 && value>root->right->data){
        return leftRotate(root);
    }

    if(balance>1 && value>root->left->data){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance<-1 && value<root->right->data){
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* findMin(Node* root){
    Node* current=root;

    while(current->left!=NULL){
        current=current->left;
    }

    return current;
}

Node* deleteNode(Node* root,int value){
    if(root==NULL){
        return root;
    }

    if(value<root->data){
        root->left=deleteNode(root->left,value);
    }
    else if(value>root->data){
        root->right=deleteNode(root->right,value);
    }
    else{
        if(root->left==NULL || root->right==NULL){
            Node* temp;

            if(root->left!=NULL){
                temp=root->left;
            }
            else{
                temp=root->right;
            }

            if(temp==NULL){
                temp=root;
                root=NULL;
            }
            else{
                *root=*temp;
            }

            delete temp;
        }
        else{
            Node* temp=findMin(root->right);
            root->data=temp->data;
            root->right=deleteNode(root->right,temp->data);
        }
    }

    if(root==NULL){
        return root;
    }

    updateHeight(root);

    int balance=getBalance(root);

    if(balance>1 && getBalance(root->left)>=0){
        return rightRotate(root);
    }

    if(balance>1 && getBalance(root->left)<0){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance<-1 && getBalance(root->right)<=0){
        return leftRotate(root);
    }

    if(balance<-1 && getBalance(root->right)>0){
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preorder(Node* root){
    if(root==NULL){
        return;
    }

    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

void freeTree(Node* root){
    if(root==NULL){
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main(){
    Node* root=NULL;
    int n,value,del;

    cout<<"Enter number of nodes: ";
    cin>>n;

    cout<<"Enter values: ";
    for(int i=0;i<n;i++){
        cin>>value;
        root=insert(root,value);
    }

    cout<<"Enter value to delete: ";
    cin>>del;

    root=deleteNode(root,del);

    cout<<"Preorder after deletion: ";
    preorder(root);
    cout<<endl;

    cout<<"Root after deletion: ";
    if(root!=NULL){
        cout<<root->data<<endl;
    }
    else{
        cout<<"Empty"<<endl;
    }

    cout<<"Height after deletion: "<<getHeight(root)-1<<endl;

    freeTree(root);

    return 0;
}
