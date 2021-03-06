NUMBER_COUNT = 10

alphabet = [
    'A',
    'Б',
    'B',
    'Г',
    'Д',
    'E',
    'Ж',
    'З',
    'И',
    'К',
]

class Data:
    def __init__(self, inputs, result=None):
        self.inputs = inputs
        self.results = [-1] * NUMBER_COUNT
        if result is not None:
            pos = alphabet.index(result)
            self.results[pos] = 1

values = {
    '11110'
    '10010'
    '11110'
    '10010'
    '10010': 'A',
    '11110'
    '10000'
    '11100'
    '10010'
    '11100': 'Б',
    '11100'
    '10100'
    '11100'
    '10010'
    '11110': 'B',
    '11100'
    '10100'
    '10000'
    '10000'
    '10000': 'Г',
    '01110'
    '01010'
    '01010'
    '11111'
    '10001': 'Д',
    '11100'
    '10000'
    '11000'
    '10000'
    '11100': 'E',
    '10101'
    '01110'
    '00100'
    '01110'
    '10101': 'Ж',
    '11100'
    '00100'
    '01000'
    '00100'
    '11100': 'З',
    '10010'
    '10010'
    '10110'
    '11010'
    '10010': 'И',
    '10010'
    '10100'
    '11000'
    '10100'
    '10010': 'К'
}

dataset = [
    Data([int(ch) for ch in string], result)
    for string, result in values.items()
]


test_values = {
    '01111'
    '01001'
    '01111'
    '01001'
    '01001': 'A',
    '01111'
    '01000'
    '01110'
    '01001'
    '01110': 'Б',
    '01110'
    '01010'
    '01110'
    '01001'
    '01111': 'B',
    '01110'
    '01010'
    '01000'
    '01000'
    '01000': 'Г',
    '01110'
    '01000'
    '01000'
    '01000'
    '01000': 'Г',
    '01110'
    '01010'
    '01010'
    '11111'
    '10001': 'Д',
    '01110'
    '01010'
    '01010'
    '11111'
    '00000': 'Д',
    '01110'
    '01000'
    '01100'
    '01000'
    '01110': 'E',
    '01110'
    '01000'
    '01110'
    '01000'
    '01110': 'E',
    '10111'
    '01110'
    '00100'
    '01110'
    '10101': 'Ж',
    '11110'
    '00110'
    '01100'
    '00110'
    '11110': 'З',
    '10001'
    '10001'
    '10101'
    '11001'
    '10001': 'И',
    '01001'
    '01010'
    '01100'
    '01010'
    '01001': 'К',
    '11111'
    '11111'
    '11111'
    '11111'
    '11111': None,
    '00000'
    '00000'
    '00000'
    '00000'
    '00000': None,
    '11111'
    '10001'
    '11111'
    '00000'
    '00000': None,
    '00100'
    '00100'
    '00100'
    '00100'
    '00100': None,
    '10001'
    '10001'
    '10001'
    '10001'
    '10001': None,
    '10001'
    '01010'
    '00100'
    '01010'
    '10001': None,
    '00100'
    '01010'
    '10001'
    '01010'
    '00100': None,
    '11111'
    '11011'
    '11111'
    '10001'
    '10001': 'A',
    '11111'
    '10001'
    '11111'
    '11011'
    '11011': 'A',
    '11111'
    '10000'
    '11111'
    '10001'
    '11111': 'Б',
    '11111'
    '11000'
    '11110'
    '11011'
    '11111': 'Б',
    '11111'
    '11011'
    '11010'
    '11110'
    '11100': 'Г',
    '11111'
    '10001'
    '10001'
    '11111'
    '10000': 'Г',
    '11111'
    '10000'
    '11000'
    '10000'
    '11111': None,
    '11111'
    '10001'
    '11111'
    '10001'
    '11111': 'E',
    '11111'
    '11000'
    '11110'
    '11111'
    '11111': 'E',
    '00100'
    '01010'
    '11111'
    '11011'
    '11011': None,
    '01011'
    '01001'
    '11000'
    '11011'
    '11000': 'И',
    '11011'
    '11110'
    '00000'
    '00010'
    '11011': 'К',
    '11111'
    '00001'
    '00111'
    '00001'
    '11111': None,
    '11100'
    '10100'
    '00001'
    '10001'
    '11111': 'B',
    '11100'
    '10100'
    '11111'
    '00001'
    '00001': 'B',
    '01110'
    '01000'
    '01111'
    '01100'
    '00001': 'E',
    '01110'
    '10001'
    '10101'
    '10000'
    '10000': 'A',
    '10001'
    '01010'
    '11111'
    '01010'
    '10001': 'Ж',
    '10000'
    '10000'
    '11111'
    '10001'
    '11111': None,
    '11111'
    '00100'
    '00100'
    '00100'
    '00100': None,
    '11111'
    '00000'
    '11111'
    '00000'
    '11111': None,
}

test_dataset = [
    Data([int(ch) for ch in string], result)
    for string, result in test_values.items()
]
