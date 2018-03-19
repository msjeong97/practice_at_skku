#include "cfg_lib.h"
#include "live.c"

#define MAX_NAME 20

FILE* fp_cfg;

struct cfg_procedure* global_cfg_procedure;

int main(){
	struct cfg_block* test_block;

	fp_cfg = fopen("CFG.out", "w");
	fprintf(fp_cfg, "# Control Flow Graph\n");
	if (!yyparse()){
		global_cfg_procedure = NULL;
		construct_cfg_program(head);
		print_cfg_procedure(global_cfg_procedure);
		start_liveness(global_cfg_procedure);
	}

	fclose(fp_cfg);

	return 0;
}

char print_cfg_procedure(struct cfg_procedure* head_procedure){
	char block_name;

	if(head_procedure == NULL) return 'A';

	block_name = print_cfg_procedure(head_procedure->prev);

	fprintf(fp_cfg, "\n%s	[%c0-%d]\n",
						head_procedure->name,
						block_name,
						head_procedure->num
		);

	// before print block, initialize num
	initialize_cfg_block_num(head_procedure->end_block->prev);
	print_cfg_block(head_procedure->end_block->prev, block_name);

	return block_name + 1;
}

int initialize_cfg_block_num(struct cfg_block* head_block){
	int prev_block_num;

	if(head_block->type == e_start) return -1;

	prev_block_num = initialize_cfg_block_num(head_block->prev);
	
	head_block->num = prev_block_num + 1;

	return head_block->num;
}

int print_cfg_block(struct cfg_block* head_block, char block_name){
	int block_num;

	if(head_block->type == e_start) return 1;

	print_cfg_block(head_block->prev, block_name);

	fprintf(fp_cfg, "%c%d\n{\n", block_name, head_block->num);

	print_cfg_step(head_block->step);

	fprintf(fp_cfg, "}\nPredecessor: ");

	print_cfg_block_list(head_block->pred,block_name);

	fprintf(fp_cfg, "\nSuccessor: ");

	print_cfg_block_list(head_block->succ,block_name);

	fprintf(fp_cfg, "\n\n");

	return 1;
}

int print_cfg_step(struct cfg_step* head_step){
	
	if(head_step == NULL) return 1;

	print_cfg_step(head_step->prev);

	fprintf(fp_cfg,"\t");
	if(head_step->type == e_vardecl) print_vardecl(head_step->step.vardecl);
	else if(head_step->type == e_stmt) print_stmt(head_step->step.stmt);
	else if(head_step->type == e_expr) print_expr(head_step->step.expr);
	else fprintf(stderr, "error: invalid step type\n");

	fprintf(fp_cfg, "\n");

	return 1;
}

int print_vardecl(struct VarDecl* head_vardecl){

	if(head_vardecl == NULL) return 0;

	if(head_vardecl->type->e == eInt) fprintf(fp_cfg,"int ");
	else if(head_vardecl->type->e == eFloat) fprintf(fp_cfg,"float ");
	else if(head_vardecl->type->e == eClass) fprintf(fp_cfg,"%s ",head_vardecl->type->id);

	fprintf(fp_cfg,"%s",head_vardecl->ident->id);

	if(head_vardecl->assignType == eAsInt) fprintf(fp_cfg, " = %d", head_vardecl->assigner.intnum);
	else if(head_vardecl->assignType == eAsFloat) fprintf(fp_cfg, " = %f", head_vardecl->assigner.floatnum);

	return 1;

}

int print_stmt(struct Stmt* head_stmt){

	if(head_stmt == NULL) return 0;
	
	if(head_stmt->e == eExpr) print_expr(head_stmt->type.exprStmt->expr);
	else if(head_stmt->e == eAssign){
		print_ref_var_expr(head_stmt->type.assignStmt->refVarExpr);
		fprintf(fp_cfg, " = ");
		print_expr(head_stmt->type.assignStmt->expr);
	}else if(head_stmt->e == eRet){
		fprintf(fp_cfg,"return ");
		print_expr(head_stmt->type.retStmt->expr);
	}else if(head_stmt->e == eSemi){
		fprintf(fp_cfg,"\n");
	}else fprintf(stderr, "error: invalid stmt try to be printed");

	return 1;
}

int print_expr(struct Expr* head_expr){

	if(head_expr == NULL) return 0;

	if(head_expr->e == eOper) print_oper_expr(head_expr->type.operExpr);
	else if(head_expr->e == eRef) print_ref_expr(head_expr->type.refExpr);
	else if(head_expr->e == eIntnum) fprintf(fp_cfg,"%d",head_expr->type.intnum);
	else if(head_expr->e == eFloatnum) fprintf(fp_cfg,"%f",head_expr->type.floatnum);

	return 1;
}

int print_oper_expr(struct OperExpr* head_oper_expr){

	if(head_oper_expr == NULL) return 0;

	if(head_oper_expr->e == eUn){

		if(head_oper_expr->type.un->e == eNegative) fprintf(fp_cfg, "-");
		print_expr(head_oper_expr->type.un->expr);

	}else if(head_oper_expr->e == eAddi){
		
		print_expr(head_oper_expr->type.addi->lhs);
		if(head_oper_expr->type.addi->e == ePlus) fprintf(fp_cfg," + ");
		else if(head_oper_expr->type.addi->e == eMinus) fprintf(fp_cfg," - ");
		print_expr(head_oper_expr->type.addi->rhs);

	}else if(head_oper_expr->e == eMult){

		print_expr(head_oper_expr->type.mult->lhs);
		if(head_oper_expr->type.mult->e == eMul) fprintf(fp_cfg," * ");
		else if(head_oper_expr->type.mult->e == eDiv) fprintf(fp_cfg," / ");
		print_expr(head_oper_expr->type.mult->rhs);

	}else if(head_oper_expr->e == eRela){

		print_expr(head_oper_expr->type.rela->lhs);
		if(head_oper_expr->type.rela->e == eLT) fprintf(fp_cfg, " < ");
		else if(head_oper_expr->type.rela->e == eGT) fprintf(fp_cfg," > ");
		else if(head_oper_expr->type.rela->e == eLE) fprintf(fp_cfg," <= ");
		else if(head_oper_expr->type.rela->e == eGE) fprintf(fp_cfg," >= ");
		print_expr(head_oper_expr->type.rela->rhs);

	}else if(head_oper_expr->e == eEqlt){

		print_expr(head_oper_expr->type.eqlt->lhs);
		if(head_oper_expr->type.eqlt->e == eEQ) fprintf(fp_cfg," == ");
		else if(head_oper_expr->type.eqlt->e == eNE) fprintf(fp_cfg," != ");
		print_expr(head_oper_expr->type.eqlt->rhs);

	}else if(head_oper_expr->e == eBracket){
		fprintf(fp_cfg,"( ");
		print_expr(head_oper_expr->type.bracket);
		fprintf(fp_cfg, " )");
	}

	return 1;
}

int print_ref_expr(struct RefExpr* head_ref_expr){

	if(head_ref_expr == NULL) return 0;

if(head_ref_expr->e == eVar) print_ref_var_expr(head_ref_expr->type.refVarExpr);
	else if(head_ref_expr->e == eCall) print_ref_call_expr(head_ref_expr->type.refCallExpr);

	return 1;
}

int print_ref_var_expr(struct RefVarExpr* head_ref_var_expr){
	
	if(head_ref_var_expr == NULL) return 0;
	
	if(head_ref_var_expr->refExpr != NULL){
		print_ref_expr(head_ref_var_expr->refExpr);
		fprintf(fp_cfg," . ");
	}

	print_ident_expr(head_ref_var_expr->identExpr);

	return 1;
}

int print_ident_expr(struct IdentExpr* head_ident_expr){
	
	if(head_ident_expr == NULL) return 0;
	
	fprintf(fp_cfg,"%s", head_ident_expr->id);
	if(head_ident_expr->expr != NULL){
		fprintf(fp_cfg," [ ");
		print_expr(head_ident_expr->expr);
		fprintf(fp_cfg," ]");
	}

	return 1;
}

int print_ref_call_expr(struct RefCallExpr* head_ref_call_expr){

	if(head_ref_call_expr == NULL) return 0;

	if(head_ref_call_expr->refExpr != NULL){
		print_ref_expr(head_ref_call_expr->refExpr);
		fprintf(fp_cfg," . ");
	}

	print_call_expr(head_ref_call_expr->callExpr);

	return 1;
}

int print_call_expr(struct CallExpr* head_call_expr){
	
	if(head_call_expr == NULL) return 0;

	fprintf(fp_cfg,"%s ( ",head_call_expr->id);	
	print_arg(head_call_expr->arg);
	fprintf(fp_cfg," )");

	return 1;
}

int print_arg(struct Arg* head_arg){
	int prev_result;

	if(head_arg == NULL) return 0;
	
	if(print_arg(head_arg->prev) != 0) fprintf(fp_cfg,", ");

	print_expr(head_arg->expr);

	return 1;
}

int print_cfg_block_list(struct cfg_block_list* head_block_list, char block_name){

	if(head_block_list == NULL) return 0;
	
	if(print_cfg_block_list(head_block_list->prev, block_name)) fprintf(fp_cfg, ", ");

	if(head_block_list->block->type == e_normal) fprintf(fp_cfg, "%c%d", block_name, head_block_list->block->num);
	else if(head_block_list->block->type == e_start) fprintf(fp_cfg,"start");
	else if(head_block_list->block->type == e_end) fprintf(fp_cfg,"end");
	else fprintf(fp_cfg,"error: invalid block in print block list\n");

	return 1;
}

int construct_cfg_program(struct Program* head_program){

	struct Class* tmp_class = head_program->_class;
	struct ClassMethodDef* tmp_class_method = head_program->classMethodDef;
	struct MainFunc* tmp_main = head_program->mainFunc;

	if (head_program == NULL){
		fprintf(stderr, "no Abstract Syntax Tree");
		return 0;
	}

	construct_cfg_class(tmp_class);

	construct_cfg_class_method(tmp_class_method);

	construct_cfg_main(tmp_main);

	return 1;
}

int construct_cfg_class(struct Class* head_class){

	if(head_class == NULL) return 0;

	construct_cfg_class(head_class->prev);

	construct_cfg_member(head_class->priMember);
	construct_cfg_member(head_class->pubMember);

	return 1;
}

int construct_cfg_class_method(struct ClassMethodDef* head_class_method){
	
	char* tmp;

	if(head_class_method == NULL) return 0;

	construct_cfg_class_method(head_class_method->prev);

	//generate name
	tmp = (char*)malloc(sizeof(char)*MAX_NAME);
	memset(tmp, 0, MAX_NAME);
	strcat(tmp,head_class_method->className);
	strcat(tmp,"::");
	strcat(tmp,head_class_method->methodName);
	strcat(tmp,"()");
	construct_cfg_procedure(head_class_method->compoundStmt, tmp);

	return 1;
}

int construct_cfg_main(struct MainFunc* head_main){
	
	if(head_main == NULL) return 0;

	//generate name
	construct_cfg_procedure(head_main->compoundStmt, "main()");

	return 1;
}

int construct_cfg_member(struct Member* head_member){

	if(head_member == NULL) return 0;

	construct_cfg_method(head_member->methodDef);

	return 1;
}

int construct_cfg_method(struct MethodDef* head_method){

	char* tmp;
	
	if(head_method == NULL) return 0;

	construct_cfg_method(head_method->prev);

	//generate name
	tmp = (char*)malloc(sizeof(char)*MAX_NAME);
	memset(tmp,0,MAX_NAME);
	strcat(tmp,head_method->id);
	strcat(tmp,"()");
	construct_cfg_procedure(head_method->compoundStmt,tmp);

	return 1;
}

int construct_cfg_procedure(struct CompoundStmt* head_compound, char* procedure_name){
	struct cfg_procedure* tmp_procedure;
	struct cfg_block* start_block = (struct cfg_block*)malloc(sizeof(struct cfg_block));
	struct cfg_block* end_block = (struct cfg_block*)malloc(sizeof(struct cfg_block));
	struct cfg_block* first_block;
	struct cfg_block* final_block;

	tmp_procedure = generate_procedure();

	global_cfg_procedure = tmp_procedure;

	// initialize procedure
	tmp_procedure->name = procedure_name;
	tmp_procedure->num = -1;
	tmp_procedure->end_block = end_block;
	
	// initialize start, end block
	start_block->type = e_start;
	end_block->type = e_end;

	start_block->prev = NULL;
	end_block->prev = start_block;

	// insert first block
	first_block = generate_block();

	// make link
	link_block(start_block, first_block);

	final_block = construct_cfg_stmt_compound(first_block, head_compound);

	link_block(final_block, end_block);

	return 1;
}

struct cfg_block* construct_cfg_stmt_compound(struct cfg_block* dst_block, struct CompoundStmt* head_compound){
	struct cfg_block* next_block;

	if(head_compound == NULL) return dst_block;

	next_block = construct_cfg_vardecl(dst_block, head_compound->varDecl);

	next_block = construct_cfg_stmt(next_block, head_compound->stmt);
	
	return next_block;
}

// list type -> recursive
struct cfg_block* construct_cfg_vardecl(struct cfg_block* dst_block, struct VarDecl* head_vardecl){
	struct cfg_block* next_block;
	step_union u;

	if(head_vardecl == NULL) return dst_block;

	next_block = construct_cfg_vardecl(dst_block, head_vardecl->prev);

	u.vardecl = head_vardecl;
	generate_step(next_block, u, e_vardecl);

	return next_block;
}

struct cfg_block* construct_cfg_expr(struct cfg_block* dst_block, struct Expr* head_expr){
	step_union u;

	if(head_expr == NULL) return dst_block;

	u.expr = head_expr;
	generate_step(dst_block, u, e_expr);

	return dst_block;
}

// list type -> recursive
struct cfg_block* construct_cfg_stmt(struct cfg_block* dst_block, struct Stmt* head_stmt){
	struct cfg_block* next_block;
	Type_e tmp_e;

	if(head_stmt == NULL) return dst_block;

	next_block = construct_cfg_stmt(dst_block, head_stmt->prev);

	//generate step
	tmp_e = head_stmt->e;
	if(tmp_e == eExpr || tmp_e == eAssign || tmp_e == eSemi) next_block = construct_cfg_stmt_rest(next_block, head_stmt);
	else if(tmp_e == eRet) next_block = construct_cfg_stmt_return(next_block, head_stmt);
	else if(tmp_e == eWhile) next_block = construct_cfg_stmt_while(next_block, head_stmt);
	else if(tmp_e == eDo) next_block = construct_cfg_stmt_do(next_block, head_stmt);
	else if(tmp_e == eFor) next_block = construct_cfg_stmt_for(next_block, head_stmt);
	else if(tmp_e == eIf) next_block = construct_cfg_stmt_if(next_block, head_stmt);

	// special case -> parameter is not Stmt, but CompoundStmt
	else if(tmp_e == eCompound) next_block = construct_cfg_stmt_compound(next_block, head_stmt->type.compoundStmt);

	return next_block;
}

struct cfg_block* construct_cfg_stmt_return(struct cfg_block* dst_block, struct Stmt* head_stmt){
	struct RetStmt* return_stmt = head_stmt->type.retStmt;
	struct cfg_block* next_block;

	if(head_stmt == NULL) return dst_block;

	// to print 'return', use construct_cfg_stmt_rest instead of construct_cfg_expr
	next_block = construct_cfg_stmt_rest(dst_block, head_stmt);

	link_block(next_block, global_cfg_procedure->end_block);

	next_block = generate_block();

	return next_block;
}

struct cfg_block* construct_cfg_stmt_while(struct cfg_block* dst_block, struct Stmt* head_stmt){
	struct WhileStmt* while_stmt = head_stmt->type.whileStmt;
	struct cfg_block* next_block;
	struct cfg_block* next_expr_block;
	struct cfg_block* next_stmt_block;
	struct cfg_block* expr_block;
	struct cfg_block* stmt_block;

	if(head_stmt == NULL) return dst_block;

	expr_block = generate_block();
	stmt_block = generate_block();
	next_block = generate_block();

	link_block(dst_block, expr_block);

	next_expr_block = construct_cfg_expr(expr_block, while_stmt->cond);
	
	link_block(next_expr_block, stmt_block);
	link_block(next_expr_block, next_block);

	next_stmt_block = construct_cfg_stmt(stmt_block, while_stmt->body);

	link_block(next_stmt_block, expr_block);

	return next_block;	
}

struct cfg_block* construct_cfg_stmt_do(struct cfg_block* dst_block, struct Stmt* head_stmt){
	struct DoStmt* do_stmt = head_stmt->type.doStmt;
	struct cfg_block* next_block;
	struct cfg_block* expr_block;
	struct cfg_block* stmt_block;
	struct cfg_block* next_expr_block;
	struct cfg_block* next_stmt_block;

	if(head_stmt == NULL) return dst_block;

	expr_block = generate_block();
	stmt_block = generate_block();
	next_block = generate_block();

	link_block(dst_block, stmt_block);

	next_stmt_block = construct_cfg_stmt(stmt_block, do_stmt->body);

	link_block(next_stmt_block, expr_block);

	next_expr_block = construct_cfg_expr(expr_block, do_stmt->cond);

	link_block(next_expr_block, stmt_block);
	link_block(next_expr_block, next_block);

	return next_block;
}

struct cfg_block* construct_cfg_stmt_for(struct cfg_block* dst_block, struct Stmt* head_stmt){ // for(expr1;expr2;expr3) stmt
	struct ForStmt* for_stmt = head_stmt->type.forStmt;
	struct cfg_block* next_block;
	struct cfg_block* expr2_block;
	struct cfg_block* stmt_expr3_block;
	struct cfg_block* next_expr2_block;
	struct cfg_block* next_stmt_expr3_block;
	struct cfg_block* next_dst_block;

	if(head_stmt == NULL) return dst_block;

	next_block = generate_block();
	expr2_block = generate_block();
	stmt_expr3_block = generate_block();

	next_dst_block = construct_cfg_expr(dst_block, for_stmt->init);

	link_block(next_dst_block, expr2_block);

	next_expr2_block = construct_cfg_expr(expr2_block, for_stmt->cond);

	link_block(next_expr2_block, stmt_expr3_block);
	link_block(next_expr2_block, next_block);

	next_stmt_expr3_block = construct_cfg_stmt(stmt_expr3_block, for_stmt->body);
	next_stmt_expr3_block = construct_cfg_expr(next_stmt_expr3_block, for_stmt->incr);

	link_block(next_stmt_expr3_block, expr2_block);

	return next_block;
}

struct cfg_block* construct_cfg_stmt_if(struct cfg_block* dst_block, struct Stmt* head_stmt){// if(expr1)stmt1(else stmt2)
	struct IfStmt* if_stmt = head_stmt->type.ifStmt;
	struct cfg_block* next_block;
	struct cfg_block* if_block;
	struct cfg_block* else_block;
	struct cfg_block* next_if_block;
	struct cfg_block* next_else_block;
	struct cfg_block* next_dst_block;

	if(head_stmt == NULL) return dst_block;

	next_block = generate_block();
	if_block = generate_block();

	next_dst_block = construct_cfg_expr(dst_block, if_stmt->cond);

	link_block(next_dst_block, if_block);

	next_if_block = construct_cfg_stmt(if_block, if_stmt->ifBody);

	link_block(next_if_block, next_block);

	if(if_stmt->elseBody != NULL){
		
		else_block = generate_block();
		
		link_block(next_dst_block, else_block);
		next_else_block = construct_cfg_stmt(else_block, if_stmt->elseBody);
		link_block(next_else_block, next_block);

	}else link_block(next_dst_block, next_block);

	return next_block;

}

struct cfg_block* construct_cfg_stmt_rest(struct cfg_block* dst_block, struct Stmt* head_stmt){
	// expr stmt, assign stmt, ;
	// BUT retStmt will be inserted after construct_cfg_stmt_return

	step_union u;

	if(head_stmt == NULL) return dst_block;

	u.stmt = head_stmt;
	generate_step(dst_block, u, e_stmt);

	return dst_block;
}

struct cfg_procedure* generate_procedure(){

	struct cfg_procedure* tmp_procedure;

	tmp_procedure = (struct cfg_procedure*)malloc(sizeof(struct cfg_procedure));

	tmp_procedure->prev = global_cfg_procedure;
	global_cfg_procedure = tmp_procedure;

	return tmp_procedure;
}

// pred and succ should be inserted in caller's side
struct cfg_block* generate_block(){

	struct cfg_block* tmp_block;	
	struct cfg_block_list* tmp_pred;
	struct cfg_block_list* tmp_succ;

	if(global_cfg_procedure == NULL){
		fprintf(stderr, "call generate_block without generating procedure");
		return NULL;
	}

	tmp_block = (struct cfg_block*)malloc(sizeof(struct cfg_block));

	// initialize block
	global_cfg_procedure->num++;
	tmp_block->type = e_normal;
	tmp_block->pred = NULL;
	tmp_block->succ = NULL;
	tmp_block->step = NULL;

	// insert into procedure's block list
	tmp_block->prev = global_cfg_procedure->end_block->prev;
	global_cfg_procedure->end_block->prev = tmp_block;

	return tmp_block;

}

struct cfg_block* eliminate_block(struct cfg_block* obj_block){
	
	struct cfg_block_list* tmp1_block_list;
	struct cfg_block_list* tmp2_block_list;
	struct cfg_block* next_of_obj_block;

	if(obj_block == NULL) return NULL;

	// free block_list ( pred, succ ) ( maybe not needed )
	tmp1_block_list = obj_block->pred;
	while(tmp1_block_list != NULL){
		tmp2_block_list = tmp1_block_list;
		tmp1_block_list = tmp1_block_list->prev;
		free(tmp2_block_list);
	}
	tmp1_block_list = obj_block->succ;
	while(tmp1_block_list != NULL){
		tmp2_block_list = tmp1_block_list;
		tmp1_block_list = tmp1_block_list->prev;
		free(tmp2_block_list);
	}

	// relink
	next_of_obj_block = global_cfg_procedure->end_block;
	while(next_of_obj_block->prev != obj_block && next_of_obj_block->prev != NULL) next_of_obj_block = next_of_obj_block->prev;

	if(next_of_obj_block->prev == NULL){
		fprintf(stderr,"error: failed to find block while eliminate_block\n");
		return NULL;
	}else{
		next_of_obj_block->prev = obj_block -> prev;
		global_cfg_procedure->num -= 1;
		free(obj_block);
		return NULL;
	}

}

struct cfg_step* generate_step(struct cfg_block* dst_block, step_union u, step_e e){
	struct cfg_step* tmp_step;

	tmp_step = (struct cfg_step*)malloc(sizeof(struct cfg_step*));
	tmp_step->type = e;
	if(e == e_vardecl) tmp_step->step.vardecl = u.vardecl;
	else if(e == e_stmt) tmp_step->step.stmt = u.stmt;
	else if(e == e_expr) tmp_step->step.expr = u.expr;
	else fprintf(stderr, "error: invalid step type\n");

	tmp_step->prev = dst_block->step;
	dst_block->step = tmp_step;

	return tmp_step;
}

int link_block(struct cfg_block* prev, struct cfg_block* next){
	struct cfg_block_list* pred_block_list;
	struct cfg_block_list* succ_block_list;
	struct cfg_block* tmp_pred_block;
	struct cfg_block* tmp_block;

	if( prev == NULL || next == NULL) return 0;


	/* check prev block wheather it's empty and not start or end block
		-> if empty, remove prev block and link next with pred of pre */

	if(prev->step == NULL && prev->type == e_normal){
		/* delink prev's pred, prev & link prev's pred, next */
		while(prev->pred != NULL){
			tmp_pred_block = prev->pred->block;
			delink_block(tmp_pred_block, prev);
			link_block(tmp_pred_block, next);
		}

		/* delete prev block */
		eliminate_block(prev);
	}else{

		pred_block_list = (struct cfg_block_list*)malloc(sizeof(struct cfg_block_list));
		succ_block_list = (struct cfg_block_list*)malloc(sizeof(struct cfg_block_list));

		// insert into next
		pred_block_list->block = prev;
		pred_block_list->prev = next->pred;
		next->pred = pred_block_list;

		// insert into prev
		succ_block_list->block = next;
		succ_block_list->prev = prev->succ;
		prev->succ = succ_block_list;
	
	}

	return 1;
}

int delink_block(struct cfg_block* prev, struct cfg_block* next){
	
	struct cfg_block_list* next_of_obj_list;
	struct cfg_block_list* obj_list;

	if( prev == NULL || next == NULL ) return 0;

	// delete next in prev's succ
	next_of_obj_list = prev->succ;
	while(next_of_obj_list != NULL){
		if(next_of_obj_list->block == next){
			prev->succ = next_of_obj_list->prev;
			free(next_of_obj_list);
			break;
		}else if(next_of_obj_list->prev != NULL && next_of_obj_list->prev->block == next){
			obj_list = next_of_obj_list->prev;
			next_of_obj_list->prev = obj_list->prev;
			free(obj_list);
			break;
		}
		next_of_obj_list = next_of_obj_list -> prev;
	}

	// delete prev in next's pred
	next_of_obj_list = next->pred;
	while(next_of_obj_list != NULL){
		if(next_of_obj_list->block == prev){
			next->pred = next_of_obj_list->prev;
			free(next_of_obj_list);
			break;
		}else if(next_of_obj_list->prev != NULL && next_of_obj_list->prev->block == prev){
			obj_list = next_of_obj_list->prev;
			next_of_obj_list->prev = obj_list->prev;
			free(obj_list);
			break;
		}
		next_of_obj_list = next_of_obj_list -> prev;
	}

	return 1;
}

