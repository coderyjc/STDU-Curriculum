function f = myFactor(n)
% ���� n �Ľ׳�
if n <= 1
    f = 1;
else
    f = myFactor(n - 1) * n;
end