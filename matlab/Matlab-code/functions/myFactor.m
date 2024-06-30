function f = myFactor(n)
% ¼ÆËã n µÄ½×³Ë
if n <= 1
    f = 1;
else
    f = myFactor(n - 1) * n;
end