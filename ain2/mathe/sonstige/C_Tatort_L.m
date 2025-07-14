clear all
close all
MatlabOn = 0;    % fuer Octave auf 0 setzen

I = [500,24*60];

%% Daten 
T0 = 36;           % Starttemperatur
a = 21;            % Ausssentemperatur
alpha = -1.0e-02;  % Waermeleitkoeffizient (gegeben)

Messung=[[12*60+36, 26.8];[14*60+8,22.4]];  % Messzeiten und -werte
T = @(t,t0) (T0-a)*exp(alpha*(t-t0))+a;     % Loesung des Newtonschen
                                            % Abkuehlungsgesetzes

%% Todezeitpunkt 
for i=1:2
    t0_val(i) = log((Messung(i,2)-a)/(T0-a))/(-alpha)+Messung(i,1); 

%% Umrechnung in Stunde und Minute

    hour=floor(t0_val(i)/60);
    minute = floor((t0_val(i)/60-hour)*60);

    fprintf("Der Todeszeitpunkt nach der ersten Messung ist um %02d:%02d Uhr\n",hour,minute);
end

%% Ergebnisgraphen zu den jewieligen Messungen
T1 = @(t) (T0-a)*exp(alpha*(t-t0_val(1)))+a;
T2 = @(t) (T0-a)*exp(alpha*(t-t0_val(2)))+a;

%% Fehlerfunktion
E = @(t0) (T(Messung(1,1),t0)-Messung(1,2)).^2+(T(Messung(2,1),t0)-Messung(2,2)).^2;
% Todeszeitpunkt basierend auf beiden Messungen (aus E'(t0)=0)
t0_val(3) = 100*log((29*exp(47/5) + 7*exp(212/25))/(75*exp(46/25) + 75)); 

hour=floor(t0_val(3)/60);
minute = floor((t0_val(3)/60-hour)*60);
fprintf("Der Todeszeitpunkt nach Optimierung ist um %02d:%02d Uhr\n",hour,minute);

T3 = @(t) T(t,t0_val(3));

%% Plots -------------------------------------------------------------------
%%
tt = linspace(I(1),I(2),1000);
TT1 = T1(tt);
TT2 = T2(tt);
TT3 = T3(tt);

IndT1 = find(TT1>36);
TT1(IndT1)=36;
IndT2 = find(TT2>36);
TT2(IndT2)=36;
IndT3 = find(TT3>36);
TT3(IndT3)=36;

if MatlabOn
    % Figure position fuer Matlab
    h = figure(1);
    h.Position = [49 639 1636 420];
else
    % Figure position fuer Octave
    figure(1,"position",[49 639 1636 420]);
end

subplot(1,3,1)
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

subplot(1,3,2)
hold on
grid on
plot(tt,TT3,'-','Color',[0,0.5,0.]);
plot(Messung(1,1),Messung(1,2),'o')
plot(Messung(2,1),Messung(2,2),'o')
xlabel('Zeit')
ylabel('Temperatur');
legend('T3','Messung 1','Messung 2');
title('optimaler Graph (T3)')

subplot(1,3,3)
J=[600,700];
tt0 = linspace(J(1),J(2),1000);
EE = E(tt0);
hold on
grid on
plot(tt0,EE);
for l=1:2
    plot(t0_val(l),E(t0_val(l)),'mo');
end
xlabel('je vermuteter Todeszeitpunkt t_0')
ylabel('Fehler');
legend('E','Messung 1','Messung 2')
title('Quadratfehler')

print('Tatort.png','-dpng','-r300');
