function D_SkriptNewton_L()
clear all
close all
MatlabOn=0;

I = [0,pi/2];
f  = @(x) x - cos(x);
df = @(x) 1 + sin(x);
x0 = (I(1)+I(2))/2;

[x iter] = MyNewton(f,df,x0,1.0e-08,1);

fprintf("Eine genäherte Nullstelle wurde nach %d Iterationen gefunden: ",iter);
fprintf("%.2e\n",x);

%%
htwg_gruen=[0,155,145]/255;
drot = [200,0,0]/255;
xx = linspace(I(1),I(2),1000);
if MatlabOn
    % Figure position fuer Matlab
    h = figure(1);
    h.Position = [3 538 560 420];
else
    % Figure position fuer Octave
    figure(1,"position",[3 538 560 420]);
end

hold on
grid on
plot(xx,f(xx),'-','Color',htwg_gruen);
plot(x,f(x),'o','Color',drot);
set(gca,'XAxisLocation','origin','YAxisLocation','origin')
xlabel('x')
ylabel('y')
legend('f','Nullstelle');
if MatlabOn; print(h,'-dpng','PicNewton.png'); end


end



function [x iter]=MyNewton(f,df,x0,TOL,flag)
%
% x=MyNewton(f,df,x0,TOL,flag)
%

iter = 0;
x = x0;
while abs(f(x))>TOL & iter<10
    iter = iter+1;
    if abs(df(x))<eps
        fprintf("Error in MyNewton\n");
        break
    else
        x = x - f(x)/df(x);
        if flag
            fprintf("iter = %010d: x = %10.2e, res = %10.2e\n",iter,x,abs(f(x))); 
        end
    end
end


end
