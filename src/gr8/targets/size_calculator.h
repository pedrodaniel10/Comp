#ifndef __GR8_SEMANTICS_SIZECALCULATOR_H__
#define __GR8_SEMANTICS_SIZECALCULATOR_H__

#include <string>
#include <iostream>
#include <cdk/ast/basic_node.h>
#include <cdk/symbol_table.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace gr8 {

  /**
   * Calculates offset for variables in functions
   */
  class size_calculator : public basic_ast_visitor {
      size_t _size = 0;

  public:
    size_calculator(std::shared_ptr<cdk::compiler> compiler) :
      basic_ast_visitor(compiler){
      
    }

  public:
    ~size_calculator() {
    }

    inline size_t size(){
        return _size;
    }
    
    inline void addSize(int i){
        _size += i;
    }

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // gr8

#endif
