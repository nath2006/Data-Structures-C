#include <stdio.h>
#include <stdlib.h>

// =====================
// CIRCULAR SINGLE LINKED LIST
// =====================

// (1) node SLL biasa: value + next
typedef struct TNode {
    int value;             // (2) data
    struct TNode *next;    // (3) pointer ke next
} TNode;

// (4) insertFrontCSLL (mengikuti dokumen)
void csll_insertFront(TNode **head, int x) {
    // (5) buat node baru
    TNode *node = (TNode*) malloc(sizeof(TNode));
    // (6) jika gagal
    if (node == NULL) return;

    // (7) isi data
    node->value = x;

    // (8) jika list kosong, node menunjuk dirinya sendiri
    if (*head == NULL) {
        node->next = node; // (9) circular: next = diri sendiri
        *head = node;      // (10) head = node
        return;            // (11) selesai
    }

    // (12) cari tail: node yang next-nya head
    TNode *curr = *head;               // (13) mulai dari head
    while (curr->next != *head) {      // (14) berhenti saat ketemu tail
        curr = curr->next;             // (15) maju
    }
    // (16) curr sekarang tail

    node->next = *head;  // (17) node baru menunjuk head lama
    curr->next = node;   // (18) tail menunjuk node baru (biar tetap circular)
    *head = node;        // (19) head pindah ke node baru
}

// (20) insertBackCSLL (mengikuti dokumen)
void csll_insertBack(TNode **head, int x) {
    // (21) buat node baru
    TNode *node = (TNode*) malloc(sizeof(TNode));
    // (22) jika gagal
    if (node == NULL) return;

    // (23) isi data
    node->value = x;

    // (24) list kosong
    if (*head == NULL) {
        node->next = node; // (25) circular
        *head = node;      // (26) head = node
        return;            // (27) selesai
    }

    // (28) cari tail
    TNode *curr = *head;              // (29) mulai dari head
    while (curr->next != *head) {     // (30) berhenti di tail
        curr = curr->next;            // (31) maju
    }

    node->next = *head; // (32) node baru harus menunjuk head agar circular
    curr->next = node;  // (33) tail lama menunjuk node baru
    // (34) head tidak berubah
}

// (35) deleteCSLL (mengikuti dokumen)
void csll_delete(TNode **head, int x) {
    // (36) jika kosong
    if (*head == NULL) return;

    // (37) KASUS: hanya 1 node dan dia yang dihapus
    if ((*head)->value == x && (*head)->next == *head) {
        free(*head);      // (38) free
        *head = NULL;     // (39) jadi kosong
        return;           // (40) selesai
    }

    // (41) KONDISI: hapus head (tapi node > 1)
    if ((*head)->value == x) {
        // (42) cari tail
        TNode *tail = *head;
        while (tail->next != *head) {
            tail = tail->next;
        }

        TNode *temp = *head;        // (43) simpan head lama
        tail->next = (*head)->next; // (44) tail lompat ke node ke-2 (head baru)
        *head = (*head)->next;      // (45) head maju
        free(temp);                 // (46) free head lama
        return;                     // (47) selesai
    }

    // (48) KONDISI: hapus non-head
    TNode *curr = *head;                         // (49) mulai dari head
    while (curr->next != *head && curr->next->value != x) {
        curr = curr->next;                       // (50) maju
    }

    // (51) kalau balik ke head, berarti tidak ketemu
    if (curr->next == *head) return;

    // (52) del adalah node setelah curr
    TNode *del = curr->next;
    curr->next = del->next; // (53) bypass del
    free(del);              // (54) free del
}

// (55) print CSLL dengan do-while (berhenti saat kembali ke head)
void csll_print(TNode *head) {
    // (56) kalau kosong
    if (head == NULL) {
        printf("(kosong)\n");
        return;
    }

    // (57) mulai dari head
    TNode *curr = head;
    // (58) do-while wajib untuk circular
    do {
      //  printf("[%d]", curr->value);     // (59) cetak node
      printf("[%d | %p] -> next-%p", 
            curr->value,
          (void*)curr,
          (void*)curr->next
        );
        
        curr = curr->next;               // (60) maju
        if (curr != head) printf(" -> "); // (61) pemisah
    } while (curr != head);              // (62) stop jika balik ke head

    printf(" (circular)\n");             // (63) penutup
}

// (64) free semua node CSLL
void csll_freeAll(TNode **head) {
    // (65) kalau kosong
    if (*head == NULL) return;

    // (66) start dari node setelah head
    TNode *curr = (*head)->next;

    // (67) loop sampai kembali ke head
    while (curr != *head) {
        TNode *next = curr->next; // (68) simpan next
        free(curr);               // (69) free
        curr = next;              // (70) maju
    }

    // (71) free head terakhir
    free(*head);
    *head = NULL;                 // (72) reset
}

int main() {
    TNode *head = NULL;

    csll_insertBack(&head, 10);
    csll_insertBack(&head, 20);
    csll_insertBack(&head, 30);

    printf("CSLL: ");
    csll_print(head);

    csll_insertFront(&head, 5);
    printf("After insertFront 5: ");
    csll_print(head);

    csll_delete(&head, 20);
    printf("After delete 20: ");
    csll_print(head);

    csll_freeAll(&head);
    return 0;
}
