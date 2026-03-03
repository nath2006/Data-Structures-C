//semangat mas/mba udah dapet hint kerjain soalnya wkwk

#include <stdio.h>
#include <stdlib.h>

typedef struct TNode {
    int key;
    struct TNode *left, *right;
} TNode;

TNode* new_node(int x) {
    TNode *n = (TNode*)malloc(sizeof(TNode));
    if (!n) exit(1);
    n->key = x; n->left = n->right = NULL;
    return n;
}

TNode* insert_if_absent(TNode *root, int x) {
    if (root == NULL) return new_node(x);
    if (x < root->key) root->left  = insert_if_absent(root->left, x);
    else if (x > root->key) root->right = insert_if_absent(root->right, x);
    return root; 
}

int bst_max(TNode *root) {
    TNode *cur = root;
    while (cur->right) cur = cur->right;
    return cur->key;
}

void free_bst(TNode *root) {
    if (!root) return;
    free_bst(root->left);
    free_bst(root->right);
    free(root);
}

int main(void) {
    int Q;
    if (scanf("%d", &Q) != 1) return 0;

    TNode *root = NULL;

    int *ans = (int*)malloc(sizeof(int) * Q);
    if (!ans) exit(1);

    // 1) BACA SEMUA INPUT DULU 
    for (int i = 0; i < Q; i++) {
        int x;
        scanf("%d", &x);

        root = insert_if_absent(root, x);
        ans[i] = bst_max(root);   // simpan, belum print
    }

    // 2) BARU CETAK SEMUA OUTPUT SETELAH INPUT SELESAI
    printf("\n");
    for (int i = 0; i < Q; i++) {
      
        printf("%d\n", ans[i]);
    }

    free(ans);
    free_bst(root);
    return 0;
}
