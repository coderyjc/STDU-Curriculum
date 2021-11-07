# -!- coding: utf-8 -!-

"""
@Author: Jingcun Yan
@Date: 2021/11/04
@Time: 16:25
@Description:
"""

import torch


class Net(torch.nn.Module):
    def __init__(self, n_feature, n_hidden, n_output):
        super(Net, self).__init__()
        # 两层感知机
        self.hidden = torch.nn.Linear(n_feature, n_hidden)
        self.predict = torch.nn.Linear(n_hidden, n_output)

    def forward(self, x):
        x = torch.relu_(self.hidden(x))
        x = self.predict(x)
        return x
