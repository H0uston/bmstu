import ctypes

try:
    lib = ctypes.CDLL('libfunc.so')
except:
    print("Can't find library!")
    exit(-1)
_filter = lib.filter_square
_filter.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int))
_filter.restype = ctypes.c_int


def filter(nums: list or tuple) -> list:
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)
    dst = None
    size_filtered = ctypes.c_int()
    size_filtered.value = 0
    rc = _filter(src, dst, src_len, size_filtered)

    if (rc == -1 and size_filtered.value > 0):
        dst = (ctypes.c_int * size_filtered.value)()
        _filter(src, dst, src_len, size_filtered)
        return list(dst)
    elif (size_filtered.value == 0):
        return list()
    else:
        return list()


def main():
    #try:
    print("Enter elements through space: ")
    try:
        array = list(map(int, input().split(" ")))
    except:
        array = []
    new_array = filter(array)
    print("Result: ")
    if (len(new_array) == 0):
        print("Empty")
    else:
        for i in range(len(new_array)):
            print(new_array[i], end=' ')
    #except:


if __name__ == "__main__":
    main()

