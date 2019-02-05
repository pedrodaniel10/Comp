#ifndef __GR8_FUNCTIONCALLNODE_H__
#define __GR8_FUNCTIONCALLNODE_H__

#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing function call nodes.
   */
  class function_call_node: public cdk::expression_node {
      std::string* _identifier;
      cdk::sequence_node* _parameters;

  public:
    inline function_call_node(int lineno, 
                                std::string* identifier,
                                cdk::sequence_node* parameters) :
            cdk::expression_node(lineno), _identifier(identifier), 
        _parameters(parameters) {
    }

  public:     
      inline std::string* identifier(){
          return _identifier;
      }
      
      inline cdk::sequence_node* parameters(){
          return _parameters;
      }
      
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_call_node(this, level);
    }

  };

} // gr8

#endif
