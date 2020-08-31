%問題
%
%　画像を用意し、その画像のy軸とx軸の画素数をそれぞれM, N、
%中心を(M/2, N/2)とする。
%以下の(1)～(6)のアフィン変換をした画像を表示する。
%
%(1)x軸方向に0.6倍、y軸方向に4倍
%(2)pi/4回転
%(3)上下左右反転
%(4)x軸方向に-40、y軸方向に60平行移動
%(5)x軸方向に0.4、y軸方向に0.6シェア
%(6)上記(1)～(5)の同時アフィン変換

clear;
close all;

%%%%画像の読み込み%%%%
X = imread('street1.jpg');
X = double(X);
[M, N, C] = size(X);

figure(1);
imagesc(uint8(X));
axis image;
title('original');

%%%%下準備%%%%
n_0 = round(N / 2);
m_0 = 0;

%%%%%%%%%%%%%%%%%%%アフィン行列（T）の作成%%%%%%%%%%%%%%%%%%

%%%%拡大、縮小%%%%
xMag = 6;
yMag = 0.4;
T_magnification = [xMag , 0 , 0;
                   0  ,yMag , 0;
                   0  ,0,  1];
        
%%%%回転%%%%
angle = pi / 4;
T_rotation = [cos(angle), -sin(angle), 0;
              sin(angle), cos(angle), 0;
              0, 0, 1];

%%%%反転%%%%
T_inversion = [-1. 0, 0
               0, -1, 0
               0, 0, 1];

%%%%平行移動%%%%
xShift = -40;
yShift = 60;
T_translation = [1, 0, xShift;
                 0, 1, yShift;
                 0, 0, 1];

%%%%シェア%%%%
xShear = 0.4;
yShear = 0.6;
T_shear = [1, xShear, 0
          yShear, 1, 0
          0, 0, 1];
      
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%変換と表示%%%%
X_m = Affine_TR(X, inv(T_magnification));
figure(2);
imagesc(uint8(X_m));
axis image;
title('Magnification');

X_r = Affine_TR(X, inv(T_rotation));
figure(3);
imagesc(uint8(X_r));
axis image;
title('Rotation');

X_i = Affine_TR(X, inv(T_inversion));
figure(4);
imagesc(uint8(X_i));
axis image;
title('Inversion');

X_t = Affine_TR(X, inv(T_translation));
figure(5);
imagesc(uint8(X_t));
axis image;
title('Translation');

X_s = Affine_TR(X, inv(T_shear));
figure(6);
imagesc(uint8(X_s));
axis image;
title('Shear');

T_new = inv(T_magnification) * inv(T_rotation) * inv(T_inversion) * inv(T_translation) * inv(T_shear);
X_new = Affine_TR(X, T_new);
figure(7);
imagesc(uint8(X_new));
axis image;
title('All');

%%%%引数にした画像をアフィン変換する関数%%%%
function X_new = Affine_TR(X, T)

[M, N, C] = size(X);
n_0 = round(N / 2);
m_0 = round(M / 2);
X_new = zeros(M, N, C, 'uint8');
    for m_new = 1 : M
        for n_new = 1 : N
            xy_vec = [  n_new - n_0;
                       -m_new + m_0;
                                  1];

            aff_xy = T \ xy_vec;

            n = round(aff_xy(1) + n_0);
            m = round(-aff_xy(2) + m_0);

            if 0 < n && n < N && 0 < m && m < M
                X_new(m_new, n_new, :) = X(m, n, :);
            end
        end
    end
end