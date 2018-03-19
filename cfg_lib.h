#ifndef CFG_LIB
#define CFG_LIB

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AST.h"

struct Program* head;

typedef enum
{e_vardecl, e_stmt, e_expr} step_e;

typedef enum
{e_normal, e_start, e_end} block_type_e;

typedef union{
	struct VarDecl* vardecl;
	struct Stmt* stmt;
	struct Expr* expr;
} step_union;

struct cfg_step{
	step_e type;
	step_union step;
	struct cfg_step* prev;
};

struct cfg_block{
	int num;// block's number -> ex) A0's number is 0, A1's number is 1, ...
	int visit;// for liveness
	int use[50];// for liveness
	int def[50];// for liveness
	int in[50];// for liveness
	int out[50];//for liveness
	block_type_e type;// 0 is normal block, 1 is start block, 2 is end block
	struct cfg_block_list* pred;
	struct cfg_block_list* succ;
	struct cfg_block* prev;// prev block -> ex) A0's prev is start, A1's prev is A0, ...
	struct cfg_step* step;
};

struct cfg_block_list{
	struct cfg_block_list* prev;
	struct cfg_block* block;
};

struct cfg_procedure{
	char* name;
	int num;//how many blocks in procedure
	struct cfg_block* end_block;
	struct cfg_block* current_block;
	struct cfg_procedure* prev;
};


char print_cfg_procedure(struct cfg_procedure* head_procedure);
int initialize_cfg_block_num(struct cfg_block* head_block);
int print_cfg_block(struct cfg_block* head_block, char block_name);
int print_cfg_step(struct cfg_step* head_step);
int print_vardecl(struct VarDecl* head_vardecl);
int print_stmt(struct Stmt* head_stmt);
int print_expr(struct Expr* head_expr);
int print_oper_expr(struct OperExpr* head_oper_expr);
int print_ref_expr(struct RefExpr* head_ref_expr);
int print_ref_var_expr(struct RefVarExpr* head_ref_var_expr);
int print_ident_expr(struct IdentExpr* head_ident_expr);
int print_ref_call_expr(struct RefCallExpr* head_ref_call_expr);
int print_call_expr(struct CallExpr* head_call_expr);
int print_arg(struct Arg* head_arg);
int print_cfg_block_list(struct cfg_block_list* head_block_list, char block_name);

int construct_cfg_program(struct Program* head_program);
int construct_cfg_class(struct Class* head_class);
int construct_cfg_class_method(struct ClassMethodDef* head_class_method);
int construct_cfg_main(struct MainFunc* head_main);
int construct_cfg_member(struct Member* head_member);
int construct_cfg_method(struct MethodDef* head_method);
int construct_cfg_procedure(struct CompoundStmt* head_compound, char* procedure_name);
struct cfg_block* construct_cfg_stmt_compound(struct cfg_block* dst_block, struct CompoundStmt* head_compound);
struct cfg_block* construct_cfg_vardecl(struct cfg_block* dst_block, struct VarDecl* head_vardecl);
struct cfg_block* construct_cfg_expr(struct cfg_block* dst_block, struct Expr* head_expr);
struct cfg_block* construct_cfg_stmt(struct cfg_block* dst_block, struct Stmt* head_stmt);
struct cfg_block* construct_cfg_stmt_return(struct cfg_block* dst_block, struct Stmt* head_stmt);
struct cfg_block* construct_cfg_stmt_while(struct cfg_block* dst_block, struct Stmt* head_stmt);
struct cfg_block* construct_cfg_stmt_do(struct cfg_block* dst_block, struct Stmt* head_stmt);
struct cfg_block* construct_cfg_stmt_for(struct cfg_block* dst_block, struct Stmt* head_stmt);
struct cfg_block* construct_cfg_stmt_if(struct cfg_block* dst_block, struct Stmt* head_stmt);
struct cfg_block* construct_cfg_stmt_rest(struct cfg_block* dst_block, struct Stmt* head_stmt);
struct cfg_procedure* generate_procedure();
struct cfg_block* generate_block();
struct cfg_block* eliminate_block(struct cfg_block* obj_block);
struct cfg_step* generate_step(struct cfg_block* dst_block, step_union u, step_e e);
int link_block(struct cfg_block* prev, struct cfg_block* next);
int delink_block(struct cfg_block* prev, struct cfg_block* next);
#endif
