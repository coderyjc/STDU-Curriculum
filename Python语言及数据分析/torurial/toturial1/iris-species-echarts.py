"""
Author: Yan Jingcun
Date: 2022-03-25
Time: 12:01:48
Description: PyEcharts 绘制不同种类的鸢尾花的萼片大小和花瓣大小的分布情况
"""

from sklearn.datasets import load_iris
import pyecharts.options as opts
from pyecharts.charts import Bar
from pyecharts.charts import Grid


#载入数据集  
iris = load_iris()

data = iris.data
sepal_area = [x[0]*x[1] for x in data]  
petal_area = [x[2]*x[3] for x in data]  

x = [i for i in range(50)]

species_1 = sepal_area[0:50]
species_2 = sepal_area[50:100]
species_3 = sepal_area[100:150]

sepal_bar = Bar(init_opts=opts.InitOpts(width="1000px", height="500px"))\
    .add_xaxis(xaxis_data=x)\
    .add_yaxis(
        series_name="species_1",
        y_axis=species_1,
        label_opts=opts.LabelOpts(is_show=False)
    )\
    .add_yaxis(
        series_name="species_2",
        y_axis=species_2,
        label_opts=opts.LabelOpts(is_show=False),
    )\
    .add_yaxis(
        series_name="species_3",
        y_axis=species_3,
        label_opts=opts.LabelOpts(is_show=False),
    )\
    .set_global_opts(
        xaxis_opts=opts.AxisOpts(
            splitline_opts=opts.SplitLineOpts(is_show=False),
            ),
        yaxis_opts=opts.AxisOpts(
            axistick_opts=opts.AxisTickOpts(is_show=True),
            splitline_opts=opts.SplitLineOpts(is_show=True),
            name="Sepal_Area"
        ),
    )

species_1 = petal_area[0:50]
species_2 = petal_area[50:100]
species_3 = petal_area[100:150]

petal_bar = Bar(init_opts=opts.InitOpts(width="1000px", height="500px"))\
    .add_xaxis(xaxis_data=x)\
    .add_yaxis(
        series_name="species_1",
        y_axis=species_1,
        label_opts=opts.LabelOpts(is_show=False)
    )\
    .add_yaxis(
        series_name="species_2",
        y_axis=species_2,
        label_opts=opts.LabelOpts(is_show=False),
    )\
    .add_yaxis(
        series_name="species_3",
        y_axis=species_3,
        label_opts=opts.LabelOpts(is_show=False),
    )\
    .set_global_opts(
        xaxis_opts=opts.AxisOpts(splitline_opts=opts.SplitLineOpts(is_show=False)),
        yaxis_opts=opts.AxisOpts(
            axistick_opts=opts.AxisTickOpts(is_show=True),
            splitline_opts=opts.SplitLineOpts(is_show=True),
            name="Petal_Area"
        ),
    )


grid = (
    Grid(init_opts=opts.InitOpts(width="1800px", height="900px"))
    .add(sepal_bar, grid_opts=opts.GridOpts(pos_bottom="60%"))
    .add(petal_bar, grid_opts=opts.GridOpts(pos_top="60%"))
    .render("iris.html")
)