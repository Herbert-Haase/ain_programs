clear all
close all

syms t t0
I = [500,24*60];

T0 = 36;
a = 21;
alpha = -1.0e-02;

T(t) = (T0-a)*exp(alpha*(t-t0))+a;

Messung=[[12*60+36, 26.8];[14*60+8,22.4]];

for mn=1:2
    t0_val(mn) = solve(T(Messung(mn,1))==Messung(mn,2),t0);
    hour=floor(t0_val(mn)/60);
    minute = floor((t0_val(mn)/60-hour)*60);
    fprintf("Der Todeszeitpunkt nach der ersten Messung ist um %02d:%02d Uhr\n",hour,minute);
end

T1(t) = subs(T(t),t0,t0_val(1));
T2(t) = subs(T(t),t0,t0_val(2));

%%
tt = linspace(I(1),I(2),1000);
TT1 = T1(tt);
TT2 = T2(tt);

IndT1 = find(TT1>36);
TT1(IndT1)=36;
IndT2 = find(TT2>36);
TT2(IndT2)=36;

h=figure(1);
h.Position = [1361 542 560 420];
hold on
plot(tt,TT1,'-','Color',[0,0,0.5]);
plot(tt,TT2,'-','Color',[0.5,0,0]);
grid on
hold on
plot(Messung(:,1),Messung(:,2),'mo')


% dT(t) = diff(T(t),t);
% dT(t)-alpha*(T(t)-a);
