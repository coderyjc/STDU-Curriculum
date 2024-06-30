"""
Author: Yan Jingcun
Date: 2022-03-25
Time: 10:40:40
Description: 标注当前位置
"""

from pyecharts import options as opts
from pyecharts.charts import Geo

# 链式调用
c = (
        Geo()
        .add_schema(maptype="china")
        # 加入自定义的点，格式为
        .add_coordinate("myPosition", 114.516288, 38.089913)
        # 为自定义的点添加属性
        .add("我的位置", [("myPosition", 100)])
        .set_series_opts(label_opts=opts.LabelOpts(is_show=False))
        .set_global_opts(title_opts=opts.TitleOpts(title="我的位置"))
)

c.render('location.html')
