%-- 信1901-4 闫竞存 --%

% clear 清除工作台（变量）
% clear v 清除变量v
% who 显示当前所有变量
% whos 显示当前所有变量的详细信息

% 算式计算
x = (12+2*(7-4))/3^2;
fprintf("x = %f\n", x)

% 计算sin(45°)
% sin的参数值以弧度为单位，pi是预定义的变量，pi=3.1415926
% matlab 对大小写敏感

sin45 = sin(45 * pi / 180);
fprintf("sin45° = %f\n", sin45)

% exp 表示 e 的多少次方
sqrt(1+2*exp(4.92+0.5));


y = 2*cos(0.3*pi)/(1+sqrt(5));
fprintf("y = %f\n", y)

redius = 5.2;
area = pi * redius ^ 2;

fprintf("area = %f\n", area)
