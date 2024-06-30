"""
Author: Yan Jingcun
Date: 2022-03-26
Time: 21:47:52
Description: pyecharts 绘制不同种类的散点图
"""

from pyecharts import options as opts
from pyecharts.charts import Scatter, Grid
from sklearn.datasets import load_iris

iris = load_iris()

data = iris.data

sepal_area = [x[0]*x[1] for x in data]  
petal_area = [x[2]*x[3] for x in data]  

x = [i for i in range(50)]

scatter_1 = (
    Scatter()
    .add_xaxis(x)
    .add_yaxis("Sepal_area", sepal_area[0:50])
    .add_yaxis("Petal_area", petal_area[0:50])
    .set_global_opts(
      title_opts=opts.TitleOpts(title="三种不同的品种的面积对比"),
      yaxis_opts=opts.AxisOpts(
        name="Species_1"
      )
    ).
    set_series_opts(
       label_opts=opts.LabelOpts(is_show=False),
    )
)
scatter_2 = (
    Scatter()
    .add_xaxis(x)
    .add_yaxis("Sepal_area", sepal_area[50:100])
    .add_yaxis("Petal_area", petal_area[50:100])
    .set_global_opts(
      yaxis_opts=opts.AxisOpts(
        name="Species_2"
      )
    ).
    set_series_opts(
       label_opts=opts.LabelOpts(is_show=False),
    )
)

scatter_3 = (
    Scatter()
    .add_xaxis(x)
    .add_yaxis("Sepal_area", sepal_area[100:150])
    .add_yaxis("Petal_area", petal_area[100:150])
    .set_global_opts(
      yaxis_opts=opts.AxisOpts(
        name="Species_3"
      )
    ).
    set_series_opts(
       label_opts=opts.LabelOpts(is_show=False),
    )
)

grid = (
    Grid(init_opts=opts.InitOpts(width="1800px", height="900px"))
    .add(scatter_1, grid_opts=opts.GridOpts(pos_left="3%", pos_right="70%"))
    .add(scatter_2, grid_opts=opts.GridOpts(pos_left="36%", pos_right="34%"))
    .add(scatter_3, grid_opts=opts.GridOpts(pos_left="69%", pos_right="1%"))
    .render("grid_horizontal.html")
)