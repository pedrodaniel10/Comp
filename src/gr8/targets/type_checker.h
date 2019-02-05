// $Id: type_checker.h,v 1.3 2018/05/19 02:41:06 ist424843 Exp $ -*- c++ -*-
#ifndef __GR8_SEMANTICS_TYPE_CHECKER_H__
#define __GR8_SEMANTICS_TYPE_CHECKER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include "targets/symbol.h"
#include "targets/basic_ast_visitor.h"

namespace gr8 {

  /**
   * Print nodes as XML elements to the output stream.
   */
  class type_checker: public basic_ast_visitor {
    cdk::symbol_table<gr8::symbol> &_symtab;

    basic_ast_visitor *_parent;

  public:
    type_checker(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<gr8::symbol> &symtab, basic_ast_visitor *parent) :
        basic_ast_visitor(compiler), _symtab(symtab), _parent(parent) {
    }

  public:
    ~type_checker() {
      os().flush();
    }

  protected:
    void processIdentityNegExpressions(cdk::unary_expression_node * const node, int lvl);
    void processMultiplicationExpressions(cdk::binary_expression_node * const node, int lvl);
    void processComparativeExpressions(cdk::binary_expression_node * const node, int lvl);
    void processLogicExpressions(cdk::binary_expression_node * const node, int lvl);
    template<typename T>
    void process_literal(cdk::literal_node<T> * const node, int lvl) {
    }
        
    inline void handleUnspecType(basic_type* t){
        if(isUnspec(t)){
            t->_name = basic_type::TYPE_INT;
            t->_size = 4;
        }
    }
    
    inline void handleUnspecType(basic_type* t1, basic_type* t2){
        if(isPointer(t1) && isPointer(t2)){
            handleUnspecType(t1->subtype(), t2->subtype());
        }
        else if(isPointer(t1) && isUnspec(t2)){
            t2->_name = basic_type::TYPE_INT;
            t2->_size = 4;
        }
        else if(isUnspec(t1) && isPointer(t2)){
            t1->_name = basic_type::TYPE_INT;
            t1->_size = 4;
        }
        else if(isUnspec(t1) && !isUnspec(t2)){
            t1->_name = t2->name();
            t1->_size = t2->size();
        }
        else if(!isUnspec(t1) && isUnspec(t2)){
            t2->_name = t1->name();
            t2->_size = t1->size();
        }
        else if(isUnspec(t1) && isUnspec(t2)){
            t1->_name = basic_type::TYPE_INT;
            t1->_size = 4;
            t2->_name = basic_type::TYPE_INT;
            t2->_size = 4;
        }
    }
        
    basic_type* dupType(basic_type* t){
        if(t == nullptr){
            return nullptr;
        }
        else{
            basic_type* type = new basic_type(t->size(), t->name());
            type->_subtype = dupType(t->subtype());
            return type;
        }
    }

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // gr8

//---------------------------------------------------------------------------
//     HELPER MACRO FOR TYPE CHECKING
//---------------------------------------------------------------------------

#define CHECK_TYPES(compiler, symtab, node) { \
  try { \
    gr8::type_checker checker(compiler, symtab, this); \
    (node)->accept(&checker, 0); \
  } \
  catch (const std::string &problem) { \
    std::cerr << (node)->lineno() << ": " << problem << std::endl; \
    return; \
  } \
  catch (char const* problem) { \
    std::cerr << (node)->lineno() << ": " << problem << std::endl; \
    return; \
  } \
}

#define ASSERT_SAFE_EXPRESSIONS CHECK_TYPES(_compiler, _symtab, node)

#endif
