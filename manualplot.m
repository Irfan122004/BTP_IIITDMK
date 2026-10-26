% Load the Excel file
filename = 'C:/B.tech/Endsem review results/temperature data.xlsx';

% Initialize figure
figure;
hold on;

% Set color order for clarity
colors = lines(5);  % Default MATLAB line colors

% Initialize results table
results = table('Size', [5, 4], ...
    'VariableTypes', {'string', 'double', 'double', 'double'}, ...
    'VariableNames', {'Sheet', 'RiseTime', 'SettlingTime_2', 'SettlingTime_5'});

% Loop through 5 sheets (40, 45, ..., 60)
sheet_index = 1; % for storing results properly
for i = 40:5:60
    % Read data
    sheetName = [num2str(i)  'degrees'];
    data = readtable(filename, 'Sheet', sheetName);
    
    time = data{:,1};  % Time column
    temp = data{:,2};  % Temperature column

    % Optional: Interpolate to smooth the curve (1000 points)
    time_smooth = linspace(min(time), max(time), 1000);
    temp_smooth = interp1(time, temp, time_smooth, 'pchip');

    % Plot with thicker lines
    plot(time_smooth, temp_smooth, 'LineWidth', 2, 'DisplayName', sheetName, ...
         'Color', colors(sheet_index, :));

    % Calculate steady-state
    steady_state = temp(end);
    
    % Rise time: time from 10% to 90% of steady-state
    y10 = 0.1 * steady_state;
    y90 = 0.9 * steady_state;
    idx10 = find(temp >= y10, 1);
    idx90 = find(temp >= y90, 1);
    rise_time = time(idx90) - time(idx10);

    % Settling time (within 2% and 5%)
    upper2 = 1.02 * steady_state;
    lower2 = 0.98 * steady_state;
    upper5 = 1.05 * steady_state;
    lower5 = 0.95 * steady_state;

    % Reverse loop to find last time it exits bounds
    st2 = NaN;
    st5 = NaN;
    for j = length(temp):-1:1
        if temp(j) < lower2 || temp(j) > upper2
            if j+1 <= length(time)
                st2 = time(j+1);
            end
            break;
        end
    end
    for j = length(temp):-1:1
        if temp(j) < lower5 || temp(j) > upper5
            if j+1 <= length(time)
                st5 = time(j+1);
            end
            break;
        end
    end

    % Save results
    results.Sheet(sheet_index) = sheetName;
    results.RiseTime(sheet_index) = rise_time;
    results.SettlingTime_2(sheet_index) = st2;
    results.SettlingTime_5(sheet_index) = st5;

    sheet_index = sheet_index + 1;
end

% Finalize plot
xlabel('Time (s)', 'FontWeight', 'bold');
ylabel('Temperature (°C)', 'FontWeight', 'bold');
title('Temperature Response Comparison', 'FontSize', 14, 'FontWeight', 'bold');
legend('Location', 'best');
grid on;
box on;

% Display results table
disp(results);
