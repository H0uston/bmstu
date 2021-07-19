import ctypes

try:
    lib = ctypes.CDLL('libfunc.so')
except:
    print("Can't find library!")
    exit(-1)

_shift_array = lib.shift_array
_shift_array.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
_shift_array.restype = ctypes.c_int


def shift_array(nums: list or tuple, k: int) -> list or tuple:
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)

    rc = _shift_array(src, src_len, k)

    if (rc == 0):
        return list(src)
    else:
        print("Something went wrong!")
        exit(-1)


def main() -> None:
    try:
        print("Enter elements through space: ")
        array = list(map(int, input().split(" ")))
        k = int(input("Enter k: "))
        if (k < 0):
            print("k must be more than 0!")
            exit(-1)
        new_array = shift_array(array, k)
        print("Result: ")
        for i in range(len(new_array)):
            print(new_array[i], end=' ')
    except:
        print("Wrong enter!")
        exit(-1)


if __name__ == "__main__":
    main()

