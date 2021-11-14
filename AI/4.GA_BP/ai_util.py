# -!- coding: utf-8 -!-

"""
@Author: Jingcun Yan
@Date: 2021/11/6
@Time: 19:15
@Description: 
"""

import numpy as np


def get_r2(N, y_numpy, y_pred):
    """
    N 为测试样本的个数;
    y_numpy 是实际值 numpy;
    y_pred 是估计值 numpy
    """
    up = np.power(np.sum(y_numpy * y_pred * N) - np.sum(y_numpy) * np.sum(y_pred), 2)
    down = (np.sum(N * np.power(y_pred, 2)) - np.power(np.sum(y_pred), 2)) * \
           (N * np.sum(np.power(y_numpy, 2)) - np.power(np.sum(y_numpy), 2))

    r2 = up / down
    return r2
