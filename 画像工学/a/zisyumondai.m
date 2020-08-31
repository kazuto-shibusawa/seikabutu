%���
%
%�@�摜��p�ӂ��A���̉摜��y����x���̉�f�������ꂼ��M, N�A
%���S��(M/2, N/2)�Ƃ���B
%�ȉ���(1)�`(6)�̃A�t�B���ϊ��������摜��\������B
%
%(1)x��������0.6�{�Ay��������4�{
%(2)pi/4��]
%(3)�㉺���E���]
%(4)x��������-40�Ay��������60���s�ړ�
%(5)x��������0.4�Ay��������0.6�V�F�A
%(6)��L(1)�`(5)�̓����A�t�B���ϊ�

clear;
close all;

%%%%�摜�̓ǂݍ���%%%%
X = imread('street1.jpg');
X = double(X);
[M, N, C] = size(X);

figure(1);
imagesc(uint8(X));
axis image;
title('original');

%%%%������%%%%
n_0 = round(N / 2);
m_0 = 0;

%%%%%%%%%%%%%%%%%%%�A�t�B���s��iT�j�̍쐬%%%%%%%%%%%%%%%%%%

%%%%�g��A�k��%%%%
xMag = 6;
yMag = 0.4;
T_magnification = [xMag , 0 , 0;
                   0  ,yMag , 0;
                   0  ,0,  1];
        
%%%%��]%%%%
angle = pi / 4;
T_rotation = [cos(angle), -sin(angle), 0;
              sin(angle), cos(angle), 0;
              0, 0, 1];

%%%%���]%%%%
T_inversion = [-1. 0, 0
               0, -1, 0
               0, 0, 1];

%%%%���s�ړ�%%%%
xShift = -40;
yShift = 60;
T_translation = [1, 0, xShift;
                 0, 1, yShift;
                 0, 0, 1];

%%%%�V�F�A%%%%
xShear = 0.4;
yShear = 0.6;
T_shear = [1, xShear, 0
          yShear, 1, 0
          0, 0, 1];
      
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%�ϊ��ƕ\��%%%%
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

%%%%�����ɂ����摜���A�t�B���ϊ�����֐�%%%%
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