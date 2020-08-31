clear
close all

t = 0.01 : 0.01 : 1;

X1 = imread('street1.jpg');
X1_double = double(X1);
X1_gray = (X1_double(:, :, 1) + X1_double(:, :, 2) + X1_double(:, :, 3)) / 3;

X2 = imread('street2.jpg');
X2_double = double(X2);
X2_gray = (X2_double(:, :, 1) + X2_double(:, :, 2) + X2_double(:, :, 3)) / 3;

X3 = imread('ngc6543a.jpg');
X3_double = double(X3);
X3_gray = (X3_double(:, :, 1) + X3_double(:, :, 2) + X3_double(:, :, 3)) / 3;

%%%% fft %%%%
Y = fft_f(X1_gray);
ifft_f(Y);

Y = fft_f(X2_gray);
ifft_f(Y);

Y = fft_f(X3_gray);
ifft_f(Y);
%%%%%%%%%%%%%

function Y = fft_f(X)
    figure
    imagesc(abs(X))
    axis image
    axis off
    colormap(gray)

    Y = fft(X);
    figure
    imagesc(abs(Y))
    axis image
    %axis off
    colormap(gray)

end

function Y2 = ifft_f(Y)
    Y2 = ifft(Y);
    figure
    imagesc(abs(Y2))
    axis image
    %axis off
    colormap(gray)
end