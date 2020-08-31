close all; clear;

x = [0.5, 1, -1];
y = [0, 2, 1];
z = [1, 0, 0.5];

x_theta = -pi / 6;
y_theta =  pi / 4;
z_theta =  pi / 4;

x(length(x) + 1) = x(1); 
y(length(y) + 1) = y(1);
z(length(z) + 1) = z(1);

triangle = [x; y; z; ones(1, length(x))];

rotation_matrix_x = [            1,             0,             0,             0;
                                 0,  cos(x_theta), -sin(x_theta),             0;
                                 0,  sin(x_theta),  cos(x_theta),             0;
                                 0,             0,             0,             1;];
                             
rotation_matrix_y = [ cos(y_theta),             0,  sin(y_theta),             0;
                                 0,             1,             0,             0;
                     -sin(y_theta),             0,  cos(y_theta),             0;
                                 0,             0,             0,             1;];
                             
rotation_matrix_z = [ cos(z_theta), -sin(z_theta),             0,             0;
                      sin(z_theta),  cos(z_theta),             0,             0;
                                 0,             0,             1,             0;
                                 0,             0,             0,             1;];
                 
triangle = rotation_matrix_x * rotation_matrix_y * rotation_matrix_z * triangle;

x_new = triangle(1,:);
y_new = triangle(2,:);
z_new = triangle(3,:);

figure;
plot3(x, y, z, 'x-b', x_new, y_new, z_new, 'o--r');
daspect([1,1,1]);
xlabel('x');
ylabel('y');
zlabel('z');
grid on;