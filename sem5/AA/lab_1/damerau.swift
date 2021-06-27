import Foundation

func damerau_matrix_distance(str_1: String, str_2: String, values: Bool = false) -> Int {
    let len_1 = str_1.count + 1
    let len_2 = str_2.count + 1

    var matrix = [[Int]]()
    for i in 0..<len_1 {
        matrix.append(Array(repeating: 0, count: len_2))
    }

    for x in 0..<len_1 {
        matrix[x][0] = x
    }
    for x in 0..<len_2 {
        matrix[0][x] = x
    }

    var d: Int;
    for i in 1..<len_1 {
        for j in 1..<len_2 {
            d = 1
            if (str_1[str_1.index(str_1.startIndex, offsetBy: i - 1)] == str_2[str_2.index(str_2.startIndex, offsetBy: j - 1)]) {
                d = 0
            }

            matrix[i][j] = min(matrix[i][j - 1] + 1,
                               matrix[i - 1][j] + 1,
                               matrix[i - 1][j - 1] + d)
            if (i > 1 && j > 1 &&
                str_1[str_1.index(str_1.startIndex, offsetBy: i - 1)] == str_2[str_2.index(str_2.startIndex, offsetBy: j - 2)] &&
                str_1[str_1.index(str_1.startIndex, offsetBy: i - 2)] == str_2[str_2.index(str_2.startIndex, offsetBy: j - 1)]) {
                matrix[i][j] = min(matrix[i][j], matrix[i - 2][j - 2] + 1)
            }
        }
    }

    if (values) {
        print("Матрица \"метода Дамерау\": ")
        print_matrix(matrix: matrix)
    }

    return matrix[len_1 - 1][len_2 - 1]
}