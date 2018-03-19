#ifndef MINICP_H
#define MINICP_H

#include "AST.h"
#include "print.h"

union union_stmt{
	struct ExprStmt* exprStmt;
	struct AssignStmt* assignStmt;
	struct RetStmt* retStmt;
	struct WhileStmt* whileStmt;
	struct DoStmt* doStmt;
	struct ForStmt* forStmt;
	struct IfStmt* ifStmt;
	struct CompoundStmt* compoundStmt;
};

union union_expr{
	struct OperExpr* operExpr;
	struct RefExpr* refExpr;
	char* intnum;
	char* floatnum;
};

union union_refexpr{
	struct RefVarExpr* refVarExpr;
	struct RefCallExpr* refCallExpr;
};

struct Program* new_program(struct Class* arg_class, struct ClassMethodDef* arg_classmethoddef, struct MainFunc* arg_mainfunc){
	struct Program* result_program = (struct Program*)malloc(sizeof(struct Program));
	result_program->_class = arg_class;
	result_program->classMethodDef = arg_classmethoddef;
	result_program->mainFunc = arg_mainfunc;
	return result_program;
}

void push_into_class_list(struct Class* arg_class_list, struct Class* arg_class){
	arg_class->prev = arg_class_list;
	return;
}

struct Class* new_class(char* arg_id, struct Member* arg_private_member, struct Member* arg_public_member){
	struct Class* result_class = (struct Class*)malloc(sizeof(struct Class));
	result_class->id = arg_id;
	result_class->priMember = arg_private_member;
	result_class->pubMember = arg_public_member;
	result_class->prev = NULL;
	return result_class;
}

struct Member* new_member(struct VarDecl* arg_vardecl, struct MethodDecl* arg_methoddecl, struct MethodDef* arg_methoddef){
	struct Member* result_member = (struct Member*)malloc(sizeof(struct Member));
	result_member->varDecl = arg_vardecl;
	result_member->methodDecl = arg_methoddecl;
	result_member->methodDef = arg_methoddef;
	return result_member;
}

void push_into_vardecl_list(struct VarDecl* arg_vardecl_list, struct VarDecl* arg_vardecl){
	arg_vardecl->prev = arg_vardecl_list;
	return;
}

void push_into_methoddecl_list(struct MethodDecl* arg_methoddecl_list, struct MethodDecl* arg_methoddecl){
	arg_methoddecl->prev = arg_methoddecl_list;
	return;
}

void push_into_methoddef_list(struct MethodDef* arg_methoddef_list, struct MethodDef* arg_methoddef){
	arg_methoddef->prev = arg_methoddef_list;
	return;
}

struct VarDecl* new_vardecl(struct Type* arg_type, struct Ident* arg_ident, char* arg_value, Assign_e arg_assigntype){
	struct VarDecl* result_vardecl = (struct VarDecl*)malloc(sizeof(struct VarDecl));
	result_vardecl->type = arg_type;
	result_vardecl->ident = arg_ident;
	result_vardecl->assignType = arg_assigntype;
	result_vardecl->prev = NULL;
	if(arg_assigntype == eAsInt){
		result_vardecl->assigner.intnum = atoi(arg_value);
	}else if(arg_assigntype == eAsFloat){
		result_vardecl->assigner.floatnum = atof(arg_value);
	}
	return result_vardecl;
}

struct MethodDecl* new_methoddecl(struct Type* arg_type, char* arg_id, struct Param* arg_param_list){
	struct MethodDecl* result_methoddecl = (struct MethodDecl*)malloc(sizeof(struct MethodDecl));
	result_methoddecl->id = arg_id;
	result_methoddecl->type = arg_type;
	result_methoddecl->param = arg_param_list;
	result_methoddecl->prev = NULL;
	return result_methoddecl;
}

struct MethodDef* new_methoddef(struct Type* arg_type, char* arg_id, struct Param* arg_param_list, struct CompoundStmt* arg_compoundstmt){
	struct MethodDef* result_methoddef = (struct MethodDef*)malloc(sizeof(struct MethodDef));
	result_methoddef->id = arg_id;
	result_methoddef->type = arg_type;
	result_methoddef->param = arg_param_list;
	result_methoddef->compoundStmt = arg_compoundstmt;
	result_methoddef->prev = NULL;
	return result_methoddef;
}

void push_into_classmethod_list(struct ClassMethodDef* arg_classmethod_list, struct ClassMethodDef* arg_classmethod){
	arg_classmethod->prev = arg_classmethod_list;
	return;
}

struct ClassMethodDef* new_classmethoddef(struct Type* arg_type, char* arg_id1, char* arg_id2, struct Param* arg_param_list, struct CompoundStmt* arg_compoundstmt){
	struct ClassMethodDef* result_classmethoddef = (struct ClassMethodDef*)malloc(sizeof(struct ClassMethodDef));
	result_classmethoddef->type = arg_type;
	result_classmethoddef->className = arg_id1;
	result_classmethoddef->methodName = arg_id2;
	result_classmethoddef->param = arg_param_list;
	result_classmethoddef->compoundStmt = arg_compoundstmt;
	result_classmethoddef->prev = NULL;
	return result_classmethoddef;
}

struct MainFunc* new_mainfunc(struct CompoundStmt* arg_compoundstmt){
	struct MainFunc* result_mainfunc = (struct MainFunc*)malloc(sizeof(struct MainFunc));
	result_mainfunc->compoundStmt = arg_compoundstmt;
	return result_mainfunc;
}

void push_into_param_list(struct Param* arg_param_list, struct Param* arg_param){
	arg_param->prev = arg_param_list;
	return;
}

struct Param* new_param(struct Type* arg_type, struct Ident* arg_ident){
	struct Param* result_param = (struct Param*)malloc(sizeof(struct Param));
	result_param->type = arg_type;
	result_param->ident = arg_ident;
	result_param->prev = NULL;
	return result_param;
}

struct Ident* new_ident(char* arg_id, char* arg_intnum){
	struct Ident* result_ident = (struct Ident*)malloc(sizeof(struct Ident));
	result_ident->id = arg_id;
	if(arg_intnum != NULL) result_ident->len = atoi(arg_intnum);
	else result_ident->len=0;
	return result_ident;
}

struct Type* new_type(char* arg_value, Type_e arg_e){
	struct Type* result_type = (struct Type*)malloc(sizeof(struct Type));
	result_type->e = arg_e;
	if(arg_e == eInt || arg_e == eFloat) result_type->id = NULL;
	else if(arg_e == eClass)result_type->id = arg_value;
	return result_type;
}

struct CompoundStmt* new_compoundstmt(struct VarDecl* arg_vardecl_list, struct Stmt* arg_stmt_list){
	struct CompoundStmt* result_compoundstmt = (struct CompoundStmt*)malloc(sizeof(struct CompoundStmt));
	result_compoundstmt->varDecl = arg_vardecl_list;
	result_compoundstmt->stmt = arg_stmt_list;
	return result_compoundstmt;
}

void push_into_stmt_list(struct Stmt* arg_stmt_list, struct Stmt* arg_stmt){
	arg_stmt->prev = arg_stmt_list;
	return;
}

struct Stmt* new_stmt(union union_stmt arg_type, Stmt_e arg_e){
	struct Stmt* result_stmt = (struct Stmt*)malloc(sizeof(struct Stmt));
	result_stmt->e = arg_e;
	result_stmt->prev = NULL;
	if(arg_e == eExpr) result_stmt->type.exprStmt = arg_type.exprStmt;
	else if(arg_e == eAssign) result_stmt->type.assignStmt = arg_type.assignStmt;
	else if(arg_e == eRet) result_stmt->type.retStmt = arg_type.retStmt;
	else if(arg_e == eWhile) result_stmt->type.whileStmt = arg_type.whileStmt;
	else if(arg_e == eDo) result_stmt->type.doStmt = arg_type.doStmt;
	else if(arg_e == eFor) result_stmt->type.forStmt = arg_type.forStmt;
	else if(arg_e == eIf) result_stmt->type.ifStmt = arg_type.ifStmt;
	else if(arg_e == eCompound) result_stmt->type.compoundStmt = arg_type.compoundStmt;
//	else if(arg_e == eSemi) result_stmt->type = NULL;
	return result_stmt;
}

struct ExprStmt* new_exprstmt(struct Expr* arg_expr){
	struct ExprStmt* result_exprstmt = (struct ExprStmt*)malloc(sizeof(struct ExprStmt));
	result_exprstmt->expr = arg_expr;
	return result_exprstmt;
}

struct AssignStmt* new_assignstmt(struct RefVarExpr* arg_refvarexpr, struct Expr* arg_expr){
	struct AssignStmt* result_assignstmt = (struct AssignStmt*)malloc(sizeof(struct AssignStmt));
	result_assignstmt->refVarExpr = arg_refvarexpr;
	result_assignstmt->expr = arg_expr;
	return result_assignstmt;
}

struct RetStmt* new_retstmt(struct Expr* arg_expr){
	struct RetStmt* result_retstmt = (struct RetStmt*)malloc(sizeof(struct RetStmt));
	result_retstmt->expr = arg_expr;
	return result_retstmt;
}

struct WhileStmt* new_whilestmt(struct Expr* arg_expr, struct Stmt* arg_stmt){
	struct WhileStmt* result_whilestmt = (struct WhileStmt*)malloc(sizeof(struct WhileStmt));
	result_whilestmt->cond = arg_expr;
	result_whilestmt->body = arg_stmt;
	return result_whilestmt;
}

struct DoStmt* new_dostmt(struct Stmt* arg_stmt, struct Expr* arg_expr){
	struct DoStmt* result_dostmt = (struct DoStmt*)malloc(sizeof(struct DoStmt));
	result_dostmt->cond = arg_expr;
	result_dostmt->body = arg_stmt;
	return result_dostmt;
}

struct ForStmt* new_forstmt(struct Expr* arg_init, struct Expr* arg_cond, struct Expr* arg_incr, struct Stmt* arg_body){
	struct ForStmt* result_forstmt = (struct ForStmt*)malloc(sizeof(struct ForStmt));
	result_forstmt->init = arg_init;
	result_forstmt->cond = arg_cond;
	result_forstmt->incr = arg_incr;
	result_forstmt->body = arg_body;
	return result_forstmt;
}

struct IfStmt* new_ifstmt(struct Expr* arg_cond, struct Stmt* arg_ifbody, struct Stmt* arg_elsebody){
	struct IfStmt* result_ifstmt = (struct IfStmt*)malloc(sizeof(struct IfStmt));
	result_ifstmt->cond = arg_cond;
	result_ifstmt->ifBody = arg_ifbody;
	result_ifstmt->elseBody = arg_elsebody;
	return result_ifstmt;
}

struct Expr* new_expr(union union_expr arg_type, Expr_e arg_e){
	struct Expr* result_expr = (struct Expr*)malloc(sizeof(struct Expr));
	result_expr->e = arg_e;
	if(arg_e == eOper) result_expr->type.operExpr = arg_type.operExpr;
	else if(arg_e == eRef) result_expr->type.refExpr = arg_type.refExpr;
	else if(arg_e == eIntnum) result_expr->type.intnum = atoi(arg_type.intnum);
	else if(arg_e == eFloatnum) result_expr->type.floatnum = atof(arg_type.floatnum);
	return result_expr;
}

struct UnOp* new_unop(struct Expr* arg_expr1, char* arg_type){
	struct UnOp* result_unop = (struct UnOp*)malloc(sizeof(struct UnOp));
	if(strcmp(arg_type,"-") == 0) result_unop->e = eNegative;
	result_unop->expr = arg_expr1;
	return result_unop;
}

struct AddiOp* new_addiop(struct Expr* arg_expr1, char* arg_type, struct Expr* arg_expr2){
	struct AddiOp* result_addiop = (struct AddiOp*)malloc(sizeof(struct AddiOp));
	result_addiop->lhs = arg_expr1;
	result_addiop->rhs = arg_expr2;
	if(strcmp(arg_type,"+") == 0) result_addiop->e = ePlus;
	else if(strcmp(arg_type,"-") == 0) result_addiop->e = eMinus;
	return result_addiop;
}

struct MultOp* new_multop(struct Expr* arg_expr1, char* arg_type, struct Expr* arg_expr2){
	struct MultOp* result_multop = (struct MultOp*)malloc(sizeof(struct MultOp));
	result_multop->lhs = arg_expr1;
	result_multop->rhs = arg_expr2;
	if(strcmp(arg_type,"*") == 0) result_multop->e = eMul;
	else if(strcmp(arg_type,"/") == 0) result_multop->e = eDiv;
	return result_multop;
}

struct RelaOp* new_relaop(struct Expr* arg_expr1, char* arg_type, struct Expr* arg_expr2){
	struct RelaOp* result_relaop = (struct RelaOp*)malloc(sizeof(struct RelaOp));
	result_relaop->lhs = arg_expr1;
	result_relaop->rhs = arg_expr2;
	if(strcmp(arg_type,"<") == 0) result_relaop->e = eLT;
	else if(strcmp(arg_type,">") == 0) result_relaop->e = eGT;
	else if(strcmp(arg_type,"<=") == 0) result_relaop->e = eLE;
	else if(strcmp(arg_type,">=") == 0) result_relaop->e = eGE;
	return result_relaop;
}

struct EqltOp* new_eqltop(struct Expr* arg_expr1, char* arg_type, struct Expr* arg_expr2){
	struct EqltOp* result_eqltop = (struct EqltOp*)malloc(sizeof(struct EqltOp));
	result_eqltop->lhs = arg_expr1;
	result_eqltop->rhs = arg_expr2;
	if(strcmp(arg_type,"==") == 0) result_eqltop->e = eEQ;
	else if(strcmp(arg_type,"!=") == 0) result_eqltop->e = eNE;
	return result_eqltop;
}

struct OperExpr* new_operexpr(struct Expr* arg_expr1, char* arg_type, struct Expr* arg_expr2, Oper_e arg_e){
	struct OperExpr* result_operexpr = (struct OperExpr*)malloc(sizeof(struct OperExpr));
	result_operexpr->e = arg_e;
	if(arg_e == eUn) result_operexpr->type.un = new_unop(arg_expr1, arg_type);
	else if(arg_e == eAddi) result_operexpr->type.addi = new_addiop(arg_expr1,arg_type,arg_expr2);
	else if(arg_e == eMult) result_operexpr->type.mult = new_multop(arg_expr1,arg_type,arg_expr2);
	else if(arg_e == eRela) result_operexpr->type.rela = new_relaop(arg_expr1,arg_type,arg_expr2);
	else if(arg_e == eEqlt) result_operexpr->type.eqlt = new_eqltop(arg_expr1,arg_type,arg_expr2);
	else if(arg_e == eBracket) result_operexpr->type.bracket = arg_expr1;
	return result_operexpr;
}

struct RefExpr* new_refexpr(union union_refexpr arg_type, Ref_e arg_e){
	struct RefExpr* result_refexpr = (struct RefExpr*)malloc(sizeof(struct RefExpr));
	result_refexpr->e = arg_e;
	if(arg_e == eVar) result_refexpr->type.refVarExpr = arg_type.refVarExpr;
	else if(arg_e == eCall) result_refexpr->type.refCallExpr = arg_type.refCallExpr;
	return result_refexpr;
}

struct RefVarExpr* new_refvarexpr(struct RefExpr* arg_refexpr, struct IdentExpr* arg_identexpr){
	struct RefVarExpr* result_refvarexpr = (struct RefVarExpr*)malloc(sizeof(struct RefVarExpr));
	result_refvarexpr->refExpr = arg_refexpr;
	result_refvarexpr->identExpr = arg_identexpr;
	return result_refvarexpr;
}

struct RefCallExpr* new_refcallexpr(struct RefExpr* arg_refexpr, struct CallExpr* arg_callexpr){
	struct RefCallExpr* result_refcallexpr = (struct RefCallExpr*)malloc(sizeof(struct RefCallExpr));
	result_refcallexpr->refExpr = arg_refexpr;
	result_refcallexpr->callExpr = arg_callexpr;
	return result_refcallexpr;
}

struct IdentExpr* new_identexpr(char* arg_id, struct Expr* arg_expr){
	struct IdentExpr* result_identexpr = (struct IdentExpr*)malloc(sizeof(struct IdentExpr));
	result_identexpr->id = arg_id;
	result_identexpr->expr = arg_expr;
	return result_identexpr;
}

struct CallExpr* new_callexpr(char* arg_id, struct Arg* arg_arg_list){
	struct CallExpr* result_callexpr = (struct CallExpr*)malloc(sizeof(struct CallExpr));
	result_callexpr->id = arg_id;
	result_callexpr->arg = arg_arg_list;
	return result_callexpr;
}

void push_into_arg_list(struct Arg* arg_arg_list, struct Arg* arg_arg){
	arg_arg->prev = arg_arg_list;
	return;
}

struct Arg* new_arg(struct Expr* arg_expr){
	struct Arg* result_arg = (struct Arg*)malloc(sizeof(struct Arg));
	result_arg->expr = arg_expr;
	result_arg->prev = NULL;
	return result_arg;
}

#endif
