import Foundation

func print_matrix(matrix: [[Int]]) {
    for i in 0..<matrix.count {
        for j in 0..<matrix[i].count {
            print(NSString(format: "%3i", matrix[i][j]), terminator: " ")
        }
        print()
    }
    print()
}

func main() -> Void {
    while (true) {
        print("Выберите действие: ")
        print("1 - Ввод двух строк;")
        print("2 - Тесты;")
        print("0 - Выход;")
        let ans = String(readLine()!)
        if (ans == "1") {
            print("Введите первую строку: ")
            let str_1 = String(readLine()!)
            print("Введите вторую строку: ")
            let str_2 = String(readLine()!)

            var begin = clock()
            var d = recursive_distance(str_1: str_1, str_2: str_2)
            var diff = Double(clock() - begin) / Double(CLOCKS_PER_SEC)
            print("Дистанция для рекурсивного метода: ", d)
            print("Время вычисления рекурсивным методом: ", diff)

            begin = clock()
            d = matrix_distance(str_1: str_1, str_2: str_2, values: true)
            diff = Double(clock() - begin) / Double(CLOCKS_PER_SEC)
            print("Дистанция для матричного метода: ", d)
            print("Время вычисления матричным методом: ", diff)

            begin = clock()
            d = damerau_matrix_distance(str_1: str_1, str_2: str_2, values: true)
            diff = Double(clock() - begin) / Double(CLOCKS_PER_SEC)
            print("Дистанция для метода Дамерау: ", d)
            print("Время вычисления методом Дамерау: ", diff)

        } else if (ans == "2") {
            unit_test()
        } else if (ans == "0") {
            return;
        } else {
            print("Повторите ввод!")
            print()
        }
    }
}

main()
