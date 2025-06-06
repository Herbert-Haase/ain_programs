function Tatort_Arbeitsblatt()

clear all
close all

I = [500,24*60];

%% Daten 
T0 = 36;
a = 21;
alpha = -1.0e-02;

Messung=[[12*60+36, 26.8];[14*60+8,22.4]];
T = @(t,t0) (T0-a)*exp(alpha*(t-t0))+a;

%% Todezeitpunkt 
for i=1:2
    t0_val(i) = log((Messung(i,2)-a)/(T0-a))/(-alpha)+Messung(i,1); 

%% Umrechnung in Stunde und Minute

    hour=floor(t0_val(i)/60);
    minute = floor((t0_val(i)/60-hour)*60);

    fprintf("Der Todeszeitpunkt nach der ersten Messung ist um %02d:%02d Uhr\n",hour,minute);
end

%% Ergebnisgraphen zu den jewieligen Messungen
T1 = @(t) T(t,t0_val(1));
T2 = @(t) T(t,t0_val(2));

%% Fehlerfunktion
T = @(t,x) (T0-a) exp(alpha)*(t-x))+a;
dT = @(t,x) (T0-a) -alpha*(t0-a) exp(-alpha)*(t-x));
d2T = @(t,x) (T0-a) alpha*alpha*(t0-a) exp(-alpha)*(t-x));
% Todeszeitpunkt basierend auf beiden Messungen (aus E'(t0)=0)
% t0_val(3) = ...;

% hour=floor(t0_val(3)/60);
% minute = floor((t0_val(3)/60-hour)*60);
% fprintf("Der Todeszeitpunkt nach Optimierung ist um %02d:%02d Uhr\n",hour,minute);

% T3 = ... ;

%% Plots -------------------------------------------------------------------
%%
tt = linspace(I(1),I(2),1000);
TT1 = T1(tt);
TT2 = T2(tt);
%> TT3 = ...;

IndT1 = find(TT1>36);
TT1(IndT1)=36;
IndT2 = find(TT2>36);
TT2(IndT2)=36;
% IndT3 = ... 
% TT3(IndT3) = ... 

% Figure position fuer Octave
% figure(1,"position",[1 1642 580 400]); 
% Figure position fuer Matlab
h = figure(1);
h.Position = [1 1642 580 400];

hold on
grid on
plot(tt,TT1,'-','Color',[0,0,0.5]);
plot(tt,TT2,'-','Color',[0.5,0,0]);
plot(Messung(1,1),Messung(1,2),'o')
plot(Messung(2,1),Messung(2,2),'o')
xlabel('Zeit')
ylabel('Temperatur');
legend('T1','T2','Messung 1','Messung 2');
title('2 Messungen, 2 Graphen (T1, T2)')


print('Tatort.png','-dpng','-r300');
end


function x=MyNewton(f,df,x0,TOL,flag)
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
