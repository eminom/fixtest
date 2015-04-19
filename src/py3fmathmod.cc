

//~ What the hell is this
//#include "structmember.h"
#include "python.h"
#include "py3fmathmod.h"
#include "cross.h"

#define FIX16ModFunc(a) _FIX16ModFunc__##a

//~
extern PyTypeObject Py3_Fixed16Type;

static PyObject *FIX16ModFunc(CompilingDate)(PyObject *self)
{

    char buf[1024] = {0};
    if( sprintf_s(buf,sizeof(buf),"Compiled on %s:%s",__TIME__,__DATE__) < 0 )
    {
        Py_INCREF(Py_None);
        return Py_None;
    }
    return PyUnicode_FromString(buf);
}

static PyMethodDef Fixed16ModMethods[] = 
{
    {"CompileDate",(PyCFunction)FIX16ModFunc(CompilingDate), METH_NOARGS,"Version of compiling datetime."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef fixv1mod = {
    PyModuleDef_HEAD_INIT,
    "fixv1mod",
    NULL,
    -1,
    Fixed16ModMethods
};

//The name shall comply with the setup module
//And this method is exported.
PyMODINIT_FUNC PyInit_FixTest(void)
{
    if( PyType_Ready(&Py3_Fixed16Type) < 0 )
    {
        PyErr_SetString(PyExc_RuntimeError,"Fixed16 not ready !");
        return NULL;
    }

    if (PyObject *m = PyModule_Create(&fixv1mod))
    {
        // Create a new type exception
        // RapperExc = PyErr_NewException("Rapv1.Excetpion",NULL,NULL);
        // Py_INCREF(RapperExc);
        // PyModule_AddObject(m,"RapError",RapperExc);  
            /*Appear as the module global name, checked by dir(r1lan)*/
        Py_INCREF(&Py3_Fixed16Type);
        PyModule_AddObject(m,"Fixed16",(PyObject*)&Py3_Fixed16Type);
        return m;
    }
    PyErr_SetString(PyExc_RuntimeError,"Init for FixTest failed. God");
    return NULL;
}


