% Newton-Verfahren, um den Nullpunkt der Funktion f(x) = x^2 zu finden
% und anschließendes Plotten der Funktion und des Nullpunkts

% Definition der Funktion und ihrer Ableitung
f = @(x) x.^2;
df = @(x) 2*x;

% Startwert (wähle beliebig, z.B. x0 = 2)
x0 = 2;

% Iterationsschritte für das Newton-Verfahren
max_iter = 10;
tol = 1e-8;

x = x0;
for i = 1:max_iter
    x_new = x - f(x)/df(x);
    if abs(x_new - x) < tol
        break;
    end
    x = x_new;
end

nullpunkt = x;

% Plot der Funktion und des Nullpunkts
x_vals = linspace(-2, 2, 400);
y_vals = f(x_vals);

figure;
plot(x_vals, y_vals, 'b-', 'LineWidth', 2); hold on;
plot(nullpunkt, f(nullpunkt), 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
uiwait(gcf);
xlabel('x');
ylabel('f(x)');
title('Newton-Verfahren für f(x) = x^2 und Nullpunkt');
grid on
legend('f(x) = x^2', 'Nullpunkt');

fprintf('Der berechnete Nullpunkt ist bei x = %.10f\n', nullpunkt);
