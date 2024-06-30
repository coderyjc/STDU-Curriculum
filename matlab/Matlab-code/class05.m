num1 = input('输入操作数1 : ');
num2 = input('输入操作数2 : ');
oprt = input('输入运算符（仅限于 + - * /）:  ', 's');
if oprt == '+'
    disp([num2str(num1), ' + ', num2str(num2), ' = ', num2str(num1+num2)]);
elseif oprt == '-'
    disp([num2str(num1), ' - ', num2str(num2), ' = ', num2str(num1-num2)]);
elseif oprt == '*'
    disp([num2str(num1), ' * ', num2str(num2), ' = ', num2str(num1*num2)]);
elseif oprt == '/'
    disp([num2str(num1), ' / ', num2str(num2), ' = ', num2str(num1/num2)]);
else
    disp('请按照要求输入相关信息');
end