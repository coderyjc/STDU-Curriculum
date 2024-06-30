 x = -4: 0.01; 4;
 y  = x;
 [x, y] = meshgrid(x, y);
 z = x.^2 + y.^2;
 subplot(1,2,1), mesh(x,y,z);  %三维网格图
subplot(1,2,2), surf(x,y,z);    %三维曲面图
colormap(hot); 
