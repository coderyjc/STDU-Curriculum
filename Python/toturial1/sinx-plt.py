"""
Author: Yan Jingcun
Date: 2022-03-20
Time: 08:36:04
Description:  matplotlib 绘制 sinx
"""

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.axisartist.axislines import SubplotZero


if __name__ == '__main__':

  # 坐标点
  x = np.linspace(0, 2 * np.pi, num=256)
  y = np.sin(x)

  # 坐标轴
  fig = plt.figure(1)
  ax = SubplotZero(fig, 1, 1, 1)
  fig.add_subplot(ax)

  for direction in ["xzero", "yzero"]:
      ax.axis[direction].set_axisline_style("-|>")
      ax.axis[direction].set_visible(True)
  for direction in ["left", "right", "bottom", "top"]:
      ax.axis[direction].set_visible(False)

  plt.xticks([0, np.pi / 2, np.pi, 3 * np.pi / 2, 2 * np.pi], ['$0$', '$\pi/2$', '$\pi$', r'$3\pi/2$', r'$2\pi$'])
  # 图像
  ax.plot(x, y)
  # 标题
  ax.set_title('y = sin(x)')
  # 展示
  plt.show()