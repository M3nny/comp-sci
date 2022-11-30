#include <stdio.h>
#include <stdlib.h>

struct vector {
    size_t len;
    int *data;
};

void v_push_back(struct vector *x, int val) {
    // aggiungi val in coda a v
    v->data = realloc(v->data, (v->len+1)*sizeof(int));
    v->data[v->len] = val;
    v->len++;
}

v_create () {
    struct vector *x = (struct vector*) malloc(sizeof(struct vector));
    v->len = 0;
    return v;
}
int main () {
    struct vector *v = v_create();
    v_push_back(v, 10);
}
