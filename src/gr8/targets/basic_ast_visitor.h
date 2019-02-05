#ifndef __GR8_BASIC_AST_VISITOR_H__
#define __GR8_BASIC_AST_VISITOR_H__

#include <string>
#include <memory>
#include <iostream>
#include <cdk/compiler.h>
#include "symbol.h"

/* do not edit -- include node forward declarations */
#define __NODE_DECLARATIONS_ONLY__
#include "ast/all.h"  // automatically generated
#undef __NODE_DECLARATIONS_ONLY__
/* do not edit -- end */

//!
//! Print nodes as XML elements to the output stream.
//!
class basic_ast_visitor {
protected:
  //! The owner compiler
  std::shared_ptr<cdk::compiler> _compiler;

private:

  // last symbol inserted in symbol table
  std::shared_ptr<gr8::symbol> _new_symbol;
  
  // current function (for return)
  std::shared_ptr<gr8::symbol> _current_function;

protected:
  basic_ast_visitor(std::shared_ptr<cdk::compiler> compiler) :
      _compiler(compiler) {
  }

  bool debug() {
    return _compiler->debug();
  }

  std::ostream &os() {
    return *_compiler->ostream();
  }

public:
  virtual ~basic_ast_visitor() {
  }

public:
  std::shared_ptr<gr8::symbol> new_symbol() {
    return _new_symbol;
  }

  void set_new_symbol(std::shared_ptr<gr8::symbol> symbol) {
    _new_symbol = symbol;
  }

  void reset_new_symbol() {
    _new_symbol = nullptr;
  }
  
  std::shared_ptr<gr8::symbol> current_function() {
    return _current_function;
  }

  void set_current_function(std::shared_ptr<gr8::symbol> symbol) {
    _current_function = symbol;
  }

  void reset_current_function() {
    _current_function = nullptr;
  }
  
  
public:
  
  inline std::string do_basic_type(basic_type* type){
    if(type == nullptr) return "";
    else if(type->_name == basic_type::TYPE_VOID) return "void";
    else if(type->_name == basic_type::TYPE_INT) return "int";
    else if(type->_name == basic_type::TYPE_DOUBLE) return "double";
    else if(type->_name == basic_type::TYPE_STRING) return "string";
    else if(type->_name == basic_type::TYPE_POINTER) return do_basic_type(type->_subtype) + "*";
    else return "unknown type";
  }

  inline std::string printBool(bool boolean){
    if(boolean) return "true";
    else return "false";
  }
  
      inline bool equalTypes(basic_type* t1, basic_type::type t2){
        if(t1 == nullptr){
            return false;
        }
        else if(t1->name() == t2){
            return true;
        }
        else{
            return false;
        }
    }
    
    inline bool equalTypes(basic_type* t1, basic_type* t2){
        if(t1 == t2){
            return true;
        }
        else if (t1 == nullptr || t2 == nullptr){
            return false;
        }
        else if ((t1->name() == t2->name()) && (t1->size() == t2->size())){
            if(t1->name() == basic_type::TYPE_POINTER){
                return equalTypes(t1->subtype(), t2->subtype());
            }
            else{
                return true;
            }
        }
        return false;
    }
    
    inline bool isInt(basic_type* t){
        return equalTypes(t, basic_type::TYPE_INT);
    }
    
    inline bool isDouble(basic_type* t){
        return equalTypes(t, basic_type::TYPE_DOUBLE);
    }
    
    inline bool isPointer(basic_type* t){
        return equalTypes(t, basic_type::TYPE_POINTER);
    }
    
    inline bool isString(basic_type* t){
        return equalTypes(t, basic_type::TYPE_STRING);
    }
    
    inline bool isVoid(basic_type* t){
        return equalTypes(t, basic_type::TYPE_VOID);
    }
    
    inline bool isUnspec(basic_type* t){
        return equalTypes(t, basic_type::TYPE_UNSPEC);
    }
    
public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#define __PURE_VIRTUAL_DECLARATIONS_ONLY__
#include "ast/visitor_decls.h"       // automatically generated
#undef __PURE_VIRTUAL_DECLARATIONS_ONLY__
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

};

#endif
