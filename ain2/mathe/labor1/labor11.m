x = 0:0.01:40;
n = 0;
w = -1;
i = 0;
n_values = []; % Initialize an empty array to store n values

while w ~= n && i ~= 10
    w = n;
    n = n + 4;
    n = n * 0.98;
    i = i + 1;
  display(n)
    n_values(end+1) = n; % Append the new n value to the array
end

% Now plot how n changed over the iterations
plot(1:length(n_values), n_values, '-o', 'LineWidth', 2)
