% Diskrete Ableitungen: Alle in einem gemeinsamen Plot

% Beispielwerte (können ersetzt werden)
X = linspace(0, 10, 100);
Y = sin(X); % Beispiel: Sinusfunktion

% 1. diskrete Ableitung (Vorwärtsdifferenzen)
dY1 = diff(Y) ./ diff(X);

% 2. diskrete Ableitung
dY2 = diff(dY1) ./ diff(X(1:end-1));

% 3. diskrete Ableitung
dY3 = diff(dY2) ./ diff(X(1:end-2));

% Anpassen der X-Werte für die Ableitungen
X1 = X(1:end-1);
X2 = X(1:end-2);
X3 = X(1:end-3);

% Gemeinsamer Plot
h = figure;
plot(X, Y, 'b', 'LineWidth', 2); hold on;
plot(X1, dY1, 'r', 'LineWidth', 2);
plot(X2, dY2, 'g', 'LineWidth', 2);
plot(X3, dY3, 'm', 'LineWidth', 2);
xlabel('X');
ylabel('Wert');
title('Originaldaten und diskrete Ableitungen');
legend('Y(X)', '1. Ableitung', '2. Ableitung', '3. Ableitung');
grid on;
uiwait(h);

% Optional: Ausgabe der Ableitungen
fprintf('1. Ableitung: Länge %d\n', length(dY1));
fprintf('2. Ableitung: Länge %d\n', length(dY2));
fprintf('3. Ableitung: Länge %d\n', length(dY3));
