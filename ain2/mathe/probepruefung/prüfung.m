% Werte
x = [0 1 2 3 4 5 6 7 8 9 10];
u = [-6.7 -1.6 1.2 2.5 3.0 3.0 2.7 2.4 2.0 1.7 1.4];

% Erste diskrete Ableitung (Zentrale Differenzen)
du = zeros(size(u));
du(2:end-1) = (u(3:end) - u(1:end-2)) ./ (x(3:end) - x(1:end-2));
du(1) = (u(2) - u(1)) / (x(2) - x(1));              % Vorwärts-Differenz für erstes Element
du(end) = (u(end) - u(end-1)) / (x(end) - x(end-1)); % Rückwärts-Differenz für letztes Element

% Zweite diskrete Ableitung (Zentrale Differenzen)
ddu = zeros(size(u));
ddu(2:end-1) = (u(3:end) - 2*u(2:end-1) + u(1:end-2)) ./ ((x(2) - x(1))^2);
ddu(1) = 0;                    % Randwerte: Setze auf 0 oder berechne einseitig, falls gewünscht
ddu(end) = 0;

% Alle Kurven in einem Plot
figure;
plot(x, u, 'bo-', 'DisplayName', 'u(x)');
hold on;
plot(x, du, 'g*-', 'DisplayName', 'Erste Ableitung');
plot(x, ddu, 'rs-', 'DisplayName', 'Zweite Ableitung');
hold off;
grid on;
xlabel('x');
ylabel('Wert');
title('u(x), erste und zweite diskrete Ableitung');
legend('show');
uiwait(gcf);
