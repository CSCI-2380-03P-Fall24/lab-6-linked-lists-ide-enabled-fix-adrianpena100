#include "LLStack.h"

// Node constructor: initialize new nodes with an input string s
// s should be stored as the data of the node
// the nodes are not initially linked to any other node
// so be sure that the "next" Node is linked to a nullptr
Node::Node(string s) {
    // Store the incoming string value
    data = s;

    // New node points to nothing initially
    next = nullptr;
}

//constructor : initiazlize the head and tail field from LLStack class 
// the stack should start with no items 
// the head and tail should both be initialized as null pointers
LLStack::LLStack() {
    // Start the stack empty
    head = nullptr;
    tail = nullptr;
    count = 0;
}

/*
    define the top() method, which will return the data at the top of the stack
    (remember the "top" of the stack is the newest element)
    If stack is empty, return "";
*/
string LLStack::top() {
    // If there are no elements, return an empty string
    if (head == nullptr) {
        return "";
    }

    // Otherwise return the top element's data
    return head->data;
}

/*
    define the size() method, which will return the number of nodes in the stack
*/
int LLStack::size() {
    // Simply return the count variable
    return count;
}

/*
    - Create the new Node and initialize the fields of class Node (data and next)
    - update the head, tail and count accordingly

    Hint: To update head and tail properly, You have to consider two scenarios:
    1. If there is no element in the stack and this is the first one going to the stack
    2. If there is another head in the stack
*/
void LLStack::push(string s) {
    // Create a new node containing the input string
    Node* node = new Node(s);

    // Case 1: If the stack is empty
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        // Case 2: If there are already elements, link the new node at the top
        node->next = head;
        head = node;
    }

    // Increment the count after successful insertion
    count++;
}

/*
    First, Check if the stack is empty or not. If not, update the head,tail and count accordingly.
        *Don't forget to release memory using delete
    Hint: To update head and tail properly, You should consider two different scenarios:
    1. If LLStack has more than one element
    2. If LLStack has exactly one element
*/
void LLStack::pop() {
    // Do nothing if stack is already empty
    if (head == nullptr) {
        return;
    }

    // Save pointer to current head to delete later
    Node* toDelete = head;

    // Move head to the next node (effectively removing the first element)
    head = head->next;

    // Delete the old head to free memory
    delete toDelete;

    // Decrement the count
    count--;

    // If list is now empty, reset tail as well
    if (head == nullptr) {
        tail = nullptr;
    }
}

/*
    define the removeAll() method, which removes all nodes 
    that have data equal to the given target string.
    - Traverse through the linked list
    - For each matching node, unlink it and delete it
    - Update head, tail, and count accordingly
    - Return how many nodes were removed

    Hints:
    ----------------------------------------
    - Always check if the list becomes empty after deletions (head == nullptr).
      If so, make sure tail is also set to nullptr.
    - Use a counter variable (such as 'removed') to track how many were deleted.
    - Be careful not to lose your place when deleting nodes:
        * Save curr->next in a temporary pointer before deleting curr.
    - Handle edge cases:
        * Stack is empty (no nodes to remove)
        * Target not found (return 0)
        * All nodes match the target (list becomes empty)
*/
int LLStack::removeAll(const string& target) {
    // Track how many nodes are removed
    int removed = 0;

    // Pointers for traversal
    Node* prev = nullptr;
    Node* curr = head;

    // Loop through the list until we reach the end
    while (curr != nullptr) {
        // Check if current node's data matches the target string
        if (curr->data == target) {
            // Save current node to delete later
            Node* toDelete = curr;

            // If we are deleting the first node (head)
            if (prev == nullptr) {
                // Move head forward
                head = curr->next;
            } else {
                // Otherwise, link the previous node to the next node
                prev->next = curr->next;
            }

            // If the node to delete is the tail, move tail back one node
            if (toDelete == tail) {
                tail = prev;
            }

            // Move to the next node before deleting current
            curr = curr->next;

            // Delete the matched node and free memory
            delete toDelete;

            // Update stack size and removed counter
            count--;
            removed++;

            // Note: 'prev' does not advance here because current node was deleted
        } else {
            // If not deleted, move both prev and curr forward
            prev = curr;
            curr = curr->next;
        }
    }

    // After traversal, if head is nullptr, set tail to nullptr as well
    if (head == nullptr) {
        tail = nullptr;
    }

    // Return how many nodes were removed from the list
    return removed;
}