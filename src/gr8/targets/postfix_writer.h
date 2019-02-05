#ifndef __GR8_SEMANTICS_POSTFIX_WRITER_H__
#define __GR8_SEMANTICS_POSTFIX_WRITER_H__

#include <string>
#include <iostream>
#include <stack>
#include <set>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace gr8 {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<gr8::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;
    std::stack<int> _againLabels;
    std::stack<int> _stopLabels;
       
    enum Segment {
        BSS,
        DATA,
        RODATA,
        TEXT,
        UNINIT
    };

    Segment _actualSegment = UNINIT;
    Segment _previousSegment = UNINIT;
    bool _isVarPublic = false;
    std::string _globalVarLabel;
    int _offsetArg;
    int _offsetVar;
    bool _isParam = false;
    
    std::set<std::string> _externIdentifiers;
    
  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<gr8::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0){
    }
        
    void switchSegment(Segment segment){
        if(_actualSegment != segment){
            _previousSegment = _actualSegment;
            switch(segment){
                case BSS:
                    _pf.BSS();
                    break;
                case DATA:
                    _pf.DATA();
                    break;
                case RODATA:
                    _pf.RODATA();
                    break;
                case TEXT:
                    _pf.TEXT();
                    break;
                default:
                    throw std::string("SwitchSegment: wrong segment.");
            }
            _actualSegment = segment;
        }
        if(_previousSegment == UNINIT){
            _previousSegment = _actualSegment;
        }
    }
    
    void writeExternIdentifiers(){
        _pf.EXTERN("printi");
        _pf.EXTERN("printd");
        _pf.EXTERN("prints");
        _pf.EXTERN("println");
        _pf.EXTERN("readi");
        _pf.EXTERN("readd");
        
        for(std::string identifier : _externIdentifiers){
            _pf.EXTERN(identifier);
        }
    }

  public:
    ~postfix_writer() {
      os().flush();
    }

  private:     
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }
    
    void processMultiplicationExpressions(cdk::binary_expression_node * const node, int lvl);
    void processComparativeExpressions(cdk::binary_expression_node * const node, int lvl);

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // gr8

#endif
