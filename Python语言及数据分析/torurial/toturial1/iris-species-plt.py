"""
Author: Yan Jingcun
Date: 2022-03-25
Time: 12:01:48
Description: matplotlib 绘制不同种类的鸢尾花的萼片大小和花瓣大小的分布情况
"""

from sklearn.datasets import load_iris
import matplotlib.pyplot as plt
import numpy as np


#载入数据集  
iris = load_iris()

data = iris.data
sepal_area = [x[0]*x[1] for x in data]  
petal_area = [x[2]*x[3] for x in data]  

X = np.arange(50)

species_1 = sepal_area[0:50]
species_2 = sepal_area[50:100]
species_3 = sepal_area[100:150]

fig, ax = plt.subplots(2, 1)

#绘制柱状图
ax[0].bar(X + 0.0, species_1, color = '#C23532', width = 0.2)
ax[0].bar(X + 0.25, species_2, color = '#304655', width = 0.2)
ax[0].bar(X + 0.5, species_3, color = '#62A1A9', width = 0.2)
ax[0].set_title('sepal area compare')
ax[0].set_ylabel('sepal_area')


species_1_p = petal_area[0:50]
species_2_p = petal_area[50:100]
species_3_p = petal_area[100:150]

#绘制柱状图
ax[1].bar(X + 0.0, species_1_p, color = '#C23532', width = 0.2)
ax[1].bar(X + 0.25, species_2_p, color = '#304655', width = 0.2)
ax[1].bar(X + 0.5, species_3_p, color = '#62A1A9', width = 0.2)
ax[1].set_title('Petal area compare')
ax[1].set_ylabel('petal_area')

plt.show()