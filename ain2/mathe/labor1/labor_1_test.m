t = linspace(0,2*pi);
x = 0.1*cos(t);
y = sin(t);
plot(x,y)
daspect([1 1 1])
title("hello circle");
legend("I am legend");
hold on
plot(y,x,'--')
set(gca,'XAxisLocation', 'origin', 'YAxisLocation', 'origin');
