#include <iostream>
#include <vector>

using namespace std;

//Basics of Doubly Linked Lists
class Node {
    public:
    int data;
    Node* next;
    Node* back;

    public:
    Node(int data1, Node* next1,Node* back1){
        data=data1;
        next = next1;
        back = back1;
    }

    public:
    Node(int data1){
        data =data1;
        next=nullptr;
        back=nullptr;
    }

};

//Converting An Array to DLL
Node* covertArrtoDLL(vector<int> &arr){
    Node* head= new Node(arr[0]);
    Node* prev=head;
    for(int i =1;i<arr.size();i++){
        Node* temp= new Node(arr[i],nullptr,prev);
        prev->next=temp;
        prev=temp;
    }

    return head;
}


//Deletion
//Head
Node* delHead(Node* head){
    if(head==NULL) return NULL;
    if(head->next==NULL) return NULL;

    Node* prev =head;
    head=head->next;
    head->back=nullptr;
    prev->next=nullptr;
    delete prev;
    return head;
}
//Tail
Node* delTail(Node* head){
    Node* tail= head;

    while(tail->next!= NULL){
        tail=tail->next;
    }
    Node* prev = tail->back;
    prev->next=nullptr;
    tail->back=nullptr;
    delete tail;
    return head;
}
//Kth Element
Node* delKthel(Node* head, int k){
    if(head==NULL) return NULL;
    int cnt=0;
    Node* KNode= head;
    while(KNode!= NULL){
        cnt++;
        if(k==cnt) break;

        KNode= KNode->next;
    }
    Node* prev = KNode->back;
    Node* forw= KNode->next;
    if(prev==NULL && forw==NULL) return NULL;
    if(prev==NULL) return delHead(head);
    if(forw==NULL) return delTail(head);

    prev->next=forw;
    forw->back=prev;

    KNode->next=nullptr;
    KNode->back=nullptr;
    delete KNode;   
    return head;
}
//Node
void delNode(Node* temp){
    Node* prev = temp->back;
    Node* forw= temp->next;

    if(forw==NULL){
        prev->next=nullptr;
        temp->back=nullptr;
        free(temp);
        return;
    }
    prev->next=forw;
    forw->back=prev;

    temp->back=temp->next=nullptr;
    free(temp);
}


//Insertion(Before)
//Head
Node* insertBefHead(Node* head,int val){
    Node* newHead= new Node(val,head,nullptr);
    head->back=newHead;
    return newHead;
}
//Tail
Node* insertBefTail(Node* head, int val){
    if(head->next==NULL) return insertBefHead(head,val);
    Node* tail= head;

    while(tail->next!=NULL){
        tail=tail->next;
    }
    Node* prev = tail->back;
    Node* newNode= new Node(val,tail,prev);
    prev->next=newNode;
    tail->back=newNode;
    return head;
}
//Kth Element
Node* insertBefKth(Node* head, int val, int k){
    if(k==1) return insertBefHead(head, val);
    Node* temp= head;
    int cnt=0;
    while(temp!=NULL){
        cnt++;
        if(cnt==k)break;
        temp=temp->next;
    }
    Node* prev=temp->back;
    Node* newNode= new Node(val,temp,prev);
    prev->next=newNode;
    temp->back=newNode;
    return head;
}
//Node
void insertBefNode(Node* node, int val){
    Node* prev = node->back;
    Node* newNode= new Node(val,node,prev);
    prev->next=newNode;
    node->back=newNode;
}

//Reversing a DLL
Node* reverseDLL(Node* head){
    if(head==NULL || head->next==NULL){
        return head;
    }
    Node* prev = NULL;
    Node* current=head;
    while(current!=NULL){
        prev=current->back;
        current->back=current->next;
        current->next=prev;

        current=current->back;
    }
    return prev->back;
}

//Delete All Occurances
Node* Deletealloccurance(Node* head,int key){
    Node* temp =head;
    while(temp!=NULL){
        if(temp->data==key){
            if(temp==head){
                head=temp->next;
            }
            Node* nextNode = temp->next;
            Node* prevNode = temp->back;
            if(nextNode!=NULL) nextNode->back= prevNode;
            if(prevNode!=NULL) prevNode->next=nextNode;
            free(temp);
            temp=temp->next;
        }else{
            temp=temp->next;
        }
        
    }
    return head;

}
//Find pairs with given sum in DLL
Node* findTail(Node* head){
    Node* tail = head;
    while(tail->next!=NULL) tail=tail->next;
    return tail;
}
vector<pair<int,int>> findpairsDLL(Node* head,int k){
    vector<pair<int,int>> ans;
    if(head==NULL) return ans;
    Node* left = head;
    Node* right = findTail(head);
    while(left->data < right->data){
        if(left->data+right->data==k){
            ans.push_back({left->data,right->data});
            left=left->next;
            right=right->back;
        }
        else if(left->data+right->data<k){
            left= left->next;
        }else right= right->back;
    }
    return ans;
}