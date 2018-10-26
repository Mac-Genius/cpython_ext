#include <Python.h>
#include <structmember.h>

typedef struct {
    PyObject_HEAD
    int field1;
} CPython;

static void
CPython_dealloc(CPython *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *
CPython_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    CPython *self;
    self = (CPython *) type->tp_alloc(type, 0);
    self->field1 = -1;
    return (PyObject *) self;
}

static int
CPython_init(CPython *self, PyObject *args, PyObject *kwds)
{
    return 0;
}

static PyObject *
CPython_enter(CPython *self) {
    return (PyObject *)self;
}

static PyObject *
CPython_exit(CPython *self, PyObject *args) {
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMemberDef CPython_members[] = {
    {"field1", T_INT, offsetof(CPython, field1), 0, "Field 1"},
    {NULL}  /* Sentinel */
};

static PyMethodDef CPython_methods[] = {
    {"__enter__", (PyCFunction)CPython_enter, METH_NOARGS, "Enter"},
    {"__exit__", (PyCFunction)CPython_exit, METH_VARARGS, "Exit"},
    {NULL}  /* Sentinel */
};

static PyTypeObject CPythonType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "cpython.CPython",
    .tp_doc = "CPython objects",
    .tp_basicsize = sizeof(CPython),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = CPython_new,
    .tp_init = (initproc) CPython_init,
    .tp_dealloc = (destructor) CPython_dealloc,
    .tp_members = CPython_members,
    .tp_methods = CPython_methods,
};

static PyModuleDef cpython_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_cpython",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit__cpython(void)
{
    PyObject *m;
    if (PyType_Ready(&CPythonType) < 0)
        return NULL;

    m = PyModule_Create(&cpython_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&CPythonType);
    PyModule_AddObject(m, "CPython", (PyObject *) &CPythonType);
    return m;
}
