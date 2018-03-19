#ifndef PRINT_H
#define PRINT_H

#include "AST.h"

struct Program *head;

//print ast
void dfs (void);
void Classi(struct Class *);
void ClassMethodDefi(struct ClassMethodDef  *);
void MainFunci(struct MainFunc *);
void Typei(struct Type *);
void CompoundStmti(struct CompoundStmt *, int);
void inCompoundStmti(struct CompoundStmt *, int);
void Parami(struct Param *);
void Memberi(struct Member *,int);
void Identi(struct Ident *);
void VarDecli(struct VarDecl *,int);
void MethodDecli( struct MethodDecl *,int);
void MethodDefi( struct MethodDef *,int);
void Stmti(struct Stmt *,int);
void ExprStmti(struct ExprStmt *,int);
void AssignStmti(struct AssignStmt *,int);
void RetStmti(struct RetStmt *,int);
void WhileStmti(struct WhileStmt *,int);
void DoStmti(struct DoStmt *,int);
void ForStmti(struct ForStmt *,int);
void IfStmti(struct IfStmt *,int);
void Expri(struct Expr *,int);
void RefVarExpri(struct RefVarExpr *,int);
void OperExpri(struct OperExpr *,int);
void RefExpri(struct  RefExpr *,int);
void IdentExpri(struct IdentExpr *,int);
void UnOpi(struct UnOp *,int);
void AddiOpi(struct AddiOp *,int);
void MultOpi(struct MultOp *,int);
void RelaOpi(struct RelaOp * ,int);
void Eqlti(struct EqltOp *,int);
void RefCallExpri(struct RefCallExpr *,int);
void CallExpri( struct CallExpr *,int);
void Argi(struct Arg *,int );
//////print symbol table
void dfsj(void);
void MethodDefj(struct MethodDef *);
void insert(char *);
void pop(void);
void print_stack(void);
void dfs(void);
void Classj(struct Class *);
void Memberj1(struct Member *);
void Memberj2(struct Member *);
void VarDeclj(struct VarDecl *);
void MethodDeclj(struct MethodDecl * );
void Paramj(struct Param *);

void ClassMethodDefj(struct ClassMethodDef *);
void CompoundStmtj(struct CompoundStmt * );

void  Stmtj(struct Stmt *);
void WhileStmtj(struct WhileStmt*);
void DoStmtj(struct DoStmt *);
void ForStmtj(struct ForStmt *);
void IfStmtj(struct IfStmt *);
void MainFuncj(struct MainFunc *);


#endif
