#ifndef __GR8_VARIABLEDECLARATIONNODE_H__
#define __GR8_VARIABLEDECLARATIONNODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/identifier_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/typed_node.h>
#include <cdk/basic_type.h>

namespace gr8 {

  /**
   * Class for describing variable declaration nodes.
   */
  class variable_declaration_node: public cdk::typed_node {
      bool _isPublic;
      bool _isUse;
      std::string* _identifier;
      cdk::expression_node* _initialization;

  public:
    inline variable_declaration_node(int lineno, 
                                bool isPublic,
                                bool isUse,
                                basic_type* type,
                                std::string* identifier,
                                cdk::expression_node* initialization) :
            cdk::typed_node(lineno), _isPublic(isPublic), _isUse(isUse),
            _identifier(identifier),  _initialization(initialization) {
        this->type(type);
    }

  public:    
      inline bool isPublic(){
          return _isPublic;
      }
      
      inline bool isUse(){
          return _isUse;
      }
      
      inline std::string* identifier(){
          return _identifier;
      }
      
      inline cdk::expression_node* initialization(){
          return _initialization;
      }
      
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_declaration_node(this, level);
    }

  };

} // gr8

#endif
