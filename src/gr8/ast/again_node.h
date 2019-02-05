#ifndef __GR8_AGAINNODE_H__
#define __GR8_AGAINNODE_H__

#include <cdk/ast/basic_node.h>

namespace gr8 {

  /**
   * Class for describing again nodes.
   */
  class again_node: public cdk::basic_node {
      cdk::integer_node* _argument;
  public:
    inline again_node(int lineno, cdk::integer_node* argument) : 
      cdk::basic_node(lineno), _argument(argument) {}

  public:
      inline cdk::integer_node* argument(){
          return _argument;
      }
      
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_again_node(this, level);
    }
  };

} // gr8

#endif