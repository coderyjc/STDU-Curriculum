for i in 1:10
 min=100000
 for m in 1:6
  if T[m][i]<min
   K[m]=T[m][i] //������ʱ���д洢����
   min=T[m][i]  //ѡ����ʱ��̵�ʱ��
            n++   //���ʱ��t1����Ӧ�ĵ�n�Ŵ�����
            sort(K)  //��ʱ�����н����������򣬵�t1����Ӧ�Ĵ洢�����ʲ���ʱ����ʹ��t2����Ӧ�Ĵ洢��
        K->A //����ʱ�ʹ������Ӧ����
    for j in 1:6  //�����jָ�������Ʒ��1~6�ֱ�Ϊ����ˮ��ʳƷ�������ޱ���������ҩƷ
     if A[n][j]>=D[i][j] //A[n][j]ָt1��Ӧ��������j����Ʒ��������DΪ��i�����ֵ��������
        A[n][j]-A=D[i][j]  //�����ͳ�������A[n][j]
        sum_time+=T[n][i]  
     else 
      n=k->1;   //��ʱnΪK�еڶ����������ڶ��̵�ʱ������Ӧ�Ĵ��������

        ���sum_time
        
        
filename='C:\Users\86176\Desktop\������1.xlsx';
sheet=1;
xlRange='C17:L22';
subsetA=xlsread(filename,sheet,xlRange);
D=subsetA;%���ֵ�����ʱ��
filename='C:\Users\86176\Desktop\������1.xlsx';
sheet=1;
xlRange='C2:H7';
subsetA=xlsread(filename,sheet,xlRange);
S=subsetA;%�洢������
filename='C:\Users\86176\Desktop\������1.xlsx';
sheet=1;
xlRange='C27:H36';
subsetA=xlsread(filename,sheet,xlRange);
X=subsetA;%���������
for i=1:10%ʮ�����ֵ�
    min=100000
    for j=1:6%6���ֿ�
        if D(j,i)<min%(����ʱ��������)
            k=D(j,i)
            min=k
            sort(k)
            n=n+1
        end  
        %for m=1:6
            %if S(n,m)>=X(i,m)
               % S(n,m)=S(n,m)-X(i,m)
               % sum_time=sum_time+T(n,i)
            %else
              %  n=n-1
            end