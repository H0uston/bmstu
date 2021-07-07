from function import *


def test_shift_array() -> None:
    assert check_it(shift_array([1, 2, 3, 4, 5], 3)) == [4, 5, 1, 2, 3], "First test. 5 numbers."
    assert check_it(shift_array([1, 2, 3, 4, 5, 6, 7, 8, 9], 5)) == [6, 7, 8, 9, 1, 2, 3, 4, 5], "Second test. 9 numbers."
    assert check_it(shift_array([4, 6, 13, 11], 4)) == [4, 6, 13, 11], \
        "Third test. All numbers at the same place."
    assert check_it(shift_array([-12, -6, -3, 0, 1, 2, 3], 3)) == [0, 1, 2, 3, -12, -6, -3], \
        "Fourth test. Random numbers."
    assert check_it(shift_array([1], 3)) == [1], "Fifth test. Only one number."
    assert check_it(shift_array([1, 2, 3, 4, 5, 6, 7, 8, 9], 16)) == [8, 9, 1, 2, 3, 4, 5, 6, 7], \
        "Sixth test. k is more than count of numbers in array"
    assert check_it(shift_array([1, -2, 3, 4, 5], 0)) == [1, -2, 3, 4, 5], \
        "Seventh test. k == 0."
    print("SHIFT_ARRAY: OK")


def test_filter() -> None:
    assert check_it(filter_square([1, 2, 3, 4, 5])) == [1, 4], "First test. 5 numbers."
    assert check_it(filter_square([0, 12, 11, 6, -18, -9])) == [0], "Second test. Random numbers."
    assert check_it(filter_square([1, 4, 9, 16])) == [1, 4, 9, 16], "All numbers at the same place."
    assert check_it(filter_square([11, -9, 6, -28, 13])) == [], "No square numbers"
    print("FILTER: OK")


def check_it(array: list) -> list:
    if not isinstance(array, (list, tuple)):
        raise TypeError("The result should be a list or tuple.")
    return list(array)


if __name__ == "__main__":
    test_shift_array()
    test_filter()

