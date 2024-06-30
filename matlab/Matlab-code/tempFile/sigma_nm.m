function rst = sigma_nm(m, n)
if n == 1 
    rst = 1;
else
    rst = n^m +  sigma_nm(m, n - 1);
end
return;