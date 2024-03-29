#include <iostream>
using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template<typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");

        Node<T>* temp = front;
        T val = temp->data;

        front = front->next;
        if (front)
            front->prev = nullptr;
        else
            rear = nullptr;

        delete temp;
        size--;

        return val;
    }

    bool isEmpty() {
        return size == 0;
    }

    static Node<T>* cloneList(Node<T>* head) {
        if (!head) return nullptr;

        Node<T>* clonedHead = new Node<T>(head->data);
        Node<T>* current = head->next;
        Node<T>* clonedCurrent = clonedHead;

        while (current) {
            Node<T>* newNode = new Node<T>(current->data);
            clonedCurrent->next = newNode;
            newNode->prev = clonedCurrent;
            clonedCurrent = newNode;
            current = current->next;
        }

        return clonedHead;
    }

    static Node<T>* mergeLists(Node<T>* head1, Node<T>* head2) {
        Node<T>* mergedHead = cloneList(head1);
        Node<T>* mergedTail = mergedHead;

        while (mergedTail->next)
            mergedTail = mergedTail->next;

        Node<T>* current = head2;
        while (current) {
            Node<T>* newNode = new Node<T>(current->data);
            mergedTail->next = newNode;
            newNode->prev = mergedTail;
            mergedTail = newNode;
            current = current->next;
        }

        return mergedHead;
    }

    static Node<T>* intersectLists(Node<T>* head1, Node<T>* head2) {
        Node<T>* resultHead = nullptr;
        Node<T>* resultTail = nullptr;

        Node<T>* current1 = head1;
        while (current1) {
            Node<T>* current2 = head2;
            while (current2) {
                if (current1->data == current2->data) {
                    Node<T>* newNode = new Node<T>(current1->data);
                    if (!resultHead) {
                        resultHead = resultTail = newNode;
                    }
                    else {
                        resultTail->next = newNode;
                        newNode->prev = resultTail;
                        resultTail = newNode;
                    }
                    break;
                }
                current2 = current2->next;
            }
            current1 = current1->next;
        }

        return resultHead;
    }

    friend Node<T>* operator+(Queue<T>& queue1, Queue<T>& queue2) {
        return mergeLists(queue1.front, queue2.front);
    }

    friend Node<T>* operator*(Queue<T>& queue1, Queue<T>& queue2) {
        return intersectLists(queue1.front, queue2.front);
    }
};

int main() {
    Queue<int> queue1;
    queue1.enqueue(1);
    queue1.enqueue(2);
    queue1.enqueue(3);

    Queue<int> queue2;
    queue2.enqueue(2);
    queue2.enqueue(3);
    queue2.enqueue(4);

    Node<int>* merged = queue1 + queue2;
    while (merged) {
        cout << merged->data << " ";
        merged = merged->next;
    }
    cout << endl;

    Node<int>* common = queue1 * queue2;
    while (common) {
        cout << common->data << " ";
        common = common->next;
    }
    cout << endl;

    return 0;
}
