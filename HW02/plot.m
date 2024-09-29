% plot_task.m

powers = 10:30;
times = [];

fid = fopen('task1.output', 'r');

for i = 1:length(powers)
    fgetl(fid);
    times(i) = str2double(fgetl(fid));
    fgetl(fid);
    fgetl(fid);
    fgetl(fid);
end

fclose(fid);

figure;
plot(powers, times, 'o');
xlabel('Size of the array (power)');
ylabel('Time (milliseconds)');
title('Scaling Analysis Plot');

saveas(gcf, 'task1.pdf');

