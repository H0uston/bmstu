from numpy.random import rayleigh, uniform, exponential, normal
from matplotlib import pyplot
import math
from numpy import arange


class Generator:
    def __init__(self, low, high):
        self.low = low
        self.high = high
    
    def generate_time(self):
        res = -1
        while (res < 0):
            res = normal(self.low, self.high)

        return res

class Processor:
    def __init__(self, intensity):
        self.intensity = intensity
    
    def generate_time(self):
        return exponential(self.intensity)


class Model:
    def __init__(self, generators, processor, requests_n):
        self.generators = generators
        self.processor = processor
        self.requests_n = requests_n
    
    def start(self):
        processed_n = 0
        self.queue = []
        self.events = []
        self.totally_waited = 0
        
        for generator in self.generators:
            self.events.append([generator.generate_time(), 'g', 0])

        self.is_free = True
        while processed_n < self.requests_n:
            event = self.events.pop(0)
            if event[1] == 'g':
                self._generate(event)
            elif event[1] == 'p':
                processed_n += 1
                self._process(event[0])

        return self.totally_waited

    def _add_event(self, event: list):
        i = 0
        while i < len(self.events) and self.events[i][0] < event[0]:  # выбирается время куда вставить
            i += 1
        self.events.insert(i, event)

    def _generate(self, event):
        self.queue.append(event[0])
        self._add_event([event[0] + self.generators[event[2]].generate_time(), 'g', event[2]])
        if self.is_free:
            self._process(event[0])

    def _process(self, time):
        if len(self.queue) > 0:
            processing_time = self.processor.generate_time()
            self.totally_waited += processing_time + time - self.queue.pop(0)  # время когда заявка обработается
            self._add_event([time + processing_time, 'p'])
            self.is_free = False
        else:
            self.is_free = True

def view(requests_n, proc_intensity, generator_dispersion):
    max_intensity = 1
    sigma = math.sqrt(1 / proc_intensity)
    proc = Processor(sigma)
    Xdata = list()
    Ydata = list()

    for intensity in arange(0.1 * max_intensity, max_intensity, max_intensity / 100):
        average_time = 0
        for i in range(200):
            m = 1 / intensity
            d = 1 / generator_dispersion
            b = (math.sqrt(12 * d) + 2 * m) / 2
            a = 2 * m - b
            gen = Generator(a, b)
            model = Model([gen], proc, requests_n)
            average_time += model.start()
        average_time /= 200
        Xdata.append(intensity / proc_intensity)
        Ydata.append(average_time / requests_n)

    pyplot.grid(True)
    pyplot.plot(Xdata, Ydata)
    pyplot.xlabel("Ro")
    pyplot.ylabel("Average time")
    pyplot.show()


def main():
    requests_n = int(input("Enter the number of request: "))
    assert(requests_n > 0)

    processor_intensity = float(input("Enter processors intensity: "))

    generators_n = int(input("Enter the number of generators: "))

    generators = []
    generators_summ_intensity = 0
    generator_dispersion = float(input("Enter generators dispersion: "))
    for i in range(generators_n):
        generator_intensity = float(input("Enter #{0} generators intensity: ".format(i)))
        m = 1 / generator_intensity
        d = 1 / generator_dispersion
        b = (math.sqrt(12 * d) + 2 * m) / 2
        a = 2 * m - b
        generators.append(Generator(a, b))
        generators_summ_intensity += generator_intensity

    sigma = math.sqrt(1 / processor_intensity)
    processor = Processor(sigma)

    model = Model(generators, processor, requests_n)

    time = model.start()
    print("Ro =", generators_summ_intensity / processor_intensity, "\nAll time:", time, "\nAverage processing time: ",
     time / requests_n)

    view(requests_n, processor_intensity, generator_dispersion)

if __name__ == "__main__":
    main()