#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 1. تعريف حجم المخزن
#define SIZE 5

// 2. تعريف هيكل المخزن الدائري
typedef struct {
    char buffer[SIZE];
    int head;   
    int tail;   
    int count;  
} CircularBuffer;

// 3. دالة التهيئة
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// 4. التحقق من حالة الامتلاء
bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

// 5. التحقق من حالة الفراغ
bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// 6. دالة الكتابة
void write(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\n[Error] Buffer Overflow! Cannot write: %c\n", data);
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}

// 7. دالة القراءة
char read(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\n[Error] Buffer Underflow!\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}

// 8. الدالة الرئيسية
int main() {
    CircularBuffer cb;
    init(&cb);

    char name[100];
    char suffix[] = "CE-ESY";

    printf("Enter your name: ");
    if (scanf("%99s", name) != 1) return 1;

    strcat(name, suffix);
    printf("Processing: %s\n", name);

    for (int i = 0; i < strlen(name); i++) {
        write(&cb, name[i]);
    }

    printf("Result from Buffer: ");
    while (!isEmpty(&cb)) {
        printf("%c", read(&cb));
    }

    if (isEmpty(&cb)) {
        printf("\nBuffer is now empty.\n");
    }

    return 0;
}
