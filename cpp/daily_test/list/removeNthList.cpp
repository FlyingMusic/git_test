#include <stdio.h>

using namespace std;


typedef struct node{
    int           data;
    struct node*  next;
    node(int d):data(d), next(NULL){}
}node;
#if 0
node *remove_nth_from_end(node *head, int n) {
    if(NULL == head || 0 >= n) {
        return head;
    }
    node *front = head;
    node *behind = head;
    int cnt = 0;
    while(front && cnt != n+1) {
        front = front->next;
        cnt++;
    }
    if(NULL == front && cnt != n) {
        return head;
    }
    while(front) {
        front = front->next;
        behind = behind->next;
    }
    if(behind == head) 
        head = head->next;
    else 
        behind->next = behind->next->next;
    return head;
}
#endif
node *remove_nth_from_end(node *head, int n) {
    if(NULL == head || 0 >= n) {
        return head;
    }
    node *front = head;
    node *behind = head;
    int cnt = 0;
    while(front) {
        front = front->next;
        if(cnt > n) {
            behind = behind->next; 
        }
        cnt++;
    }
    if(cnt < n) {
        return head;
    } else if(cnt == n) {
        head = head->next;
    } else {
        behind->next = behind->next->next;
    }
    return head;
}
void print_without_headnode(node *head) {
    if(NULL == head) {
        return;
    }
    while(head){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}



int main() {
    
    node node1(1);
    node node2(2);
    node node3(3);
    node node4(4);
    node node5(5);
    node node6(6);
    node node7(7);

    //五个结点
    node *head = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &node7;
    node7.next = NULL;
    print_without_headnode(head);
    head = remove_nth_from_end(head, 6);
    print_without_headnode(head);
    return 0;
}
