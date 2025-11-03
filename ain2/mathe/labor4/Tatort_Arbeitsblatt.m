function Tatort()

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
% E = @(t0) ... ;
% Todeszeitpunkt basierend auf beiden Messungen (aus E'(t0)=0)
% t0_val(3) = ...;
% Fehlerfunktion
%% Fehlerfunktion
E = @(t0) (Messung(1,2) - T(Messung(1,1),t0))^2 + (Messung(2,2) - T(Messung(2,1),t0))^2;

% Numerische Ableitung für Newton-Verfahren
dE = @(t0) (E(t0+1e-6) - E(t0-1e-6))/(2e-6);

% Startwert: Durchschnitt der beiden Einzelschätzungen
t0_initial = (t0_val(1) + t0_val(2))/2;

% Newton-Verfahren zur Minimumfindung
t0_val(3) = MyNewton(dE, @(x)1, t0_initial, 1e-6, false);

% hour=floor(t0_val(3)/60);
% minute = floor((t0_val(3)/60-hour)*60);
% fprintf("Der Todeszeitpunkt nach Optimierung ist um %02d:%02d Uhr\n",hour,minute);

% T3 = ... ;

%% Plots -------------------------------------------------------------------
%%
tt = linspace(I(1),I(2),1000);
TT1 = T1(tt);
TT2 = T2(tt);
% Optimale Temperaturkurve definieren
T3 = @(t) T(t, t0_val(3));

% Werte für den Plot berechnen
TT3 = T3(tt);
IndT3 = find(TT3 > 36);
TT3(IndT3) = 36;

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
% h.Position = [1 1642 580 400];
set(gcf, 'Position', [1, 1642, 580, 400]);


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


% Position 1 (links)
subplot(1,3,1)
hold on
grid on
plot(tt, TT1, '-', 'Color', [0,0,0.5]);  % Kurve erste Messung
plot(tt, TT2, '-', 'Color', [0.5,0,0]);  % Kurve zweite Messung
plot(Messung(1,1), Messung(1,2), 'o');   % Messpunkt 1
plot(Messung(2,1), Messung(2,2), 'o');   % Messpunkt 2
xlabel('Zeit [Minuten]');
ylabel('Temperatur [°C]');
legend('erste Messung', 'zweite Messung', 'Messung 1', 'Messung 2');
title('Lösungen der Einzelmessungen');

% Position 2 (in der Mitte)
subplot(1,3,2)
hold on
grid on
plot(tt, TT3, '-', 'Color', [0,0,0.8]);  % Optimale Kurve
plot(Messung(1,1), Messung(1,2), 'o');   % Messpunkt 1
plot(Messung(2,1), Messung(2,2), 'o');   % Messpunkt 2
xlabel('Zeit [Minuten]');
ylabel('Temperatur [°C]');
legend('optimale Lösung', 'Messung 1', 'Messung 2');
title('optimale Lösung');

% Position 3 (rechts)
subplot(1,3,3)
% Bereich von t0-Werten für die Fehlerfunktion
t0_range = linspace(min(t0_val(1:2))-50, max(t0_val(1:2))+50, 200);
error_values = zeros(size(t0_range));
for i = 1:length(t0_range)
    error_values(i) = E(t0_range(i));
end
hold on
grid on
plot(t0_range, error_values, '-', 'Color', [0,0,0.8]);  % Fehlerkurve
plot(t0_val(3), E(t0_val(3)), 'ro');  % Markierung des Minimums
xlabel('Zeit [Minuten]');
ylabel('Fehler E(t0)');
title('Fehlerkurve');

uiwait(h);


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
