
%module ms3d
%{
        #include "ms3d.h"
%}

%typemap(out) float* getJointPosition{
        int i;
        //$1, $1_dim0, $1_dim1
        $result = PyList_New(3);
        for (i=0; i<3; i++){
                PyObject* o = PyFloat_FromDouble((double) $1[i]);
                PyList_SetItem($result, i, o);
        }
} 

%include "ms3d.h"
