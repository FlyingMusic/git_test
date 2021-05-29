/* 1. 单链表翻转
 * 2. 删除单链表倒数第k个结点
 * 3. 判断单链表是否成环,找出入环点
 * 4. 判断两个单链表是否相交,如果相交,找出交点
 *  4.1 两个链表不成环 -> 直接判断两个链表最后的结点是否是同一结点
 *  4.2 不知道是否成环 -> 判断list1是否成环，如成环，找到入环点，如不成环，找到最后一个结点 同样判断list2
 *                        如果一个成环一个不成环，肯定不相交
 *                        如果都不成环，直接比较两个尾结点
 *                        如果都成环，从一个入环点开始遍历，转一圈，能遇到另一个入环点则相交
 * */
#include <stdio.h>
#include <iostream>

using namespace std;


typedef struct node{
    int           data;
    struct node*  next;
    node(int d):data(d), next(NULL){}
}node;

bool isRing(node* head) {
    if(NULL == head) {
        return false;
    }
    node *fast = head;
    node *slow = head;
    while(true) {
        fast = fast->next;
#if 0
        if(slow == fast)
            return true;
#endif
        if(NULL == fast)
            return false;
        fast = fast->next;
        if(fast == slow)
            return true;
        if(NULL == fast)
            return false;
        slow = slow->next;
    }
}

node *findEnter(node* head) {
    if(NULL == head) {
        return NULL;
    }
    node *fast = head;
    node *slow = head;
    while(true) {
        fast = fast->next;
        if(NULL == fast)
            return NULL;
        fast = fast->next;
        if(NULL == fast)
            return NULL;
        slow = slow->next;
        if(fast == slow)
            break;
    }
    node *p1 = head;
    node *p2 = slow;
    while(p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
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
    
    node node0(-1);
    node node1(0);
    node node2(1);
    node node3(2);
    node node4(3);
    node node5(4);

    //五个结点
    node *head = &node0;
    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node3;
    cout << findEnter(head)->data << endl;
    //cout << isRing(head) << endl;
    return 0;
}
