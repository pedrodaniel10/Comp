#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void gr8::type_checker::do_sequence_node(cdk::sequence_node * const node, int lvl) {}
void gr8::type_checker::do_nil_node(cdk::nil_node * const node, int lvl) {}
void gr8::type_checker::do_data_node(cdk::data_node * const node, int lvl) {}
void gr8::type_checker::do_block_node(gr8::block_node *const node, int lvl) {}
void gr8::type_checker::do_stop_node(gr8::stop_node *const node, int lvl) {} 
void gr8::type_checker::do_again_node(gr8::again_node *const node, int lvl) {} 

//---------------------------------------------------------------------------

void gr8::type_checker::do_sweeping_from_to_by_do_node(gr8::sweeping_from_to_by_do_node *const node, int lvl) {                                                                                                                                                      
    node->lvalue()->accept(this, lvl + 2);
    node->from()->accept(this, lvl + 2);
    node->to()->accept(this, lvl + 2);
    node->increment()->accept(this, lvl + 2);
    
    handleUnspecType(node->from()->type());
    handleUnspecType(node->to()->type());
    handleUnspecType(node->increment()->type());
    
    if(!isInt(node->lvalue()->type())){
        throw "'lvalue' in sweeping is expecting int but it was given " + \
                do_basic_type(node->lvalue()->type());
    }
    if(!isInt(node->from()->type())){
        throw "'from' in sweeping is expecting int but it was given " + \
                do_basic_type(node->from()->type());
    }
    if(!isInt(node->to()->type())){
        throw "'to' in sweeping is expecting int but it was given " + \
                do_basic_type(node->to()->type());
    }
    if(!isInt(node->increment()->type())){
        throw "'increment' in sweeping is expecting int but it was given " + \
                do_basic_type(node->increment()->type());
    }
}  

void gr8::type_checker::do_return_node(gr8::return_node *const node, int lvl) {
    basic_type* returnType = _parent->current_function()->type();
    
    if(node->expression() == nullptr){
        if(!isVoid(returnType)){
            throw "Return instructions doesn't have argument. Is not a procedure.";
        }
    }
    else{
        node->expression()->accept(this, lvl + 2);
        
        handleUnspecType(returnType, node->expression()->type());
        
        if(!equalTypes(returnType, node->expression()->type())){
            if(isDouble(returnType) && isInt(node->expression()->type())){
                //accept
            }
            else{
                throw "Not matching types for return. Expecting " + do_basic_type(returnType) \
                        + " and is given " + do_basic_type(node->expression()->type());
            }
        }
    }
}                                                                                                                                                                                                                                                                    
void gr8::type_checker::do_index_node(gr8::index_node *const node, int lvl) {                                                                                                                                                                                        
    ASSERT_UNSPEC;
    node->index()->accept(this, lvl + 2);
    node->pointer()->accept(this, lvl + 2);
    
    handleUnspecType(node->index()->type());
    //std::cout << "------------before" << std::endl;
    //std::cout << do_basic_type(node->pointer()->type()) << std::endl;
    handleUnspecType(node->pointer()->type());
    //std::cout << "------------after" << std::endl;
    //std::cout << do_basic_type(node->pointer()->type()) << std::endl;
    
    if(!isInt(node->index()->type())){
        throw "Excepecting type int for index but " + do_basic_type(node->index()->type()) \
                + " was given.";
    }
    
    if(!isPointer(node->pointer()->type())){
        throw "Excepecting type pointer for pointer but " + do_basic_type(node->index()->type()) \
                + " was given.";
    }
    
    node->type(dupType(node->pointer()->type()->subtype()));    
}      
void gr8::type_checker::do_null_node(gr8::null_node *const node, int lvl) {                                                                                                                                                                                          
    ASSERT_UNSPEC;
    
    basic_type* type = new basic_type(4, basic_type::TYPE_POINTER);
    type->_subtype = new basic_type(0, basic_type::TYPE_UNSPEC);
    
    node->type(type); //unspec*
}                                                                                                                                                                                                                                                                  
void gr8::type_checker::do_function_declaration_node(gr8::function_declaration_node *const node, int lvl) {                                                                                                                                                          
    std::string id = *node->identifier();
    
    if(id == "covfefe"){
        id = "_main";
        node->identifier(new std::string(id));
    }
    else if (id == "_main"){
        id = "covfefe";
        node->identifier(new std::string(id));
    }
    std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
    
    if(symbol == nullptr){
        std::shared_ptr<gr8::symbol> newFuncDecl = std::make_shared<gr8::symbol>(node->type(), *node->identifier(), 
                                                                                 true, node->isPublic(), false);
        for(cdk::basic_node* var : node->parameters()->nodes()){
            newFuncDecl.get()->addParam(dupType(((gr8::variable_declaration_node*)var)->type()));
            //std::cout << do_basic_type(((gr8::variable_declaration_node*)var)->type()) << std::endl;
        }
        
        _symtab.insert(id, newFuncDecl);
        _parent->set_new_symbol(newFuncDecl);
    }
    else{
        if(!symbol.get()->isFunction()){
            throw "Already declarated as variable.";
        }
        else{
            size_t numParamsDecl = node->parameters()->size();
            std::vector<basic_type*>* typeParamsSymTable = symbol.get()->params();
            std::vector<cdk::basic_node*>* paramsDecl = &node->parameters()->nodes();
            
            if(numParamsDecl != typeParamsSymTable->size()){
                throw "Number of parameters different from previous declaration.";
            }
            
            for(size_t i = 0; i < numParamsDecl; i++){
                if(!equalTypes(typeParamsSymTable->at(i), 
                         ((gr8::variable_declaration_node*) paramsDecl->at(i))->type())){
                    throw "Type of parameters are different from previous declaration.";
                }
            }
        }
    }
} 
void gr8::type_checker::do_function_define_node(gr8::function_define_node *const node, int lvl) {                                                                                                                                                                    
    std::string id = *node->identifier();
    
    if(id == "covfefe"){
        id = "_main";
        node->identifier(new std::string(id));
    }
    else if (id == "_main"){
        id = "covfefe";
        node->identifier(new std::string(id));
    }
    
    std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
    
    if(symbol == nullptr){
        std::shared_ptr<gr8::symbol> newFuncDecl = std::make_shared<gr8::symbol>(node->type(), *node->identifier(), 
                                                                                 true, node->isPublic(), false);
        for(cdk::basic_node* var : node->parameters()->nodes()){
            newFuncDecl.get()->addParam(dupType(((gr8::variable_declaration_node*)var)->type()));
            //std::cout << do_basic_type(((gr8::variable_declaration_node*)var)->type()) << std::endl;
        }
        
        newFuncDecl.get()->setDefined(true);
        _symtab.insert(id, newFuncDecl);
        _parent->set_new_symbol(newFuncDecl);
        _parent->set_current_function(newFuncDecl);
    }
    else{
        if(!symbol.get()->isFunction()){
            throw "Already declarated as variable.";
        }
        else if(symbol.get()->isDefined()){
            throw "Function is already defined.";
        }
        else{
            size_t numParamsDecl = node->parameters()->size();
            std::vector<basic_type*>* typeParamsSymTable = symbol.get()->params();
            std::vector<cdk::basic_node*>* paramsDecl = &node->parameters()->nodes();
            
            if(numParamsDecl != typeParamsSymTable->size()){
                throw "Number of parameters different from previous declaration.";
            }
            
            for(size_t i = 0; i < numParamsDecl; i++){
                if(!equalTypes(typeParamsSymTable->at(i), 
                         ((gr8::variable_declaration_node*) paramsDecl->at(i))->type())){
                    throw "Type of parameters are different from previous declaration.";
                }
            }
            symbol.get()->setDefined(true);
            _parent->set_current_function(symbol);
        }
    }
}                                                                                                                                                                                                                                                                    
void gr8::type_checker::do_function_call_node(gr8::function_call_node *const node, int lvl) { 
    ASSERT_UNSPEC;
    std::string id = *node->identifier();
    std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
    
    if(symbol == nullptr){
        throw "Function " + id + " is not declared.";
    }
    else{
        if(!symbol.get()->isFunction()){
            throw "Already declarated as variable.";
        }
        else{
            size_t numParamsDecl = node->parameters()->size();
            std::vector<basic_type*>* typeParamsSymTable = symbol.get()->params();
            std::vector<cdk::basic_node*>* paramsCall = &node->parameters()->nodes();
            
            if(numParamsDecl != typeParamsSymTable->size()){
                throw "Number of parameters different from previous declaration.";
            }
            
            for(size_t i = 0; i < numParamsDecl; i++){
                basic_type* paramType = typeParamsSymTable->at(i);
                
                cdk::expression_node* param = (cdk::expression_node*) paramsCall->at(i);
                param->accept(this, lvl + 2);
                
                handleUnspecType(paramType, param->type());
                
                if(!equalTypes(paramType, param->type())){
                    if(isDouble(paramType) && isInt(param->type())){
                        //accept
                    }
                    else{
                        throw "Parameter: expecting " + do_basic_type(paramType) + \
                              " but was given " + do_basic_type(param->type());
                    }
                }
            }
        }
        node->type(dupType(symbol.get()->type()));
    }
}                                                                                                                                                                                                                                                                    
void gr8::type_checker::do_variable_declaration_node(gr8::variable_declaration_node *const node, int lvl) {    
    std::string id = *node->identifier();
    std::shared_ptr<gr8::symbol> symbol = _symtab.find_local(id);
    
    if(symbol == nullptr){    
        if(node->initialization() != nullptr){
            node->initialization()->accept(this, lvl + 2);
            handleUnspecType(node->type(), node->initialization()->type());

            if(!equalTypes(node->type(), node->initialization()->type())){
                if(isDouble(node->type()) && isInt(node->initialization()->type())){
                    //accept
                }
                else{
                    throw "Variable initialization: expecting " + do_basic_type(node->type()) + \
                        "but was given " + do_basic_type(node->initialization()->type());
                }        
            }
        }
        std::shared_ptr<gr8::symbol> newVar = std::make_shared<gr8::symbol>(node->type(), *node->identifier(), 
                                                                               node->isPublic(), node->isUse());
        _symtab.insert(id, newVar);
        _parent->set_new_symbol(newVar);
    }
    else {
        throw "Identifier " + id + " already declarated.";
    }
}  
//---------------------------------------------------------------------------

void gr8::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void gr8::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

void gr8::type_checker::processIdentityNegExpressions(cdk::unary_expression_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->argument()->accept(this, lvl + 2);
    
    handleUnspecType(node->argument()->type());
    
    if(isInt(node->argument()->type())){
        node->type(dupType(node->argument()->type())); //int
    }
    else if(isDouble(node->argument()->type())){
        node->type(dupType(node->argument()->type())); // double
    }
    else{
        throw "Unexpected type on identity/neg operation: " + do_basic_type(node->argument()->type());
    }
}

void gr8::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
    processIdentityNegExpressions(node, lvl);
}

void gr8::type_checker::do_identity_node(gr8::identity_node *const node, int lvl) {                                                                                                                                                              
    processIdentityNegExpressions(node, lvl);                                                                                                                                                                                                                                                      
} 

void gr8::type_checker::do_memory_allocation_node(gr8::memory_allocation_node *const node, int lvl) {                                                                                                                                                                
    ASSERT_UNSPEC;
    node->argument()->accept(this, lvl + 2);
    
    handleUnspecType(node->argument()->type());
    
    if(isInt(node->argument()->type())){
        basic_type* type = new basic_type(4, basic_type::TYPE_POINTER);
        type->_subtype = new basic_type(0, basic_type::TYPE_UNSPEC);
    
        node->type(type); // unspec*
    }
    else{
        throw "Unexpected type on memory allocation operation: " + do_basic_type(node->argument()->type());
    }
}  

void gr8::type_checker::do_address_of_node(gr8::address_of_node *const node, int lvl) {                                                                                                                                                                              
    ASSERT_UNSPEC;
    node->lvalue()->accept(this, lvl + 2);
       
    basic_type* type = new basic_type(4, basic_type::TYPE_POINTER);
    type->_subtype = dupType(node->lvalue()->type());
    
    node->type(type);
}  

void gr8::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->argument()->accept(this, lvl + 2);
    
    handleUnspecType(node->argument()->type());
    
    if(isInt(node->argument()->type())){
        /*!int*/
        node->type(dupType(node->argument()->type())); //int
    }
    else{
        throw "Unexpected type on not operation: " + do_basic_type(node->argument()->type());
    }
}

//---------------------------------------------------------------------------

void gr8::type_checker::processMultiplicationExpressions(cdk::binary_expression_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl + 2);
    node->right()->accept(this, lvl + 2);
    
    handleUnspecType(node->left()->type(), node->right()->type());
    
    if(isInt(node->left()->type()) && isInt(node->right()->type())){
        /*int * int
         *int / int
         */
        node->type(new basic_type(4, basic_type::TYPE_INT)); //int
    }
    else if((isInt(node->left()->type()) && isDouble(node->right()->type())) || \
            (isDouble(node->left()->type()) && isInt(node->right()->type())) || \
            (isDouble(node->left()->type()) && isDouble(node->right()->type()))){
        /*int * double, double * int, double * double
         *int / double, double / int, double / double
         */
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE)); //double
    }
    else {
        throw "Unexpected type on mul/div operation: " + do_basic_type(node->left()->type())\
                +" , " + do_basic_type(node->right()->type());
    }
}

void gr8::type_checker::processComparativeExpressions(cdk::binary_expression_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl + 2);
    node->right()->accept(this, lvl + 2);
    
    handleUnspecType(node->left()->type(), node->right()->type());
    
    if(isInt(node->left()->type()) && isInt(node->right()->type())){
        /*int < int
         *int > int
         */
        node->type(new basic_type(4, basic_type::TYPE_INT)); //int
    }
    else if((isInt(node->left()->type()) && isDouble(node->right()->type())) || \
            (isDouble(node->left()->type()) && isInt(node->right()->type())) || \
            (isDouble(node->left()->type()) && isDouble(node->right()->type()))){
        /*int < double, double < int, double < double
         *int > double, double > int, double > double
         */
        node->type(new basic_type(4, basic_type::TYPE_INT)); //int
    }
    else {
        throw "Unexpected type on lt/gt operation: " + do_basic_type(node->left()->type())\
                +" , " + do_basic_type(node->right()->type());
    }
}

void gr8::type_checker::processLogicExpressions(cdk::binary_expression_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl + 2);
    node->right()->accept(this, lvl + 2);
    
    handleUnspecType(node->left()->type(), node->right()->type());
    
    if(!isInt(node->left()->type()) || \
       !isInt(node->right()->type())){
        throw "Unexpected type on and/or operation: " + do_basic_type(node->left()->type())\
                +" , " + do_basic_type(node->right()->type());
    }
    
    node->type(dupType(node->left()->type())); //int
}

void gr8::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl + 2);
    node->right()->accept(this, lvl + 2);
    
    handleUnspecType(node->left()->type(), node->right()->type());
    
    if(isInt(node->left()->type()) && isInt(node->right()->type())){
        /*int + int*/
        node->type(new basic_type(4, basic_type::TYPE_INT)); //int
    }
    else if((isInt(node->left()->type()) && isDouble(node->right()->type())) || \
            (isDouble(node->left()->type()) && isInt(node->right()->type())) || \
            (isDouble(node->left()->type()) && isDouble(node->right()->type()))){
        /*int + double, double + int, double + double*/
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE)); //double
    }
    else if((isPointer(node->left()->type()) && isInt(node->right()->type()))){
        /*pointer + int*/
        node->type(dupType(node->left()->type())); //pointer
    }
    else if((isInt(node->left()->type()) && isPointer(node->right()->type()))){
        /*int + pointer*/
        node->type(dupType(node->right()->type())); //pointer
    }
    else{
        throw "Unexpected type on add operation: " + do_basic_type(node->left()->type())\
                +" , " + do_basic_type(node->right()->type());
    }

}
void gr8::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl + 2);
    node->right()->accept(this, lvl + 2);
    
    //std::cout << "------------before" << std::endl;
    //std::cout << do_basic_type(node->left()->type()) << std::endl;
    //std::cout << do_basic_type(node->right()->type()) << std::endl;
    handleUnspecType(node->left()->type(), node->right()->type());
    //std::cout << "------------after" << std::endl;
    //std::cout << do_basic_type(node->left()->type()) << std::endl;
    //std::cout << do_basic_type(node->right()->type()) << std::endl;
    
    if(isInt(node->left()->type()) && isInt(node->right()->type())){
        /*int - int*/
        node->type(new basic_type(4, basic_type::TYPE_INT)); //int
    }
    else if((isInt(node->left()->type()) && isDouble(node->right()->type())) || \
            (isDouble(node->left()->type()) && isInt(node->right()->type())) || \
            (isDouble(node->left()->type()) && isDouble(node->right()->type()))){
        /*int - double, double - int, double - double*/
        node->type(new basic_type(8, basic_type::TYPE_DOUBLE)); //double
    }
    else if(isPointer(node->left()->type()) && isInt(node->right()->type())){
        /*pointer - int*/
        node->type(dupType(node->left()->type())); //pointer
    }
    else if(isPointer(node->left()->type()) && isPointer(node->right()->type())){
        /*pointer - pointer*/
        if(equalTypes(node->left()->type(), node->right()->type())){
            node->type(new basic_type(4, basic_type::TYPE_INT)); //int
        }        
        else{
            throw "Unexpected type on sub operation: " + do_basic_type(node->left()->type())\
            +" , " + do_basic_type(node->right()->type());
        }
    }
    else{
        throw "Unexpected type on sub operation: " + do_basic_type(node->left()->type())\
            +" , " + do_basic_type(node->right()->type());
    }  
}
void gr8::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
    processMultiplicationExpressions(node,lvl);
}
void gr8::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
    processMultiplicationExpressions(node,lvl);
}
void gr8::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl + 2);
    node->right()->accept(this, lvl + 2);
    
    handleUnspecType(node->left()->type(), node->right()->type());
    
    if(!isInt(node->left()->type()) || \
       !isInt(node->right()->type())){
        throw "Unexpected type on mod operation: " + do_basic_type(node->left()->type())\
                +" , " + do_basic_type(node->right()->type());
    }
    
    node->type(dupType(node->left()->type())); //int
}
void gr8::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
    processComparativeExpressions(node,lvl);
}
void gr8::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
    // does not exist in gr8
}
void gr8::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
    // does not exist in gr8
}
void gr8::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
    processComparativeExpressions(node,lvl);
}
void gr8::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
    // does not exist in gr8
}
void gr8::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->left()->accept(this, lvl + 2);
    node->right()->accept(this, lvl + 2);
    
    handleUnspecType(node->left()->type(), node->right()->type());
    
    if(isInt(node->left()->type()) && isInt(node->right()->type())){
        /*int == int*/
        node->type(new basic_type(4, basic_type::TYPE_INT)); //int
    }
    else if((isInt(node->left()->type()) && isDouble(node->right()->type())) || \
            (isDouble(node->left()->type()) && isInt(node->right()->type())) || \
            (isDouble(node->left()->type()) && isDouble(node->right()->type()))){
        /*int == double, double == int, double == double*/
        node->type(new basic_type(4, basic_type::TYPE_INT)); //int
    }
    else if(isPointer(node->left()->type()) && isPointer(node->right()->type())){
        /*pointer == pointer*/
        if(equalTypes(node->left()->type(), node->right()->type())){
            node->type(new basic_type(4, basic_type::TYPE_INT)); //int
        }
        else{
            throw "Unexpected type on eq operation: " + do_basic_type(node->left()->type())\
                +" , " + do_basic_type(node->right()->type());
        }
    }
    else {
        throw "Unexpected type on eq operation: " + do_basic_type(node->left()->type())\
                +" , " + do_basic_type(node->right()->type());
    }
}

void gr8::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
    processLogicExpressions(node, lvl);
}
void gr8::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
    processLogicExpressions(node, lvl);
}
//---------------------------------------------------------------------------

void gr8::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
    ASSERT_UNSPEC;
    const std::string &id = node->name();
    std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);

    if (symbol != nullptr) {
        if(symbol->isFunction()){
            throw "Already declared as function.";
        }
        node->type(symbol->type());
    } else {
      throw "Variable with identifier " + id + " was not declarated.";
  }
}

void gr8::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
}

void gr8::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
    ASSERT_UNSPEC;
    node->lvalue()->accept(this, lvl + 2);
    node->rvalue()->accept(this, lvl + 2);

    //std::cout << "------------before" << std::endl;
    //std::cout << do_basic_type(node->lvalue()->type()) << std::endl;
    //std::cout << do_basic_type(node->rvalue()->type()) << std::endl;
    handleUnspecType(node->lvalue()->type(), node->rvalue()->type());
    //std::cout << "------------after" << std::endl;
    //std::cout << do_basic_type(node->lvalue()->type()) << std::endl;
    //std::cout << do_basic_type(node->rvalue()->type()) << std::endl;
    
    if(!equalTypes(node->lvalue()->type(), node->rvalue()->type())){
        if(isDouble(node->lvalue()->type()) && isInt(node->rvalue()->type())){
            //accept
        }
        else{
            throw "Assignment: types must be the same but was given " + \
              do_basic_type(node->lvalue()->type()) + "=" + do_basic_type(node->rvalue()->type());
        }
    }
   
    node->type(dupType(node->lvalue()->type()));
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
    node->argument()->accept(this, lvl + 2);
}

void gr8::type_checker::do_print_node(gr8::print_node * const node, int lvl) {
    node->argument()->accept(this, lvl + 2);
    handleUnspecType(node->argument()->type());
    
    if(!isInt(node->argument()->type()) && !isDouble(node->argument()->type()) && \
       !isString(node->argument()->type())){
        throw "Wrong type in print operation: " + do_basic_type(node->argument()->type());
    }
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_read_node(gr8::read_node * const node, int lvl) {
    ASSERT_UNSPEC;
    if(node->type() == nullptr){
        node->type(new basic_type(0, basic_type::TYPE_UNSPEC));
    }
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_if_node(gr8::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);

  if(!equalTypes(node->condition()->type(), basic_type::TYPE_INT)){
      throw "Condition of if-node should be of type int, but " + \
              do_basic_type(node->condition()->type()) + " was given.";
  }
}

void gr8::type_checker::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
  
  if(!equalTypes(node->condition()->type(), basic_type::TYPE_INT)){
      throw "Condition of if-else-node should be of type int, but " + \
              do_basic_type(node->condition()->type()) + " was given.";
  }
}
