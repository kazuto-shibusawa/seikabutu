clear; close all;

%âÊëúÇÃì«Ç›çûÇ›
X = imread('street1.jpg');
imagesc(X);
axis image;
[M, N, C] = size(X);
m_0 = 0;
n_0 = round(N / 2);

for m = 1 :M
    for n = 1 : N
        x = n - n_0;
        y = -m + m_0;
    end
end

    %ägëÂÅAèkè¨
    xMag = 0.5;
    yMag = 2;
    
    Tmag = [xMag , 0 , 0;
            0  ,yMag , 0;
            0  ,0,  1];
        
angle = pi / 4;
Trot = [cos(angle), -sin(angle), 0;
        sin(angle), cos(angle), 0;
        0, 0, 1];
    
xshift = -n_0;
yshift = 0;
Trans = [1, 0, xshift;
    0, 1, yshift;
    0, 0, 1];

X_new = zeros(M,N,C); 
for  m_new = 1 : M
    for n_new = 1 : N
        x_new = n_new - n_0;
        y_new = -m_new + m_0;
        
        xy1_new = [x_new;y_new;1];
        
        xy1 = inv(Tmag) * inv(Trot) * inv(Trans) * xy1_new;
        
        x = xy1(1);
        y = xy1(2);
        
        m = round(-y + m_0);
        n = round(x + n_0);
        
        if 0 < m && m <= M ...
              &&  0 < n && n <= N 
            X_new(m_new,n_new,:) = X(m,n,:);
        end
    end
end
    
    figure(1);
    imagesc(uint8(X_new));
    axis image;
    
