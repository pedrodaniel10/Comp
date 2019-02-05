#ifndef __GR8_SEMANTICS_SYMBOL_H__
#define __GR8_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace gr8 {

  class symbol {
    basic_type *_type;
    std::string _name;
    
    bool _isPublic;
    bool _isUse;
    bool _isGlobal;
    int _offset = 0;
    
    bool _isFunction = false;
    bool _isDefined = false;
    std::vector<basic_type*> _params;
    int _lblReturn;
    


  public:
    
     //constructor for variables 
     symbol(basic_type *type, const std::string &name, bool isPublic, bool isUse) :
        _type(type), _name(name), _isPublic(isPublic), _isUse(isUse){
    }
      
      
    //constructor for functions
    symbol(basic_type *type, const std::string &name, bool isFunction, 
           bool isPublic, bool isDefined) :
        _type(type), _name(name), _isPublic(isPublic), _isFunction(isFunction), 
        _isDefined(isDefined){
    }

    virtual ~symbol() {
      delete _type;
    }

    basic_type* type() const {
      return _type;
    }
    const std::string &name() const {
      return _name;
    }
    
    inline bool isFunction(){
        return _isFunction;
    }
    
    inline void addParam(basic_type* type){
        _params.push_back(type);
    }
    
    inline std::vector<basic_type*>* params(){
        return &_params;
    }
    
    inline bool isDefined(){
        return _isDefined;
    }
    
    inline void setDefined(bool defined){
        _isDefined = defined;
    }
    
    inline bool isPublic(){
        return _isPublic;
    }
    
    inline bool isUse(){
        return _isUse;
    }
    
    inline int offset(){
        return _offset;
    }
    
    inline void offset(int offset){
        _offset = offset;
    }
    
    inline int lblReturn(){
        return _lblReturn;
    }
    
    inline void lblReturn(int lbl){
        _lblReturn = lbl;
    }
    
    inline bool isGlobal(){
        return _isGlobal;
    }
    
    inline void isGlobal(bool isGlobal){
        _isGlobal = isGlobal;
    }
    
  };

} // gr8

#endif
