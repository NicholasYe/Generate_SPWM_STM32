%-----硬件设置-------------------------------------
timerCLK = 168000000;%timer时钟，160MHz/1分频
ARR      = 7999;
baseRate = timerCLK / (ARR + 1);%载波频率
%-----正弦波设置------------------------------------
F          = 25;%频率
T          = 1/F;%周期
ampScale   = 0.85;%调幅
N          = round(baseRate / F);%一周波分多少段
stepTime   = 1/F/N;%积分步进值
%-----计算------------------------------------------
CCR  = (1:1:N)';

for i=1:1:N
    area  = double(quad(@(x)sin(2*pi*F*x),(i-1)*stepTime,i*stepTime));
    CCR(i) = round((ampScale*area*ARR / stepTime + ARR) / 2);
end
