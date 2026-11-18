
#include <iostream>

using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value){
        data=value;
        left=NULL;
        right=NULL;
    }
};

class ListNode{
public:
    int data;
    ListNode* next;

    ListNode(int value){
        data=value;
        next=NULL;
    }
};

Node* insert(Node* root,int value){
    if(root==NULL) return new Node(value);

    if(value<root->data) root->left=insert(root->left,value);
    else if(value>root->data) root->right=insert(root->right,value);

    return root;
}

void inorderToList(Node* root,ListNode* &head,ListNode* &tail){
    if(root==NULL) return;

    inorderToList(root->left,head,tail);

    ListNode* newNode=new ListNode(root->data);

    if(head==NULL){
        head=newNode;
        tail=newNode;
    }
    else{
        tail->next=newNode;
        tail=newNode;
    }

    inorderToList(root->right,head,tail);
}

int countList(ListNode* head){
    int count=0;

    while(head!=NULL){
        count++;
        head=head->next;
    }

    return count;
}

Node* buildBalancedTree(ListNode* &head,int n){
    if(n<=0) return NULL;

    Node* leftSubtree=buildBalancedTree(head,n/2);

    Node* root=new Node(head->data);
    root->left=leftSubtree;

    head=head->next;

    root->right=buildBalancedTree(head,n-n/2-1);

    return root;
}

Node* balanceExistingBST(Node* root){
    ListNode* head=NULL;
    ListNode* tail=NULL;

    inorderToList(root,head,tail);

    int n=countList(head);

    Node* balancedRoot=buildBalancedTree(head,n);

    while(head!=NULL){
        ListNode* temp=head;
        head=head->next;
        delete temp;
    }

    return balancedRoot;
}

int height(Node* root){
    if(root==NULL) return -1;

    int leftHeight=height(root->left);
    int rightHeight=height(root->right);

    return 1+(leftHeight>rightHeight?leftHeight:rightHeight);
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

    int n;
    cin>>n;

    for(int i=0;i<n;i++){
        int value;
        cin>>value;
        root=insert(root,value);
    }

    cout<<"Height before balancing: "<<height(root)<<endl;

    Node* balancedRoot=balanceExistingBST(root);

    cout<<"Height after balancing: "<<height(balancedRoot)<<endl;

    cout<<"Balanced BST: ";
    preorder(balancedRoot);
    cout<<endl;

    freeTree(root);
    freeTree(balancedRoot);

    return 0;
}
