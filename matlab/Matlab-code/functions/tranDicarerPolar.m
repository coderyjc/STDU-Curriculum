function [tho, theta] = tranDicarerPolar(x, y)
% 直角坐标转换为极坐标
% tho  
% theta  
tho = sqrt(x * x + y * y);
theta = atan(y / x);
