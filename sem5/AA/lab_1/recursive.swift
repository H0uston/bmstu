import Foundation

func recursive_distance(str_1: String, str_2: String) -> Int {
    let len_1 = str_1.count
    let len_2 = str_2.count

    if (len_1 == 1 && len_2 == 1) {
        if (str_1 == str_2) {
            return 0
        } else {
            return 1
        }
    } else if (len_1 == 0 || len_2 == 0) {
        return max(len_1, len_2)
    }

    var d = 1
    if (String(str_1.suffix(1)) == String(str_2.suffix(1))) {
        d = 0
    }

    if (len_1 > 1 && len_2 > 1) {
        if (str_1[str_1.index(str_1.endIndex, offsetBy: -1)] == str_2[str_2.index(str_2.endIndex, offsetBy: -2)] &&
            str_1[str_1.index(str_1.endIndex, offsetBy: -2)] == str_2[str_2.index(str_2.endIndex, offsetBy: -1)]) {
            return min(recursive_distance(str_1: str_1, str_2: String(str_2.prefix(len_2 - 1))) + 1,
                    recursive_distance(str_1: String(str_1.prefix(len_1 - 1)), str_2: str_2) + 1,
                    recursive_distance(str_1: String(str_1.prefix(len_1 - 1)), str_2: String(str_2.prefix(len_2 - 1))) + d,
                    recursive_distance(str_1: String(str_1.prefix(len_1 - 2)), str_2: String(str_2.prefix(len_2 - 2))) + 1)
        }
    }

    return min(recursive_distance(str_1: str_1, str_2: String(str_2.prefix(len_2 - 1))) + 1,
            recursive_distance(str_1: String(str_1.prefix(len_1 - 1)), str_2: str_2) + 1,
            recursive_distance(str_1: String(str_1.prefix(len_1 - 1)), str_2: String(str_2.prefix(len_2 - 1))) + d)
}
