// $Id: index_node.h,v 1.1 2018/03/09 00:57:42 ist424843 Exp $ -*- c++ -*-
#ifndef __GR8_INDEXNODE_H__
#define __GR8_INDEXNODE_H__

#include <cdk/ast/lvalue_node.h>

namespace gr8 {

  /**
   * Class for describing index nodes.
   */
  class index_node: public cdk::lvalue_node {
    cdk::expression_node* _pointer;
    cdk::expression_node* _index;

  public:
    inline index_node(int lineno, cdk::expression_node* pointer, cdk::expression_node* index) :
        cdk::lvalue_node(lineno), _pointer(pointer), _index(index) {
    }

  public:
    inline cdk::expression_node* pointer() {
      return _pointer;
    }
    inline cdk::expression_node* index() {
      return _index;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_node(this, level);
    }

  };

} // gr8

#endif
