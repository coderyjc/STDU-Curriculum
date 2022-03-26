"""
Author: Yan Jingcun
Date: 2022-03-25
Time: 22:18:51
Description: 用Matplotlib的分类散点子图绘制不同种类(species)鸢尾花萼片和花瓣的大小关系。
"""

from sklearn.datasets import load_iris
import matplotlib.pyplot as plt
import numpy as np

iris = load_iris()

data = iris.data

sepal_area = [x[0]*x[1] for x in data]  
petal_area = [x[2]*x[3] for x in data]  

iris = load_iris()
y = iris.target

y = [i + np.random.random(1)[0] / 2 for i in y]

color_2 = [i + 2 for i in iris.target]

plt.scatter(y, sepal_area, c=iris.target, label="Sepal_Area")
plt.scatter(y, petal_area, c=iris.target, alpha=0.6, label="Petal_Area")
plt.xlabel("Species")
plt.ylabel("Area")
plt.title("Area Comparation")

plt.show()