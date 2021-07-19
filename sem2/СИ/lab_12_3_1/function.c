#include <stdlib.h>
#include <stdbool.h>
#include <Python.h>

// Функции Си
/**
 * Производит сдвиг элементов массива
 * @param array[in/out] - массив
 * @param n[in] - размер массива
 * @param k[in] - на какое количество элементов нужно сдвинуть
 * @return 0, если все параметры верны, -1, если есть ошибка
 */
int shift_array(int *array, int n, int k)
{
    if (array == NULL || k < 0 || n <= 0)
        return (-1);
    int tmp;
    if (k > n)
        k %= n;

    // Переворачивает все элементы до k
    for (int i = 0; i < k / 2; i++)
    {
        tmp = array[i];
        array[i] = array[k - i - 1];
        array[k - i - 1] = tmp;
    }

    // Переворачивает все элементы после k
    for (int i = k; i < (k + (n - k) / 2); i++)
    {
        tmp = array[i];
        array[i] = array[n - (i - k) - 1];
        array[n - (i - k) - 1] = tmp;
    }

    // Переворачивает весь массив
    for (int i = 0; i < n / 2; i++)
    {
        tmp = array[i];
        array[i] = array[n - i - 1];
        array[n - i - 1] = tmp;
    }

    return 0;
}

/**
 * Проверяет является ли число полным квадратом
 * @param n[in] - число
 * @return true - да, false - нет
 */
bool is_square(int n)
{
    int i = 1;
    while (n > 0)
    {
        n -= i;
        i += 2;
    }
    return n == 0;
}

/**
 * Считает количество полных квадратов в массиве
 * @param array[in] - массив
 * @param n[in] - размер массива
 * @return число полных квадратов
 */
int count_square(const int *array, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        if (is_square(array[i]))
            count++;
    return count;
}

/**
 * Заносит из array в array_filtered все полные квадраты
 * @param array[in] - массив
 * @param array_filtered[in/out] - массив с полными квадратами
 * @param n[in] - размер массива array
 * @return возвращает количество полных квадратов в array или -1, если переданные параметры неверны
 */
int filter_square(const int *array, int *array_filtered, int n, int *size_filtered)
{
    if (array == NULL || n <= 0 || size_filtered == NULL)
        return -2;

    int count = count_square(array, n);
    *size_filtered = count;

    if (count > *size_filtered || *size_filtered < 0 || array_filtered == NULL)
        return -1;

    int j = 0;
    for (int i = 0; i < n && j < *size_filtered; i++)
        if (is_square(array[i]))
        {
            array_filtered[j] = array[i];
            j++;
        }

    return 0;
}

// Функции для модуля расширения
/**
 * Заносит элементы из массива СИ в список Python
 * @param arr[in] - массив
 * @param n[in] - размер массива
 * @return список из Python
 */
static PyObject* copy_to_py_list(const int *arr, int n)
{
    PyObject *plist, *pitem;

    plist = PyList_New(n);
    if (!plist)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        pitem = PyLong_FromLong(arr[i]);
        if (!pitem)
        {
            Py_DECREF(plist);
            return NULL;
        }

        PyList_SET_ITEM(plist, i, pitem);
    }

    return plist;
}

// Производит сдвиг списка
static PyObject* py_shift_array(PyObject *self, PyObject *args)
{
	PyObject *list, *item, *item_int, *plist;
	int *array;
	int size, k;

	if (!PyArg_ParseTuple(args, "Oi", &list, &k))
		return NULL;

	list = PySequence_Fast(list, "Argument must be iterable");
	if (!list)
		return NULL;

	size = PyList_Size(list);
	if (size <= 0)
		return NULL;

	array = malloc(size * sizeof(int));
	if (!array)
	{
		Py_DECREF(list);

		return NULL;
	}

	for (int i = 0; i < size; i++)
	{
		item = PySequence_Fast_GET_ITEM(list, i);
		if (!item)
		{
			Py_DECREF(list);
			free(array);
			
			return NULL;
		}

		item_int = PyNumber_Long(item);
		if (!item_int)
		{
			Py_DECREF(list);
			free(array);

			return NULL;
		}

		array[i] = PyLong_AS_LONG(item_int);

		Py_DECREF(item_int);
	}

	shift_array(array, size, k);

	plist = copy_to_py_list(array, size);

	free(array);
	Py_DECREF(list);

	return plist;
}

// Производит фильтрацию списка
PyObject *py_filter_square(PyObject *self, PyObject *args)
{
	PyObject *list, *item, *item_int, *plist;
	int *array = NULL, *array_filtered = NULL;
	int size, size_filtered;
	int status;

	if (!PyArg_ParseTuple(args, "O", &list))
		return NULL;

	list = PySequence_Fast(list, "Argument must be iterable");
	if (!list)
		return NULL;

	size = PyList_Size(list);
	if (size <= 0)
		return NULL;

	array = malloc(size * sizeof(int));
	if (!array)
	{
		Py_DECREF(list);

		return NULL;
	}

	for (int i = 0; i < size; i++)
	{
		item = PySequence_Fast_GET_ITEM(list, i);
		if (!item)
		{
			Py_DECREF(list);
			free(array);
			
			return NULL;
		}

		item_int = PyNumber_Long(item);
		if (!item_int)
		{
			Py_DECREF(list);
			free(array);

			return NULL;
		}

		array[i] = PyLong_AS_LONG(item_int);

		Py_DECREF(item_int);
	}

	status = filter_square(array, array_filtered, size, &size_filtered);

	if (status == -1 && size_filtered > 0)
	{
		array_filtered = malloc(size_filtered * sizeof(int));

		if (!array_filtered)
        {
            free(array);
            Py_DECREF(list);
            return NULL;
        }

		filter_square(array, array_filtered, size, &size_filtered);
        plist = copy_to_py_list(array_filtered, size_filtered);
	}
    else
    {
        plist = Py_BuildValue("[]");
    }

	free(array);
	free(array_filtered);
	Py_DECREF(list);

	return plist;
}

// Функции доступные в моделе расширения
static PyMethodDef function_methods[] = { 
	{"filter_square", py_filter_square, METH_VARARGS, "filter_square(iterable)->list"},
    {"shift_array", py_shift_array, METH_VARARGS, "shift_array(iterable, int)->list"},
    {NULL, NULL, 0, NULL}
};

// Описание модуля
static struct PyModuleDef function_definition = { 
    PyModuleDef_HEAD_INIT,
    "function",
    "A Python module",
    -1, 
    function_methods
};

// Создание модуля
PyMODINIT_FUNC PyInit_function(void) {
    Py_Initialize();
    return PyModule_Create(&function_definition);
}