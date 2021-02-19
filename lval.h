#ifndef LVAL_H
#define LVAL_H

#include "mpc.h"

/* Create Enumeration of Possible lval Types */
enum {LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_STR, LVAL_FUN, LVAL_SEXPR, LVAL_QEXPR };


#define LASSERT(args, cond, fmt, ...) \
  if (!(cond)) { \
    lval* err = lval_err(fmt, ##__VA_ARGS__); \
    lval_del(args); \
    return err; \
  }

#define LASSERT_TYPE(func, args, index, expect) \
  LASSERT(args, args->cell[index]->type == expect, \
    "Function '%s' passed incorrect type for argument %i. Got %s, Expected %s.", \
    func, index, ltype_name(args->cell[index]->type), ltype_name(expect))

#define LASSERT_NUM(func, args, num) \
  LASSERT(args, args->count == num, \
    "Function '%s' passed incorrect number of arguments. Got %i, Expected %i.", \
    func, args->count, num)

#define LASSERT_NOT_EMPTY(func, args, index) \
  LASSERT(args, args->cell[index]->count != 0, \
    "Function '%s' passed {} for argument %i.", func, index);


struct lval;
typedef struct lval lval;

struct lenv;
typedef lval*(*lbuiltin)(struct lenv*, lval*);

/* Declare New lval Struct */
struct lval {
  int type;

  long num;
  char* err;
  char* sym;
  char* str;
  lbuiltin builtin;
  struct lenv* env;
  lval* formals;
  lval* body;

  /* Count and Pointer to a list of "lval*" */
  int count;
  lval** cell;
};

char* ltype_name(int t);

lval* lval_num(long x);
lval* lval_err(char* fmt, ...);
lval* lval_sym(char* s);
lval* lval_str(char* s);
lval* lval_fun(lbuiltin func);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_lambda(lval* formals, lval* body);

lval* lval_add(lval* v, lval* x);
lval* lval_copy(lval* v);
void lval_del(lval* v);

lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
lval* lval_join(lval* x, lval* y);
int lval_eq(lval* x, lval* y);

lval* lval_eval(struct lenv* e, lval* v);

lval* lval_read(mpc_ast_t* t);
void lval_print(lval* v);
void lval_println(lval* v);

#endif