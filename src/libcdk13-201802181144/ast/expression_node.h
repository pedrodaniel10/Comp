#ifndef __CDK13_AST_EXPRESSIONNODE_H__
#define __CDK13_AST_EXPRESSIONNODE_H__

#include <cdk/ast/typed_node.h>

namespace cdk {

  /**
   * Expressions are typed nodes that have a value.
   */
  class expression_node: public typed_node {

  protected:
    /**
     * @param lineno the source code line corresponding to the node
     */
    expression_node(int lineno) :
        typed_node(lineno) {
    }

  };

} // cdk

#endif
