"""
Author: Yan Jingcun
Date: 2022-03-22
Time: 10:02:51
Description: 
"""

from pyecharts import options as opts
from pyecharts.charts import Scatter
from sklearn.datasets import load_iris    #导入数据集iris

#载入数据集  
iris = load_iris()

data = iris.data

sepal_area = [x[0]*x[1] for x in data]  
petal_area = [x[2]*x[3] for x in data]  
x = [i for i in range(len(sepal_area))]

c = (
    Scatter()
    .add_xaxis(x)
    .add_yaxis("speal", sepal_area)
    .add_yaxis("petal", petal_area)
    .set_global_opts(
        title_opts=opts.TitleOpts(title="萼片（sepal）和花瓣（petal）的大小关系"),
        xaxis_opts=opts.AxisOpts(
            axistick_opts=opts.AxisTickOpts(is_align_with_label=True),
            is_scale=False,
            boundary_gap=False,
        ),
    )
    .set_series_opts(
        areastyle_opts=opts.AreaStyleOpts(opacity=0.5),
        label_opts=opts.LabelOpts(is_show=False),
        axistick_opts=opts.AxisTickOpts(
            is_show=False,
            is_inside=False
        )
    )
    .render("iris.html")
)
