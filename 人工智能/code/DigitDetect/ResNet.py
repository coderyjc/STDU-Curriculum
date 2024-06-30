# -!- coding: utf-8 -!-

"""
@Author: Jingcun Yan
@Date: 2021/11/13
@Time: 10:02
@Description: 
"""
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
from torch.nn import functional as F

# 判断能否使用cuda加速
device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

# 循环次数
num_epochs = 5
# 分类
num_classes = 10
# 每次投喂数据量
batch_size = 100
# 学习率
learning_rate = 0.001

# MNIST dataset
train_dataset = torchvision.datasets.MNIST(root='data/',
                                           train=True,
                                           transform=transforms.ToTensor(),
                                           download=True)

test_dataset = torchvision.datasets.MNIST(root='data/',
                                          train=False,
                                          transform=transforms.ToTensor())

# Data loader
train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                           batch_size=batch_size,
                                           shuffle=True)

test_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                          batch_size=batch_size,
                                          shuffle=False)


class ResBlk(nn.Module):

    def __init__(self, ch_in, ch_out, stride=1):
        # 初始化
        super(ResBlk, self).__init__()
        # 根据resnet网络结构构建2个（block）块结构 第一层卷积 卷积核大小3*3,步长为1，边缘加1
        self.conv1 = nn.Conv2d(ch_in, ch_out, kernel_size=3, stride=1, padding=1)
        # 将第一层卷积处理的信息通过BatchNorm2d
        self.bn1 = nn.BatchNorm2d(ch_out)
        # 第二块卷积接收第一块的输出，操作一样
        self.conv2 = nn.Conv2d(ch_out, ch_out, kernel_size=3, stride=1, padding=1)
        self.bn2 = nn.BatchNorm2d(ch_out)

        # 确保输入维度等于输出维度
        self.extra = nn.Sequential()  # 先建一个空的extra
        if ch_out != ch_in:
            # [b, ch_in, h, w] => [b, ch_out, h, w]
            self.extra = nn.Sequential(
                nn.Conv2d(ch_in, ch_out, kernel_size=1, stride=stride),
                nn.BatchNorm2d(ch_out)
            )

    def forward(self, x):
        out = F.relu(self.bn1(self.conv1(x)))
        out = self.bn2(self.conv2(out))
        out = self.extra(x) + out
        out = F.relu(out)
        return out


class ResNet18(nn.Module):

    def __init__(self):
        super(ResNet18, self).__init__()

        # 首先定义一个卷积层
        self.conv1 = nn.Sequential(
            nn.Conv2d(1, 32, kernel_size=3, stride=3, padding=0),
            nn.BatchNorm2d(32)
        )

        # [b, 32, h, w] => [b, 64, h ,w]
        self.blk1 = ResBlk(32, 64, stride=1)
        # [b, 64, h, w] => [b, 128, h, w]
        self.blk2 = ResBlk(64, 128, stride=1)
        # # [b, 128, h, w] => [b, 256, h, w]
        self.blk3 = ResBlk(128, 256, stride=1)
        # # [b, 256, h, w] => [b, 256, h, w]
        self.blk4 = ResBlk(256, 256, stride=1)

        self.outlayer = nn.Linear(256 * 1 * 1, 10)  # 最后是全连接层

    def forward(self, x):
        # [128, 1, 28, 28] => [128, 32, 9, 9]
        x = self.conv1(x)
        x = F.relu(x)

        # [128, 32, 9, 9] => [128, 64, 9, 9]
        x = self.blk1(x)  # 然后通过4次resnet网络结构
        # [128, 64, 9, 9] => [128, 128, 9, 9]
        x = self.blk2(x)
        # [128, 128, 9, 9] => [128, 256, 9, 9]
        x = self.blk3(x)
        # [128, 256, 9, 9] => [128, 256, 9, 9]
        x = self.blk4(x)

        # [128, 256, 9, 9] => [128, 256, 1, 1]
        x = F.adaptive_avg_pool2d(x, [1, 1])
        # [128, 256, 1, 1]
        x = x.view(x.size(0), -1)  # 平铺一维值
        # [128, 256]
        x = self.outlayer(x)  # 全连接层

        return x


model = ResNet18().to(device)

# Loss and optimizer
criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

loss_rate_list = []

# Train the model
total_step = len(train_loader)
for epoch in range(num_epochs):
    for i, (images, labels) in enumerate(train_loader):
        images = images.to(device)
        labels = labels.to(device)

        # Forward pass
        outputs = model(images)
        loss = criterion(outputs, labels)

        # Backwad and optimize
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if (i + 1) % 100 == 0:
            print('Epoch[{}/{}], Step[{}/{}], Loss:{:.4f}'
                  .format(epoch + 1, num_epochs, i + 1, total_step, loss.item()))
            loss_rate_list.append(loss.item())

best_accuracy = 0

# Test the model
model.eval()
with torch.no_grad():
    correct = 0
    total = 0
    for images, labels in test_loader:
        images = images.to(device)
        labels = labels.to(device)
        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()
    best_accuracy = 100 * correct / total
    print('Test Accuracy of the model 10000 test images:{}%'.format(best_accuracy))

# draw loss rate
title = 'best_accuracy=' + str(best_accuracy)
fig, ax = plt.subplots()
ax.plot(range(30), loss_rate_list, lw=1, color='red')
ax.set(title=title)
fig.show()

# Save the model checkpoint
torch.save(model.state_dict(), 'resnet-model.ckpt')
