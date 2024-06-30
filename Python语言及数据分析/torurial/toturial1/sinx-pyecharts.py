"""
Author: Yan Jingcun
Date: 2022-03-21
Time: 22:08:27
Description: pyecharts 绘制 sin(x)
"""

from multiprocessing.sharedctypes import Value
import pyecharts.options as opts
import numpy as np
from pyecharts.charts import Line

x = np.linspace(0, np.pi * 2)
y = np.sin(x)


c = (
    Line()
    .add_xaxis(x)
    .add_yaxis("y = sin(x)", y, 
    is_smooth=True,
    is_symbol_show=False)
    .set_series_opts(
        label_opts=opts.LabelOpts(is_show=False),
        axistick_opts=opts.AxisTickOpts(
            is_show=False,
            is_inside=False
        )
    )
    .render("sinx.html")
)
