#include <stdio.h>    // (1) untuk printf
#include <stdlib.h>   // (2) untuk malloc dan free

// =====================
// DOUBLE LINKED LIST
// =====================

// (3) struct node DLL: punya prev, value, next
typedef struct DNode {
    struct DNode *prev;   // (4) pointer ke node sebelumnya
    int value;            // (5) data
    struct DNode *next;   // (6) pointer ke node berikutnya
} DNode;

// (7) appendTail: tambah node di belakang tail
void dll_appendTail(DNode **head, DNode **tail, int x) {
    // (8) alokasi node baru
    DNode *node = (DNode*) malloc(sizeof(DNode));
    // (9) kalau malloc gagal, stop
    if (node == NULL) return;

    // (10) isi data
    node->value = x;
    // (11) karena append di belakang, next = NULL (tail baru)
    node->next = NULL;
    // (12) prev node baru = tail lama (bisa NULL kalau list kosong)
    node->prev = *tail;

    // (13) cek list kosong?
    if (*tail == NULL) {
        // (14) kalau kosong, node ini jadi head dan tail
        node->prev = NULL;  // (15) head->prev harus NULL
        *head = node;       // (16) head menunjuk node
        *tail = node;       // (17) tail menunjuk node
    } else {
        // (18) sambungkan tail lama ke node baru
        (*tail)->next = node; // (19) tail->next menunjuk node baru
        *tail = node;         // (20) geser tail ke node baru
    }
}

// (21) printForward: traversal maju head -> tail
void dll_printForward(DNode *head) {
    // (22) mulai dari head
    DNode *curr = head;
    // (23) cetak pembuka
    printf("NULL");
    // (24) selama curr masih ada
    while (curr != NULL) {
        // (25) cetak node
        printf(" <-> [%d]", curr->value);
        // (26) maju
        curr = curr->next;
    }
    // (27) tutup
    printf(" <-> NULL\n");
}

// (28) printBackward: traversal mundur tail -> head
void dll_printBackward(DNode *tail) {
    // (29) mulai dari tail
    DNode *curr = tail;
    // (30) cetak pembuka
    printf("NULL");
    // (31) selama curr masih ada
    while (curr != NULL) {
        // (32) cetak node
        printf(" <-> [%d]", curr->value);
        // (33) mundur
        curr = curr->prev;
    }
    // (34) tutup
    printf(" <-> NULL\n");
}

// (35) deleteNode: hapus node bernilai x, 4 kondisi (seperti dokumen)
void dll_deleteNode(DNode **head, DNode **tail, int x) {
    // (36) jika list kosong, stop
    if (*head == NULL) return;

    // (37) cari node yang value == x
    DNode *curr = *head;
    // (38) maju sampai ketemu atau habis
    while (curr != NULL && curr->value != x) {
        curr = curr->next;
    }
    // (39) kalau tidak ketemu, stop
    if (curr == NULL) return;

    // (40) KONDISI 1: hanya 1 node (curr adalah head dan tail)
    if (curr == *head && curr == *tail) {
        free(curr);        // (41) bebaskan node
        *head = NULL;      // (42) list jadi kosong
        *tail = NULL;      // (43) list jadi kosong
        return;            // (44) selesai
    }

    // (45) KONDISI 2: hapus head
    if (curr == *head) {
        *head = curr->next;     // (46) head maju
        (*head)->prev = NULL;   // (47) head->prev wajib NULL
        free(curr);             // (48) bebaskan node lama
        return;                 // (49) selesai
    }

    // (50) KONDISI 3: hapus tail
    if (curr == *tail) {
        *tail = curr->prev;     // (51) tail mundur
        (*tail)->next = NULL;   // (52) tail->next wajib NULL
        free(curr);             // (53) bebaskan node lama
        return;                 // (54) selesai
    }

    // (55) KONDISI 4: hapus node tengah
    DNode *a = curr->prev;  // (56) node sebelum curr
    DNode *b = curr->next;  // (57) node setelah curr
    a->next = b;            // (58) bypass curr ke depan
    b->prev = a;            // (59) bypass curr ke belakang
    free(curr);             // (60) hapus curr
}

// (61) bersihkan seluruh list
void dll_freeAll(DNode **head, DNode **tail) {
    // (62) mulai dari head
    DNode *curr = *head;
    // (63) loop sampai NULL
    while (curr != NULL) {
        // (64) simpan next dulu
        DNode *next = curr->next;
        // (65) free node sekarang
        free(curr);
        // (66) maju
        curr = next;
    }
    // (67) reset head & tail
    *head = NULL;
    *tail = NULL;
}

int main() {
    DNode *head = NULL; // (68) head awal kosong
    DNode *tail = NULL; // (69) tail awal kosong

    // (70) append beberapa data
    dll_appendTail(&head, &tail, 10);
    dll_appendTail(&head, &tail, 20);
    dll_appendTail(&head, &tail, 30);

    // (71) cetak maju & mundur
    printf("DLL forward : ");
    dll_printForward(head);
    printf("DLL backward: ");
    dll_printBackward(tail);

    // (72) hapus 20 (tengah)
    dll_deleteNode(&head, &tail, 20);

    // (73) cetak lagi
    printf("After delete 20:\n");
    printf("DLL forward : ");
    dll_printForward(head);

    // (74) bersihkan
    dll_freeAll(&head, &tail);
    return 0; // (75) selesai
}
