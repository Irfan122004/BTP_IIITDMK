% Data
Time = [2399, 17615, 32325, 47520, 57716, 67928, 77752, 87909, 96791, 104475, 112161, 120275, 126084, 132268, 138420, 144241];
actualrpm = [4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 8, 8, 10, 10, 10, 10];
desiredrpm = [4, 4, 4, 4, 6, 6, 6, 6, 8, 8, 8, 8, 10, 10, 10, 10];
 
beltspeed = [1, 1, 1, 1, 1.5072, 1.5072, 1.5072, 1.5072, 2.01, 2.01, 2.01, 2.01, 2.51, 2.51, 2.51, 2.51];
desired_beltspeed = [1, 1, 1, 1, 1.5072, 1.5072, 1.5072, 1.5072, 2.01, 2.01, 2.01, 2.01, 2.51, 2.51, 2.51, 2.51];

% Plotting
figure;
hold on;

% Plot actual vs time
plot(Time, beltspeed, 'b-', 'LineWidth', 3);

% Plot desired vs time
plot(Time, desired_beltspeed, 'r--', 'LineWidth', 3);

% Adding titles and labels with increased font size
title('Actual vs Desired Beltspeed', 'FontSize', 28);
xlabel('Time (in ms)', 'FontSize', 24);
ylabel('Beltspeed (m/min)', 'FontSize', 24);

% Adding legends
legend('Actual Beltspeed', 'Desired Beltspeed', 'FontSize', 14);

% Increasing axis font size
set(gca, 'FontSize', 12);

hold off;
