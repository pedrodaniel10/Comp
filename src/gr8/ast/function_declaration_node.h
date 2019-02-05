#ifndef __GR8_FUNCTIONDECLARATIONNODE_H__
#define __GR8_FUNCTIONDECLARATIONNODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/identifier_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/typed_node.h>
#include <cdk/basic_type.h>

namespace gr8 {

  /**
   * Class for describing function declaration nodes.
   */
  class function_declaration_node: public cdk::typed_node {
      bool _isPublic;
      bool _isProcedure;
      std::string* _identifier;
      cdk::sequence_node* _parameters;
      

  public:
    inline function_declaration_node(int lineno, 
                                bool isPublic,
                                bool isProcedure,
                                basic_type* type,
                                std::string* identifier,
                                cdk::sequence_node* parameters) :
            cdk::typed_node(lineno), _isPublic(isPublic), 
            _isProcedure(isProcedure), _identifier(identifier), 
        _parameters(parameters) {
        this->type(type);
    }

  public:
      inline bool isPublic(){
          return _isPublic;
      }

      inline bool isProcedure(){
          return _isProcedure;
      }
      
      inline std::string* identifier(){
          return _identifier;
      }
      
      inline cdk::sequence_node* parameters(){
          return _parameters;
      }
      
      inline void identifier(std::string* id){
          _identifier = id;
      }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_declaration_node(this, level);
    }

  };

} // gr8

#endif
