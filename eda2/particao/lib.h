typedef struct {
  int *array;
  int size;
} Vector;

typedef struct {
  int data;
  int locked;
} Record;

Vector *new_vector();
void add(Vector *vec, int n);
void change(Vector *vec, int idx, int n);
void free_vector(Vector *vec);
int get_key(Record *arr, int size);

void print_arr(int *arr, int size);
void print_vec(Vector *vec);
void swap(int *a, int *b);
void insertion_sort(int *arr, int size);

Vector *substitution(int archive[], int M);
