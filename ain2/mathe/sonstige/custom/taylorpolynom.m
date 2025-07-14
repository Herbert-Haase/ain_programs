% Berechnung und Plot des Taylorpolynoms von f(x) = x^2 und Vergleich mit der Originalfunktion

% Funktion und Taylor-Entwicklungspunkt
f = @(x) x.^2;
x0 = 1; % Entwicklungspunkt

% Taylorpolynom 2. Ordnung für f(x) = x^2 um x0
% f(x) ≈ f(x0) + f'(x0)*(x-x0) + 0.5*f''(x0)*(x-x0)^2

f0 = f(x0);            % Funktionswert an x0
df0 = 2*x0;            % Erste Ableitung von f(x) = x^2 ist f'(x) = 2x
ddf0 = 2;              % Zweite Ableitung von f(x) = x^2 ist f''(x) = 2

taylor2 = @(x) f0 + df0 * (x - x0) + 0.5 * ddf0 * (x - x0).^2;

% Plotbereich
x_vals = linspace(x0-2, x0+2, 400);

figure;
plot(x_vals, f(x_vals), 'b', 'LineWidth', 2); hold on;
plot(x_vals, taylor2(x_vals), 'r--', 'LineWidth', 2);
xlabel('x');
ylabel('y');
title('f(x) = x^2 und Taylorpolynom 2. Ordnung um x_0=1');
legend('Originalfunktion', 'Taylorpolynom 2. Ordnung');
grid on;
uiwait(gcf);
