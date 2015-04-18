

#include "py3fmath.h"
#include <structmember.h>       // For PyMemberDef

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <sstream>

static
void FIX16Func(Dealloc)(Py3_Fixed16 *self)
{
	// Py_XDECREF(self->name);
	/*Notice that Py_TYPE is different from Py_Type*/
    // PySys_WriteStdout("Dealloc XX one Py3.Fixed16\n");
	Py_TYPE(self)->tp_free((PyObject*)self);
}


static 
PyObject* FIX16Func(Str)(Py3_Fixed16 *self)
{
	char buff[BUFSIZ];
	sprintf(buff, "%f", float(self->value));
	return PyUnicode_FromFormat("fixed(%s)", buff);
}

static PyObject* FIX16Func(Repr)(Py3_Fixed16 *self)
{
    char buff[BUFSIZ];
    sprintf(buff, "%f", float(self->value));
    return PyUnicode_FromFormat("fixed(%s)", buff);
}

static
int FIX16Func(Init)(Py3_Fixed16 *self, PyObject *args, PyObject *kwds)
{
	float floatValue = 0;
	static char *kwlist[]={"float", NULL};
	if( ! PyArg_ParseTupleAndKeywords(args, kwds, "f", kwlist, &floatValue)){
		//No need to set excetpion ourselves
		return -1;
	}
	self->value = floatValue;	//~ automatical conversion
	return 0;
}

static 
PyObject* FIX16Func(New)(PyTypeObject *_type, PyObject *args, PyObject *kwds)
{
	if( Py3_Fixed16 *self = (Py3_Fixed16*)_type->tp_alloc(_type, 0))
	{
		self->value = 99;	//~ default
		return (PyObject*)self;	//~ Not a C++ derivation. 
	}
	PyErr_SetString(PyExc_RuntimeError, "Cannot alloc FIX16 object");
	return NULL;	//~ Raise this error
}



static 
PyObject* FIX16Func(float)(Py3_Fixed16 *self, void*closure)
{
	return PyFloat_FromDouble(float(self->value));
}

static 
PyObject* FIX16Func(int)(Py3_Fixed16 *self, void*closure)
{
	return PyLong_FromLong(int(self->value));
}

static 
PyObject* FIX16Func(intValue)(Py3_Fixed16 *self, void*closure)
{
    return PyLong_FromLong(self->value.intValue);
}

static PyGetSetDef Py3_Fixed16GetSet[]={
	{"float", (getter)FIX16Func(float), (setter)0, 
		"The floating representation for this fixed16", NULL},
	{"int", (getter)FIX16Func(int), (setter)0, 
		"The integer representation for this fixed16", NULL},
    {"intValue", (getter)FIX16Func(intValue), (setter)0,
        "The internal storage for fixed16", NULL},
	{NULL},
};

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//~ Methods
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

static 
PyObject* FIX16Func(print)(Py3_Fixed16 *self, void*closure)
{
    //TODO: fix return NONE
    PySys_WriteStdout("Some debug information\n");

    //~
    Py_INCREF(Py_None);
    return Py_None;
}
//

static PyObject* new_fixed16_ex(fixed16 value, PyTypeObject *type)
{
    Py3_Fixed16 *self = (Py3_Fixed16*)(type->tp_alloc(type,0));
    if(self!=NULL){
        self->value = value;    // copy
    }
    return (PyObject*)self;
}

#define new_fixed16(value)  \
    new_fixed16_ex(value, &Py3_Fixed16Type)


static PyMethodDef Py3_Fixed16Methods[]={
	{"print", (PyCFunction)FIX16Func(print), 
		METH_NOARGS, "print the debug information for this fixed16 object"},
    // {"__sub__", (PyCFunction)FIX16Func(sub),
    //     METH_VARARGS, "sub operator"},
	{NULL},
};


//~ what the hell is this?
static PyMemberDef Py3_Fixed16Members[] = {
    {0}
};


// As number

#define _OutDebug(...)  PySys_WriteStdout(__VA_ARGS__)
//#define _OutDebug(...)  

#define _B_INFO "Binary operator :"

#define _Decl(NAME, __OP__) \
static PyObject* FIX16Func(NAME)(PyObject *left, PyObject *right){\
    if( !Py3_Fixed16Check(left) && !Py3_Fixed16Check(right)){\
        PyErr_SetString(PyExc_TypeError, "Do not support " #__OP__ " for Py.Fixed16");\
        return NULL;\
    }\
    PyObject *result = Py_NotImplemented;\
    if(Py3_Fixed16Check(left) && Py3_Fixed16Check(right)) {\
        Py3_Fixed16 *lhs = (Py3_Fixed16*)left;\
        Py3_Fixed16 *rhs = (Py3_Fixed16*)right;\
        result = new_fixed16(lhs->value __OP__ rhs->value);\
        _OutDebug(_B_INFO"Fixed16 " #__OP__ " Fixed16\n");\
    } else if(Py3_Fixed16Check(left) && PyFloat_Check(right)){\
        Py3_Fixed16 *lhs = (Py3_Fixed16*)left;\
        float rhs = (float)PyFloat_AsDouble(right);\
        result = new_fixed16(lhs->value __OP__ fixed16(rhs));\
        _OutDebug(_B_INFO"Fixed16 " #__OP__ " float\n");\
    } else if(PyFloat_Check(left) && Py3_Fixed16Check(right)){\
        float lhs = (float)PyFloat_AsDouble(left);\
        Py3_Fixed16 *rhs = (Py3_Fixed16*)right;\
        result = new_fixed16(fixed16(lhs) __OP__ rhs->value);\
        _OutDebug(_B_INFO"float " #__OP__ " Fixed16\n");\
    }\
    if(result==Py_NotImplemented){\
        Py_INCREF(result);\
    }\
    return result;\
}

_Decl(add, +)
_Decl(sub, -)
_Decl(mult, *)
_Decl(div, /)

// #define _Decli(NAME, __OP__) \
// static PyObject* FIX16Func(NAME)(PyObject *left, PyObject *right){\
//     if( !Py3_Fixed16Check(left) && !Py3_Fixed16Check(right)){\
//         PyErr_SetString(PyExc_TypeError, "Do not support " #__OP__ " for Py.Fixed16");\
//         return NULL;\
//     }\
//     _OutDebug("Inplace "#__OP__"\n");\
//     PyObject *result = Py_NotImplemented;\
//     if(Py3_Fixed16Check(left) && Py3_Fixed16Check(right)) {\
//         Py3_Fixed16 *lhs = (Py3_Fixed16*)left;\
//         Py3_Fixed16 *rhs = (Py3_Fixed16*)right;\
//         lhs->value __OP__ rhs->value;\
//     } else if(Py3_Fixed16Check(left) && PyFloat_Check(right)){\
//         _OutDebug("Yes ??? Fixed16 "#__OP__" float\n");\
//         Py3_Fixed16 *lhs = (Py3_Fixed16*)left;\
//         float rhs = (float)PyFloat_AsDouble(right);\
//         lhs->value __OP__ rhs;\
//     } else if(PyFloat_Check(left) && Py3_Fixed16Check(right)){\
//         PyErr_SetString(PyExc_TypeError, "Do not support inplace for float "#__OP__" Py.Fixed16");\
//         return NULL;\
//     }\
//     if(result==Py_NotImplemented){\
//         Py_INCREF(result);\
//     }\
//     return result;\
// }

// _Decli(iadd, +=)
// _Decli(isub, -=)
// _Decli(imult,*=)
// _Decli(idiv, /=)


static PyNumberMethods Py3_Fixed16AsNumbers = {
    FIX16Func(add),                /* nb_add */
    FIX16Func(sub),                /* nb_subtract */
    FIX16Func(mult),               /* nb_multiply */
    0,                            /* nb_remainder */
    0,                               /* nb_divmod */
    0,                                          /* nb_power */
    (unaryfunc)0,                  /* nb_negative */
    (unaryfunc)0,                  /* nb_positive */
    (unaryfunc)0,                       /* nb_absolute */
    (inquiry)0,                        /* nb_bool */
    0,                                          /*nb_invert*/
    0,                                          /*nb_lshift*/
    0,                                          /*nb_rshift*/
    0,                                          /*nb_and*/
    0,                                          /*nb_xor*/
    0,                                          /*nb_or*/
    0,                                          /*nb_int*/
    0,                                          /*nb_reserved*/
    0,                                          /*nb_float*/
    0,                            /*nb_inplace_add*/
    0,                            /*nb_inplace_subtract*/
    0,                           /*nb_inplace_multiply*/
    0,                                          /*nb_inplace_remainder*/
    0,                                          /*nb_inplace_power*/
    0,                                          /*nb_inplace_lshift*/
    0,                                          /*nb_inplace_rshift*/
    0,                                          /*nb_inplace_and*/
    0,                                          /*nb_inplace_xor*/
    0,                                          /*nb_inplace_or*/
    0,                               /* nb_floor_divide */
    FIX16Func(div),                  /* nb_true_divide */
    0,                                          /* nb_inplace_floor_divide */
    0,                           /* nb_inplace_true_divide */
};

PyTypeObject Py3_Fixed16Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "Py3.Fixed16",             /* tp_name */
    sizeof(Py3_Fixed16),        /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)FIX16Func(Dealloc), /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    (reprfunc)FIX16Func(Repr),  /* tp_repr */
    &Py3_Fixed16AsNumbers,      /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    (reprfunc)FIX16Func(Str), /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Py3_Fixed16 objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    Py3_Fixed16Methods,             /* tp_methods */
    Py3_Fixed16Members,     //,     /* tp_members */
    Py3_Fixed16GetSet,                /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)FIX16Func(Init), /* tp_init */
    0,                         /* tp_alloc */
    FIX16Func(New),                 /* tp_new */
};


//~ The Module is done.
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

