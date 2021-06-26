import random
import sys

MAX_NUMBER = 256
COUNT_OF_ROTORS = 3


def create_rotor(seed=3):
    rotor = [i for i in range(MAX_NUMBER)]

    random.Random(seed).shuffle(rotor)

    return rotor


def create_reflector():
    reflector = [i for i in range(MAX_NUMBER)]
    reflector.reverse()

    return reflector


def convert_bfile_to_list(file_name):
    file = open(file_name, 'rb')

    encoded_string = file.read()
    byte_list = []
    for sym in encoded_string:
        byte_list.append(ord(chr(sym)))
    file.close()

    return byte_list


def convert_list_to_bfile(byte_list, res_file_name):
    res_file = open(res_file_name, 'wb')

    res_file.write(bytearray(byte_list))

    res_file.close()


def turn_rotor(byte_list):
    byte_list.insert(0, byte_list.pop())
    return byte_list


def backwards(x, rotors):
    for i in range(COUNT_OF_ROTORS - 1, -1, -1):
        x = rotors[i].index(x)

    return x


def straight(x, rotors):
    for i in range(COUNT_OF_ROTORS):
        x = rotors[i][x]

    return x


def main(argv):
    if len(argv) == 1:
        file_name = "file.txt"
        res_file_name = "result.txt"
    elif len(argv) == 2:
        file_name = argv[1]
        res_file_name = "result.txt"
    else:
        file_name = argv[1]
        res_file_name = argv[2]

    # Создать роторы
    rotors = []
    for i in range(COUNT_OF_ROTORS):
        rotors.append(create_rotor(i))

    # Создать рефлектор
    reflector = create_reflector()

    # Чтение файла
    byte_list = convert_bfile_to_list(file_name)

    res = []
    # Счёт поворотов
    turns = 0
    # Процесс
    for byte in byte_list:
        turns += 1
        turn_rotor(rotors[0])
        if turns % MAX_NUMBER == 0:
            turn_rotor(rotors[1])
            if turns % (MAX_NUMBER * MAX_NUMBER) == 0:
                turn_rotor(rotors[2])
        straight_coded = straight(byte, rotors)
        coded = backwards(reflector[straight_coded], rotors)
        res.append(coded)
    # Сохранить
    convert_list_to_bfile(res, res_file_name)


if __name__ == "__main__":
    main(sys.argv)
