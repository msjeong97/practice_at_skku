#ifndef LIVE_H
#define LIVE_H


#include "AST.h"
#include "cfg_lib.h"
#include "timer.h"




struct IDList{
	char *ID;
	struct IDList *next;
};
struct IdentList{
	char *ID;
	int index;
	struct IdentList *next;
};
struct WorkList{
	struct cfg_block *block;
	struct WorkList *next;
};


int start_liveness (struct cfg_procedure *);

void liveness(struct cfg_procedure *);
void temp_proc(struct cfg_procedure *);

void temp_func(struct cfg_block *);
void func(struct cfg_block * );
void temp_varDecl(struct VarDecl *, struct IDList* ,struct cfg_step * r, struct cfg_block *);

void temp_set(struct cfg_block *,struct cfg_step *,struct IDList *);

void setUseDef(struct cfg_block *);
	
void getIDExpr(struct IDList *,struct Expr *);
	
void getIDRefVar(struct IDList *,struct RefVarExpr *);
void getIDRefCall(struct IDList *,struct RefCallExpr *);


int getIndex(char *);

void initIn(struct cfg_block *);
	
void initOut(struct cfg_block *);
	
void setInOut(struct cfg_block *);
	
void addWorkAll(struct WorkList *, struct cfg_block *);
	
void addWork(struct WorkList *, struct cfg_block *);
	
void printLiveness(struct cfg_block *);
	


void subtraction(int *, int *, int *);


//void not(int *, int *);
//void and(int *, int *,int *);


void ori(int *, int *, int *);




#endif