#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "live.h"
#include "cfg_lib.h"
#include "timer.c"
#define MAX 50

FILE *fp;
char *ids[300] = {NULL,};
int func_count = 0;

int start_liveness (struct cfg_procedure * cp) {
	fp = fopen("Liveness.out", "w");
	fprintf(fp, "# The Result of Livenss Analysis\n\n");
	liveness(cp);
	fclose (fp);
	return 0;
}

void liveness(struct cfg_procedure * cp){
	double time_lapse;
	//struct cfg_procedure *temp_procedure = head;
	struct cfg_block *temp_block;
	
	set_timer();

	temp_proc(cp);

	time_lapse = lab_timer();
	fprintf(fp,"\n%.7f seconds take.\n",time_lapse);
}
void temp_proc(struct cfg_procedure *temp_procedure){
	struct cfg_block * temp_block;
	int i;
	if(temp_procedure == NULL)
		return;
	if(temp_procedure->prev){
		//printf("123\n");
		temp_proc(temp_procedure->prev);
	}
	fprintf(fp, "%s\n",temp_procedure->name);
	//printf("%s\n",temp_procedure->name);/////
	fprintf(fp, "       Begin (IN)       Begin (OUT)\n");
	temp_block = temp_procedure->end_block;
	/*for(i=0;i<50;i++){
		temp_block->in[i] = 0;
		temp_block->out[i] = 0;
		temp_block->def[i] = 0;
		temp_block->use[i] = 0;
	}*/
	temp_func(temp_block);
	for(i=0;i<300;i++){
		ids[i] = NULL;
	}

	//printf("\n");//////
	func_count++;
}

void temp_func(struct cfg_block * cfgBlock){
	if(cfgBlock->type == e_start)
		return;
	if(cfgBlock->prev)
		temp_func(cfgBlock->prev);
	if(cfgBlock->type == e_normal)
		func(cfgBlock);
}

void func(struct cfg_block * cfgBlock){//count is A B ...
	int i;//printf("func\n");
	//printf("start\n",func_count);
	setUseDef(cfgBlock);
	/*for(i=0;i<MAX;i++){
		if(ids[i])
			printf("iter : in : %d, out : %d use : %d def : %d | %s\n",cfgBlock->in[i],cfgBlock->out[i],cfgBlock->use[i],cfgBlock->def[i],ids[i]);
		
	}*/
	//printf("\n");


	initIn(cfgBlock);
	/*for(i=0;i<MAX;i++){
		if(ids[i])
			printf("iter : in : %d, out : %d use : %d def : %d | %s\n",cfgBlock->in[i],cfgBlock->out[i],cfgBlock->use[i],cfgBlock->def[i],ids[i]);
		
	}*/
	//printf("\n");
	initOut(cfgBlock);
	/*for(i=0;i<MAX;i++){
		if(ids[i])
			printf("iter : in : %d, out : %d use : %d def : %d | %s\n",cfgBlock->in[i],cfgBlock->out[i],cfgBlock->use[i],cfgBlock->def[i],ids[i]);
		
	}*/
	//printf("\n");
	setInOut(cfgBlock);
	/*for(i=0;i<MAX;i++){
		if(ids[i])
			printf("iter : in : %d, out : %d use : %d def : %d | %s\n",cfgBlock->in[i],cfgBlock->out[i],cfgBlock->use[i],cfgBlock->def[i],ids[i]);
		
	}
	printf("\n");*/

	printLiveness(cfgBlock);

}
void temp_varDecl(struct VarDecl* varDecl,struct IDList* idList,struct cfg_step * stepPtr, struct cfg_block *cfgBlock){
	struct IDList *idPtr;
	struct IDList *temp = idList;
	char * temp_id;
	int index;
	if(varDecl== NULL)
		return;
	if(varDecl->prev)
		temp_varDecl(varDecl->prev,idList,stepPtr,cfgBlock);
	while(temp->next != NULL)
		temp = temp->next;
	index = getIndex(stepPtr->step.vardecl->ident->id);////

	cfgBlock->def[index] = 1;
	cfgBlock->use[index] = 0;
	free(idList);
	idList = malloc(sizeof(struct IDList));
	memset(idList,0,sizeof(struct IDList));




	///getRefVar
	//idPtr = idList;

	//while(idPtr->next != NULL)
	//	idPtr = idPtr->next;
	//idPtr->next = malloc(sizeof(struct IDList));
	//memset(idPtr->next,0,sizeof(struct IDList));
	//idPtr = idPtr->next;
	//idPtr->ID = malloc(sizeof(varDecl->ident->id));
	//memset(idPtr->ID,0,sizeof(varDecl->ident->id));
	//strcpy(idPtr->ID,varDecl->ident->id);
	/////






	//idPtr = idList->next;
	//while(idPtr != NULL){
	//	index = getIndex(idPtr->ID);
	//	cfgBlock->use[index] = 1;
	//	idPtr = idPtr->next;
	//}

}

void temp_set(struct cfg_block *cfgBlock,struct cfg_step *stepPtr,struct IDList *idList ){
	struct IDList *idPtr;
	int index=0;
	//printf("122\n");
	if(stepPtr == NULL)
		return;
	if(stepPtr->prev)
		temp_set(cfgBlock,stepPtr->prev,idList);


	if(stepPtr->type == e_vardecl){
		temp_varDecl(stepPtr->step.vardecl,idList,stepPtr,cfgBlock);

	}
	else if(stepPtr->type == e_stmt){
		if(stepPtr->step.stmt->e == e_expr){
			
			getIDExpr(idList,stepPtr->step.stmt->type.exprStmt->expr);//////
			idPtr = idList->next;
			while(idPtr != NULL){
				index = getIndex(idPtr->ID);
				cfgBlock->use[index] = 1;
				idPtr = idPtr->next;
			}
		}
		else if(stepPtr->step.stmt->e == eAssign){
			index = getIndex(stepPtr->step.stmt->type.assignStmt->refVarExpr->identExpr->id);////
			/*if(cfgBlock->def[index]==0){
				cfgBlock->def[index] = 1;
				if(cfgBlock->use[index] == 1)
					cfgBlock->use[index] = 0;
			}
			else{
				if(cfgBlock->use[index] == 1)
					cfgBlock->use[index] = 0;
			}*/
			cfgBlock->def[index] = 1;
			//cfgBlock->use[index] = 0;
			


			getIDRefVar(idList, stepPtr->step.stmt->type.assignStmt->refVarExpr);///
			free(idList);
			idList = malloc(sizeof(struct IDList));
			memset(idList,0,sizeof(struct IDList));


			getIDExpr(idList,stepPtr->step.stmt->type.assignStmt->expr);
			idPtr = idList->next;
			while(idPtr!=NULL){
				index = getIndex(idPtr->ID);////
				cfgBlock->use[index]=1;
				idPtr=idPtr->next;
			}
		}
		else if(stepPtr->step.stmt->e == eRet){
			if(stepPtr->step.stmt->type.retStmt->expr){
				getIDExpr(idList,stepPtr->step.stmt->type.retStmt->expr);//////
				idPtr = idList->next;
				while(idPtr != NULL){
					index = getIndex(idPtr->ID);
					cfgBlock->use[index] = 1;
					idPtr = idPtr->next;
				}
			}
				
		}

	}
	else if(stepPtr->type == e_expr){
		getIDExpr(idList,stepPtr->step.expr);//////
		idPtr = idList->next;
		while(idPtr != NULL){
			index = getIndex(idPtr->ID);
			cfgBlock->use[index] = 1;
			idPtr = idPtr->next;
		}

	}	
}
void setUseDef(struct cfg_block *cfgBlock){
	struct cfg_block_list *blockPtr;
	struct cfg_step *stepPtr = cfgBlock->step;
	struct IDList *idList = NULL;
	struct IDList *idPtr;
	char *name;
	int index = 0;

	idList = malloc(sizeof(struct IDList));
	memset(idList,0,sizeof(struct IDList));

	//{eExpr, eAssign, eRet, eWhile, eDo, eFor, eIf, eCompound, eSemi} Stmt_e;
	temp_set(cfgBlock,stepPtr,idList);
	cfgBlock->visit = 1;
	if(cfgBlock->succ){//////////
		blockPtr = cfgBlock->succ;
		while(blockPtr != NULL){
			if(blockPtr->block->visit != 1){
				setUseDef(blockPtr->block);
			}
			blockPtr = blockPtr->prev;
		}
	}

}
//{eOper, eRef, eIntnum, eFloatnum} Expr_e;
void getIDExpr(struct IDList *idList,struct Expr *expr){
	struct IDList *ptr = NULL;
	//{eUn, eAddi, eMult, eRela, eEqlt, eBracket} Oper_e;
	if(expr == NULL)
		return;
	if(expr->e == eOper){
		if(expr->type.operExpr->e == eUn){
			getIDExpr(idList,expr->type.operExpr->type.un->expr);
		}
		else if(expr->type.operExpr->e == eAddi){
			getIDExpr(idList,expr->type.operExpr->type.addi->lhs);
			getIDExpr(idList,expr->type.operExpr->type.addi->rhs);
		}
		else if(expr->type.operExpr->e == eMult){
			getIDExpr(idList,expr->type.operExpr->type.mult->lhs);
			getIDExpr(idList,expr->type.operExpr->type.mult->rhs);
		}
		else if(expr->type.operExpr->e == eRela){
			getIDExpr(idList,expr->type.operExpr->type.rela->lhs);
			getIDExpr(idList,expr->type.operExpr->type.rela->rhs);
		}
		else if(expr->type.operExpr->e == eEqlt){
			getIDExpr(idList,expr->type.operExpr->type.eqlt->lhs);
			getIDExpr(idList,expr->type.operExpr->type.eqlt->rhs);
		}
		else if(expr->type.operExpr->e == eBracket){
			getIDExpr(idList,expr->type.operExpr->type.bracket);
		}
	}
	//{eVar, eCall} Ref_e;
	else if(expr->e == eRef){
		if(expr->type.refExpr->e == eVar){
			getIDRefVar(idList,expr->type.refExpr->type.refVarExpr);
		}
/*		else if(expr->type.refExpr->e == eCall){
			getIDRefCall(idList,expr->type.refExpr->type.refCallExpr);
		}*/
	}
	else 
		return;
}
void getIDRefVar(struct IDList *idList,struct RefVarExpr *refVarExpr){
	struct IDList *temp = idList;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(struct IDList));
	memset(temp->next,0,sizeof(struct IDList));
	temp = temp->next;
	temp->ID = malloc(sizeof(refVarExpr->identExpr->id));
	memset(temp->ID,0,sizeof(refVarExpr->identExpr->id));
	strcpy(temp->ID,refVarExpr->identExpr->id);
	return;
}
void getIDRefCall(struct IDList *idList,struct RefCallExpr *refCallExpr){
	struct IDList *temp = idList;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(struct IDList));
	memset(temp->next,0,sizeof(struct IDList));
	temp = temp->next;
	temp->ID = malloc(sizeof(refCallExpr->callExpr->id));
	memset(temp->ID,0,sizeof(refCallExpr->callExpr->id));
	strcpy(temp->ID,refCallExpr->callExpr->id);
	return;
}

int getIndex(char *id){
	int i = 0;

	while(ids[i]){
		if(strcmp(id, ids[i])==0)
			return i;
		i++;
	}
	ids[i] = id;
	return i;
}
void initIn(struct cfg_block *cfgBlock){
	int i;
	struct cfg_block_list *blockPtr = NULL;

	cfgBlock->visit = 2;
	if(cfgBlock->succ){
		while(blockPtr != NULL){
			if(blockPtr->block->visit != 2)
				initIn(blockPtr->block);
			blockPtr = blockPtr->prev;
		}

	}
	for(i =0;i<MAX;i++)
		cfgBlock->in[i] = cfgBlock->use[i];

}
void initOut(struct cfg_block *cfgBlock){
	int i;
	struct cfg_block_list *blockPtr = NULL;
	int temp[MAX] = {0,};
	int cnt;

	cfgBlock->visit = 3;
	if(cfgBlock->succ){
		blockPtr = cfgBlock->succ;
		while(blockPtr != NULL){
			if(blockPtr->block->visit != 3 )
				initOut(blockPtr->block);
			blockPtr = blockPtr->prev;
		}
	}
	if(cfgBlock->succ){
		blockPtr = cfgBlock->succ;
		while(blockPtr != NULL){
			cnt = 0;
			//ori(temp,temp,blockPtr->block->in);
			while(cnt<MAX){
				if((temp[cnt]==1)||(blockPtr->block->in[cnt]==1))
					temp[cnt]=1;
				cnt++;
			}

			blockPtr = blockPtr->prev;
		}
	}
	for(i=0;i<MAX;i++){
		cfgBlock->out[i]=temp[i];
	}

	subtraction(cfgBlock->in, cfgBlock->out, cfgBlock->def);
	ori(cfgBlock->in, cfgBlock->in, cfgBlock->use);
}
void setInOut(struct cfg_block *cfgBlock){
	struct WorkList * workList, *workListPtr;
	struct cfg_block *block;
	int oldIn[MAX] = {0,};
	int newOut[MAX] = {0,};
	int out[MAX] = {0,};
	int flag = 1;
	int i;
	int cnt;
	struct cfg_block_list *blockPtr= NULL;
	int temp[MAX] = {0,};

	workList = malloc(sizeof(struct WorkList));
	memset(workList,0,sizeof(struct WorkList));

	addWorkAll(workList,cfgBlock);
	while((workList->next) != NULL){
		memset(oldIn, 0, sizeof(int)*MAX);
		memset(newOut, 0, sizeof(int)*MAX);
		memset(out, 0, sizeof(int)*MAX);

		block = workList->next->block;
		workList = workList->next;
		for(i=0;i<MAX;i++)
			oldIn[i] = block->in[i];
		if(block->succ){
			blockPtr = block->succ;
			while(blockPtr!=NULL){
				//ori(newOut,newOut,blockPtr->block->in);
				cnt = 0;
				while(cnt<MAX){

					if((newOut[cnt]==1)||(blockPtr->block->in[cnt]==1))
						newOut[cnt]=1;
					cnt++;
				}
				blockPtr=blockPtr->prev;
			}
		}
		for(i=0;i<MAX;i++){
			block->out[i] = newOut[i];
		}
		subtraction(block->in,block->out,block->def);
		ori(block->in,block->in,block->use);

		for(i=0;i<MAX;i++){
			if(block->in[i] != oldIn[i]){
				flag = 0;
				break;
			}
		}
		if(flag == 0){
			if(block->pred){
				blockPtr = block->pred;
				while(blockPtr != NULL){
					addWork(workList,blockPtr->block);
					blockPtr = blockPtr->prev;
				}
			}
		}
		flag = 1;
	}
}
void addWorkAll(struct WorkList *workList, struct cfg_block *cfgBlock){
	struct cfg_block_list *blockPtr = NULL;

	cfgBlock->visit = 4;
	if(cfgBlock->succ){
		blockPtr = cfgBlock->succ;
		while(blockPtr != NULL){
			if(blockPtr->block->visit != 4)
				addWorkAll(workList,blockPtr->block);
			blockPtr = blockPtr->prev;
		}
	}
	addWork(workList,cfgBlock);
}
void addWork(struct WorkList *workList, struct cfg_block *cfgBlock){
	struct WorkList *workListPtr;

	workListPtr = workList;
	while(workListPtr->next != NULL)
		workListPtr = workListPtr->next;

	workListPtr->next = malloc(sizeof(struct WorkList));
	workListPtr = workListPtr->next;
	memset(workListPtr, 0, sizeof(struct WorkList));
	workListPtr->block = cfgBlock;
}
void printLiveness(struct cfg_block *cfgBlock){
	//func_count + 'A' = block alphabet
	struct cfg_block_list * blockPtr = NULL;
	int i;
	int first = 1;
	int start_flag=0;
	cfgBlock->visit = 5;
	/*if(cfgBlock->succ){
		blockPtr = cfgBlock->succ;
		while(blockPtr != NULL){
			if(blockPtr->block->visit != 5){
				printLiveness(blockPtr->block);
			}
			blockPtr = blockPtr->prev;
		}
	}*/

	fprintf(fp,"%c%d : {",'A'+func_count,cfgBlock->num);

	for(i=0;i<MAX;i++){
		if(cfgBlock->in[i] == 1){
			if(start_flag == 0){
				fprintf(fp,"%s",ids[i]);
				start_flag = 1;
			}
			else
				fprintf(fp,", %s",ids[i]);
		}
		first = 0;
		
	}
	fprintf(fp, "}   ");

	first = 1;
	fprintf(fp, "{" );
	start_flag=0;

	for(i=0;i<MAX;i++){
		if(cfgBlock->out[i] == 1){
			if(start_flag == 0){
				fprintf(fp,"%s",ids[i]);
				start_flag = 1;
			}
			else
				fprintf(fp,", %s",ids[i]);
		}
		first = 0;
	}
	fprintf(fp,"}\n");

	
}


void subtraction(int *result, int *b1, int *b2){
	int temp[MAX]={0,};
	int cnt = 0;
	//not(temp, b2);
	while(cnt<MAX){
		if(b2[cnt]==0)
			temp[cnt]=1;
		if(b2[cnt]==1)
			temp[cnt]=0;
		cnt++;
	}
	//and(result, b1, temp);
	cnt = 0;
	while(cnt<MAX){
		if((b1[cnt]==1)&&(temp[cnt]==1))
			result[cnt]=1;
		cnt++;
	}
	return;
}

/*
void and(int *result, int *b1,int *b2){
	int cnt=0;

	while(cnt<MAX){
		if((b1[cnt]==1)&&(b2[cnt]==1))
			result[cnt]=1;
		cnt++;
	}
	return;
}
void not(int *result, int *b){
	int cnt=0;

	while(cnt<MAX){
		if(b[cnt]==0)
			result[cnt]=1;
		if(b[cnt]==1)
			result[cnt]=0;
		cnt++;
	}
	return ;
}
*/
void ori(int *result, int *b1, int *b2){
	int cnt=0;

	while(cnt<MAX){
		if((b1[cnt]==1)||(b2[cnt]==1))
			result[cnt]=1;
		cnt++;
	}

	return ;
}


