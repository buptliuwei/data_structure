struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {} 
}

ListNode* removeduplicates(ListNode head) {
    if (head == NULL) {
        return NULL
    }
    ListNode* slow = head, fast = head -> next;
    while (fast != NULL) {
        if (fast -> val != slow -> val) {
            slow -> next = fast;
            slow = slow -> next;
        }
        fast = fast -> next;
    }
    // 断开后面与重复的元素相连
    slow -> next =NULL;
    return head;
}  