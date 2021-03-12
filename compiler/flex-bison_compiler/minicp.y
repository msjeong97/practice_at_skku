%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "minicp.h"
%}

%union {
	int intnum;
	float floatnum;
	char* str;
	struct Program* _program;
	struct Class* _class;
	struct Member* _member;
	struct VarDecl* _vardecl;
	struct MethodDecl* _methoddecl;
	struct MethodDef* _methoddef;
	struct ClassMethodDef* _classmethoddef;
	struct MainFunc* _mainfunc;
	struct Param* _param;
	struct Ident* _ident;
	struct Type* _type;
	struct CompoundStmt* _compoundstmt;
	struct Stmt* _stmt;
	struct ExprStmt* _exprstmt;
	struct AssignStmt* _assignstmt;
	struct RetStmt* _retstmt;
	struct WhileStmt* _whilestmt;
	struct DoStmt* _dostmt;
	struct ForStmt* _forstmt;
	struct IfStmt* _ifstmt;
	struct Expr* _expr;
	struct OperExpr* _operexpr;
	struct RefExpr* _refexpr;
	struct RefVarExpr* _refvarexpr;
	struct RefCallExpr* _refcallexpr;
	struct IdentExpr* _identexpr;
	struct CallExpr* _callexpr;
	struct Arg* _arg;
}

%token <str> UNOP
%token <str> ADDIOP
%token <str> MULTOP
%token <str> RELAOP
%token <str> EQLTOP
%token <str> ID
%token <str> INTNUM
%token <str> FLOATNUM
%token <str> CLASS
%token <str> LPAREN
%token <str> RPAREN
%token <str> LBRACE
%token <str> RBRACE
%token <str> PRIVATE
%token <str> PUBLIC
%token <str> INT
%token <str> FLOAT
%token <str> SEMICOLON
%token <str> COLON
%token <str> EQUAL
%token <str> DOT
%token <str> COMMA
%token <str> MAIN
%token <str> LBRACK
%token <str> RBRACK
%token <str> RETURN
%token <str> WHILE
%token <str> DO
%token <str> FOR
%token <str> IF
%token <str> ELSE

%type <_program> Program
%type <_class> ClassList
%type <_class> Class
%type <_member> Member
%type <_vardecl> VarDeclList
%type <_methoddecl> MethodDeclList
%type <_methoddef> MethodDefList
%type <_vardecl> VarDecl
%type <_methoddecl> MethodDecl
%type <_methoddef> MethodDef
%type <_classmethoddef> ClassMethodList
%type <_classmethoddef> ClassMethodDef
%type <_mainfunc> MainFunc
%type <_param> ParamList
%type <_param> Param
%type <_ident> Ident
%type <_type> Type
%type <_compoundstmt> CompoundStmt
%type <_stmt> StmtList
%type <_stmt> Stmt
%type <_exprstmt> ExprStmt
%type <_assignstmt> AssignStmt
%type <_retstmt> RetStmt
%type <_whilestmt> WhileStmt
%type <_dostmt> DoStmt
%type <_forstmt> ForStmt
%type <_ifstmt> IfStmt
%type <_expr> Expr
%type <_operexpr> OperExpr
%type <_refexpr> RefExpr
%type <_refvarexpr> RefVarExpr
%type <_refcallexpr> RefCallExpr
%type <_identexpr> IdentExpr
%type <_callexpr> CallExpr
%type <_arg> ArgList

%left ADDIOP MULTOP RELAOP EQLTOP LPAREN RPAREN
%right UNOP EQUAL

%start Program

%%

Program : /* (ClassList)? (ClassMethodList)? MainFunc */
	ClassList ClassMethodList MainFunc {
		$$ = new_program($1,$2,$3);
		head = $$;
	} |
	ClassMethodList MainFunc {
		$$ = new_program(NULL,$1,$2);
		head = $$;
	} |
	ClassList MainFunc {
		$$ = new_program($1,NULL,$2);
		head = $$;
	} |
	MainFunc {
		$$ = new_program(NULL,NULL,$1);
		head = $$;
	} ;

ClassList : // (Class)+
	ClassList Class {// classlist value's prev is not null, 
		push_into_class_list($1,$2);
		$$ = $2;
	} |
	Class {// prev = NULL 
		$$ = $1;
	} ;

Class : /* class id { (private : Member)? (public : Member)? } */
	CLASS ID LBRACE PRIVATE COLON Member PUBLIC COLON Member RBRACE {
		$$ = new_class($2,$6,$9);
	} |
	CLASS ID LBRACE PUBLIC COLON Member RBRACE {
		$$ = new_class($2,NULL,$6);
	} |
	CLASS ID LBRACE PRIVATE COLON Member RBRACE {
		$$ = new_class($2,$6,NULL);
	} |
	CLASS ID LBRACE RBRACE {
		$$ = new_class($2,NULL,NULL);
	} ;

Member : /* (VarDeclList)? (MethodDeclList)? (MethodDefList)? */
	VarDeclList MethodDeclList MethodDefList {
		$$ = new_member($1,$2,$3);
	} |
	MethodDeclList MethodDefList {
		$$ = new_member(NULL,$1,$2);
	} |
	VarDeclList MethodDefList {
		$$ = new_member($1,NULL,$2);
	} |
	VarDeclList MethodDeclList {
		$$ = new_member($1,$2,NULL);
	} |
	MethodDefList {
		$$ = new_member(NULL,NULL,$1);
	} |
	MethodDeclList {
		$$ = new_member(NULL,$1,NULL);
	} |
	VarDeclList {
		$$ = new_member($1,NULL,NULL);
	} |
	/*Blank*/ {
		$$ = new_member(NULL,NULL,NULL);
	} ;

VarDeclList : /* (VarDecl)+ */
	VarDeclList VarDecl {
		push_into_vardecl_list($1,$2);
		$$ = $2;
	} |
	VarDecl {
		$$ = $1;
	} ;

MethodDeclList : /* (MethodDecl)+ */
	MethodDeclList MethodDecl {
		push_into_methoddecl_list($1,$2);
		$$ = $2;
	} |
	MethodDecl {
		$$ = $1;
	} ;

MethodDefList : /* (FuncDef)+ */
	MethodDefList MethodDef {
		push_into_methoddef_list($1,$2);
		$$ = $2;
	} |
	MethodDef {
		$$ = $1;
	} ;

VarDecl : /* Type Ident (= (intnum | floatnum))? ; */
	Type Ident EQUAL INTNUM SEMICOLON {
		$$ = new_vardecl($1,$2,$4,eAsInt);
	} |
	Type Ident EQUAL FLOATNUM SEMICOLON {
		$$ = new_vardecl($1,$2,$4,eAsFloat);
	} |
	Type Ident SEMICOLON {
		$$ = new_vardecl($1,$2,NULL,eNon);
	} ;

MethodDecl : /* Type id ( (ParamList)? ); */
	Type ID LPAREN ParamList RPAREN SEMICOLON {
		$$ = new_methoddecl($1,$2,$4);
	} |
	Type ID LPAREN RPAREN SEMICOLON {
		$$ = new_methoddecl($1,$2,NULL);
	} ;

MethodDef : /* Type id ( (ParamList)? ) CompoundStmt */
	Type ID LPAREN ParamList RPAREN CompoundStmt {
		$$ = new_methoddef($1,$2,$4,$6);
	} |
	Type ID LPAREN RPAREN CompoundStmt {
		$$ = new_methoddef($1,$2,NULL,$5);
	} ;

ClassMethodList : /* (ClassMethodDef)+ */
	ClassMethodList ClassMethodDef {
		push_into_classmethod_list($1,$2);
		$$ = $2;
	} |
	ClassMethodDef {
		$$ = $1;
	} ;

ClassMethodDef : /* Type id :: id ( (ParamList)? ) CompoundStmt */
	Type ID COLON COLON ID LPAREN ParamList RPAREN CompoundStmt {
		$$ = new_classmethoddef($1,$2,$5,$7,$9);
	} |
	Type ID COLON COLON ID LPAREN RPAREN CompoundStmt {
		$$ = new_classmethoddef($1,$2,$5,NULL,$8);
	} ;

MainFunc : /* int main ( ) CompoundStmt */
	INT MAIN LPAREN RPAREN CompoundStmt {
		$$ = new_mainfunc($5);
	};

ParamList : /* Param (, Param)* */
	ParamList COMMA Param {
		push_into_param_list($1,$3);
		$$ = $3;
	} |
	Param {
		$$ = $1;
	} ;

Param : /* Type Ident */
	Type Ident {
		$$ = new_param($1,$2);
	} ;

Ident : /* id | id [ intnum ] */
	ID {
		$$ = new_ident($1,NULL);
	} |
	ID LBRACK INTNUM RBRACK {
		$$ = new_ident($1,$3);
	} ;

Type : /* int | float | id */
	INT {
		$$ = new_type($1,eInt);
	} |
	FLOAT {
		$$ = new_type($1,eFloat);
	} |
	ID {
		$$ = new_type($1,eClass);
	} ;

CompoundStmt : /* { (VarDeclList)? (StmtList)? } */
	LBRACE VarDeclList StmtList RBRACE {
		$$ = new_compoundstmt($2,$3);
	} |
	LBRACE StmtList RBRACE {
		$$ = new_compoundstmt(NULL,$2);
	} |
	LBRACE VarDeclList RBRACE {
		$$ = new_compoundstmt($2,NULL);
	} |
	LBRACE RBRACE {
		$$ = new_compoundstmt(NULL,NULL);
	} ;

StmtList : /* (Stmt)+ */
	StmtList Stmt {
		push_into_stmt_list($1,$2);
		$$ = $2;
	} |
	Stmt {
		$$ = $1;
	} ;

Stmt : /* ExprStmt | AssignStmt | RetStmt | WhileStmt | DoStmt | ForStmt | IfStmt | CompoundStmt | ; */
	ExprStmt {
		union union_stmt s;
		s.exprStmt = $1;
		$$ = new_stmt(s,eExpr);
	} |
	AssignStmt {
		union union_stmt s;
		s.assignStmt = $1;
		$$ = new_stmt(s,eAssign);
	} |
	RetStmt {
		union union_stmt s;
		s.retStmt = $1;
		$$ = new_stmt(s,eRet);
	} |
	WhileStmt {
		union union_stmt s;
		s.whileStmt = $1;
		$$ = new_stmt(s,eWhile);
	} |
	DoStmt {
		union union_stmt s;
		s.doStmt = $1;
		$$ = new_stmt(s,eDo);
	} |
	ForStmt {

		union union_stmt s;
		s.forStmt = $1;
		$$ = new_stmt(s,eFor);
	} |
	IfStmt {
		union union_stmt s;
		s.ifStmt = $1;
		$$ = new_stmt(s,eIf);
	} |
	CompoundStmt {
		union union_stmt s;
		s.compoundStmt = $1;
		$$ = new_stmt(s,eCompound);
	} |
	SEMICOLON {
		union union_stmt s;
		$$ = new_stmt(s,eSemi);
	} ;

ExprStmt : /* Expr ; */
	Expr SEMICOLON {
		$$ = new_exprstmt($1);
	} ;

AssignStmt : /* RefVarExpr = Expr ; */
	RefVarExpr EQUAL Expr SEMICOLON {
		$$ = new_assignstmt($1,$3);
	} ;

RetStmt : /* return (EXPR)? ; */
	RETURN Expr SEMICOLON {
		$$ = new_retstmt($2);
	} |
	RETURN SEMICOLON{
		$$ = new_retstmt(NULL);
	}

WhileStmt : /* while ( Expr ) Stmt */
	WHILE LPAREN Expr RPAREN Stmt {
		$$ = new_whilestmt($3,$5);
	} ;

DoStmt : /* do Stmt while ( Expr ) ; */
	DO Stmt WHILE LPAREN Expr RPAREN SEMICOLON {
		$$ = new_dostmt($2,$5);
	} ;

ForStmt : /* for ( Expr ; Expr ; Expr ) Stmt */
	FOR LPAREN Expr SEMICOLON Expr SEMICOLON Expr RPAREN Stmt {
		$$ = new_forstmt($3,$5,$7,$9);
	} ;

IfStmt : /* if ( Expr ) Stmt (else Stmt)? */
	IF LPAREN Expr RPAREN Stmt ELSE Stmt {
		$$ = new_ifstmt($3,$5,$7);
	} |
	IF LPAREN Expr RPAREN Stmt {
		$$ = new_ifstmt($3,$5,NULL);
	} ;

Expr : /* OperExpr | RefExpr | intnum | floatnum */
	OperExpr {
		union union_expr e;
		e.operExpr = $1;
		$$ = new_expr(e,eOper);
	} |
	RefExpr {
		union union_expr e;
		e.refExpr = $1;
		$$ = new_expr(e,eRef);
	} |
	INTNUM {
		union union_expr e;
		e.intnum = $1;
		$$ = new_expr(e,eIntnum);
	} |
	FLOATNUM {
		union union_expr e;
		e.floatnum = $1;
		$$ = new_expr(e,eFloatnum);
	} ;

OperExpr : /* unop Expr | Expr addiop Expr | Expr multop Expr | Expr relaop Expr | Expr eqltop Expr | ( Expr ) */
	UNOP Expr {
		$$ = new_operexpr($2,$1,NULL,eUn);// 0 for unop
	} |
	Expr ADDIOP Expr {
		$$ = new_operexpr($1,$2,$3,eAddi);// 1 for addiop
	} |
	Expr MULTOP Expr {
		$$ = new_operexpr($1,$2,$3,eMult);// 2 for multop
	} |
	Expr RELAOP Expr {
		$$ = new_operexpr($1,$2,$3,eRela);// 3 for relaop
	} |
	Expr EQLTOP Expr {
		$$ = new_operexpr($1,$2,$3,eEqlt);// 4 for eqltop
	} |
	LPAREN Expr RPAREN {
		$$ = new_operexpr($2,NULL,NULL,eBracket);// 5 for paren
	} ;

RefExpr : /* RefVarExpr | RefCallExpr */
	RefVarExpr {
		union union_refexpr r;
		r.refVarExpr = $1;
		$$ = new_refexpr(r,eVar);
	} |
	RefCallExpr {
		union union_refexpr r;
		r.refCallExpr = $1;
		$$ = new_refexpr(r,eCall);
	} ;

RefVarExpr : /* (RefExpr .)? IdentExpr */
	RefExpr DOT IdentExpr {
		$$ = new_refvarexpr($1,$3);
	} |
	IdentExpr {
		$$ = new_refvarexpr(NULL,$1);
	} ;

RefCallExpr : /* (RefExpr .)? CallExpr */
	RefExpr DOT CallExpr {
		$$ = new_refcallexpr($1,$3);
	} |
	CallExpr {
		$$ = new_refcallexpr(NULL,$1);
	} ;

IdentExpr : /* id [ Expr ] | id */
	ID LBRACK Expr RBRACK {
		$$ = new_identexpr($1,$3);
	} |
	ID {
		$$ = new_identexpr($1,NULL);
	} ;

CallExpr : /* id ( (ArgList)? ) */
	ID LPAREN ArgList RPAREN {
		$$ = new_callexpr($1,$3);
	} |
	ID LPAREN RPAREN {
		$$ = new_callexpr($1,NULL);
	} ;

ArgList : /* Expr (, Expr)* */
	ArgList COMMA Expr {
		struct Arg* sub_arg = new_arg($3);
		push_into_arg_list($1,sub_arg);
		$$ = sub_arg;
	} |
	Expr {
		$$ = new_arg($1);
	} ;

%%
int yyerror (char *s) {
	return fprintf(stderr, "%s!\n", s);
}
