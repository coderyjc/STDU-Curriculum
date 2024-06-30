for i in 1:10
 min=100000
 for m in 1:6
  if T[m][i]<min
   K[m]=T[m][i] //将所用时间列存储起来
   min=T[m][i]  //选出用时最短的时间
            n++   //最短时间t1所对应的第n号储备库
            sort(K)  //对时间序列进行升序排序，当t1所对应的存储库物资不够时，则使用t2所对应的存储库
        K->A //将用时和储备库对应起来
    for j in 1:6  //这里的j指所需的物品，1~6分别为饮用水、食品、帐篷、棉被、绷带和药品
     if A[n][j]>=D[i][j] //A[n][j]指t1对应储备库存放j类物品数量，而D为第i个受灾点的需求量
        A[n][j]-A=D[i][j]  //物资送出，重置A[n][j]
        sum_time+=T[n][i]  
     else 
      n=k->1;   //此时n为K中第二个数，即第二短的时间所对应的储备库序号

        输出sum_time
        
        
filename='C:\Users\86176\Desktop\工作簿1.xlsx';
sheet=1;
xlRange='C17:L22';
subsetA=xlsread(filename,sheet,xlRange);
D=subsetA;%受灾点所用时间
filename='C:\Users\86176\Desktop\工作簿1.xlsx';
sheet=1;
xlRange='C2:H7';
subsetA=xlsread(filename,sheet,xlRange);
S=subsetA;%存储的物资
filename='C:\Users\86176\Desktop\工作簿1.xlsx';
sheet=1;
xlRange='C27:H36';
subsetA=xlsread(filename,sheet,xlRange);
X=subsetA;%所需的物资
for i=1:10%十个受灾点
    min=100000
    for j=1:6%6个仓库
        if D(j,i)<min%(对于时间来排序)
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