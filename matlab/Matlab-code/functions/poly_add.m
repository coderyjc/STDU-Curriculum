function rst =  poly_add(a, b)
% 任意长度多项式相加
if length(a) == length(b)
    rst = a + b;
elseif length(a) > length(b)
    rst = a + [zeros(1, length(a) - length(b)), b];
else   
    rst = b + [zeros(1, length(b) - length(a)), a];
end