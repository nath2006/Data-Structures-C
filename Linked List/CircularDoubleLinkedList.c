#include <stdio.h>
#include <stdlib.h>

// =====================
// CIRCULAR DOUBLE LINKED LIST
// =====================

// (1) node CDLL: sama seperti DLL, tapi tidak ada NULL saat circular
typedef struct DNode {
    struct DNode *prev;  // (2) prev
    int value;           // (3) data
    struct DNode *next;  // (4) next
} DNode;

// (5) insertBackCDLL: tail bisa diakses O(1) dari head->prev (sesuai dokumen)
void cdll_insertBack(DNode **head, int x) {
    // (6) buat node baru
    DNode *node = (DNode*) malloc(sizeof(DNode));
    // (7) kalau gagal
    if (node == NULL) return;

    // (8) isi value
    node->value = x;

    // (9) list kosong: node menunjuk dirinya sendiri (next dan prev)
    if (*head == NULL) {
        node->next = node; // (10) next = dirinya
        node->prev = node; // (11) prev = dirinya
        *head = node;      // (12) head = node
        return;            // (13) selesai
    }

    // (14) akses tail secara O(1)
    DNode *tail = (*head)->prev; // (15) tail = head->prev

    // (16) sambungkan node baru ke lingkaran
    node->next = *head;  // (17) node baru maju ke head (circular)
    node->prev = tail;   // (18) node baru mundur ke tail

    tail->next = node;   // (19) tail maju ke node baru
    (*head)->prev = node; // (20) head mundur ke node baru (node jadi tail baru)
}

// (21) deleteNodeCDLL: 2 kondisi (sesuai dokumen)
void cdll_delete(DNode **head, int x) {
    // (22) kalau kosong
    if (*head == NULL) return;

    // (23) cari node x dengan do-while sampai balik ke head
    DNode *curr = *head;
    do {
        if (curr->value == x) break; // (24) ketemu
        curr = curr->next;           // (25) maju
    } while (curr != *head);         // (26) stop jika balik ke head

    // (27) jika tidak ketemu
    if (curr->value != x) return;

    // (28) KASUS 1: hanya 1 node (next == dirinya)
    if (curr->next == curr) {
        free(curr);      // (29) free
        *head = NULL;    // (30) kosong
        return;          // (31) selesai
    }

    // (32) KASUS UMUM: lepas node dari lingkaran
    DNode *a = curr->prev; // (33) sebelum
    DNode *b = curr->next; // (34) sesudah

    a->next = b; // (35) bypass ke depan
    b->prev = a; // (36) bypass ke belakang

    // (37) kalau yang dihapus adalah head, head pindah ke b
    if (curr == *head) {
        *head = b; // (38)
    }

    free(curr); // (39)
}

// (40) print maju CDLL
void cdll_printForward(DNode *head) {
    // (41) kalau kosong
    if (head == NULL) {
        printf("(kosong)\n");
        return;
    }

    DNode *curr = head; // (42)
    do {
        printf("[%d]", curr->value); // (43)
        curr = curr->next;           // (44)
        if (curr != head) printf(" <-> "); // (45)
    } while (curr != head);          // (46)

    printf(" (circular)\n");         // (47)
}

// (48) free semua node CDLL
void cdll_freeAll(DNode **head) {
    // (49) kalau kosong
    if (*head == NULL) return;

    // (50) mulai dari node setelah head
    DNode *curr = (*head)->next;
    while (curr != *head) {
        DNode *next = curr->next; // (51)
        free(curr);               // (52)
        curr = next;              // (53)
    }

    // (54) free head terakhir
    free(*head);
    *head = NULL;                 // (55)
}

int main() {
    DNode *head = NULL;

    cdll_insertBack(&head, 10);
    cdll_insertBack(&head, 20);
    cdll_insertBack(&head, 30);

    printf("CDLL forward: ");
    cdll_printForward(head);

    cdll_delete(&head, 10);
    printf("After delete 10: ");
    cdll_printForward(head);

    cdll_delete(&head, 30);
    printf("After delete 30: ");
    cdll_printForward(head);

    cdll_freeAll(&head);
    return 0;
}
