clear all
close all

MatlabOn = 0;

% Zeitspanne: 19:10-20:20, in Sekunden
Tmax = 70*60;          % 70 Minuten
% Parameter (a,b angegeben; c berechnet)
a = 5.0e-02;           
b = 4.0e-07;
c = 40*60;

time=0:1:Tmax;                  % in Sekunden
Besucher = @(t) a*exp(-b.*(t-c).^2);   % ankommende Besucher zur Zeit t
Kassen   = @(b) round(log(b+1));         % Kassenoeffnungen zum Besucher b

%%
AnkommendeBesucher = Besucher(time);
AnwesendeBesucher  = floor(cumsum(AnkommendeBesucher));

fprintf('anwesende Personen nach %d Minuten: %d\n\n',Tmax/60,AnwesendeBesucher(end));

%%
KasseJeBesucherInt = Kassen(AnwesendeBesucher);
KasseJeBesucherCount = KasseJeBesucherInt(2:end)-KasseJeBesucherInt(1:end-1);
IndKassensprung = find(KasseJeBesucherCount~=0);       % Spruenge finden

%%
% Zeiten der Kassenoeffnungen
% Startzeitpunkt: 19:20 das sind 69600 Sekunden nach 0:00 Uhr
sectotal = time(IndKassensprung)+69600;
sec = mod(sectotal,60);
mintotal = (sectotal-sec)/60;
min = mod(mintotal,60);
htotal = (mintotal-min)/60;

for l=1:length(IndKassensprung)
    fprintf('Kasse %d oeffnet um %02d:%02d:%02d Uhr (%.2f bzw %.2f sec)\n',l,htotal(l),min(l),sec(l),sectotal(l),sectotal(l)-69600);
end

%%
htwg_gruen=[0.0,0.60784,0.56863]; 

if MatlabOn
   hf=figure(1);
   hf.Position = [0 0 1920 1080];
else
   figure(1,"position",[0 0 1920 1080]);
end
     
subplot(2,3,2)
plot(AnwesendeBesucher,KasseJeBesucherInt,'.','Color',htwg_gruen);
grid on
xlabel('anwesende Personen')
ylabel('offene Kassen')
title('Anzahl Kassen je Besucher (B)')

% -------------------------------------------------------------------
subplot(2,3,5)
plot(time,AnwesendeBesucher,'-','LineWidth',2,'Color',htwg_gruen)
grid on
xlabel('Zeit')
ylabel('anwesende Personen')
title('anwesende Personen je Zeit (E)')

% -------------------------------------------------------------------
subplot(2,3,1)
plot(AnwesendeBesucher,time,'-','LineWidth',2,'Color',htwg_gruen)
grid on
xlabel('anwesende Personen')
ylabel('Zeit')
title('Zeit je anwesende Personen (A)')

% -------------------------------------------------------------------
subplot(2,3,4)
plot(time,KasseJeBesucherInt,'.','Color',htwg_gruen)
grid on
ylabel('offene Kassen')
xlabel('Zeit')
title('Kassenoeffnung je Zeit (D)')

% -------------------------------------------------------------------
subplot(2,3,3)
plot(time,AnkommendeBesucher,'-','LineWidth',2,'Color',htwg_gruen)
grid on
ylabel('ankommende Personen')
xlabel('Zeit')
title('ankommende Personen je Zeit (C)')

print(hf,'-dpng','B_Kinobesucher.png');

