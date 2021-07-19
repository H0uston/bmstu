import function

def main():
    print("Input numbers for array: ")
    array = list(map(int, input().split(" ")))
    if (array == []):
        return -1
    
    k = int(input("Input number for shift: "))
    print("Shift array: ")
    array = function.shift_array(array, k)
    for i in range(len(array)):
        print(array[i], end=" ")
    print()
    
    print("Filter square numbers: ")
    array = function.filter_square(array)
    print(array)

if __name__ == "__main__":
    main()
