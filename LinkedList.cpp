#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;



//Basics of Linked Lists
class ListNode {
    public:
    int data;
    ListNode* next;

    public:
    ListNode(int data1, ListNode* next1){
        data=data1;
        next = next1;
    }

    public:
    ListNode(int data1){
        data =data1;
        next=nullptr;
    }

};
//Converting An Array to LL
ListNode* covertArrtoLL(vector<int> &arr){
    ListNode* head= new ListNode(arr[0]);

    ListNode* mover = head;

    for(int i =0;i<arr.size();i++){
        ListNode* temp = new ListNode(arr[i]);
        mover->next = temp;
        mover = temp; 
    }

    return head;
}

//Traversing through a LL
void TraverseLL(ListNode* head){
    ListNode* temp = head;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
}

//Length of LL
int LengthLL(ListNode* head){
    ListNode* temp = head;
    int count=0;
    while(temp){
        temp = temp->next;
        count++;
    }
    return count;   
}

//Deletion
//Head
ListNode* removeHead(ListNode* head){
    if(head == NULL) return head;
    ListNode* temp = head;
    head = head->next;
    delete temp;
    return head;
}
//Tail
ListNode* removeTail(ListNode* head){
    if(head== NULL || head->next==NULL) return NULL;

    ListNode* temp=head;
    while (temp->next->next != NULL)
    {
        temp=temp->next;
    }
    delete temp->next;
    temp->next = nullptr;

    return head;
}
//Kth Element
ListNode* removeK(ListNode* head, int k){
    if(head==NULL) return head;

    if(k==1){
        ListNode* temp = head;
        head=head->next;
        free(temp);
        return head; 
    }
    int cnt=0;
    ListNode* temp= head;
    ListNode* prev=NULL;
    while(temp != NULL){
        cnt++;
        if(cnt==k){
            prev->next= prev->next->next;
            free(temp);
            break;
        }
        prev=temp;
        temp=temp->next;
    }
    return head;
}
//A specific Value
ListNode* removeVAl(ListNode* head, int val){
    if(head==NULL) return head;

    if(head->data==val){
        ListNode* temp = head;
        head=head->next;
        free(temp);
        return head; 
    }
    ListNode* temp= head;
    ListNode* prev=NULL;
    while(temp != NULL){
        if(temp->data==val){
            prev->next= prev->next->next;
            free(temp);
            break;
        }
        prev=temp;
        temp=temp->next;
    }
    return head;
}


//Insertion
//head
ListNode* insertHead(ListNode* head,int val){
    ListNode * temp = new ListNode(val,head);
    return temp;    
}

//TAil
ListNode* insertTail(ListNode* head, int val){
    if(head==NULL){
        return new ListNode(val);
    }
    ListNode* temp= head;
    while(temp->next != NULL){
        temp=temp->next;
    }
    ListNode* newListNode= new ListNode(val);
    temp->next=newListNode;

    return head;
}
//Kth Elemnt
ListNode* insertKth(ListNode* head, int val,int k){
    if(head==NULL){
        if(k==1) return new ListNode(val);
        return NULL;
    }

    if(k==1){
        return new ListNode(val,head);
    }
    int cnt=0;
    ListNode* temp=head;

    while(temp!=NULL){
        cnt++;
        if(cnt==k-1){
            ListNode* newListNode= new ListNode(val,temp->next);
            temp->next=newListNode;
            break;
        }
        temp=temp->next;
    }
    return head;
}
//Insering value(val) before elemnt X
ListNode* insertBeforeVal(ListNode* head, int val,int x){
    if(head==NULL){
        return NULL;
    }

    if(head->data==x){
        return new ListNode(val,head);
    }
    ListNode* temp=head;

    while(temp->next!=NULL){
        if(temp->next->data==x){
            ListNode* newListNode= new ListNode(val,temp->next);
            temp->next=newListNode;
            break;
        }
        temp=temp->next;
    }
    return head;
}



//Problems

//Finding Middle element
//Brute Force
ListNode* middleel_brute(ListNode* head){
    ListNode* temp=head;
    int cnt=0,middle;

    while(temp!=NULL){
        cnt++;
        temp=temp->next;
    }
    middle=(cnt/2)+1;
    temp=head;

    while(temp !=NULL){
        middle=middle-1;
        if(middle==0) break;
        temp=temp->next;
    }
    return temp;
}
//Optimal
//Tortoise & Hare Algorithm
ListNode* midleel_optimal(ListNode* head){
    if (head==nullptr || head->next==nullptr) return head;//Necessary for less time complexity
    ListNode* slow =head;
    ListNode* fast = head;

    while(fast!=NULL && fast->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}

//Reversing a LL
ListNode* reverseLL(ListNode* head){
    if(head==NULL || head->next==NULL) return head;
    ListNode* temp= head;
    ListNode* prev= NULL;
    ListNode* front;
    
    while(temp!=NULL){
        front=temp->next;
        temp->next=prev;
        prev=temp;
        temp=front;
    }
    return prev;
}
//Recurvise Method
ListNode* reverseLL_recursive(ListNode* head){
    if(head==NULL || head->next==NULL) return head;

    ListNode* newHead= reverseLL_recursive(head->next);

    ListNode* front = head->next;
    front->next=head;
    head->next=NULL;
    return newHead;
}

//Detecting a loop in LL
//Brute- Storing each node in a map, checking if i have encounter that node earlier
//Optimal Method - Tortoise or Hare method(fast & slow pointer)
// The earlier approach of using a hash map requires extra memory, which becomes costly when the linked list is very large. 
// To optimize space, we use the Tortoise and Hare Algorithm (Floyd’s Cycle Detection). If the list contains a loop, both pointers will eventually enter the cycle. 
// Since the hare is faster, it covers more distance and will eventually overtake the tortoise inside the loop, leading to a meeting point. On the other hand, 
// if the list has no loop, the hare will simply reach the end, and the algorithm terminates without any meeting.

bool hasCycle(ListNode *head) {
    ListNode* slow=head;
    ListNode* fast=head;
    
    while(fast!=NULL && fast->next==NULL){
        slow=slow->next;
        fast= fast->next->next;
        if(slow==fast)  return true;
    }
    return false;
}

//Finding starting pt of loop in LL
//Brute

ListNode* startloop_brute(ListNode* head){
    ListNode* temp=head;
    unordered_map<ListNode*,int> mpp ;
    while(temp!=NULL){
        if(mpp[temp]==1){
            return temp;
        }
        mpp[temp]=1;
        temp=temp->next;
    }
    return NULL;
}
//VVVVIMP Intuition
//Optimal method(Tortiose & Hare method)
// To detect a cycle using the Tortoise and Hare method, we start by initializing two pointers, slow and fast, at the head of the linked list.
// The slow pointer moves forward one step at a time, while the fast pointer advances two steps at a time.
// If the fast pointer or its next becomes null, it means the end of the linked list has been reached. In this case, there is no loop, and the list is linear.
// If the slow and fast pointers eventually meet at the same node, it confirms that a cycle exists in the linked list.
// Storing the entire node in the map is essential to distinguish between nodes with identical values but different positions in the list. This ensures accurate loop detection and not just duplicate value checks.

ListNode* startloop_optimal(ListNode* head){
    ListNode* fast=head;
    ListNode* slow=head;

    while(fast->next!=NULL && fast!=NULL){
        fast=fast->next->next;
        slow=slow->next;
        if(slow==fast){
            slow=head;
            while(slow!=fast){
                slow=slow->next;
                fast=fast->next;
            }
            return slow;
        }
    }
    return NULL;
}

//Lenghth of loop of LL


int lenofloop_LL(ListNode* head){
    ListNode* fast=head;
    ListNode* slow=head;
    int d=0, l1=0,l=0;
    while(fast->next!=NULL && fast!=NULL){
        fast=fast->next->next;
        slow=slow->next;
        l1++;
        if(slow==fast){
            slow=head;
            while(slow!=fast){
                slow=slow->next;
                fast=fast->next;
                d++;
            }
            l=d+l1;
            return l;
        }
    }
    return NULL;
}

//Check if LL is a palindrome
//Brute - Storing elements in a stack*

bool ispalindrome_brute(ListNode* head){
    stack<int> st;
    ListNode* temp= head;
    int el;
    while(temp!=NULL){
        st.push(temp->data);
        temp=temp->next;
    }
    temp=head;
    while(temp!=NULL){
        el=st.top();
        if(el!=temp->data) return false;
        temp=temp->next;
        st.pop();
    }
    return true;
}
//Optimal
// Return true if the list is empty or has only one node, since such lists are palindromes by default.
// Use two pointers ‘slow’ and ‘fast’ to find the middle node, where slow moves one step and fast moves two steps at a time.
// Reverse the second half of the linked list starting from the node after the middle (slow->next), preparing it for comparison.
// Set two pointers: one at the head of the list and the other at the head of the reversed second half, to compare both halves.
// Compare both halves node by node; if any mismatch occurs, return false, otherwise continue till the end of either list.
// Reverse the second half again to restore the original list structure, and return true if all nodes matched successfully.

bool ispalindrome_optimal(ListNode* head){
    ListNode *slow,*fast=head;

    while(fast->next!=NULL && fast->next->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }
    ListNode* newHead= reverseLL(slow->next);
    ListNode* second= newHead;
    fast=head;
    while(second!=NULL){
        if(second->data!=fast->data){
            reverseLL(newHead);
            return false;
        } 
        fast=fast->next;
        second=second->next;
    }
    reverseLL(newHead);
    return true;
    
}

//Odd Even LL
//Brute - storing elements in a list

ListNode* oddevenLL_brute(ListNode* head){
    vector<int> arr;
    ListNode* temp=head;
    while(temp!=NULL && temp->next!=NULL){
        arr.push_back(temp->data);
        temp=temp->next->next;
    }
    temp=head->next;
    while(temp!=NULL && temp->next!=NULL){
        arr.push_back(temp->data);
        temp=temp->next->next;
    }
    int i=0;
    temp=head;
    while(temp!=NULL ){
        temp->data=arr[i];
        temp=temp->next;
        i++;
    }
}
//Optimal
// Initialize two dummy nodes to serve as heads of two separate linked lists one for even and one for odd nodes.
// Keep two pointers that will track the last node in each of these even and odd lists.
// Traverse the original linked list node by node.
// If a node has an even value, append it to the end of the even list using the even pointer.
// If a node has an odd value, append it to the end of the odd list using the odd pointer.
// Move the pointer forward in the original list after each assignment.
// After the traversal ends, connect the last node of the even list to the head of the odd list.
// Make sure the end of the odd list points to null to prevent loops.
// Return the head of the new list, which is the next node after the dummy even head.

ListNode* oddevenLL_optimal(ListNode* head){
    ListNode* odd=head;
    ListNode* even = head->next;
    ListNode* evenHead = head->next;

    while(even!=NULL && even->next!=NULL){
        odd->next=odd->next->next;
        odd= odd->next;
        even->next= even->next->next;
        even  = even->next;
    }
    odd->next=evenHead;
    return head;

}
//Remone Nth from back of LL
//Brute
ListNode* removenth_brute(ListNode* head,int n){
    ListNode* temp=head;
    int cnt=0,res=0;
    while(temp!=NULL){
        cnt++;
        temp=temp->next;
    }
    res=cnt-n-1;
    if(res==0){
        ListNode* newHead=head->next;
        return newHead;
    }   
    temp=head;
    while(res!=0){
        res--;
        temp=temp->next;
    }
    ListNode* delNode=temp->next;
    temp->next=temp->next->next;
    free(delNode);
    return head;
}
//Optimal
// Initialize two pointers, slow and fast, to the head of the linked list. Initially, only fast will move till it crosses N nodes, after which both of the pointers will move simultaneously.
// Traverse the linked list till the fast pointer reaches the last node, that is, the Lth Node, at this stage, the slow pointer is guaranteed to be at the (L-N)th node.
// Point this slow pointer to the (L-N+2)th node, effectively skipping the Nth node from the end or the (L-N+1)th node from the start.
// Finally, free up the space occupied by this to delete it.

ListNode* removenth_optimal(ListNode* head,int n){
    ListNode* slow=head;
    ListNode* fast=head;
    for(int i =0;i<n;i++) fast = fast->next;
    if(fast==NULL){
        ListNode* newHead=head->next;
        return newHead;
    }
    while(fast->next!=NULL){
        slow=slow->next;
        fast=fast->next;
    }
    ListNode* delNode=slow->next;
    slow->next=delNode->next;
    free(delNode);
    return head;
}
//Delete middle of LL
ListNode* midleel_optimal(ListNode* head){
    if (head==nullptr || head->next==nullptr) return NULL;//Necessary for less time complexity
    ListNode* slow =head;
    ListNode* fast = head;
    ListNode* slow_prev= NULL;
    while(fast!=NULL && fast->next!=NULL){
        slow_prev=slow;
        slow=slow->next;
        fast=fast->next->next;
    }
    slow_prev->next=slow->next;
    return head;
    
}
//Sort the LL
//Brute- Store elements in a List and then storing it back in LL in order

//Optimal - Merge Sort
// This algorithm would divide the linked list into halves recursively until single nodes remain. These sorted halves of the linked list are merged back together in a sorted order.
// If the linked list is empty or has only one node, it is already sorted, thus we can return the head directly.
// Use the slow and fast pointer technique to find the middle of the linked list, where slow moves one step and fast moves two steps at a time.
// Split the linked list into two halves at the midpoint by pointing middle to null, where the left half starts from the head and the right half starts from the node after the middle.
// Recursively apply merge sort on both halves of the linked list until each part is broken down into single nodes or empty lists.
// Merge the two sorted halves using a helper function that compares node values from both halves, attaches the smaller one to the result list, and continues until all nodes from both halves are merged.
// Return the head of the merged and fully sorted linked list, which will represent the final sorted list.

//Midlle of LL(first middle in even)

ListNode* findmiddle(ListNode* head){
    ListNode* slow= head;
    ListNode* fast = head->next;
    while(fast!= NULL && fast->next!= NULL){
        slow=slow->next;
        fast- fast->next;
    }
    return slow;
}
//Merge 2 LL in order

ListNode* Merge2LL(ListNode* list1, ListNode* list2){
    ListNode* dummyNode = new ListNode(-1);
    ListNode* temp= dummyNode;

    while(list1!=NULL && list2!=NULL){
        if(list1->data < list2->data){
            temp->next=list1;
            temp=list1;
            list1=list1->next;
        }else{
            temp->next=list2;
            temp=list2;
            list2=list2->next;
        }
    }
    if(list1) temp->next=list1;
    else temp->next=list2;

    return dummyNode->next;
}
ListNode* sortLL(ListNode* head){
    if(head==NULL || head->next==NULL) return head;

    ListNode* middle= findmiddle(head);
    ListNode* right= middle->next;
    ListNode* left = head;
    middle->next=nullptr;
    left= sortLL(left);
    right=sortLL(right);

    return Merge2LL(left,right);
}
//Sort a LL of 0's 1's and 2's by changing links
//Optimal
ListNode* sort012LL(ListNode* head){
    ListNode* zerohead= new ListNode(-1);
    ListNode* zero_start = zerohead;
    ListNode* onehead= new ListNode(-1);
    ListNode* one_start = onehead;
    ListNode* twohead= new ListNode(-1);
    ListNode* two_start = twohead;
    ListNode* temp =head;

    while(temp!=NULL){
        if(temp->data==0){
            zerohead->next=temp;
            zerohead=zerohead->next;
        }else if(temp->data==1){
            onehead->next=temp;
            onehead=onehead->next;
        }else if(temp->data==2){
            twohead->next=temp;
            twohead=twohead->next;
        }
    }
    zerohead->next=one_start->next;
    onehead->next=two_start->next;
    
    return one_start->next;
}
//Intersection of Two Linked Lists
//Brute- storing each el of first LL in a map, and then comparing

//optimal
ListNode* collision(ListNode *t1, ListNode *t2){
    while(t1!=t2){
        t1=t1->next;
        t2=t2->next;
    }
    return t1;
}
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode* t1=headA;
    ListNode* t2=headB;
    ListNode* intersection;
    int n1=0,n2=0;

    while(t1!=NULL){
        n1++;
        t1=t1->next;
    }
    while(t2!=NULL){
        n2++;
        t2=t2->next;
    }
    t1=headA;
    t2=headB;
    if(n1>=n2){
        for(int i=0;i<(n1-n2);i++){
            t1=t1->next;
        }
        intersection=collision(t1,t2);
    }else{
        for(int i=0;i<(n2-n1);i++){
            t2=t2->next;
        }
        intersection=collision(t2,t1);
    }
    return intersection;
}
//BEST APPROACH
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB){
    if(headA==NULL || headB==NULL) return NULL;
    ListNode* t1=headA;
    ListNode* t2=headB;

    while(t1!=t2){
        t1=t1->next;
        t2=t2->next;

        if(t1==t2) return t1;

        if(t1==NULL) t1=headB;
        if(t2==NULL)t2=headA;   

    }
    return t1;
}
//Adding 1 to a no represented by a LL
ListNode* adding1LL(ListNode* head){
    head= reverseLL(head);
    ListNode* temp=head;
    int carry=1;

    while(temp!=NULL){
        temp->data=temp->data+carry;
        if(temp->data<10){
            carry=0;
            break;
        }
        else{
            temp->data=0;
            carry=1;
        }
        temp=temp->next;
    }
    if(carry>0){
        head= insertTail(head,1);
        
    }
    head=reverseLL(head);
    return head;

}
//Optimal(Without reversing) - recursion
int helper(ListNode* temp){
    if(temp==NULL) return 1;

    int carry=helper(temp->next);

    temp->data=temp->data+carry;
    if(temp->data<10) return 0;
    temp->data=0;
    return 1;
}
ListNode* adding1LL_opitimal(ListNode* head){
    int carry=helper(head);

    if(carry==1){
        ListNode* newHead= new ListNode(1);
        head=newHead->next;
        return newHead;
    }
    return head;
}
//Adding 2 nos. in form of LL(VVVIMP)

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* dummyNode= new ListNode(-1);
    ListNode* curr = dummyNode;
    ListNode* t1=l1;
    ListNode* t2=l2;
    int carry=0;

    while(t1!=NULL || t2!=NULL){
        int sum= carry;
        if(t1) sum=sum+t1->data;
        if(t2) sum+sum+t2->data;

        ListNode* newNode= new ListNode(sum%10);
        carry=sum/10;
        curr->next=newNode;
        curr=curr->next;

        if(t1) t1=t1->next;
        if(t2) t2=t2->next;
    }
    if(carry){
        ListNode* newNode= new ListNode(carry);
        curr->next=newNode;
        curr=curr->next;
    }
    return dummyNode->next;
}

//HARD PROBLEMS
//Reverse Nodes in K groups
// Start with a dummy node pointing to the head of the list to simplify edge cases.
// Set a pointer groupPrev to dummy (this keeps track of the end of the previous reversed group).
// While there are at least k nodes remaining:
// Use getKthNode from groupPrev to find the end of the current k-sized group.
// If getKthNode returns null (less than k nodes left), break the loop.
// Keep track of the next group’s start using kth.next.
// Temporarily break the link after the k-th node so we can reverse this segment cleanly.
// Call reverseLinkedList on the current group’s head to reverse this k-segment.
// Connect the previous group’s tail (groupPrev) to the head of the reversed segment.
// Connect the tail of the reversed segment to the start of the next group.
// Update groupPrev to point to the tail of the reversed segment.
// Once done, return the new head of the list (i.e., dummy.next).

ListNode* getKthnode(ListNode* temp,int k){
    k-=1;
    while(temp!=NULL && k>0){
        k--;
        temp=temp->next;
    }
    return temp;
}
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* temp=head;
    ListNode* prevLast=NULL;

    while(temp!=NULL){
        ListNode* KthNode= getKthnode(temp,k);
        if(KthNode==NULL){
            if(prevLast) prevLast->next=temp;
            break;
        }
        

        ListNode* nextNode=KthNode->next;
        KthNode->next=NULL;
        reverseLL(temp);
        if(temp==head) head=KthNode;
        else prevLast->next=KthNode;

        prevLast=temp;
        temp=nextNode;
    }
    return head;
    
}
//Rotate a LL
// Handle edge cases where the list is empty, has one node, or k is 0 — in these cases, return head as-is.
// Traverse the list to calculate its total length.
// Connect the last node to the first node, converting the list into a circular linked list.
// Calculate effective rotations as k % length to avoid unnecessary full rotations.
// Find the new tail node, which is located at the (length - k % length - 1)th position from the start.
// Set the new head to the node just after the new tail.
// Break the circular link by setting newTail.next = null.
// Return the new head of the rotated list.

ListNode* rotateRight(ListNode* head, int k) {
    if(head==NULL || k==0) return head;
    ListNode* tail=head;
    int len=1, step=0;
    
    while(tail->next!=NULL){
        tail=tail->next;
        len++;
    }
    if(k%len==0) return head;
    tail->next=head;
    step=len-(k%len);
    ListNode* temp=head;
    temp=getKthnode(temp,step);
    head= temp->next;
    temp->next=NULL;
    return head;
}
//Flattening a LL
// Problem Statement: Given a linked list containing ‘N’ head nodes where every node in the linked list contains two pointers:
// ‘Next’ points to the next node in the list
// ‘Child’ pointer to a linked list where the current node is the head
// Each of these child linked lists is in sorted order and connected by a 'child' pointer. Your task is to flatten this linked list such that all nodes appear in a single layer or level in a 'sorted order'.\

class Node{
public:
    int val;
    Node* next;
    Node* random;//child for flattening ques
    Node(int _val){
        val=_val;
        next=NULL;
        random=NULL;
    }
};
Node* merge2list(Node* list1, Node* list2){
    Node* dummyNode = new Node(-1);
    Node* res = dummyNode;
    while(list1!=NULL && list2!= NULL){
        if(list1->val>list2->val){
            res->random=list1;
            res=list1;
            list1=list1->random;
        }else{
            res->random=list2;
            res=list2;
            list2=list2->random;
        }
        res->next=NULL;
    }
    if(list1) res->random=list1;
    if(list2) res->random=list2;
    return dummyNode->random;
}
Node* flatteningLL(Node* head){
    if(head==NULL || head->next==NULL) return head;
    Node* mergedhead= flatteningLL(head->next);
    return merge2list(head,mergedhead);
}
//Copy List with random pointer
//Problem Statement: A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.
// Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node has its value set to the value of its corresponding original node.
// Both the next and random pointer of the new nodes should point to new nodes in the copied list such that the pointers in the original list and copied list represent the same list state.
// None of the pointers in the new list should point to nodes in the original list

//Brute(storing all new, old Nodes in a map)

Node* copyRandomList(Node* head) {
    Node* temp=head;
    unordered_map<Node*,Node*> mpp;
    while (temp!=NULL)
    {
        Node* newNode= new Node(temp->val);
        mpp[temp]=newNode;
        temp=temp->next;
    }
    temp=head;
    while(temp!=NULL){
        Node* copynode=mpp[temp];
        copynode->next=mpp[temp->next];
        copynode->random=mpp[temp->random];
        temp=temp->next;
    }
    return mpp[head];
}
//Optimal
// Traverse the list again to set the random pointer of copied nodes to the corresponding copied node duplicating the original arrangement. As a final traversal, separate the copied and original nodes by detaching alternate nodes.
// Traverse the original node and create a copy of each node and insert it in between the original node and the next node.
// Traverse this modified list and for each original node that has a random pointer, set the copied node’s random pointer to the corresponding copies random node. If the original node’s random pointer is full, set the copied node’s random pointe to null as well.
// Traverse the modified list again and extract the coped nodes by breaking the links between the original nodes and the copied nodes. Revert the original list to its initial state by fixing the next pointers.
// Return the head of the deep copy obtained after extracting the copied nodes from the modified list.

Node* copyRandomList_opt(Node* head){
    Node* temp =head;
    Node* nextNode=NULL;
    while(temp!=NULL){
        Node* copyNode = new Node(temp->val);
        nextNode=temp->next;
        temp->next=copyNode;
        copyNode->next=nextNode;
        temp=temp->next->next;
    }

    temp=head;
    while(temp!=NULL){
        Node* copynode=temp->next;
        if(temp->random==NULL) copynode->random=NULL;
        else copynode->random=temp->random->next;
        temp=temp->next->next;
    }
    temp=head;
    Node* dummyNode=new Node(-1);
    Node* res= dummyNode;
    while(temp!=NULL){
        res->next=temp->next;
        temp->next=temp->next->next;
        res=res->next;
        temp=temp->next;
    }
    return dummyNode->next;
}