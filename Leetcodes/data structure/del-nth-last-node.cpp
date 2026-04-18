#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* removeNthFromEnd(ListNode* head, int n) {
    // Dummy node simplifies edge case where head itself is removed
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    ListNode* fast = dummy;
    ListNode* slow = dummy;

    // Move fast pointer n+1 steps ahead
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }

    // Move both until fast reaches the end
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }

    // slow is now just before the node to delete
    ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;

    ListNode* result = dummy->next;
    delete dummy;
    return result;
}

// --- Helpers ---

ListNode* buildList(int arr[], int size) {
    if (size == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* curr = head;
    for (int i = 1; i < size; i++) {
        curr->next = new ListNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

void printList(ListNode* head) {
    if (!head) { cout << "[]" << endl; return; }
    cout << "[";
    while (head) {
        cout << head->val;
        if (head->next) cout << ",";
        head = head->next;
    }
    cout << "]" << endl;
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    // Test 1: [1,2,3,4,5], n=2 → [1,2,3,5]
    int a1[] = {1, 2, 3, 4, 5};
    ListNode* l1 = removeNthFromEnd(buildList(a1, 5), 2);
    cout << "Test 1: "; printList(l1); freeList(l1);

    // Test 2: [1], n=1 → []
    int a2[] = {1};
    ListNode* l2 = removeNthFromEnd(buildList(a2, 1), 1);
    cout << "Test 2: "; printList(l2); freeList(l2);

    // Test 3: [1,2], n=1 → [1]
    int a3[] = {1, 2};
    ListNode* l3 = removeNthFromEnd(buildList(a3, 2), 1);
    cout << "Test 3: "; printList(l3); freeList(l3);

    return 0;
}