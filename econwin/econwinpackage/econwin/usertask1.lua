--用户任务定义


--走马灯定时器
timer1 = timer(a);

--输入滤波定时器
timer2 = timer(100);
timer3 = timer(100);

timer4 = timer(100);
timer5 = timer(100);
timer6 = timer(100);

retval = false;

input6 = false;
olda = 0;

--model207 = new207(1);
model107 = new107(2);

plctask1step = 5;

--上升沿和下降沿扑捉
R_trig_1 = R_TRIG();
R_trig_2 = R_TRIG();
R_trig_3 = R_TRIG();
R_trig_4 = R_TRIG();
cnt = 0;
x = 0;



--任务主函数
function task1()
    --print(1);
    --timer2:checkin(model107.inport.in0);
    --timer3:checkin(model107.inport.in1);
    --timer4:checkin(model107.inport.in2);
    --timer5:checkin(model107.inport.in3);

    timer2:checkin(button1);
    timer3:checkin(button2);
    timer4:checkin(button3);
    timer5:checkin(button4);

	R_trig_1:checkin(timer2.Q);
    R_trig_2:checkin(timer3.Q);
    R_trig_3:checkin(timer4.Q);
    R_trig_4:checkin(timer5.Q);

    cnt = cnt + 1;
    if(R_trig_1.Q) then
        cnt = 0;
        x = os.clock();
        plctask1step = 0;
    end
    if(R_trig_2.Q) then
        print("s,cnt:",os.clock()-x,cnt);
        plctask1step = 5;
    end

    if(R_trig_3.Q) then
		if(a< 2000) then
			a= a+ 10;
			timer1:setms(a);
			olda = a;
		end
    end
    if(R_trig_4.Q) then
		if((a -10)> 0) then
			a= a- 10;
			timer1:setms(a);
			olda = a;
		end
    end

	if(ola ~= a) then
		olda = a;
		timer1:setms(a);

	end

    if(timer1.Q) then
        retval = false;


        if(plctask1step == 0) then

            plctask1step = 1;
            model107.outport.out0 = 1;
            model107.outport.out1 = 0;
            model107.outport.out2 = 0;
            model107.outport.out3 = 0;

        elseif(plctask1step == 1) then
            plctask1step = 2;
            model107.outport.out0 = 0;
            model107.outport.out1 = 1;
            model107.outport.out2 = 0;
            model107.outport.out3 = 0;

        elseif(plctask1step == 2) then
			plctask1step = 3;
			model107.outport.out0 = 0;
			model107.outport.out1 = 0;
			model107.outport.out2 = 1;
			model107.outport.out3 = 0;
        elseif(plctask1step == 3) then
            plctask1step = 0;
            model107.outport.out0 = 0;
            model107.outport.out1 = 0;
            model107.outport.out2 = 0;
            model107.outport.out3 = 1;
        end
    end
	if(timer6.Q) then
		input6 = false;
		--print(button1,button2,button3,button4);
	end

	if(model107.outport.out0 == true) then
		zhishideng1 = 1;
	else
		zhishideng1 = 0;
	end

	if(model107.outport.out1 == true) then
		zhishideng2 = 1;
	else
		zhishideng2 = 0;
	end

	if(model107.outport.out2 == true) then
		zhishideng3 = 1;
	else
		zhishideng3 = 0;
	end

	if(model107.outport.out3 == true) then
		zhishideng4 = 1;
	else
		zhishideng4 = 0;
	end


    timer1:checkin(retval);
    if(not retval) then
        retval = true;
    end

    timer6:checkin(input6);
    if(not input6) then
        input6 = true;
    end

end

--注册任务到系统
taskregister("task1",0);

