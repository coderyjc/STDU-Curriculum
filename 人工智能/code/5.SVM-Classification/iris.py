# -!- coding: utf-8 -!-

"""
@Author: Jingcun Yan
@Date: 2021/11/12
@Time: 19:15
@Description:
"""

import matplotlib.pyplot as plt
from sklearn import svm, datasets
from sklearn.model_selection import train_test_split, cross_val_score

# 导入数据
iris = datasets.load_iris()

# 切分数据以获得训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.4, random_state=0)

# RBF 核函数拟合
# model = svm.SVC(kernel='rbf').fit(X_train, y_train)
model = svm.SVC(kernel='linear').fit(X_train, y_train)

# 5次交叉验证
# cv = ShuffleSplit(n_splits=3, test_size=0.3, random_state=0)
# cross_val_score(clf, iris.data, iris.target, cv=cv)
# 整数默认使用k-fold策略
scores = cross_val_score(model, iris.data, iris.target, cv=5)

# 预测
y_predict = model.predict(X_test)

# 画图
title = 'SVC with Linear kernel, accuracy=' + str(scores.mean())
fig, ax = plt.subplots()
ax.plot(range(X_test.shape[0]), y_test, c='red', lw=1)
ax.scatter(range(X_test.shape[0]), y_predict, c='blue', s=16)
# ax.grid()
ax.set(title=title)
ax.legend(['True', 'Predict'])
fig.show()