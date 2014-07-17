--用户任务定义

--走马灯定时器
timer4 = timer(100);

--输入滤波定时器
timer5 = timer(100);
timer6 = timer(100);

retval2 = false;

plctask2step = 5;

R_trig_3 = R_TRIG();
R_trig_4 = R_TRIG();

cnt2 = 0;
x2 = 0;

--任务主函数
function task2()
    --print(1);
    timer4:checkin(model107.inport.in0);
    timer5:checkin(model107.inport.in1);

    R_trig_3:checkin(timer4.Q);
    R_trig_4:checkin(timer5.Q);

    cnt2 = cnt2 + 1;
    if(R_trig_3.Q) then
        cnt2 = 0;
        x2 = os.clock();
        plctask2step = 1;
    end
    if(R_trig_4.Q) then
        print("s2,cnt2:",os.clock()-x2,cnt2);
        plctask2step = 5;
    end

    if(timer6.Q) then
        retval2 = false;


        if(plctask2step == 0) then

            plctask2step = 1;
            model107.outport.out0 = 1;
            model107.outport.out1 = 0;
            model107.outport.out2 = 0;
            model107.outport.out3 = 0;

        elseif(plctask2step == 1) then
            plctask2step = 2;
            model107.outport.out0 = 0;
            model107.outport.out1 = 1;
            model107.outport.out2 = 0;
            model107.outport.out3 = 0;

        elseif(plctask2step == 2) then
			plctask2step = 3;
			model107.outport.out0 = 0;
			model107.outport.out1 = 0;
			model107.outport.out2 = 1;
			model107.outport.out3 = 0;
        elseif(plctask2step == 3) then
            plctask2step = 0;
            model107.outport.out0 = 0;
            model107.outport.out1 = 0;
            model107.outport.out2 = 0;
            model107.outport.out3 = 1;
        end
    end


    timer6:checkin(retval2);
    if(not retval2) then
        retval2 = true;
    end
end

--注册任务到系统
taskregister("task2",0);

