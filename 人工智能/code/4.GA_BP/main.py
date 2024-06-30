# -!- coding: utf-8 -!-

"""
@Author: Jingcun Yan
@Date: 2021/10/28
@Time: 16:25
@Description:
"""
import torch
from torch.autograd import Variable
import matplotlib.pyplot as plt

from ai_util import get_r2
from BP import Net
from GA_BP import GA

# 训练样本个数
N = 100
# 训练集输入 x
x = torch.unsqueeze(torch.linspace(-5, 5, N), dim=1)
# 训练集输出 y
y = x.pow(2)
# 转换为带有梯度的tensor
x, y = Variable(x), Variable(y)

# 输入神经元的个数
cell_input = 1
# 隐藏层神经元的个数
cell_hidden = 6
# 输出神经元的个数
cell_output = 1
# 编码长度
code_length = cell_input * cell_hidden + cell_output * cell_hidden + cell_output + cell_hidden

# 网络创建
net = Net(cell_input, cell_hidden, cell_output)
# 优化器
optimizer = torch.optim.SGD(net.parameters(), lr=0.01)
# 损失函数
loss_func = torch.nn.MSELoss()
# 训练网络
for t in range(500):
    prediction = net(x)
    loss = loss_func(prediction, y)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

print('未使用遗传算法的网络训练完成...')

# 仿真测试没有使用遗传算法预处理的网络
fig, axs = plt.subplots(1, 2, figsize=(12.8, 6.4))
axs[0].scatter(x.data.numpy(), y.data.numpy())
axs[0].plot(x.data.numpy(), prediction.data.numpy(), 'r-', lw=5)
axs[0].set(title='r2 = ' + str(get_r2(N, y.data.numpy(), prediction.data.numpy())))

# net种群数量为 50
pop_size = 50
# net种群，pytorch会自动赋weight和bias的初值
net_pop_list = [Net(cell_input, cell_hidden, cell_output) for i in range(pop_size)]
# 遗传算法
ga = GA(net_pop_list, x, y, loss_func)

print('遗传算法初始化完毕...')

ga.train()

print('遗传算法训练完成...')

# 遗传算法获得最佳网络
best_net = ga.get_best()

# # 使用预处理的网络进行训练
# optimizer = torch.optim.SGD(best_net.parameters(), lr=0.01)
# for t in range(500):
#     prediction = best_net(x)
#     loss = loss_func(prediction, y)
#     optimizer.zero_grad()
#     loss.backward()
#     optimizer.step()
#
# print('基于遗传算法优化的网络训练完成...')

# 仿真测试
prediction = best_net(x)
axs[1].scatter(x.data.numpy(), y.data.numpy())
axs[1].plot(x.data.numpy(), prediction.data.numpy(), 'g-', lw=5)
axs[1].set(title='ga-r2 = ' + str(get_r2(N, y.data.numpy(), prediction.data.numpy())))

# ga.plot_fitness_loss()

fig.show()