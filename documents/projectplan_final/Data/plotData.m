clc
clear all
close all

load('posxdatacruiseto.dat')
load('posydatacruiseto.dat')
load('posxdatagoto.dat')
load('posydatagoto.dat')
load('posxdata.dat')
load('posydata.dat')

x_gt = posxdatagoto;
y_gt = posydatagoto;
x_ct = posxdatacruiseto(50:end);
y_ct = posydatacruiseto(50:end);
x = posxdata(100:end);
y = posydata(100:end);



%goto TeamC
[pY,peakLoc]= findpeaks(y);
pX = x(peakLoc);
disp(['Deviation TeamC goTo : ',num2str(abs(0.4-mean(sqrt(pX.^2+pY.^2)))*100),' cm'])

%goto 

[pY_gt,peakLoc]= findpeaks(y_gt);
pX_gt = x_gt(peakLoc);
disp(['Deviation goTo : ',num2str(abs(0.4-mean(sqrt(pX_gt.^2+pY_gt.^2)))*100),' cm'])

%cruiseto

[pY_ct,peakLoc]= findpeaks(y_ct);
pX_ct = x_ct(peakLoc);
disp(['Deviation CruiseTo : ',num2str(abs(0.4-mean(sqrt(pX_ct.^2+pY_ct.^2)))*100),' cm'])

figure
hold on
rectangle('Position',[0.375,-0.025,0.05,0.05],...
        'LineWidth',2)
rectangle('Position',[-0.025,0.375,0.05,0.05],...
        'LineWidth',2)
rectangle('Position',[-0.025,-0.425,0.05,0.05],...
        'LineWidth',2)
rectangle('Position',[-0.425,-0.025,0.05,0.05],...
        'LineWidth',2)
    
plot(pX,pY,'rx');
plot(pX_gt,pY_gt,'gx');
plot(pX_ct,pY_ct,'bx');

grid on
axis equal

figure

subplot(3,1,1)
plot(sqrt(pX.^2+pY.^2),0,'rx')
xlim([0,0.6])

subplot(3,1,2)
plot(sqrt(pX_gt.^2+pY_gt.^2),0,'gx')
xlim([0,0.6])

subplot(3,1,3)
plot(sqrt(pX_ct.^2+pY_ct.^2),0,'bx')
xlim([0,0.6])

figure
hold on

plot(pX,pY,'rx');
plot(pX_gt,pY_gt,'gx');
plot(pX_ct,pY_ct,'bx');

plot(x,y,'r');
plot(x_gt,y_gt,'g');
plot(x_ct,y_ct,'b');

