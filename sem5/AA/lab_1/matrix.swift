import Foundation

func matrix_distance(str_1: String, str_2: String, values: Bool = false) -> Int {
    let len_1 = str_1.count
    let len_2 = str_2.count

    var matrix = [[Int]]()
    var row_1 = [Int]()
    var row_2 = [Int]()
    for x in 0..<len_2 + 1 {
        row_1.append(x)
    }
    var d : Int
    for i in 1..<len_1 + 1 {
        row_2 = [i]
        for j in 1..<len_2 + 1 {
            d = 1
            if (str_1[str_1.index(str_1.startIndex, offsetBy: i - 1)] == str_2[str_2.index(str_2.startIndex, offsetBy: j - 1)]) {
                d = 0
            }

            row_2.append(
                    min(row_1[j] + 1,
                            row_2[j - 1] + 1,
                            row_1[j - 1] + d)
            )
        }
        matrix.append(row_1)
        row_1 = row_2
    }
    matrix.append(row_1)
    if (values) {
        print("Матрица \"Матричного метода\": ")
        print_matrix(matrix: matrix)
    }

    return row_1[row_1.count - 1]
}