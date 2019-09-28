// 若无环，开始遍历之后，fast和slow不可能与slow重回，且fast或fast->next最终必然到达NULL；若有环，fast必然
// 不迟于slow先进入环，且由于fast移动步长为2，slow移动步长为1，则slow进入环后继续绕环遍历一周之前fast必然能与slow
// 重合（且必然是第一重和）
struct Node
{
    Node *next;
};


bool hasCircle(Node *head, Node* &encounter){
    Node *fast = head, *slow = head;
    while (fast && fast -> next){
        fast = fast -> next -> next;
        slow = slow -> next;
        if (fast == slow){
            encounter = fast;
            return true;
        }
    }
    encounter = NULL;
    return false;
}

// 找环的入口点，从起点和相交的节点往下走，每次走一步，直到两个指针相等，可以有数学公式推导
Node *findEntry(Node* head, Node* encounter){
    Node *p1 = head, *p2 = encounter;
    while (p1 != p2)
    {
        p1 = p1 -> next;
        p2 = p2 -> next;
    }
    return p1;
}
