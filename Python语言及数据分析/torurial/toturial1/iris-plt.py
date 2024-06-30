"""
Author: Yan Jingcun
Date: 2022-03-21
Time: 23:06:59
Description: matplotlib 绘制 iris
"""

from base64 import encode
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris    #导入数据集iris

#载入数据集  
iris = load_iris()  
data = iris.data

# 计算面积
sepal_area = [x[0]*x[1] for x in data]  
petal_area = [x[2]*x[3] for x in data]  
x = [i for i in range(len(sepal_area))]
  
# 画图
plt.scatter(x, sepal_area, color='red', label='sepal_area')
plt.scatter(x, petal_area, color='blue', label='petal_area')
plt.title('relation of sepal_area and petal_area')

plt.show()