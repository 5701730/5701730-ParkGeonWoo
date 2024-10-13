#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

// 노드 생성함수
TreeNode* createNode(int data, TreeNode* parent) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = node->right = NULL;
    node->parent = parent;
    return node;
}

// 두 노드를 스왑하는 함수
void swap(TreeNode* a, TreeNode* b, int* moveCount) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
    (*moveCount)++;  // 이동 횟수 증가
    printf("노드 %d와 노드 %d가 교환되었습니다.\n", a->data, b->data);
}

// 재정렬 함수(상향식으로)
int heapifyUp(TreeNode* node) {
    int moveCount = 0;  // 이동 횟수 추적
    while (node->parent != NULL && node->data > node->parent->data) {
        swap(node, node->parent, &moveCount);
        node = node->parent;
    }
    return moveCount;
}

// 최대 힙 트리 삽입 함수
int InsertMaxHeapTree(TreeNode** root, int data) {
    if (*root == NULL) {
        *root = createNode(data, NULL);
        return 0;  // 이동 횟수 0
    }

    //노드 삽입 위치를 찾음
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = *root;

    while (front < rear) {
        TreeNode* current = queue[front++];

        if (current->left == NULL) {
            current->left = createNode(data, current);
            return heapifyUp(current->left);  // 재정렬후 이동횟수 반환함
        }
        else {
            queue[rear++] = current->left;
        }

        if (current->right == NULL) {
            current->right = createNode(data, current);
            return heapifyUp(current->right);  // 재정렬 후 이동횟수 반환함
        }
        else {
            queue[rear++] = current->right;
        }
    }
    return 0;  // 이동 횟수가 0이면 0을 반환
}

// 루트노드 삭제하는 함수
int DeleteMaxHeapTree(TreeNode** root) {
    if (*root == NULL) return 0;

    // 마지막 노드를 찾기위함
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = *root;

    TreeNode* lastNode = NULL;

    while (front < rear) {
        lastNode = queue[front++];
        if (lastNode->left != NULL) queue[rear++] = lastNode->left;
        if (lastNode->right != NULL) queue[rear++] = lastNode->right;
    }

    printf("삭제된 루트 노드: %d\n", (*root)->data);

    int moveCount = 0;  //횟수 초기화
    if (lastNode != *root) {
        (*root)->data = lastNode->data;
        // 라스트노드가 노드가 아닐때 삭제
        if (lastNode->parent->left == lastNode) {
            lastNode->parent->left = NULL;
        }
        else {
            lastNode->parent->right = NULL;
        }
        free(lastNode);
        moveCount += heapifyDown(*root);  // 루트가 된 노드가 다시 재정렬 후 이동횟수 반환
    }
    else {
        free(*root);
        *root = NULL;
    }
    return moveCount;
}

// 재정렬 함수
int heapifyDown(TreeNode* root) {
    int moveCount = 0;
    TreeNode* current = root;

    while (current != NULL) {
        TreeNode* largest = current;
        if (current->left != NULL && current->left->data > largest->data) {
            largest = current->left;
        }
        if (current->right != NULL && current->right->data > largest->data) {
            largest = current->right;
        }

        if (largest != current) {
            swap(current, largest, &moveCount);
            current = largest;
        }
        else {
            break;
        }
    }

    return moveCount;
}

// 트리 레벨별로 프린트하는 함수
void PrintHeapByLevel(TreeNode* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        printf("%d ", root->data);
    }
    else if (level > 1) {
        PrintHeapByLevel(root->left, level - 1);
        PrintHeapByLevel(root->right, level - 1);
    }
}

// 트리의 높이를 반환함수
int GetTreeHeight(TreeNode* node) {
    if (node == NULL) return 0;
    int leftHeight = GetTreeHeight(node->left);
    int rightHeight = GetTreeHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 힙트리 전체 레벨을 보여주는 함수
void PrintHeap(TreeNode* root) {
    int height = GetTreeHeight(root);
    for (int i = 1; i <= height; i++) {
        PrintHeapByLevel(root, i);
        printf("\n");
    }
}

// 사용자 인터페이스 함수
void runUserInterface(TreeNode* root) {
    char command;
    int value, moves;

    while (1) {
        printf("\n메뉴 입력 (i: 삽입, d: 삭제, p: 출력, c: 종료): ");
        scanf_s(" %c", &command);

        switch (command) {
        case 'i': // 삽입
            printf("추가할 값 입력: ");
            scanf_s("%d", &value);
            moves = InsertMaxHeapTree(&root, value);
            printf("노드가 %d번 이동되었습니다.\n", moves);
            break;

        case 'd': // 삭제
            moves = DeleteMaxHeapTree(&root);
            printf("노드가 %d번 이동되었습니다.\n", moves);
            break;

        case 'p': // 출력
            printf("트리 레벨별 출력:\n");
            PrintHeap(root);
            break;

        case 'c': // 종료
            printf("프로그램을 종료합니다.\n");
            return;

        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = NULL;  // 루트 노드를 빈 노드로 초기화
    for (int i = 0; i < size; i++) {
        InsertMaxHeapTree(&root, inputData[i]);  // 루트 노드의 주소를 전달 후 삽입
    }
    return root;  //최대힙 노드를 반환
}


// 노드를 해제하는 함수
void freeTree(TreeNode* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}


int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 최대 힙트리 생성
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        InsertMaxHeapTree(&root, inputData[i]);
    }

    // 사용자 인터페이스 실행함
    runUserInterface(root);

    freeTree(root);

    return 0;
}
