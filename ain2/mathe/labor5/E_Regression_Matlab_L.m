function E_Regression_Matlab_L()

clear all
close all

P = load('GlockeR.dat');
c0 = [0 0 1]; % Startwerte

% Zielfunktion: Summe der Quadrate der Residuen
resfun = @(c) sum((P(:,2) - AnsatzFunktion(P(:,1),c)).^2);

% Finde die besten Parameter mit fminsearch
c = fminsearch(resfun, c0);

%%
I = [P(1,1), P(end,1)];
xx = linspace(I(1), I(2), 1000);

grid on
hold on
plot(xx, AnsatzFunktion(xx, c), 'k-');
plot(P(:,1), P(:,2), 'ro');
legend('Fit','Daten')
xlabel('x')
ylabel('y')
uiwait(gcf);
end

%%
function y = AnsatzFunktion(x, c)
    y = c(1) * exp(-(x - c(2)).^2 / c(3));
end
