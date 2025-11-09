//Huffman Coding
#include <stdio.h>
#include <stdlib.h>

// Huffman Tree Node
struct Node {
    char data;
    int freq;
    struct Node *left, *right;
};

// Min Heap (Global for simplicity)
struct Node* heap[100]; // array of pointers to nodes
int heapSize = 0;

// Create new node (small helper)
struct Node* createNode(char data, int freq) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

// Swap function
void swap(int i, int j) {
    struct Node* temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

// Heapify down (fix heap after removal)
void heapifyDown(int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < heapSize && heap[left]->freq < heap[smallest]->freq)
        smallest = left;
    if (right < heapSize && heap[right]->freq < heap[smallest]->freq)
        smallest = right;

    if (smallest != i) {
        swap(i, smallest);
        heapifyDown(smallest);
    }
}

// Heapify up (fix heap after insertion)
void heapifyUp(int i) {
    int parent = (i - 1) / 2;
    if (i && heap[i]->freq < heap[parent]->freq) {
        swap(i, parent);
        heapifyUp(parent);
    }
}

// Insert into heap
void insertHeap(struct Node* node) {
    heap[heapSize] = node;
    heapifyUp(heapSize);
    heapSize++;
}

// Extract min from heap
struct Node* extractMin() {
    struct Node* minNode = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
    return minNode;
}

// Build Huffman Tree
struct Node* buildHuffmanTree(char data[], int freq[], int size) {
    // Insert all nodes into heap
    for (int i = 0; i < size; i++) {
        insertHeap(createNode(data[i], freq[i]));
    }

    // Combine until one node remains
    while (heapSize > 1) {
        struct Node* left = extractMin();
        struct Node* right = extractMin();

        struct Node* newNode = createNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        insertHeap(newNode);
    }
    return extractMin(); // final root
}

// Print Huffman Codes
void printCodes(struct Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Driver function
int main() {
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = buildHuffmanTree(arr, freq, size);

    int codes[100];
    printCodes(root, codes, 0);

    return 0;
}