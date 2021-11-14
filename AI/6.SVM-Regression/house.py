# -!- coding: utf-8 -!-

"""
@Author: Jingcun Yan
@Date: 2021/11/12
@Time: 19:44
@Description:
"""

import matplotlib.pyplot as plt
from sklearn import svm, datasets
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.neural_network import MLPRegressor
from sklearn.metrics import r2_score

# 导入数据
housing = datasets.fetch_california_housing()

housing.data = housing.data[:100, :4]
housing.target = housing.target[:100]

# 切分数据以获得训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(housing.data, housing.target, test_size=0.3, random_state=0)

# RBF 核函数拟合
model = svm.SVR(kernel='rbf', C=180).fit(X_train, y_train)

# 5次交叉验证
# cv = ShuffleSplit(n_splits=3, test_size=0.3, random_state=0)
# cross_val_score(clf, housing.data, housing.target, cv=cv)
# 整数默认使用k-fold策略
scores = cross_val_score(model, housing.data, housing.target, cv=5)

# 预测
y_predict = model.predict(X_test)

r2 = r2_score(y_test, y_predict)

# 画图
title = 'SVR with Linear kernel, R^2=' + str(r2)
fig, axs = plt.subplots(1, 2, figsize=(12.8, 6.4))
axs[0].scatter(range(X_test.shape[0]), y_test, c='red', s=16)
axs[0].plot(range(X_test.shape[0]), y_predict, c='blue', lw=1)
# ax.grid()
axs[0].set(title=title)
axs[0].legend(['Predict', 'Real'])


# 神经网络拟合
net = MLPRegressor(max_iter=500, learning_rate_init=0.002).fit(X_train, y_train)
y_predict = net.predict(X_test)
r2 = r2_score(y_test, y_predict)
# 画图
title = 'BP, R^2=' + str(r2)
axs[1].scatter(range(X_test.shape[0]), y_test, c='red', s=16)
axs[1].plot(range(X_test.shape[0]), y_predict, c='green', lw=1)
# ax.grid()
axs[1].set(title=title)
axs[1].legend(['Predict', 'Real'])

fig.show()
