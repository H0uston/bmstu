import Foundation

func test_funcs(str_1: String, str_2: String, res: Int) -> Int {
    if (res == recursive_distance(str_1: str_1, str_2: str_2) &&
        res == matrix_distance(str_1: str_1, str_2: str_2) &&
        res == damerau_matrix_distance(str_1: str_1, str_2: str_2)) {
        return 0
    } else {
        // print(recursive_distance(str_1: str_1, str_2: str_2))
        // print(matrix_distance(str_1: str_1, str_2: str_2))
        // print(damerau_matrix_distance(str_1: str_1, str_2: str_2))
        return 1
    }
}

func unit_test() -> Void {
    var err = 0

    // Пустые строки
    err += test_funcs(str_1: "", str_2: "", res: 0)

    if (err != 0) {
        print("FAIL 1!")
    }

    // Одинаковые строки
    err += test_funcs(str_1: "a", str_2: "a", res: 0)
    err += test_funcs(str_1: "bb", str_2: "bb", res: 0)
    err += test_funcs(str_1: "ccc", str_2: "ccc", res: 0)
    err += test_funcs(str_1: "dddd", str_2: "dddd", res: 0)
    err += test_funcs(str_1: "Rising", str_2: "Rising", res: 0)
    if (err != 0) {
        print("FAIL 2!")
    }

    // Разные
    err += test_funcs(str_1: "a", str_2: "", res: 1)
    err += test_funcs(str_1: "", str_2: "a", res: 1)
    err += test_funcs(str_1: "a", str_2: "b", res: 1)
    err += test_funcs(str_1: "ab", str_2: "yw", res: 2)
    err += test_funcs(str_1: "ab", str_2: "", res: 2)
    err += test_funcs(str_1: "", str_2: "ht", res: 2)
    err += test_funcs(str_1: "i", str_2: "bc", res: 2)
    err += test_funcs(str_1: "au", str_2: "b", res: 2)
    err += test_funcs(str_1: "", str_2: "aye", res: 3)
    err += test_funcs(str_1: "yew", str_2: "", res: 3)
    err += test_funcs(str_1: "aqw", str_2: "hft", res: 3)
    err += test_funcs(str_1: "aeygdf", str_2: "j", res: 6)
    err += test_funcs(str_1: "atw", str_2: "pokjpk", res: 6)

    if (err != 0) {
        print("FAIL 3!")
    }

    // Тесты с семинара
    err += test_funcs(str_1: "скат", str_2: "кот", res: 2)
    err += test_funcs(str_1: "увлечение", str_2: "развлечения", res: 4)

    if (err != 0) {
        print("FAIL 4!")
    }

    // Смещанные строки
    err += test_funcs(str_1: "gd", str_2: "gy", res: 1)
    err += test_funcs(str_1: "yh", str_2: "eh", res: 1)
    err += test_funcs(str_1: "abc", str_2: "abd", res: 1)
    err += test_funcs(str_1: "abc", str_2: "dbc", res: 1)
    err += test_funcs(str_1: "abc", str_2: "aoj", res: 2)
    err += test_funcs(str_1: "bear", str_2: "beer", res: 1)
    err += test_funcs(str_1: "Kaufmann", str_2: "Kauffrau", res: 4)
    err += test_funcs(str_1: "September", str_2: "December", res: 3)

    if (err != 0) {
        print("FAIL 5!")
    }

    // Тесты на алгоритм Дамерау-Левенштейна
    if (!(damerau_matrix_distance(str_1: "университет", str_2: "универистет") == 1)) {
        err += 1
    }
    if (!(damerau_matrix_distance(str_1: "ab", str_2: "ba") == 1)) {
        err += 1
    }
    if (!(damerau_matrix_distance(str_1: "скат", str_2: "ксат") == 1)) {
        err += 1
    }
    if (!(damerau_matrix_distance(str_1: "скат", str_2: "кста") == 2)) {
        err += 1
    }
    if (!(damerau_matrix_distance(str_1: "привет", str_2: "привте") == 1)) {
        err += 1
    }

    if (err != 0) {
        print("FAIL 6!")
    }

    if (err == 0) {
        print("Everything is OK!")
    }
}