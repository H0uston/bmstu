from perceptron.perceptron import Perceptron
from perceptron.layers import *
from training_dataset import dataset, test_dataset, NUMBER_COUNT
import random

def train_perceptron():
    network = Perceptron()
    input_count = len(dataset[0].inputs)
    print('----------------------------')
    print('Генерация слоёв')
    for _ in range(input_count):
        network.s_layer.add_neuron(None, lambda value: value)
    print('Сгенерировано на S-слое: ', input_count)

    a_neurons_count = 10 * input_count ** 2
    for position in range(a_neurons_count):
        # функция активации
        neuron = ANeuron(None, lambda value: int(value >= 0))
        # инициализация весов нейронов А слоя
        neuron.input_weights = [
            random.choice([-1, 0, 1]) for i in range(input_count)
        ]
        neuron.calculate_bias()
        network.a_layer.neurons.append(neuron)
    print('Сгенерировано на A-слое: ', a_neurons_count)

    for _ in range(NUMBER_COUNT):
        network.r_layer.add_neuron(a_neurons_count, lambda: 0, lambda value: 1 if value >=0 else -1, 0.01, 0)
    print('Сгенерировано на R-слое: ', NUMBER_COUNT)

    network.train(dataset)
    network.optimize(dataset)
    return network


def test_network(network):
    total_classifications = len(test_dataset) * len(test_dataset[0].results)
    misc = 0
    for data in test_dataset:
        results = network.solve(data.inputs)
        for result, expected_result in zip(results, data.results):
            if result != expected_result:
                misc += 2

    print(
        'Итоговая точность на {:d} тестах: {:.2f}%'.format(
            len(test_dataset),
            float(total_classifications - misc) / total_classifications * 100
        )
    )


def main():
    network = train_perceptron()
    test_network(network)


if __name__ == '__main__':
    main()