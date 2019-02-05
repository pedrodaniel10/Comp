// $Id: sweeping_from_to_by_do_node.h,v 1.4 2018/03/09 20:16:31 ist424843 Exp $ -*- c++ -*-
#ifndef __GR8_SWEEPINGFROMTOBYDONODE_H__
#define __GR8_SWEEPINGFROMTOBYDONODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing sweeping-from-to-by-do-cycle nodes (for instruction).
   */
  class sweeping_from_to_by_do_node : public cdk::basic_node {
    cdk::lvalue_node* _lvalue;
    cdk::expression_node* _from;
    cdk::expression_node* _to;
    cdk::expression_node* _increment;
    cdk::basic_node* _block;

  public:
    inline sweeping_from_to_by_do_node(int lineno, 
                                  cdk::lvalue_node* lvalue,
                                  cdk::expression_node* from, 
                                  cdk::expression_node* to,
                                  cdk::expression_node* increment, 
                                  cdk::basic_node* block) :
        basic_node(lineno), _lvalue(lvalue), _from(from),
        _to(to), _increment(increment), _block(block) {
    }

  public:
    inline cdk::lvalue_node* lvalue() {
     return _lvalue;
    }
      
    inline cdk::expression_node* from() {
      return _from;
    }
    
    inline cdk::expression_node* to() {
      return _to;
    }
    
    inline cdk::expression_node* increment() {
      return _increment;
    }
    
    inline cdk::basic_node* block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweeping_from_to_by_do_node(this, level);
    }

  };

} // gr8

#endif
