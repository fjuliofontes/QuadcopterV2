%% gen random circle at random position

radius=3;%just an example
theta=linspace(0,2*pi,200);%you can increase this if this isn't enough yet
xoff = (5-2).*rand(1) + 2;
yoff = (7-3).*rand(1) + 3;

x=radius*cos(theta)-xoff;
y=radius*sin(theta)-yoff;

scale = (1-0.98).*rand(1) + 0.98;
y = y .* scale;

figure;
plot(x,y), grid on

%% center 
x_scf = 1;
y_scf = (max(x)-min(x))/(max(y)-min(y));

x_off = - ((max(x) + min(x)) / 2.0);
y_off = - ((max(y) + min(y)) / 2.0);

xs = (x + x_off)*x_scf;
ys = (y + y_off)*y_scf;

figure;
plot(xs,ys) , grid on