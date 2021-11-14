# -!- coding: utf-8 -!-

"""
@Author: Jingcun Yan
@Date: 2021/11/04
@Time: 16:25
@Description:
"""

import numpy.random
from matplotlib import pyplot as plt
import numpy as np


class GA:

    def __init__(self, pop_list, input_set, output_set, func, cross_rate=0.85, mutation=0.00001):
        """
        针对实验4的遗传算法
        :param pop_list: net种群
        :param input_set 输入集合
        :param output_set 输出集合
        :param func: 损失函数
        :param cross_rate: 染色体概率
        :param mutation: 变异概率
        """
        # 初始化
        self.pop_list = numpy.array(pop_list)
        self.func_loss = func
        self.cross_rate = cross_rate
        self.mutation = mutation
        self.x = input_set
        self.y = output_set
        # 用于后面重置（reset）
        self.pop_size = len(pop_list)
        self.copy_pop_list = pop_list.copy()
        # 用于绘制均方误差变化曲线和适应度曲线
        self.fitness_mean = []
        self.fitness_max = []
        self.loss_mean = []
        self.loss_max = []

    # 获取适应度值
    def get_fitness(self):
        '''
        返回适应度值，MSELoss的倒数
        :return:适应度值
        '''
        result = [1 / self.func_loss(net(self.x), self.y) for net in self.pop_list]
        return result

    # 自然选择
    def select(self):
        # 预处理
        fitness = [_tensor.detach().numpy() for _tensor in self.get_fitness()]
        # 统计
        self.fitness_max.append(np.max(fitness))
        self.fitness_mean.append(np.mean(fitness))
        # 自然选择
        best_list = np.array([self.pop_list[np.argmax(fitness)] for _ in range(10)])
        rest_list = self.pop_list[
            np.random.choice(np.arange(len(self.pop_list)), size=len(self.pop_list) - 10, replace=True,
                             p=fitness / np.sum(fitness))]
        self.pop_list = np.concatenate([best_list, rest_list])

    # 染色体交叉
    def crossover(self):
        for net in self.pop_list:
            if np.random.rand() < self.cross_rate:
                # 交叉
                net1 = self.pop_list[numpy.random.randint(0, self.pop_size)]
                net2 = self.pop_list[numpy.random.randint(0, self.pop_size)]
                for i in range(2):
                    # 交换weight-hidden
                    position = numpy.random.randint(0, 6)
                    t = net1.hidden.weight.data[position]
                    net1.hidden.weight.data[position] = net2.hidden.weight.data[position]
                    net2.hidden.weight.data[position] = t
                    # 交换bias-hidden
                    t = net1.hidden.bias.data[position]
                    net1.hidden.bias.data[position] = net2.hidden.bias.data[position]
                    net2.hidden.bias.data[position] = t

    # 基因变异
    def mutate(self):
        for net in self.pop_list:
            if np.random.rand() < self.mutation:
                net.hidden.weight.data[numpy.random.randint(0, 6)] = numpy.random.randn()
                net.hidden.bias.data[numpy.random.randint(0, 6)] = numpy.random.randn()

    # 进化
    def evolution(self):
        self.select()
        self.crossover()
        self.mutate()

    # 返回适应度值最大的网络
    def get_best(self):
        fitness = self.get_fitness()
        fitness = [_tensor.detach().numpy() for _tensor in fitness]
        return self.pop_list[np.argmax(fitness)]

    # 一维变量作图
    def train(self, iter_time=200):
        for _ in range(iter_time):
            self.evolution()

    def plot_fitness_loss(self):
        fig, ax = plt.subplots()
        ax.plot(np.array([_ for _ in range(200)]), self.fitness_max, 'r-', lw=2)
        ax.plot(np.array([_ for _ in range(200)]), self.fitness_mean, 'b-', lw=2)
        ax.legend(['best', 'mean'])
        ax.set(title='fitness')
        fig.show()
