#ifndef __GR8_MEMORYALLOCATIONNODE_H__
#define __GR8_MEMORYALLOCATIONNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace gr8 {

  /**
   * Class for describing memory allocation nodes.
   */
  class memory_allocation_node: public cdk::unary_expression_node {
  public:
    inline memory_allocation_node(int lineno, cdk::expression_node* arg) : 
                                cdk::unary_expression_node(lineno, arg) {}

  public:
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_memory_allocation_node(this, level);
    }
  };

} // gr8

#endif