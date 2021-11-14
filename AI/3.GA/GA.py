# -!- coding: utf-8 -!-

from matplotlib import pyplot as plt
import numpy as np
import pandas as pd


class GA():

    def __init__(self, nums, bound, func, DNA_SIZE=None, cross_rate=0.8, mutation=0.00001):
        nums = np.array(nums)
        bound = np.array(bound)
        self.bound = bound

        min_nums, max_nums = np.array(list(zip(*bound)))
        self.var_len = var_len = max_nums - min_nums
        bits = np.ceil(np.log2(var_len + 1))

        if DNA_SIZE is None:
            DNA_SIZE = int(np.max(bits))
        self.DNA_SIZE = DNA_SIZE

        # POP_SIZE为进化的种群数
        self.POP_SIZE = len(nums)
        POP = np.zeros((*nums.shape, DNA_SIZE))
        for i in range(nums.shape[0]):
            for j in range(nums.shape[1]):
                # 编码方式：
                num = int(round((nums[i, j] - bound[j][0]) * ((2 ** DNA_SIZE) / var_len[j])))
                # 用python自带的格式化转化为前面空0的二进制字符串，然后拆分成列表
                POP[i, j] = [int(k) for k in ('{0:0' + str(DNA_SIZE) + 'b}').format(num)]
        self.POP = POP
        # 用于后面重置（reset）
        self.copy_POP = POP.copy()
        self.cross_rate = cross_rate
        self.mutation = mutation
        self.func = func
        # 用于打印适应度值
        self.mean_fitness = []
        self.max_fitness = []

    def translateDNA(self):
        W_vector = np.array([2 ** i for i in range(self.DNA_SIZE)]).reshape((self.DNA_SIZE, 1))[::-1]
        binary_vector = self.POP.dot(W_vector).reshape(self.POP.shape[0:2])
        for i in range(binary_vector.shape[0]):
            for j in range(binary_vector.shape[1]):
                binary_vector[i, j] /= ((2 ** self.DNA_SIZE) / self.var_len[j])
                binary_vector[i, j] += self.bound[j][0]
        return binary_vector

    # 获取适应度值
    def get_fitness(self, non_negative=False):
        result = self.func(*np.array(list(zip(*self.translateDNA()))))
        self.mean_fitness.append(np.mean(result))
        self.max_fitness.append(np.max(result))
        if non_negative:
            min_fit = np.min(result, axis=0)
            result = result - min_fit + 1e-3
        return result

    # 自然选择
    def select(self):
        fitness = self.get_fitness(non_negative=True)

        self.POP = self.POP[np.random.choice(np.arange(self.POP.shape[0]), size=self.POP.shape[0], replace=True,
                                             p=fitness / np.sum(fitness))]

    # 染色体交叉
    def crossover(self):
        for people in self.POP:
            if np.random.rand() < self.cross_rate:
                i_ = np.random.randint(0, self.POP.shape[0], size=1)
                cross_points = np.random.randint(0, 2, size=(len(self.var_len), self.DNA_SIZE)).astype(np.bool)
                people[cross_points] = self.POP[i_, cross_points]

    # 基因变异
    def mutate(self):
        for people in self.POP:
            for var in people:
                for point in range(self.DNA_SIZE):
                    if np.random.rand() < self.mutation:
                        var[point] = 1 if var[point] == 0 else 1

    # 进化
    def evolution(self):
        self.select()
        self.crossover()
        self.mutate()

    # 重置
    def reset(self):
        self.POP = self.copy_POP.copy()

    # 打印当前状态日志
    def log(self):
        return pd.DataFrame(np.hstack((self.translateDNA(), self.get_fitness().reshape((len(self.POP), 1)))),
                            columns=[f'x{i}' for i in range(len(self.var_len))] + ['F'])

    # 一维变量作图
    def plot_in_jupyter_1d(self, iter_time=200):
        log = []
        for _ in range(iter_time):
            self.evolution()
            log.append(self.log().values[0])

        fig, axs = plt.subplots(1, 2, figsize=(15.4, 8.6))

        # 最大值的图像
        x = np.linspace(*self.bound[0], self.var_len[0] * 50)
        axs[0].plot(x, self.func(x))
        x = self.translateDNA().reshape(self.POP_SIZE)
        axs[0].scatter(x, self.func(x), s=180, lw=0, c='red', alpha=0.5)
        axs[0].set(xlabel='x', ylabel='y', title='2x + 7sin(10x) + cos(4x)')

        x = np.linspace(1, 101, 200)
        axs[1].plot(x, self.max_fitness[1::2], c='red')
        axs[1].plot(x, self.mean_fitness[1::2], c='blue')
        axs[1].set(xlabel='time', ylabel='fitmess', title='fitness')
        axs[1].legend(['best', 'mean'])

        fig.show()


if __name__ == '__main__':
    func = lambda x: 2 * x + 7 * np.sin(10 * x) + np.cos(4 * x)
    ga = GA([[np.random.rand() * 5] for _ in range(100)], [(0, 5)], DNA_SIZE=10, func=func)
    ga.plot_in_jupyter_1d()