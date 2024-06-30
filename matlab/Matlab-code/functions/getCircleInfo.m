function [s, p] = getCircleInfo(r)
% getCircleInfo calculate the area and perimeter of a circle of radir
% r 半径
% s 面积
% p 周长
s = pi * r * r;
p = 2 * pi * r;