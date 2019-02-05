// $Id: print_node.h,v 1.2 2018/03/09 20:16:31 ist424843 Exp $ -*- c++ -*-
#ifndef __GR8_PRINTNODE_H__
#define __GR8_PRINTNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {
    cdk::expression_node* _argument;
    bool _hasNewLine;

  public:
    inline print_node(int lineno, cdk::expression_node *argument, bool hasNewLine) :
        cdk::basic_node(lineno), _argument(argument), _hasNewLine(hasNewLine) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }
    
    inline bool hasNewLine(){
        return _hasNewLine;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }

  };

} // gr8

#endif
