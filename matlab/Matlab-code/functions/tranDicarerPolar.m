function [tho, theta] = tranDicarerPolar(x, y)
% ֱ������ת��Ϊ������
% tho  
% theta  
tho = sqrt(x * x + y * y);
theta = atan(y / x);
