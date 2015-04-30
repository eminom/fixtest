
//~

#ifndef _FIXSHOW_PY3__DEF__
#define _FIXSHOW_PY3__DEF__

// The strange fixed point class is scracthed from 
// http://developer.mbed.org/users/sravet/code/fixedpoint/
// If you have any problem using this fixed point lib, please fight the origin author.
// 

#include "Python.h"     //Windows and MacOSX do care about capitals
#include "fp/fixed_class.h"
#include "fp/fixed_func.h"

typedef fixedpoint::fixed_point<16> fixed16;

typedef struct {
	PyObject_HEAD
	fixed16 value;
}Py3_Fixed16;

extern PyTypeObject Py3_Fixed16Type;	//` a structure(describing a Py3 class)

// The style is inherited from RAPLANV1
#define FIX16Func(a)	__Fixed16Func_##a
#define Py3_Fixed16Check(op)	PyObject_TypeCheck(op, &Py3_Fixed16Type)

#endif
