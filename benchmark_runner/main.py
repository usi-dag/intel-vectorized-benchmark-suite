import math

import matplotlib.pyplot as plt
import numpy as np
import json

plt_colors = plt.rcParams['axes.prop_cycle'].by_key()['color']
bar_colors = [plt_colors[3], plt_colors[0], plt_colors[2]]
benchmarks = ['axpy', 'blackscholes', 'canneal', 'jacobi-2d', 'lavaMD', 'particlefilter', 'pathfinder', 'somier', 'streamcluster',
              # 'swaptions'
              ]
machines = {
    'p620': [{'size': 128, 'avx': 'AVX'}],
    'mini': [{'size': 128, 'avx': 'AVX2'}, {'size': 256, 'avx': 'AVX2'}],
    'tower': [{'size': 128, 'avx': 'AVX512'}, {'size': 256, 'avx': 'AVX512'}, {'size': 512, 'avx': 'AVX512'}]
}
benchmark_types = [
    'serial', 'autovec', 'explicitvec', 'fullvec'
]


def plot(autovec_speedup, explicit_speedup, fullvec_speedup, machine_name, configuration):
    labels = benchmarks
    # autovec_speedup = [20, 34, 30, 35, 27, 20, 34, 30, 35, 27]
    # explicit_speedup = [25, 32, 34, 20, 25, 25, 32, 34, 20, 25]
    # fullvec_speedup = [4, 32, 32, 10, 25, 4, 32, 32, 10, 25]

    x = np.arange(len(labels))  # the label locations
    width = 0.25  # the width of the bars

    fig, ax = plt.subplots()
    rects1 = ax.bar(x - width, autovec_speedup, width, label='autoVec', color=bar_colors[0])
    rects2 = ax.bar(x, explicit_speedup, width, label='explicitVec', color=bar_colors[1])
    rects3 = ax.bar(x + width, fullvec_speedup, width, label='fullVec', color=bar_colors[2])

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel('Execution-time speedup factor')

    ax.set_title(f'{machine_name} - {configuration["avx"]} - size: {configuration["size"]}')
    ax.set_xticks(x, labels)
    ax.legend()

    plt.axhline(y=1, color='grey', alpha=0.5, zorder=0, linestyle='-')

    ax.bar_label(rects1, padding=3, rotation=90)
    ax.bar_label(rects2, padding=3, rotation=90)
    ax.bar_label(rects3, padding=3, rotation=90)

    ax.spines['right'].set_visible(False)
    ax.spines['top'].set_visible(False)

    plt.xticks(rotation=35, ha='right')

    fig.tight_layout()

    # plt.ylim((0, math.ceil(18)))

    plt.show()


def load(dir):
    res = []
    for type in benchmark_types:
        with open(f'../{dir}/{type}.json') as f:
            print(f'../{dir}/{type}.json')
            data = json.load(f)
            res.append(data['benchmarks'][0]['cpu_time'])

    return res


def main():
    # TODO read json data
    serial = []
    autovec = []
    explicitvec = []
    fullvec = []

    for machine, configurations in machines.items():
        for configuration in configurations:
            for benchmark in benchmarks:
                path = f'_{benchmark}/out/{machine}/VECTOR_SIZE_{configuration["size"]}'
                s, a, e, f = load(path)
                serial.append(s)
                autovec.append(a)
                explicitvec.append(e)
                fullvec.append(f)

            autovec = np.divide(serial, autovec)
            explicitvec = np.divide(serial, explicitvec)
            fullvec = np.divide(serial, fullvec)

            plot(autovec, explicitvec, fullvec, machine, configuration)

            serial = []
            autovec = []
            explicitvec = []
            fullvec = []

    return 1


if __name__ == '__main__':
    main()


