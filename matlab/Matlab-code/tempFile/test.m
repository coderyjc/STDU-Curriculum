n=input('ÇëÊäÈënµÄÖµ£¬n = ');
rst = 1 : 1 : n;
for t = 1: 1: n
    rst(t) = t ^ -2;
end
disp(sqrt(6 * sum(rst)));