
#include<iostream>
using namespace std;

class Node{
public:
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int value){
        data=value;
        height=1;
        left=NULL;
        right=NULL;
    }
};

class QueueNode{
public:
    Node* data;
    QueueNode* next;

    QueueNode(Node* value){
        data=value;
        next=NULL;
    }
};

class Queue{
private:
    QueueNode* front;
    QueueNode* rear;

public:
    Queue(){
        front=NULL;
        rear=NULL;
    }

    bool isEmpty(){
        return front==NULL;
    }

    void enqueue(Node* value){
        QueueNode* newNode=new QueueNode(value);

        if(rear==NULL){
            front=rear=newNode;
            return;
        }

        rear->next=newNode;
        rear=newNode;
    }

    Node* dequeue(){
        if(isEmpty()){
            return NULL;
        }

        QueueNode* temp=front;
        Node* value=temp->data;

        front=front->next;

        if(front==NULL){
            rear=NULL;
        }

        delete temp;
        return value;
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
    while(root->left!=NULL){
        root=root->left;
    }

    return root;
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
                delete root;
                return NULL;
            }
            else{
                Node* oldRoot=root;
                root=temp;
                delete oldRoot;
            }
        }
        else{
            Node* temp=findMin(root->right);
            root->data=temp->data;
            root->right=deleteNode(root->right,temp->data);
        }
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

void printLevelOrder(Node* root){
    if(root==NULL){
        return;
    }

    Queue q;
    q.enqueue(root);

    cout<<"Level Order: ";

    while(!q.isEmpty()){
        Node* current=q.dequeue();

        cout<<current->data<<"(BF="<<getBalance(current)<<") ";

        if(current->left!=NULL){
            q.enqueue(current->left);
        }

        if(current->right!=NULL){
            q.enqueue(current->right);
        }
    }

    cout<<endl;
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

    int values[5]={10,20,30,40,50};

    cout<<"Inserting five values:"<<endl;

    for(int i=0;i<5;i++){
        root=insert(root,values[i]);
        cout<<values[i]<<" ";
    }

    cout<<endl<<endl;

    cout<<"Deleting two values:"<<endl;

    root=deleteNode(root,10);
    cout<<"Deleted: 10"<<endl;

    root=deleteNode(root,20);
    cout<<"Deleted: 20"<<endl;

    cout<<endl;

    printLevelOrder(root);

    cout<<endl;
    cout<<"AVL Balance Verification:"<<endl;

    cout<<"Every balance factor must be -1, 0, or 1."<<endl;

    freeTree(root);

    return 0;
}
