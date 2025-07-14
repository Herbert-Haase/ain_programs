% Beispielprogramm: Diskrete Ableitung (1., 2. und 3.) von X- und Y-Punkten berechnen und plotten

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

% Plotten
h = figure;
subplot(4,1,1);
plot(X, Y, 'b');
title('Originaldaten Y(X)');
xlabel('X'); ylabel('Y');

subplot(4,1,2);
plot(X1, dY1, 'r');
title('1. diskrete Ableitung');
xlabel('X'); ylabel('dY/dX');

subplot(4,1,3);
plot(X2, dY2, 'g');
title('2. diskrete Ableitung');
xlabel('X'); ylabel('d^2Y/dX^2');

subplot(4,1,4);
plot(X3, dY3, 'm');
title('3. diskrete Ableitung');
xlabel('X'); ylabel('d^3Y/dX^3');
uiwait(h);

% sgtitle('Diskrete Ableitungen der Y(X)-Daten');

% Optional: Ausgabe der Ableitungen
fprintf('1. Ableitung: Länge %d\n', length(dY1));
fprintf('2. Ableitung: Länge %d\n', length(dY2));
fprintf('3. Ableitung: Länge %d\n', length(dY3));
