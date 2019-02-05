#include <string>
#include <sstream>
#include <stack>
#include <set>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"
#include "ast/return_node.h"
#include "ast/function_define_node.h"
#include "size_calculator.h"  // all.h is automatically generated

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
}
void gr8::postfix_writer::do_data_node(cdk::data_node * const node, int lvl) {
}
void gr8::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    //if(x==0) x=1 else x=0
    int lblElse = ++_lbl;
    int lblFim = ++_lbl;
    node->argument()->accept(this, lvl + 2);
    _pf.JNZ(mklbl(lblElse));
    _pf.INT(1);
    _pf.JMP(mklbl(lblFim));
    _pf.LABEL(mklbl(lblElse));
    _pf.INT(0);
    _pf.LABEL(mklbl(lblFim));
}
void gr8::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    //if(left != 0) accept(right);
    int end = ++_lbl;
    
    node->left()->accept(this, lvl + 2);
    
    _pf.DUP32(); // dup for test
    _pf.JZ(mklbl(end));
    _pf.TRASH(node->left()->type()->size()); //it's !0, irrelevant
    
    node->right()->accept(this, lvl + 2); //and value is the value of this accept
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(end));
}
void gr8::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    //if(left == 0) accept(right);
    int end = ++_lbl;
    
    node->left()->accept(this, lvl + 2);
    
    _pf.DUP32(); // dup for test
    _pf.JNZ(mklbl(end));
    _pf.TRASH(node->left()->type()->size()); //it's 0, irrelevant
    
    node->right()->accept(this, lvl + 2); //or value is the value of this accept
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(end));
}
void gr8::postfix_writer::do_block_node(gr8::block_node *const node, int lvl) {
    _symtab.push();
    node->declarations()->accept(this, lvl + 2);
    node->instructions()->accept(this, lvl + 2);
    _symtab.pop();
}
void gr8::postfix_writer::do_sweeping_from_to_by_do_node(gr8::sweeping_from_to_by_do_node *const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    //sweeping i from a to b by c do
    //condition
    //if(c < 0 && i < b) endsweep
    //if(c>=0 && i>b) endsweep
    //how to do in assembly
    //if(c<0) (1)
    //  i<b ? sweepend endif1
    //else
    //  i>b ? sweepend endif1

    int condition = ++_lbl;
    int increment = ++_lbl;
    int endSweep = ++_lbl;
    
    int elseLbl = ++_lbl;
    int endif1 = ++_lbl;
    
    _againLabels.push(increment);
    _stopLabels.push(endSweep);
     
    //-----------------------init
    node->from()->accept(this, lvl + 2);    // a
    node->lvalue()->accept(this, lvl + 2);  // &i
    _pf.STINT();
    
    //---------------------condition
    _pf.ALIGN();
    _pf.LABEL(mklbl(condition));
    
    node->increment()->accept(this, lvl + 2); //c
    _pf.INT(0); //0
    _pf.LT();//c<0
    _pf.JZ(mklbl(elseLbl)); // if false goto else    
    
    //if1 body
    node->lvalue()->accept(this, lvl + 2); //&i
    _pf.LDINT(); //i
    node->to()->accept(this, lvl + 2); //b
    _pf.LT(); // i<b
    _pf.JZ(mklbl(endif1)); // if false endif 
    _pf.JMP(mklbl(endSweep)); // if true endsweep
    
    //else body
    _pf.ALIGN();
    _pf.LABEL(mklbl(elseLbl));
    node->lvalue()->accept(this, lvl + 2); //&i
    _pf.LDINT(); //i
    node->to()->accept(this, lvl + 2); //b
    _pf.GT(); //i>b
    _pf.JZ(mklbl(endif1)); // if false endif
    _pf.JMP(mklbl(endSweep)); // if true endsweep
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(endif1));          
    
    //----------------------sweeping body
    node->block()->accept(this, lvl + 2);
    
    //-----------------------increment
    _pf.ALIGN();
    _pf.LABEL(mklbl(increment));
    node->lvalue()->accept(this, lvl + 2); // &i
    _pf.LDINT(); // i
    node->increment()->accept(this, lvl + 2); // c
    _pf.ADD(); // i + c
    node->lvalue()->accept(this, lvl + 2); // &i
    _pf.STINT(); // i = i + c
    _pf.JMP(mklbl(condition));
    
    //-----------------------endsweep
    _pf.ALIGN();
    _pf.LABEL(mklbl(endSweep));
        
    _againLabels.pop();
    _stopLabels.pop();
}
void gr8::postfix_writer::do_stop_node(gr8::stop_node *const node, int lvl) {
    std::stack<int> stack;
    
    if(_stopLabels.empty()){
        std::cerr << "ERROR: stop is not in a sweeping." << std::endl;
        exit(1);
    }
    else{
        if(node->argument()->value() == 0){
            std::cerr << "ERROR: stop argument cannot be 0." << std::endl;
            exit(1);
        }
        
        while(stack.size() != (unsigned int)node->argument()->value()){
            if(_stopLabels.empty()){
                std::cerr << "ERROR: stop there in't nth inner cycle." << std::endl;
                exit(1);
            }
            stack.push(_stopLabels.top());
            _stopLabels.pop();
        }
        
        _pf.JMP(mklbl(stack.top()));
        
        // construct _stopLabels
        while(!stack.empty()){
            _stopLabels.push(stack.top());
            stack.pop();
        }
    }
} 
void gr8::postfix_writer::do_again_node(gr8::again_node *const node, int lvl) {
    std::stack<int> stack;
    
    if(_againLabels.empty()){
        std::cerr << "ERROR: again is not in a sweeping." << std::endl;
        exit(1);
    }
    else{
        if(node->argument()->value() == 0){
            std::cerr << "ERROR: again argument cannot be 0." << std::endl;
            exit(1);
        }
        
        while(stack.size() != (unsigned int)node->argument()->value()){
            if(_againLabels.empty()){
                std::cerr << "ERROR: again there in't nth inner cycle." << std::endl;
                exit(1);
            }
            stack.push(_againLabels.top());
            _againLabels.pop();
        }
        
        _pf.JMP(mklbl(stack.top()));
        
        // construct _againLabels
        while(!stack.empty()){
            _againLabels.push(stack.top());
            stack.pop();
        }
    }
}
void gr8::postfix_writer::do_return_node(gr8::return_node *const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    node->expression()->accept(this, lvl + 2);
    
    if(isInt(node->expression()->type())){
        if(isDouble(current_function().get()->type())){
           _pf.I2D(); 
           _pf.STFVAL64();
        }
        else{
            _pf.STFVAL32();
        }
    }
    else if(isDouble(node->expression()->type())){
        _pf.STFVAL64();
    }
    else{
        _pf.STFVAL32();
    }
    
    _pf.JMP(mklbl(current_function()->lblReturn()));
}
void gr8::postfix_writer::do_index_node(gr8::index_node *const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    //pointer[index]
    node->index()->accept(this, lvl + 2); //index
    _pf.INT(node->type()->size()); //sizeof(*object)
    _pf.MUL();
    node->pointer()->accept(this, lvl + 2);
    _pf.ADD();
    
}
void gr8::postfix_writer::do_identity_node(gr8::identity_node *const node, int lvl) {    
    ASSERT_SAFE_EXPRESSIONS;
    node->argument()->accept(this, lvl + 2);
} 
   

void gr8::postfix_writer::do_memory_allocation_node(gr8::memory_allocation_node *const node, int lvl) { 
    ASSERT_SAFE_EXPRESSIONS;
    node->argument()->accept(this, lvl + 2); //number of objects
    _pf.INT(node->type()->subtype()->size()); //sizeof(object)
    _pf.MUL(); //n*sizeof(object) bytes
    _pf.ALLOC();
    _pf.SP();
}                                                                                                                                                                                                                                                                    
void gr8::postfix_writer::do_address_of_node(gr8::address_of_node *const node, int lvl) { 
    ASSERT_SAFE_EXPRESSIONS;
    node->lvalue()->accept(this, lvl + 2);
}                                                                                                                                                                                                                                                                    
void gr8::postfix_writer::do_function_declaration_node(gr8::function_declaration_node *const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;  
    std::string id = *node->identifier();
    std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
    
    if(!symbol->isDefined()){
        _externIdentifiers.insert(id);
    }
}       
void gr8::postfix_writer::do_function_define_node(gr8::function_define_node *const node, int lvl) {  
    ASSERT_SAFE_EXPRESSIONS;
    int ret = ++_lbl;
    
    current_function()->lblReturn(ret);
    
    switchSegment(TEXT);
    if(node->isPublic()){
        _pf.GLOBAL(*node->identifier(), _pf.FUNC());
    }
    _pf.LABEL(*node->identifier());
    
    //calculate vars size to alloc
    gr8::size_calculator calculator(_compiler);
    node->accept(&calculator, lvl);
    
    _offsetArg = +8;
    _offsetVar = -4; 
    
    //push context for params
    _symtab.push();
    _pf.ALIGN();
    
    //offset params
    _isParam = true;
    node->parameters()->accept(this, lvl + 2);
    _isParam = false;
        
    _pf.ENTER(calculator.size());
    node->block()->accept(this, lvl + 2);
    
    _pf.ALIGN();
    _pf.LABEL(mklbl(ret));
    _pf.LEAVE();
    _pf.RET();
    
    _externIdentifiers.erase(*node->identifier());    
    _symtab.pop();
    reset_current_function();
}                                                                                                                                                                                                                                                                    
void gr8::postfix_writer::do_function_call_node(gr8::function_call_node *const node, int lvl) {      
    ASSERT_SAFE_EXPRESSIONS;
    //get symbol
    std::string id = *node->identifier();
    std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
    
    int bytesToTrash = 0;
        
    //push arguments to the stack in reverse order 
    std::vector<cdk::basic_node*>* paramsCall = &node->parameters()->nodes();
    if(node->parameters()->size() != 0){
        for (int i = node->parameters()->size() - 1; i >= 0 ; i--) {
            cdk::expression_node* param = (cdk::expression_node*) paramsCall->at(i);
            param->accept(this, lvl);
            bytesToTrash += param->type()->size();
            if(isInt(param->type()) && isDouble(symbol->params()->at(i))){
                _pf.I2D();
                bytesToTrash += 4;
            }
        }
    }
    
    _pf.CALL(id);
    _pf.TRASH(bytesToTrash);
    
    if(isDouble(node->type())){
        _pf.LDFVAL64();
    }
    else if(!isVoid(node->type())){
        _pf.LDFVAL32();
    }
}                                                                                                                                                                                                                                                                    
void gr8::postfix_writer::do_variable_declaration_node(gr8::variable_declaration_node *const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    _isVarPublic = node->isPublic();

    if(_isParam){
        new_symbol()->isGlobal(false);
        new_symbol()->offset(_offsetArg);
        _offsetArg += node->type()->size();
    }
    else if(current_function() == nullptr){//global
        new_symbol()->isGlobal(true);
        _globalVarLabel = *node->identifier();
        if(node->isUse()){
            _externIdentifiers.insert(*node->identifier());
        }
        else if(node->initialization() == nullptr){
            switchSegment(BSS);
            _pf.ALIGN();
            if(node->isPublic()){
                _pf.GLOBAL(*node->identifier(), _pf.OBJ());
            }
            _pf.LABEL(*node->identifier());
            _pf.SALLOC(node->type()->size());            
        }
        else{
            if(isInt(node->initialization()->type()) && isDouble(node->type())){
                cdk::integer_node* integer_node = dynamic_cast<cdk::integer_node*>(node->initialization());
                
                cdk::double_node doubleToInit(integer_node->lineno(), integer_node->value());
                doubleToInit.accept(this, lvl + 2);
            }
            else{
                node->initialization()->accept(this, lvl + 2);
            }
        }
    }
    else{ // not global or param
        new_symbol()->isGlobal(false);
        new_symbol()->offset(_offsetVar);
        _offsetVar -= node->type()->size();
        
        if(node->initialization() != nullptr){
            node->initialization()->accept(this, lvl + 2); //value to init
            
            if(isInt(node->initialization()->type()) && isDouble(node->type())){
                _pf.I2D();
            }
            
            _pf.LOCAL(new_symbol()->offset());
                        
            if(isDouble(node->type())){
                _pf.STDOUBLE();
            }
            else{
                _pf.STINT();
            }
        }
    }
}  
//---------------------------------------------------------------------------

void gr8::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------
void gr8::postfix_writer::do_null_node(gr8::null_node *const node, int lvl) {   
    ASSERT_SAFE_EXPRESSIONS;
    if(current_function() == nullptr){
        switchSegment(DATA);
        _pf.ALIGN();
        
        if(_isVarPublic){
            _pf.GLOBAL(_globalVarLabel, _pf.OBJ());
        }
        
        _pf.LABEL(_globalVarLabel);
        _pf.SINT(0);
        switchSegment(_previousSegment);
    }
    else{
        _pf.INT(0);
    }
}  

void gr8::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    if(current_function() == nullptr){
        switchSegment(DATA);
        _pf.ALIGN();
        
        if(_isVarPublic){
            _pf.GLOBAL(_globalVarLabel, _pf.OBJ());
        }
        
        _pf.LABEL(_globalVarLabel);
        _pf.SINT(node->value());
        switchSegment(_previousSegment);
    }
    else{
        _pf.INT(node->value()); // push an integer
    }
}

void gr8::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    if(current_function() == nullptr){
        switchSegment(DATA);
        _pf.ALIGN();
        
        if(_isVarPublic){
            _pf.GLOBAL(_globalVarLabel, _pf.OBJ());
        }
        
        _pf.LABEL(_globalVarLabel);
        _pf.SDOUBLE(node->value());
        switchSegment(_previousSegment);
    }
    else{
        _pf.DOUBLE(node->value());
    }   
}

void gr8::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    int lbl1;
    
    /* generate the string */
    switchSegment(RODATA);
    _pf.ALIGN(); // make sure we are aligned
    _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
    _pf.SSTRING(node->value()); // output string characters
    switchSegment(_previousSegment);
  
    if(current_function() == nullptr){
        switchSegment(DATA);
        _pf.ALIGN();
        if(_isVarPublic){
            _pf.GLOBAL(_globalVarLabel, _pf.OBJ());
        }
        _pf.LABEL(_globalVarLabel);
        _pf.SADDR(mklbl(lbl1));
    }
    else{
        _pf.ADDR(mklbl(lbl1)); // the string to be printed
    }    
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    node->argument()->accept(this, lvl); // determine the value

    if(isInt(node->argument()->type())){
        _pf.NEG();
    }
    else if(isDouble(node->argument()->type())){
        _pf.DNEG();
    }
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  
  if(equalTypes(node->left()->type(), node->right()->type())){
      node->right()->accept(this, lvl);
  }
  else if(isInt(node->left()->type()) && isDouble(node->right()->type())){
      _pf.I2D();
      node->right()->accept(this, lvl);
  }
  else if(isDouble(node->left()->type()) && isInt(node->right()->type())){
      node->right()->accept(this, lvl);
      _pf.I2D();
  }
  else if(isPointer(node->left()->type()) && isInt(node->right()->type())){
      _pf.INT(node->type()->subtype()->size());
      node->right()->accept(this, lvl);
      _pf.MUL();
  } 
  else if(isInt(node->left()->type()) && isPointer(node->right()->type())){
      _pf.INT(node->type()->subtype()->size());
      _pf.MUL();
      node->right()->accept(this, lvl);
  } 
  
  if(isInt(node->type()) || isPointer(node->type())){
      _pf.ADD();
  }
  else if(isDouble(node->type())){
      _pf.DADD();
  }
  else{
     std::cerr << "ERROR: ADD CANNOT HAPPEN!" << std::endl;
     exit(1);
  }
  
}
void gr8::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  if(equalTypes(node->left()->type(), node->right()->type())){
      node->right()->accept(this, lvl);
  }
  else if(isInt(node->left()->type()) && isDouble(node->right()->type())){
      _pf.I2D();
      node->right()->accept(this, lvl);
  }
  else if(isDouble(node->left()->type()) && isInt(node->right()->type())){
      node->right()->accept(this, lvl);
      _pf.I2D();
  }
  else if(isPointer(node->left()->type()) && isInt(node->right()->type())){
      _pf.INT(node->type()->subtype()->size());
      node->right()->accept(this, lvl);
      _pf.MUL();
  } 
  
  if(isInt(node->type()) || isPointer(node->type())){
      _pf.SUB();
  }
  else if(isDouble(node->type())){
      _pf.DSUB();
  }
  else{
     std::cerr << "ERROR: SUB CANNOT HAPPEN!" << std::endl;
     exit(1);
  }
}

void gr8::postfix_writer::processMultiplicationExpressions(cdk::binary_expression_node * const node, int lvl){
    node->left()->accept(this, lvl);
  
    if(equalTypes(node->left()->type(), node->right()->type())){
        node->right()->accept(this, lvl);
    }
    else if(isInt(node->left()->type()) && isDouble(node->right()->type())){
        _pf.I2D();
        node->right()->accept(this, lvl);
    }
    else if(isDouble(node->left()->type()) && isInt(node->right()->type())){
        node->right()->accept(this, lvl);
        _pf.I2D();
    }
}

void gr8::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  processMultiplicationExpressions(node,lvl);

  if(isInt(node->type())){
      _pf.MUL();
  }
  else if(isDouble(node->type())){
      _pf.DMUL();
  }
  else{
     std::cerr << "ERROR: MUL CANNOT HAPPEN!" << std::endl;
     exit(1);
  }
}
void gr8::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    processMultiplicationExpressions(node,lvl);

    if(isInt(node->type())){
        _pf.DIV();
    }
    else if(isDouble(node->type())){
        _pf.DDIV();
    }
    else{
       std::cerr << "ERROR: MUL CANNOT HAPPEN!" << std::endl;
       exit(1);
    }
}
void gr8::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}

void gr8::postfix_writer::processComparativeExpressions(cdk::binary_expression_node * const node, int lvl){
    node->left()->accept(this, lvl);
    
    if(isInt(node->left()->type()) && isDouble(node->right()->type())){
        _pf.I2D();
    }
    
    node->right()->accept(this, lvl + 2);
    
    if(isDouble(node->left()->type()) && isInt(node->right()->type())){
        _pf.I2D();
    }
    
    if(isDouble(node->left()->type()) || isDouble(node->right()->type())){
        _pf.DCMP();
        _pf.INT(0);
    }   
}

void gr8::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  processComparativeExpressions(node, lvl);
  _pf.LT();
}
void gr8::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
    processComparativeExpressions(node, lvl);
    _pf.LE();
}
void gr8::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
    processComparativeExpressions(node, lvl);
    _pf.GE();
}
void gr8::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  processComparativeExpressions(node, lvl);
  _pf.GT();
}
void gr8::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
    processComparativeExpressions(node, lvl);
    _pf.NE();
}
void gr8::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  processComparativeExpressions(node, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  std::string id = node->name();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);

  if(symbol->isGlobal()){
      _pf.ADDR(id);
  }
  else {
      _pf.LOCAL(symbol.get()->offset());
  }
}

void gr8::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);
  
  if(isDouble(node->type())){
      _pf.LDDOUBLE();
  }
  else{
      _pf.LDINT();
  }

}

void gr8::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  //no need to dup, assignment is an instruction
  node->rvalue()->accept(this, lvl + 2); // determine the new value
    
  if(isDouble(node->lvalue()->type()) && isInt(node->rvalue()->type())){
      _pf.I2D();
  }
  
  node->lvalue()->accept(this, lvl + 2); // address
  
  if(isDouble(node->lvalue()->type())){
      _pf.STDOUBLE();
  }
  else{
      _pf.STINT();
  }


}
//---------------------------------------------------------------------------

void gr8::postfix_writer::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (isDouble(node->argument()->type())) {
    _pf.TRASH(8); // delete the evaluated value
  } 
  else {
    _pf.TRASH(4);
  }
}

void gr8::postfix_writer::do_print_node(gr8::print_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (isInt(node->argument()->type())) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  } 
  else if (isString(node->argument()->type())) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  } 
  else if (isDouble(node->argument()->type())) {
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value
  }
  else {
    std::cerr << "ERROR print node: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  if(node->hasNewLine()){
     _pf.CALL("println"); // print a newline 
  } 
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_read_node(gr8::read_node * const node, int lvl) {
    ASSERT_SAFE_EXPRESSIONS;
    if(isInt(node->type())){
        _pf.CALL("readi");
        _pf.LDFVAL32();     
    }
    else if(isDouble(node->type())){
        _pf.CALL("readd");
        _pf.LDFVAL64();  
    }
    else{
        throw "postfix: wrong type in read";
    }
  
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_if_node(gr8::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl2));
}
