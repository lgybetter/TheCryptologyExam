#include <Python.h>
PyObject* wrap_makeFIPS(PyObject* self, PyObject* args) {
  	char *inputFile;
  	char *outputFile;
  	int result,kL,type;
  	if (! PyArg_ParseTuple(args, "ssii:makeFIPS", &inputFile,&outputFile,&kL,&type))
    		return NULL;
  	result = makeFIPS(inputFile,outputFile,kL,type);
	return Py_BuildValue("i", result);
}

static PyMethodDef exampleMethods[] = {
	{"makeFIPS", wrap_makeFIPS, METH_VARARGS, "FIPS"},
	{NULL, NULL}
};

void initexample() {
	  PyObject* m;
 	 m = Py_InitModule("example", exampleMethods);
}
