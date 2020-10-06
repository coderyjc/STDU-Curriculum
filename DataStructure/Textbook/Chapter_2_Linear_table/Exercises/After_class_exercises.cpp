
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode* n) : val(x), next(n) {}
};


//2.1
void mergeIncrease1(ListNode* headA, ListNode* headB) {
    ListNode* pA = headA;
    ListNode* pB = headB->next;
    while (pA->next && pB) {
        if (pA->next->val > pB->val) {
            ListNode* tB = pB;
            pB = pB->next;
            ListNode* tA = pA->next;
            pA->next = tB;
            tB->next = tA;
            pA = pA->next;
        } else if (pA->next->val < pB->val)
            pA = pA->next;
        else pB = pB->next;
    }
    if (NULL == pB)
        while (pA->next)
            pA = pA->next;
    pA->next = pB;
}


//2.2
void mergeIncrease(ListNode* headA, ListNode* headB) {
    //premise: A/B is not null and elements are increasing
    ListNode* pA = headA;
    ListNode* pB = headB->next;
    while (pA->next && pB) {
        if (pA->next->val > pB->val) {
            ListNode* tB = pB;
            pB = pB->next;
            ListNode* tA = pA->next;
            pA->next = tB;
            tB->next = tA;
            pA = pA->next;
        } else pA = pA->next;
    }
    if (NULL == pB)
        while (pA->next) 
            pA = pA->next;
    pA->next = pB;
}

//2.3
void intersection(ListNode* headA, ListNode* headB) {
    ListNode* pa = headA;
    ListNode* pb = headB->next;
    while (pa->next && pb) {
        if (pa->next->val > pb->val) {
            pb = pb->next;
        } else if (pa->next->val < pb->val) {
            ListNode* t = pa->next;
            pa->next = t->next;
            delete t;
        } else { // pa->next->val == pb->val
            pa = pa->next;
        }
    }
    pa->next = NULL;
    printList(pa);
}


//2.5

void splitList(ListNode* head) {
    ListNode* headPos = NULL;
    ListNode* headMin = NULL;
    ListNode* pp = NULL;
    ListNode* pm = NULL;
    //head = head->next;
    while (head) {
        if (head->val > 0) {
            if (headPos == NULL) {
                headPos = head;
                pp = headPos;
            } else {
                pp->next = head;
                pp = pp->next;
            }
        } else {
            if (headMin == NULL) {
                headMin = head;
                pm = headMin;
            } else {
                pm->next = head;
                pm = pm->next;
            }
        }
        head = head->next;
    }
    if(pm) pm->next = NULL;
    if(pp) pp->next = NULL;
}


//2.6
ListNode* biggestNode(ListNode* head) {
    ListNode* p = head;
    ListNode* rst = head;
    while (p) {
        if (p->val > rst->val) {
            rst = p;
        }
        p = p->next;
    }
    return rst;
}

//2.7
ListNode* reverseInplace(ListNode* head) {
    ListNode* pre = head;
    ListNode* cur = NULL;
    while (pre) {
        ListNode* t = pre->next;
        pre->next = cur;
        cur = pre;
        pre = t;
    }
    return cur;
}

//2.10
ListNode* deleteSame(ListNode* head, int val) {
    ListNode* preHead = new ListNode(0, head); //cerate a head
    ListNode* p = preHead;
    while (p->next) {
        if (p->next->val == val) {
            ListNode* t = p->next;
            p->next = p->next->next;
            delete t;
        } else p = p->next;
    }
    return preHead->next;
}
