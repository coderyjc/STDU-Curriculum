x = [0 : 0.001*pi :5*pi]; % ��������x
x(x > pi/3 & x < 2* pi/ 3 | x > 7*pi/3 & x < 8*pi/ 3) = pi/3;
y = sin(x);
plot([0 : 0.001*pi :5*pi], y);
legend('y = sin(x)'); % ͼ��
set(gca, 'XLim',[0 5*pi]); % X���������ʾ��Χ
set(gca,'XTick', [0:pi:5*pi]); % X��ļǺŵ�
set(gca,'XTickLabel',{'0' 'pi' '2*pi' '3*pi' '4*pi' '5*pi'}); % X��ļǺ�
grid on;