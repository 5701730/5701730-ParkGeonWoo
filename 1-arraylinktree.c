#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void GenerateArrayTree(int* tree) {
    
    int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    printf("(Array 트리 순서대로 출력)\n");
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}


void ArrayPreOrder(int* tree, int index, int size) {
    if (index >= size) return;
    printf("%d ", tree[index]); 
    ArrayPreOrder(tree, 2 * index + 1, size); 
    ArrayPreOrder(tree, 2 * index + 2, size); 
}


void ArrayInOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayInOrder(tree, 2 * index + 1, size); 
    printf("%d ", tree[index]); 
    ArrayInOrder(tree, 2 * index + 2, size); 
}


void ArrayPostOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayPostOrder(tree, 2 * index + 1, size); 
    ArrayPostOrder(tree, 2 * index + 2, size); 
    printf("%d ", tree[index]); 
}


void ArrayOrders(int* tree, int size) {
    printf("Array 전위 순회:\n");
    ArrayPreOrder(tree, 0, size);
    printf("\nArray 중위 순회:\n");
    ArrayInOrder(tree, 0, size);
    printf("\nArray 후위 순회:\n");
    ArrayPostOrder(tree, 0, size);
    printf("\n");
}


void PlaceNode(TreeNode** node, int data) {
    if (*node == NULL) {
        *node = (TreeNode*)malloc(sizeof(TreeNode));
        (*node)->data = data;
        (*node)->left = (*node)->right = NULL;
    }
}


void GenerateLinkTree(TreeNode** root) {
    PlaceNode(root, 1);
    PlaceNode(&(*root)->left, 2);
    PlaceNode(&(*root)->right, 9);
    PlaceNode(&(*root)->left->left, 3);
    PlaceNode(&(*root)->left->right, 5);
    PlaceNode(&(*root)->right->left, 10);
    PlaceNode(&(*root)->right->right, 13);
    PlaceNode(&(*root)->left->left->left, 4);
    PlaceNode(&(*root)->left->left->right, 6);
    PlaceNode(&(*root)->left->right->left, 7);
    PlaceNode(&(*root)->left->right->right, 8);
    PlaceNode(&(*root)->right->left->left, 11);
    PlaceNode(&(*root)->right->left->right, 12);
    PlaceNode(&(*root)->right->right->left, 14);
    PlaceNode(&(*root)->right->right->right, 15);
}


void LinkPreOrder(TreeNode* node) {
    if (node == NULL) return;
    printf("%d ", node->data); 
    LinkPreOrder(node->left);  
    LinkPreOrder(node->right); 
}


void LinkInOrder(TreeNode* node) {
    if (node == NULL) return;
    LinkInOrder(node->left);   
    printf("%d ", node->data); 
    LinkInOrder(node->right);  
}


void LinkPostOrder(TreeNode* node) {
    if (node == NULL) return;
    LinkPostOrder(node->left);  
    LinkPostOrder(node->right); 
    printf("%d ", node->data);  
}


void LinkOrders(TreeNode* root) {
    printf("Linked List 전위 순회:\n");
    LinkPreOrder(root);
    printf("\nLinked List 중위 순회l:\n");
    LinkInOrder(root);
    printf("\nLinked List 후위 순회:\n");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15]; 
    TreeNode* root = NULL; 
    
    
    GenerateArrayTree(arr);

    
    GenerateLinkTree(&root);

    root->data = 1;
    
    ArrayOrders(arr, 15);

    
    LinkOrders(root);

    return 0;
}
