num1 = input('���������1 : ');
num2 = input('���������2 : ');
oprt = input('����������������� + - * /��:  ', 's');
if oprt == '+'
    disp([num2str(num1), ' + ', num2str(num2), ' = ', num2str(num1+num2)]);
elseif oprt == '-'
    disp([num2str(num1), ' - ', num2str(num2), ' = ', num2str(num1-num2)]);
elseif oprt == '*'
    disp([num2str(num1), ' * ', num2str(num2), ' = ', num2str(num1*num2)]);
elseif oprt == '/'
    disp([num2str(num1), ' / ', num2str(num2), ' = ', num2str(num1/num2)]);
else
    disp('�밴��Ҫ�����������Ϣ');
end