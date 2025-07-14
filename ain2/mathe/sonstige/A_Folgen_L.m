clear all
close all

p = 0.01;  % Rate des Vergessens pro Tag
Sp = 3;    % Anzahl Seiten, die pro Tag gelernt werden

% implizite Darstellung
S(1)=Sp;   
it = 1;
while (it==1 | abs(S(it)-S(it-1))>0.01) & it<1000
%for i=2:100 % Anzahl (ganze) Tage
    it = it + 1;   % Schleifen zaehlen
    S(it) = S(it-1)*(1-p)+Sp;
end
fprintf("Nach %d Tagen hat der Student %.2f Seiten gelernt und  macht keine",it,S(end));
fprintf(" großen Fortschritte mehr\n");
fprintf("Theoretisch kann er maximal %.2f Seiten lernen.\n",Sp/p);

Sm = 20;
% S(Time)=20 nach Time aufloesen geht nur, wenn man S(Time) als
% explizite Folge gegeben hat (auf Papier, s. Alkohol-Beispiel
% aus der Vorlesung :)
Time = log(1-Sm*p/S(1))/log(1-p)-1;    

% Time (in Tagen) jetzt noch nach Tagen, Stunden und Minuten 
%aufteilen 0.5 Tage ist mittags um 12
Day = floor(Time);
Hour=floor((Time-floor(Time))*24);
Minute=floor(((Time-floor(Time))*24-Hour)*60);

fprintf("Der Student hat nach %d Tagen, %d Stunden und %d Minuten %d Seiten gelernt\n",...
    Day, Hour, Minute, Sm);

%%
plot(S,'ro');
xlabel('Tage')
ylabel('gelernte Seiten')
legend('Lernfortschritt','Location','SouthEast')
grid on
