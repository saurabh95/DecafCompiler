#include "codegen.h"

int validity;
static IRBuilder<> Builder(getGlobalContext());

void CodeGenContext::generateCode(ASTProgram* root)
{
	std::cout << "Generating code...\n";

	vector<const Type*> argTypes;
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "Class Program", module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

	pushBlock(bblock);
	*root->codeGen(*this); /* emit bytecode for the toplevel block */
	popBlock();

		std::cout << "Code is generated.\n";
		PassManager pm;
		pm.add(createPrintModulePass(&outs()));
		pm.run(*module);

}

static const Type *typeOf(string type) 
{
	if (type.compare("int") == 0) {
		return Type::getInt64Ty(getGlobalContext());
	}
	else if (type.compare("boolean")==0)
		return Type::getInt1Ty(getGlobalContext());

	return Type::getVoidTy(getGlobalContext());
}

// Generating Code
Value *ASTProgram::codeGen(CodeGenContext& context)
{
	int i;
	cout<<"Program Created"<<endl;
	Value *last = NULL;
	for(i=0;i<fieldmore_->size();i++)
	{
		last = (*fieldmore_)[i]->codeGen(context);	
	}
    cout << "Program has Ended" << endl; 
}

Value *Field::codeGen(CodeGenContext& context)
{
	int i;
	Value *v;
	for(i=0;i<var_->size();i++)
	{
		AllocaInst *alloc = new AllocaInst(typeOf(type_), (*var_)[i]->id__, context.currentBlock());
		context.locals()[(*var_)[i]->id__] = alloc;
      //  cout << "GONE"  << (*var_)[i]->id__ << endl;
		v=alloc;
	}
	return v;
}

Value *Variable::codeGen(CodeGenContext& context)
{
}




Value *Assignst::codeGen(CodeGenContext& context)
{
	cout<<"Assignment Statement of :"<<loc_->id___<<endl;
	if(context.locals().find(loc_->id___) == context.locals().end())
	{
		cerr<<"Undeclared Variable in assignment statement"<<loc_->id___<<endl;
		validity = 1;
		return NULL;
	}
    cout << "GONE\n";
	Value *st = exp_->codeGen(context);

	if(st!=NULL)
		st = new StoreInst(st, context.locals()[loc_->id___], context.currentBlock());

	return st;
}



Value *Returnst::codeGen(CodeGenContext& context)
{
		return ReturnInst::Create(getGlobalContext(),context.currentBlock());	
}

Value *Retvalst::codeGen(CodeGenContext& context)
{
		Value *val=exp_->codeGen(context);
		return ReturnInst::Create(getGlobalContext(),val,context.currentBlock());	
}
Value *Identifier::codeGen(CodeGenContext& context)
{
      if (context.locals().find(id_) == context.locals().end()) 
              {   
                          std::cerr << "undeclared variable in expression " << id_ << std::endl;
                                  validity = 1;
                                          return NULL;
                                              }   
          return new LoadInst(context.locals()[id_], "", false, context.currentBlock());
}



Value *Forst::codeGen(CodeGenContext& context)
{
	Value *st = init_->codeGen(context);

	if(st!=NULL)
		st = new StoreInst(st, context.locals()[id_->id_], context.currentBlock());
	
    
    
//    Value *StartVal = ass.codeGen(context);
	if (st == NULL) return NULL;

	Function *TheFunction = Builder.GetInsertBlock()->getParent();
	BasicBlock *PreheaderBB = Builder.GetInsertBlock();
	BasicBlock *LoopBB = BasicBlock::Create(getGlobalContext(), "loop", TheFunction);
	cout<<"For started"<<endl;

	Builder.CreateBr(LoopBB);

	Builder.SetInsertPoint(LoopBB);

//	PHINode *Variable = Builder.CreatePHI(Type::getDoubleTy(getGlobalContext()), 2, VarName.c_str());
//	Variable->addIncoming(StartVal, PreheaderBB);

//	Value *OldVal = NamedValues[VarName];
//	NamedValues[VarName] = Variable;
	if (bloc_->codeGen(context) == NULL)
		return NULL;


	Value *EndCond = exp_->codeGen(context);
	if (EndCond == NULL) return EndCond;

	EndCond = Builder.CreateFCmpONE(EndCond, 
			ConstantFP::get(getGlobalContext(), APFloat(0.0)),
			"loopcond");

	BasicBlock *LoopEndBB = Builder.GetInsertBlock();
	BasicBlock *AfterBB = BasicBlock::Create(getGlobalContext(), "afterloop", TheFunction);

	Builder.CreateCondBr(EndCond, LoopBB, AfterBB);

	Builder.SetInsertPoint(AfterBB);

//	Variable->addIncoming(NextVar, LoopEndBB);

	return NULL;
}


Value *Ifelsest::codeGen(CodeGenContext& context)
{
	Value *CondV = exp_->codeGen(context);
	if(CondV!=NULL)
	{
		CondV = Builder.CreateFCmpONE(CondV,ConstantFP::get(getGlobalContext(),APFloat(0.0)),"ifcond");
		Function *TheFunction = Builder.GetInsertBlock()->getParent();

		BasicBlock *IfBB = BasicBlock::Create(getGlobalContext(), "if", TheFunction);
		BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "else");
		BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");


		Builder.CreateCondBr(CondV, IfBB, ElseBB);
		Builder.SetInsertPoint(IfBB);
		cout<<"Statement number: "<<bloc1_->stat_->size()<<endl;
		Value *IfV = bloc1_->codeGen(context);
		Builder.CreateBr(MergeBB);

		IfBB = Builder.GetInsertBlock();
		TheFunction->getBasicBlockList().push_back(ElseBB);
		Builder.SetInsertPoint(ElseBB);
		Value *ElseV = bloc2_->codeGen(context);
		if(ElseV == NULL)return NULL;
		Builder.CreateBr(MergeBB);
		ElseBB = Builder.GetInsertBlock();
		TheFunction->getBasicBlockList().push_back(MergeBB);
		Builder.SetInsertPoint(MergeBB);
		cout<<"If Statement"<<endl;
		//PHINode *PN = Builder.CreatePHI(Type::getDoubleTy(getGlobalContext()),"iftmp");

	//	PN->addIncoming(IfV, IfBB);
	//	PN->addIncoming(ElseV, ElseBB);
		return NULL;
	}
	
	return NULL;
}



Value *Ifst::codeGen(CodeGenContext& context)
{

}

Value *Methodcall1::codeGen(CodeGenContext& context)
{
	Function *function = context.module->getFunction(mname_->id_);
	if(function==NULL)
	{
		cerr<<mname_->id_<<"function not declared"<<endl;
		validity = 1;
		return NULL;
	}
	int i;
	vector<Value*> args;

	for(i=0;i<explist_->size();i++)
	{
		args.push_back((*explist_)[i]->codeGen(context));
	}

	CallInst *call = NULL;
	call = CallInst::Create(function,args.begin(),args.end(),"",context.currentBlock());


	return call;
}

Value *Methodcall2::codeGen(CodeGenContext& context)
{
}

Value *Binaryexp::codeGen(CodeGenContext& context)
{

    cout << "GONE IN EXPRESSION\n";
	Instruction::BinaryOps instr;
	if(strcmp(biop_, "+")==0)
	{
		instr=Instruction::Add;
	}

	else if(strcmp(biop_, "-")==0)
	{
		instr=Instruction::Sub;
	}

	else if(strcmp(biop_, "*")==0)
	{
		instr=Instruction::Mul;
	}

	else if(strcmp(biop_, "/")==0)
	{
		instr=Instruction::SDiv;
	}
	
	else if(strcmp(biop_, "%")==0)
	{
		instr=Instruction::SRem;
	}
	
	else if(strcmp(biop_, "&&")==0)
	{
		instr=Instruction::And;
	}
	
	else if(strcmp(biop_, "||")==0)
	{
		instr=Instruction::Or;
	}


	else if(strcmp(biop_, "==")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, lhs_->codeGen(context), rhs_->codeGen(context),"",context.currentBlock());
	}
	
	else if(strcmp(biop_, "<=")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULE, lhs_->codeGen(context), rhs_->codeGen(context),"",context.currentBlock());
	}

	else if(strcmp(biop_, ">=")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGE, lhs_->codeGen(context), rhs_->codeGen(context),"",context.currentBlock());
	}
	
	else if(strcmp(biop_, "<")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULT, lhs_->codeGen(context), rhs_->codeGen(context),"",context.currentBlock());
	}

	else if(strcmp(biop_, ">")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGT, lhs_->codeGen(context), rhs_->codeGen(context),"",context.currentBlock());
	}

	else if(strcmp(biop_, "!=")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_NE, lhs_->codeGen(context), rhs_->codeGen(context),"",context.currentBlock());
	}

	Value *bin=NULL;

	Value *l = lhs_->codeGen(context);
	Value *r = rhs_->codeGen(context);

	if(l!=NULL && r!=NULL)
		bin = BinaryOperator::Create(instr, lhs_->codeGen(context),rhs_->codeGen(context), "", context.currentBlock());

	return bin;

}


Value *Number::codeGen(CodeGenContext& context)
{
	return ConstantInt::get(Type::getInt64Ty(getGlobalContext()),val_,true);
}
Value *Boollit::codeGen(CodeGenContext& context)
{
    int value = (int)b_;
	return ConstantInt::get(Type::getInt64Ty(getGlobalContext()),value,true);
}



Value *Block::codeGen(CodeGenContext& context)
{
	int i;

	for(i=0;i<var_->size();i++)
	{
		(*var_)[i]->codeGen(context);
	}
	for(i=0;i<stat_->size();i++)
	{
		(*stat_)[i]->codeGen(context);
	}
}


Value *Method::codeGen(CodeGenContext& context)
{
	cout<<"New Function"<<endl;
	int i;
	vector<const Type*> argTypes;
	for(i=0;i<arg_->arg_->size();i++)
	{
		argTypes.push_back(typeOf((*(arg_->arg_))[i].first));
	}

	FunctionType *ftype = FunctionType::get(typeOf(retype_),argTypes,false);
	Function *function = Function::Create(ftype,GlobalValue::InternalLinkage,id_->id_,context.module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", function, 0);
	Builder.SetInsertPoint(bblock);
	context.pushBlock(bblock);
	for(i=0;i<arg_->arg_->size();i++)
	{
	    AllocaInst *alloc = new AllocaInst(typeOf((*(arg_->arg_))[i].first), (*(arg_->arg_))[i].second->id_, context.currentBlock());
	    context.locals()[(*(arg_->arg_))[i].second->id_] = alloc;
//		(*(arg_->arg_))[i]->codeGen(context);
	}
	bloc_->codeGen(context);
	ReturnInst::Create(getGlobalContext(),bblock);	
	context.popBlock();
	return function;
}

Value *Vardec::codeGen(CodeGenContext& context)
{
	int i;
	for(i=0;i<var_->size();i++)
	{
	cout<<"declaring "<<(*var_)[i]->id_<<endl;
	AllocaInst *alloc = new AllocaInst(typeOf(type_), (*var_)[i]->id_, context.currentBlock());
	context.locals()[(*var_)[i]->id_] = alloc;
	}
}


