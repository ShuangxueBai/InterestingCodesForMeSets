#ifndef SomeMacro_h
#define SomeMacro_h

#define SET_PROPERTY(_type, _methodName, _property)  void set##_methodName## ( const _type##& prop) { (_property) = prop; }
#define GET_PROPERTY(_type, _methodName, _property) _type get##_methodName## () const { return (_property); }



#endif


