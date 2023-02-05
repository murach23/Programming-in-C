#include "../lisp.h"

void test(void);

#define LISPIMPL "Linked"

struct lisp{

 int value;

 struct lisp *car;

 struct lisp *cdr;

};
