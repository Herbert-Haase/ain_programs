function E_DiskreteAbleitung_L()
close all
clear all
MatlabOn=0;

P = load("Glocke.dat");
% P = load("Influenza.dat");
% P = load("GlockeR.dat");
% P = load("Covid.dat");
x = P(:,1);
u = P(:,2);
h = mean(diff(x));

% Daten glaetten falls nötig (sechster Schritt)
uorg = u;
% u = Glaettung(u,1.0e-01,10); 

% erste Ableitung (erster Schritt)
F = [1,0,-1]/2/h;         % Filter fuer gemittelter Differenzenquotient
d1u = DiffQuot(u,F,1)';  % probiere verschiedenen Filter aus

% Finde alle Extrema (dritter Schritt)
% Ind beinhaltet die Indizes bei denen ein Vorzeichenwechsel in d1u 
% stattfindet
% ungefähr zwischen diesen Werten liegt ein Extremum
Ind=find(d1u(1:end-1).*d1u(2:end)<0);
xE = (x(Ind)+x(Ind+1))/2;
uE = (u(Ind)+u(Ind+1))/2;

% falls noetig, sonst nicht
% d1u = Glaettung(d1u,1.0e-01,100); 
% zweite Ableitung (zweiter Schritt)
F = [-1,0,1]/2/h;         % Filter fuer gemittelter Differenzenquotient
d2u = DiffQuot(d1u,F,0);  % probiere verschiedenen Filter aus

% Finde Wendepunkte (vierter Schritt)
% wenn durch Rauschen mehr gefunden wurden, dann staerker gaetten
% oder gefundenen Werte mitteln
Ind=find(d2u(1:end-1).*d2u(2:end)<0);
xW = (x(Ind)+x(Ind+1))/2;
uW = (u(Ind)+u(Ind+1))/2;

% definiere eine Funktion, die die Daten gut beschreibt (fünfter Schritt)
% Vorschlag 1:
p = @(x) a*(x-b)^2+c
% Vorschlag 2:
% p = @(x) a*exp((x-b)^2/c)
% Vorschlag 3:
% p = @(x) a*sech(b*x-c)^2
% verwenden Sie die gefundenen Parameter a, b, c als Startwerte in 
% E_Regression_L_Matlab_L.m
xx = linspace(P(1,1),P(end,1),1000);
pp = p(xx);

%%
htwg_gruen=[0,155,145]/255;
drot = [200,0,0]/255;
ddrot = [100,0,0]/255;
dgruen = [0,150,0]/255;
dblau = [0,0,200]/255;
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
plot(x,uorg,'o','Color',dgruen);

% plot(x,u,'-','Color',ddrot);
% erste Ableitung
% plot(x,d1u,'o','Color',dgruen);
plot(xE,uE,'o','MarkerFaceColor',[0 0 0],'MarkerSize',10);
% zweite Ableitung
% plot(x,d2u,'o','Color',dblau);
plot(xW,uW,'o','MarkerFaceColor',[1 0 1],'MarkerSize',10);
% plot(xx,pp,'k-');
set(gca,'XAxisLocation','origin','YAxisLocation','origin')
xlabel('x')
ylabel('y')
legend('uorg');
if MatlabOn; print(h,'-dpng','PicDiskreteAbleitung.png'); end


uiwait(gcf)
end

%%

function du=DiffQuot(u,F,flag)

FL = length(F);
FW = floor((FL-1)/2);
N=length(u);
du = zeros(1,N);

switch flag
    case 1
        for i=1:N
            for j=1:FL
                % i=1 und j=1: i-2+j=-1+j=0
                ij = max(1,i-FW-1+j);
                ij = min(ij,N);
                du(i) = du(i) + u(ij)*F(j);
            end
        end
    otherwise
        for i=FW+1:N-FW
            for j=1:FL
                % i=1 und j=1: i-2+j=-1+j=0
                ij = max(1,i-FW-1+j);
                ij = min(ij,N);
                du(i) = du(i) + u(ij)*F(j);
            end
        end
end
end


function su = Glaettung(u,delta,LOOP)

su = u;
for l=1:LOOP
    du = DiffQuot(su,[1 -2 1],0)';
    su = su + delta*du;
end

end
