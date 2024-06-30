% 参数的数量可以改变
function out = charAry(a, b, c)
if nargin == 1
    out = a;
end
if nargin == 2
    out = a + b;
end
if nargin == 3
    out = (a * b * c) / 2;
end