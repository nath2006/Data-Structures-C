//semangat mas/mba udah dapet hint kerjain soalnya wkwk


#include <stdio.h>
#include <stdlib.h>

// ============================================================
//  NODE untuk Linked List (dipakai Stack & Queue)
// ============================================================

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// ============================================================
//  STACK (Single Linked List)
// ============================================================
typedef struct {
    Node* top;
    int size;
} Stack;

void stackInit(Stack* s) { s->top = NULL; s->size = 0; }

void push(Stack* s, int value) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = value;
    n->next = s->top;
    s->top  = n;
    s->size++;
}

int pop(Stack* s) {
    if (!s->top) return -1;
    Node* t = s->top;
    int val  = t->data;
    s->top   = t->next;
    free(t);
    s->size--;
    return val;
}

int peek(Stack* s) { return s->top ? s->top->data : -1; }
int stackEmpty(Stack* s) { return s->top == NULL; }

// ============================================================
//  QUEUE (Single Linked List)
// ============================================================
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

void queueInit(Queue* q) { q->front = q->rear = NULL; q->size = 0; }

void enqueue(Queue* q, int value) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data  = value;
    n->next  = NULL;
    if (!q->rear) { q->front = q->rear = n; }
    else { q->rear->next = n; q->rear = n; }
    q->size++;
}

int dequeue(Queue* q) {
    if (!q->front) return -1;
    Node* t  = q->front;
    int val  = t->data;
    q->front = t->next;
    if (!q->front) q->rear = NULL;
    free(t);
    q->size--;
    return val;
}

int queueEmpty(Queue* q) { return q->front == NULL; }

void freeStack(Stack* s) { while (!stackEmpty(s)) pop(s); }
void freeQueue(Queue* q) { while (!queueEmpty(q)) dequeue(q); }


int main() {
    int n;
    printf("Masukkan jumlah developer dan proyek (n): ");
    scanf("%d", &n);

    int developers[100], projects[100];

    printf("Masukkan preferensi %d developer (0=backend, 1=frontend): ", n);
    for (int i = 0; i < n; i++) scanf("%d", &developers[i]);

    printf("Masukkan %d proyek (index 0 = top stack): ", n);
    for (int i = 0; i < n; i++) scanf("%d", &projects[i]);

    // Isi Stack: push dari index n-1 ke 0, agar index 0 jadi top
    Stack stack;
    stackInit(&stack);
    for (int i = n - 1; i >= 0; i--) push(&stack, projects[i]);

    // Isi Queue
    Queue queue;
    queueInit(&queue);
    for (int i = 0; i < n; i++) enqueue(&queue, developers[i]);

    // -------------------------------------------------------
    //  Simulasi: deteksi deadlock dengan skip counter
    //  Setiap kali developer tidak cocok, skipCount++
    //  Jika skipCount == queue.size artinya satu siklus penuh
    //  tidak ada yang cocok -> berhenti
    // -----------------
    
    int skipCount = 0;

    while (!stackEmpty(&stack) && !queueEmpty(&queue)) {
        // Jika sudah satu siklus penuh tanpa match -> stop
        if (skipCount >= queue.size) break;

        int devPref   = dequeue(&queue);
        int topProject = peek(&stack);

        if (devPref == topProject) {
            // Cocok: developer ambil proyek
            pop(&stack);
            skipCount = 0;  // reset karena ada yang berhasil match
        } else {
            // Tidak cocok: balik ke belakang antrian
            enqueue(&queue, devPref);
            skipCount++;    // hitung berapa yang skip berturut-turut
        }
    }

    printf("\n--- Output ---\n%d\n", queue.size);

    freeStack(&stack);
    freeQueue(&queue);
    return 0;
}
