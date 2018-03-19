#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "print.h"

FILE *fp1;
FILE *fp2;
char *stack[200];
int top = 0;
int index1 = 1;
int while_num = 1;
int for_num = 1;
int do_num = 1;
int if_num = 1;
int main () {
	fp1 = fopen("ast.out", "w");
	fp2 = fopen("symt.out", "w");
	if (!yyparse ()){
		dfs ();
		dfsj();
	}
	fprintf (fp1, "\n");
	fclose (fp1);
	fprintf (fp2, "\n");
	fclose (fp2);

	return 0;
}


////print AST

void tab(int n,FILE *fp){
	int i;
	for(i=0;i<n;i++)
		fprintf(fp,"\t");
}
void dfs () {
	if (head == NULL) {
		fprintf (stderr, "expression does not exist.\n");
		return;
	}
	if(head->_class)
		Classi(head->_class);
	if(head->classMethodDef)
		ClassMethodDefi(head->classMethodDef);
	MainFunci(head->mainFunc);
	
}


void Classi(struct Class *_class){
	if(_class == NULL)
		return;
	if(_class->prev)
		Classi(_class->prev);

	fprintf(fp1, "class %s\n", _class->id);
	fprintf(fp1,"{\n");
	if(_class->priMember){
		tab(1,fp1);
		fprintf(fp1, "private :\n");
		Memberi(_class->priMember,1);
	}
	if(_class->pubMember){
		tab(1,fp1);
		fprintf(fp1, "public :\n");
		Memberi(_class->pubMember,1);
	}

	fprintf(fp1,"}\n");

}
//type classname methodname
void ClassMethodDefi(struct ClassMethodDef *classMethodDef ){
	if(classMethodDef == NULL){
		fprintf (stderr, "ClassMethodDef does not exist.\n");
		return;
	}
	if(classMethodDef->prev)
		ClassMethodDefi(classMethodDef->prev);
	
	//Typei(classMethodDef->type); 
	// is there no type?

	fprintf(fp1,"%s :: %s ",classMethodDef->className, classMethodDef-> methodName);
	fprintf(fp1, "( ");
	if(classMethodDef-> param)
		Parami(classMethodDef->param);
	fprintf(fp1, ")\n");
	CompoundStmti(classMethodDef->compoundStmt,0);
	// there is no classMethodList
	

}

void MainFunci(struct MainFunc *mainFunc){
	if (mainFunc == NULL) {
		fprintf (stderr, "Main function does not exist.\n");
		return;
	}
	fprintf(fp1, "int main()\n");
	CompoundStmti(mainFunc->compoundStmt,0);
}
void Typei(struct Type *type){
	if(type->e == eInt)
		fprintf(fp1, "int ");
	else if(type->e == eFloat)
		fprintf(fp1, "float ");
	else if(type->e == eClass)
		fprintf(fp1, "%s ",type->id);
	else
		fprintf(stderr, "Type does not exist. \n");
}


void CompoundStmti(struct CompoundStmt *compoundStmt, int n){
	tab(n-1,fp1);
	fprintf(fp1, "{\n");
	if(compoundStmt->varDecl)
		VarDecli(compoundStmt->varDecl,n+1);
	if(compoundStmt->stmt)
		Stmti(compoundStmt->stmt,n+1);
	tab(n-1,fp1);
	fprintf(fp1, "}\n");
}
void inCompoundStmti(struct CompoundStmt *compoundStmt, int n){
	tab(n,fp1);
	fprintf(fp1, "{\n");
	if(compoundStmt->varDecl)
		VarDecli(compoundStmt->varDecl,n+1);
	if(compoundStmt->stmt){
		if(compoundStmt -> stmt -> e == eSemi)
			Stmti(compoundStmt->stmt,n+2);
		else
			Stmti(compoundStmt->stmt,n+1);
	}
	tab(n,fp1);
	fprintf(fp1, "}\n");
}

void Parami(struct Param *param){
	if(param == NULL)
		return;
	if(param->prev){
		Parami(param->prev);
		fprintf(fp1, " , ");
	}
	Typei(param->type);
	Identi(param->ident);

	
}

void Memberi(struct Member *member,int n){
	if(member == NULL)
		return;
	if(member->varDecl){
		VarDecli(member->varDecl,n+1);
	}
	if(member->methodDecl)
		MethodDecli(member->methodDecl,n+1);
	if(member->methodDef)
		MethodDefi(member->methodDef,n+1);
}

void Identi(struct Ident *ident){
	if(ident-> len == 0){ // scalar
		fprintf(fp1, "%s", ident->id);
	}
	else{
		fprintf(fp1, "%s[%d]",ident->id, ident->len);
	}

}
//{eNon, eAsInt, eAsFloat} Assign_e;
void VarDecli(struct VarDecl *varDecl,int n){
	if(varDecl == NULL)
		return;
	if(varDecl->prev)
		VarDecli(varDecl->prev,n);
	tab(n,fp1);
	Typei(varDecl->type);
	Identi(varDecl->ident);

	if(varDecl->assignType == eNon){
		fprintf(fp1,";\n");
	}
	else if(varDecl->assignType == eAsInt){
		fprintf(fp1, " = ");
		fprintf(fp1,"%d;\n",varDecl->assigner.intnum);
	}
	else if(varDecl->assignType == eAsFloat){
		fprintf(fp1, " = ");
		fprintf(fp1,"%.3f;\n",varDecl->assigner.floatnum);
	}

	

}

void MethodDecli( struct MethodDecl *methodDecl,int n){
	if(methodDecl->prev)
		MethodDecli(methodDecl->prev,n);
	tab(n,fp1);
	Typei(methodDecl->type);
	fprintf(fp1, "%s ", methodDecl->id);
	fprintf(fp1, "( ");
	if(methodDecl->param)
		Parami(methodDecl->param);
	fprintf(fp1, " );\n");

}

void MethodDefi( struct MethodDef *methodDef,int n){
	if(methodDef->prev)
		MethodDefi(methodDef->prev,n);
	tab(n,fp1);
	Typei(methodDef->type);
	fprintf(fp1, "%s ", methodDef->id);
	fprintf(fp1, "( ");
	if(methodDef->param)
		Parami(methodDef->param);
	fprintf(fp1, " )\n");

	inCompoundStmti(methodDef->compoundStmt,n);

}
//eAssign, eRet, eWhile, eDo, eFor, eIf, eCompound, eSemi

void Stmti(struct Stmt *stmt,int n){
	if(stmt == NULL)
		return;
	if(stmt->prev)
		Stmti(stmt->prev,n);
	if(stmt->e == eExpr){
		if(stmt->type.exprStmt->expr != NULL){//expr is null?
			if(stmt->type.exprStmt->expr->e == eRef){//check expr type
				if(stmt->type.exprStmt->expr->type.refExpr != NULL){//refExpr is null?
					if(stmt->type.exprStmt->expr->type.refExpr->e == eVar){//check refexpr type
						//if(stmt->type.exprStmt->expr->type.refExpr->type.refVarExpr->refExpr == NULL)
							//tab(n-1,fp1);
					}
					else if(stmt->type.exprStmt->expr->type.refExpr->e == eCall){
						if(stmt->type.exprStmt->expr->type.refExpr->type.refCallExpr->refExpr == NULL)
							tab(n-1,fp1);
					}

				}
			}
		}
		
		ExprStmti(stmt->type.exprStmt,n);
	}
	else if(stmt->e == eAssign )
		AssignStmti(stmt->type.assignStmt,n);
	else if(stmt->e == eRet)
		RetStmti(stmt->type.retStmt,n);
	else if(stmt->e == eWhile)
		WhileStmti(stmt->type.whileStmt,n+1);
	else if(stmt->e == eDo)
		DoStmti(stmt->type.doStmt,n+1);
	else if(stmt->e == eFor)
		ForStmti(stmt->type.forStmt,n+1);
	else if(stmt->e == eIf)
		IfStmti(stmt->type.ifStmt,n+1);
	else if(stmt->e == eCompound){
		fprintf(fp1,"\n");
		inCompoundStmti(stmt->type.compoundStmt,n);
	}
	else if(stmt->e == eSemi){
		tab(n-1,fp1);
		fprintf(fp1,";\n");
	}
	
	//fprintf(fp1,"\n");
}

void ExprStmti(struct ExprStmt *expr_,int n){
	tab(n,fp1);
	Expri(expr_->expr,n);
	fprintf(fp1,";\n");

}

void AssignStmti(struct AssignStmt *assign_,int n){
	tab(n,fp1);
	RefVarExpri(assign_->refVarExpr,n);
	fprintf(fp1, " = ");
	Expri(assign_->expr,n);
	fprintf(fp1,";\n");
}

void RetStmti(struct RetStmt *ret_,int n){
	tab(n,fp1);
	fprintf(fp1,"return ");
	if(ret_->expr)
		Expri(ret_->expr,n);
	fprintf(fp1,";\n");
}

void WhileStmti(struct WhileStmt *while_,int n){
	tab(n-1,fp1);
	fprintf(fp1, "while( ");
	Expri(while_->cond,n);
	fprintf(fp1," )");
	Stmti(while_->body,n-1);
}

void DoStmti(struct DoStmt *do_,int n){
	tab(n-1,fp1);
	fprintf(fp1,"do \n");
	tab(n,fp1);
	Stmti(do_->body,n-1);
	tab(n-1,fp1);
	fprintf(fp1,"while( ");
	Expri(do_->cond,n);
	fprintf(fp1,");\n");
}

void ForStmti(struct ForStmt *for_,int n){
	tab(n-1,fp1);
	fprintf(fp1, "for( ");
	Expri(for_->init,n);
	fprintf(fp1, " ; ");
	Expri(for_->cond,n);
	fprintf(fp1, " ; ");
	Expri(for_->incr,n);
	fprintf(fp1, " )");
	Stmti(for_->body,n-1);
	
}

void IfStmti(struct IfStmt *if_,int n){
	tab(n-1,fp1);
	fprintf(fp1, "if( ");
	Expri(if_->cond,n);
	fprintf(fp1," )");
	Stmti(if_->ifBody,n-1);
	if(if_->elseBody){
		tab(n-1,fp1);
		fprintf(fp1,"else\n");
		if(if_->elseBody != NULL){
			if(if_->elseBody->e== eCompound)
				Stmti(if_->elseBody,n-1);
			else
				Stmti(if_->elseBody,n);
		}
	}
}
//{eOper, eRef, eIntnum, eFloatnum} Expr_e;
void Expri(struct Expr *expr, int n){
	if(expr == NULL)
		return;
	if(expr->e == eOper)
		OperExpri(expr->type.operExpr,n);
	else if(expr->e == eRef)
		RefExpri(expr->type.refExpr,n);
	else if(expr->e == eIntnum)
		fprintf(fp1,"%d",expr->type.intnum);
	else if(expr->e == eIntnum)
		fprintf(fp1,"%.3f",expr->type.floatnum);

}
void RefVarExpri(struct RefVarExpr *refVarExpr,int n){

	if(refVarExpr->refExpr){
		RefExpri(refVarExpr->refExpr,n);
		fprintf(fp1, ".");
	}
	IdentExpri(refVarExpr->identExpr,n);
}
//{eUn, eAddi, eMult, eRela, eEqlt, eBracket} Oper_e;
void OperExpri(struct OperExpr *operExpr,int n){
	if(operExpr->e == eUn)
		UnOpi(operExpr->type.un,n);
	else if(operExpr->e == eAddi)
		AddiOpi(operExpr->type.addi,n);
	else if(operExpr->e == eMult)
		MultOpi(operExpr->type.mult,n);
	else if(operExpr->e == eRela)
		RelaOpi(operExpr->type.rela,n);
	else if(operExpr->e == eEqlt)
		Eqlti(operExpr->type.eqlt,n);
	else if(operExpr->e == eBracket){
		fprintf(fp1, "( ");
		Expri(operExpr->type.bracket,n);
		fprintf(fp1, " )");
	}

}
//{eVar, eCall} Ref_e;
void RefExpri(struct  RefExpr *refExpr,int n){
	if(refExpr == NULL)
		return;
	if(refExpr->e == eVar){
		RefVarExpri(refExpr->type.refVarExpr,n);
	}
	else if(refExpr->e == eCall){
		RefCallExpri(refExpr->type.refCallExpr,n);
	}

}

void IdentExpri(struct IdentExpr *identExpr,int n){
	if(identExpr->expr){
		fprintf(fp1,"%s[",identExpr->id);
		Expri(identExpr->expr,n);
		fprintf(fp1,"]");
	}
	else{
		fprintf(fp1,"%s",identExpr->id);
	}
}
//{eNegative} Unop_e;
void  UnOpi(struct UnOp *unop,int n){
	if(unop->e == eNegative){
		fprintf(fp1,"-");
		Expri(unop->expr,n);
	}

}

//{ePlus, eMinus} Addi_e;
void AddiOpi(struct AddiOp *addiop,int n){
	if(addiop->e == ePlus){
		Expri(addiop->lhs,n);
		fprintf(fp1," + ");
		Expri(addiop->rhs,n);
	}
	else if(addiop->e == eMinus){
		Expri(addiop->lhs,n);
		fprintf(fp1," - ");
		Expri(addiop->rhs,n);
	}

}

//{eMul, eDiv} Mult_e;
void MultOpi(struct MultOp * multop,int n){
	if(multop->e == eMul){
		Expri(multop->lhs,n);
		fprintf(fp1," * ");
		Expri(multop->rhs,n);
	}
	else if(multop->e == eDiv){
		Expri(multop->lhs,n);
		fprintf(fp1," / ");
		Expri(multop->rhs,n);
	}

}

//{eLT, eGT, eLE, eGE} Rela_e;
void RelaOpi(struct RelaOp * relaop,int n){
	if(relaop->e == eLT){
		Expri(relaop->lhs,n);
		fprintf(fp1," < ");
		Expri(relaop->rhs,n);
	}
	else if(relaop->e == eGT){
		Expri(relaop->lhs,n);
		fprintf(fp1," > ");
		Expri(relaop->rhs,n);
	}
	else if(relaop->e == eLE){
		Expri(relaop->lhs,n);
		fprintf(fp1," <= ");
		Expri(relaop->rhs,n);
	}
	else if(relaop->e == eGE){
		Expri(relaop->lhs,n);
		fprintf(fp1," >= ");
		Expri(relaop->rhs,n);
	}

}

//{eEQ, eNE} Eqlt_e;
void Eqlti(struct EqltOp *eqltop,int n){
	if(eqltop->e == eEQ){
		Expri(eqltop->lhs,n);
		fprintf(fp1," == ");
		Expri(eqltop->rhs,n);
	}
	else if(eqltop->e == eNE){
		Expri(eqltop->lhs,n);
		fprintf(fp1," != ");
		Expri(eqltop->rhs,n);

	}

}

//
void RefCallExpri(struct RefCallExpr *refCallExpr,int n){
	if(refCallExpr->refExpr){
		RefExpri(refCallExpr->refExpr,n);
		fprintf(fp1, ".");
	}
	/*else{
		tab(n,fp1);
	}*/
	CallExpri(refCallExpr->callExpr,n);
	

}

void CallExpri( struct CallExpr *callExpr,int n){
	//tab(n,fp1);
	fprintf(fp1,"%s(",callExpr->id);
	if(callExpr->arg)
		Argi(callExpr->arg,n);
	fprintf(fp1,")");
}

void Argi(struct Arg *arg,int n){
	if(arg == NULL)
		return;
	if(arg->prev){
		Argi(arg->prev,n);
		fprintf(fp1, ", ");
	}
	Expri(arg->expr,n);
}

///////////////print symbol table
void insert(char *str){
	stack[top] = malloc(sizeof(str));
	stack[top] = str;
	top++;
}
void pop(){
	if(top >0){
		stack[top] = NULL;
		free(stack[top]);
		top--;
	}
	else
		fprintf (stderr, "Can't pop.\n");
}
void print_stack(){
	int i;
	if(top < 1){
		fprintf (stderr, "Can't print_stack.\n");
		return;
	}
	fprintf(fp2,"\nLocation : ");
	if(top >1){
		fprintf(fp2,"%s ",stack[0]);
		for(i=1;i<top;i++){
			fprintf(fp2,"- %s ",stack[i]);
		}
		fprintf(fp2,"\n");
	}
	else{//top  == 1, one stack element
		fprintf(fp2,"%s\n",stack[0]);
	}
}


void dfsj(){
	if (head == NULL) {
		
		fprintf (stderr, "expression does not exist.\n");
		return;
	}
	if(head->_class)
		Classj(head->_class);
	if(head->classMethodDef)
		ClassMethodDefj(head->classMethodDef);
	MainFuncj(head->mainFunc);

}
void Classj(struct Class *_class){
	if(_class == NULL)
		return;
	if(_class->prev)
		Classj(_class->prev);
	insert(_class->id);
	index1 = 1;
	if(_class->priMember){
		print_stack();
		fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
				   "Count", "Type", "Name ", "Array", "Role");
		Memberj1(_class->priMember);
		if(_class -> pubMember)
			Memberj1(_class -> pubMember);
		Memberj2(_class->priMember);
	}
	if(_class -> pubMember){
		Memberj2(_class->pubMember);
	}
	pop();
	index1 = 1;	
}
void Memberj1(struct Member *member){
	if(member == NULL)
		return;
	if(member->varDecl){
		VarDeclj(member->varDecl);
	}
}
void Memberj2(struct Member *member){
	if(member == NULL)
		return;
	if(member->methodDecl){
		MethodDeclj(member->methodDecl);
	}
	if(member->methodDef){
		MethodDefj(member->methodDef);
	}
}
void VarDeclj(struct VarDecl *varDecl){
	if(varDecl == NULL)
		return;
	if(varDecl->prev){
		VarDeclj(varDecl->prev);
	}
	if(varDecl->ident->len == 0){
		if(varDecl->type->e == eFloat){
			fprintf(fp2, "%-5d %-5s %-20s %-5s %-10s\n",
				   index1, "Float", varDecl->ident->id, "-", "Variable");
		}
		else if(varDecl->type->e == eInt){
			fprintf(fp2, "%-5d %-5s %-20s %-5s %-10s\n",
				   index1, "Int", varDecl->ident->id, "-", "Variable");
		}
		else{
			fprintf(fp2, "%-5d %-5s %-20s %-5s %-10s\n",
				   index1, varDecl->type->id, varDecl->ident->id, "-", "Variable");
		}
	}
	else{//array
		if(varDecl->type->e == eFloat){
			fprintf(fp2, "%-5d %-5s %-20s %-5d %-10s\n",
			 	  index1, "Float", varDecl->ident->id, varDecl->ident->len, "Variable");
		}
		else if(varDecl->type->e == eInt){
			fprintf(fp2, "%-5d %-5s %-20s %-5d %-10s\n",
			 	  index1, "Int", varDecl->ident->id, varDecl->ident->len, "Variable");

		}
		else{
			fprintf(fp2, "%-5d %-5s %-20s %-5d %-10s\n",
				   index1, varDecl->type->id, varDecl->ident->id, varDecl->ident->len, "Variable");
		}
	}
	index1++;
}
void MethodDeclj(struct MethodDecl * methodDecl){
	if(methodDecl->prev){
		MethodDeclj(methodDecl->prev);
	}
	index1 = 1;
	insert(methodDecl->id);
	print_stack();
	fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
			   "Count", "Type", "Name ", "Array", "Role");
	if(methodDecl->param){
		Paramj(methodDecl->param);
	}
	pop();

}
void Paramj(struct Param *param){
	if(param == NULL)
		return;
	if(param->prev){
		Paramj(param->prev);
	}
	if(param->ident->len == 0){
		if(param->type->e == eFloat){
			fprintf(fp2, "%-5d %-5s %-20s %-5s %-10s\n",
		   			index1,"Float", param->ident->id, "-", "Parameter");
		}
		else{
			fprintf(fp2, "%-5d %-5s %-20s %-5s %-10s\n",
		   			index1,"Int", param->ident->id, "-", "Parameter");

		}
	}
	else{
		if(param->type->e == eFloat){
			fprintf(fp2, "%-5d %-5s %-20s %-5d %-10s\n",
		   			index1,"Float", param->ident->id, param->ident->len, "Parameter");
		}
		else{
			fprintf(fp2, "%-5d %-5s %-20s %-5d %-10s\n",
		   			index1,"Int", param->ident->id, param->ident->len, "Parameter");
		}
	}
	index1++;
}
void MethodDefj(struct MethodDef *methodDef){
	if(methodDef->prev)
		MethodDefj(methodDef->prev);
	index1 = 1;
	insert(methodDef->id);
	print_stack();
	fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
			   "Count", "Type", "Name ", "Array", "Role");
	if(methodDef->param){
		Paramj(methodDef->param);
	}
	while_num = 1;if_num = 1;for_num = 1;do_num = 1;

	if(methodDef->compoundStmt->varDecl){
		VarDeclj(methodDef->compoundStmt->varDecl);
	}
	index1 = 1;
	if(methodDef->compoundStmt->stmt){
		Stmtj(methodDef->compoundStmt->stmt);
	}	
	pop();
	while_num = 1;if_num = 1;for_num = 1;do_num = 1;index1 = 1;

}

void ClassMethodDefj(struct ClassMethodDef *classMethodDef ){
	if(classMethodDef->prev)
		ClassMethodDefj(classMethodDef->prev);
	insert(classMethodDef->className);
	insert(classMethodDef->methodName);
	print_stack();
	fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
			   "Count", "Type", "Name ", "Array", "Role");
	index1 = 1;
	if(classMethodDef->param){
		Paramj(classMethodDef->param);
	}
	while_num = 1;if_num = 1;for_num = 1;do_num = 1;

	CompoundStmtj(classMethodDef->compoundStmt);
	pop();
	pop();
	while_num = 1;if_num = 1;for_num = 1;do_num = 1;index1 = 1;
}
void CompoundStmtj(struct CompoundStmt * compoundStmt){
	if(compoundStmt->varDecl){
		print_stack();
		fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
			   "Count", "Type", "Name ", "Array", "Role");
		VarDeclj(compoundStmt->varDecl);
	}
	index1 = 1;
	if(compoundStmt->stmt){
		Stmtj(compoundStmt->stmt);
	}	
}

void  Stmtj(struct Stmt * stmt){
	if(stmt->prev){
		Stmtj(stmt->prev);
	}
	if(stmt->e == eWhile){
		WhileStmtj(stmt->type.whileStmt);
	}
	else if(stmt->e == eDo){
		DoStmtj(stmt->type.doStmt);
	}
	else if(stmt->e == eFor){
		ForStmtj(stmt->type.forStmt);
	}
	else if(stmt->e == eIf){
		IfStmtj(stmt->type.ifStmt);
	}
	else if(stmt->e == eCompound){
		CompoundStmtj(stmt->type.compoundStmt);
	}
}
void WhileStmtj(struct WhileStmt * whileStmt){

	char str[] = "While(";
	char str_[] = ")";
	char num_str[5];
	sprintf(num_str,"%d",while_num);
	strcat(str,num_str);
	strcat(str,str_);

	insert(str);
	while_num++;
	/*if(whileStmt->body->e == eCompound ){
		print_stack();
		fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
			   "Count", "Type", "Name ", "Array", "Role");
	}*/
	Stmtj(whileStmt->body);
	pop();
}
void DoStmtj(struct DoStmt *doStmt){
	char str[] = "Do(";
	char str_[] = ")";
	char num_str[5];
	sprintf(num_str,"%d",do_num);
	strcat(str,num_str);
	strcat(str,str_);

	insert(str);
	do_num++;
	/*if(doStmt->body->e == eCompound){
		print_stack();
		fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
			   "Count", "Type", "Name ", "Array", "Role");
	}*/
	Stmtj(doStmt->body);
	pop();

}
void ForStmtj(struct ForStmt *forStmt){
	char str[] = "For(";
	char str_[] = ")";
	char num_str[5];
	sprintf(num_str,"%d",for_num);
	strcat(str,num_str);
	strcat(str,str_);

	insert(str);
	for_num++;
	/*if(forStmt->body->e == eCompound){
		print_stack();
		fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
			   "Count", "Type", "Name ", "Array", "Role");
	}*/
	Stmtj(forStmt->body);
	pop();

}
void IfStmtj(struct IfStmt *ifStmt){
	char str[] = "If(";
	char a[] = "Else(";
	char str_[] = ")";
	char num_str[5];
	sprintf(num_str,"%d",if_num);
	strcat(str,num_str);
	strcat(str,str_);

	insert(str);
	if_num++;
	/*if(ifStmt->ifBody->e == eCompound){
		print_stack();
		fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
			   "Count", "Type", "Name ", "Array", "Role");
	}*/
	Stmtj(ifStmt->ifBody);
	pop();
	if(ifStmt->elseBody){
		strcat(a,num_str);
		strcat(a,str_);
		insert(a);
		/*if(ifStmt->elseBody->e == eCompound){
			print_stack();
			fprintf(fp2, "%-5s %-5s %-20s %-5s %-10s\n",
				   "Count", "Type", "Name ", "Array", "Role");
		}*/
		Stmtj(ifStmt->elseBody);
		pop();
	}
}
void MainFuncj(struct MainFunc *mainFunc){
	insert("main");
	CompoundStmtj(mainFunc->compoundStmt);
	pop();
}